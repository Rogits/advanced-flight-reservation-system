void insertPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p);
void updatePassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p1, Passenger p2);
void searchPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p);
PassengerTreeNodePtr findPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p);

int equalPassenger(Passenger p1, Passenger p2);
int lessThanPassenger(Passenger p1, Passenger p2);
int moreThanPassenger(Passenger p1, Passenger p2);

void populatePassengersTree(PassengerTreeNodePtr *sPtr);
void rePopulatePassengersTree(PassengerTreeNodePtr *sPtr);

int promptPassengerInstructions();

void processPassengersTree(PassengerTreeNodePtr rootPtr, 
	PassengerQueueNodePtr headPtr,
	PassengerQueueNodePtr tailPtr); 

void processPassengersTree(PassengerTreeNodePtr rootPtr, 
	PassengerQueueNodePtr headPtr, PassengerQueueNodePtr tailPtr)
{
	FILE *fPtr;
	PassengerTreeNodePtr tempPtr = NULL;
	Passenger p = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	int choice;
	int input;
	
	if((fPtr = fopen("tickets.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("tickets.dat", "wb")) == NULL)
		{
			printf("\nFile could not be opened.\n\n");
		}
		else
		{
			printf("\nNew file created.\n");
		}
	}
	else
	{
		populatePassengersTree(&rootPtr);
		
		while((choice = promptPassengerInstructions()) != 0)
		{
			switch(choice)
			{
				case 1:
					textTicketsFile(fPtr);
					break;
				case 2:	
					// move to waiting queue if flight full or not existing
					p = newTicketRecord(fPtr);
					if(p.flightNum > 0 && p.seatNum > 0)
					{
						if(p.ticketNum > 0)
						{						
							insertPassengerTreeNode(&rootPtr, p);
						}
					}
					else
					{
						if(countNumberOfPassengerQueueNodes(headPtr) <= 
						getTotalNumberOfSeats(
						fetchPlane(fetchFlight(p.flightNum).planeId)))
						{
							insertPassengerQueueNode(&headPtr, &tailPtr, p);
						}
						else
						{
							printf("\n\nSorry, Flight is full try again later.\n");
						}
					}
					break;
				case 3:
					// move to waiting queue if flight full or not existing					
					p = updateTicketRecord(fPtr);
					if(p.seatNum > 0 && p.flightNum > 0)
					{
						if(p.ticketNum > 0)
						{
							if((tempPtr = findPassengerTreeNode(&rootPtr, p)) != NULL)
							{						
								updatePassengerTreeNode(&rootPtr, tempPtr->data, p);
							}						
						}
					}
					else
					{
						if(countNumberOfPassengerQueueNodes(headPtr) <= 
						getTotalNumberOfSeats(
						fetchPlane(fetchFlight(p.flightNum).planeId)))
						{
							insertPassengerQueueNode(&headPtr, &tailPtr, p);
						}
						else
						{
							printf("\n\nSorry, Flight is full try again later.\n");
						}
					}
					break;
				case 4:
					// insert one passenger on waiting after delete				
					p = deleteTicketRecord(fPtr);					
					if(p.ticketNum > 0)
					{						
						if(!isPassengerQueueNodeEmpty(headPtr))
						{
							p = headPtr->data;
							deletePassengerQueueNode(&headPtr, &tailPtr);
							// add passenger from queue
							p = newTicketRecord(fPtr);
							if(p.flightNum > 0 && p.seatNum > 0)
							{
								if(p.ticketNum > 0)
								{						
									insertPassengerTreeNode(&rootPtr, p);
								}
							}
							printf(
							"\n\nPassenger with ID %d was added from queue.\n",
							p.customerId);
						}
						rePopulatePassengersTree(&rootPtr);
					}							
					break;
				case 5:
					printf("\nEnter Passenger ID to be searched: ");
					scanf("\n%d", &input);
					p.ticketNum = input;
					searchPassengerTreeNode(&rootPtr, p);
					break;
				case 6:
					printAllTickets(fPtr);
					break;
				default:
					printf("Incorrect choice.\n");
					break;				
			}
		}
		
		fclose(fPtr);
	}
}

void insertPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p)
{
	if(*treePtr == NULL)
	{
		*treePtr = malloc(sizeof(PassengerTreeNode));
		if(*treePtr != NULL)
		{
			(*treePtr)->data = p;
			(*treePtr)->leftPassengerTreeNodePtr = NULL;
			(*treePtr)->rightPassengerTreeNodePtr = NULL;
		}
		else
		{
			printf(
			"\nPassenger with ID %d not inserted. No memory available.\n",
				p.ticketNum);
		}		
	}
	else
	{
		if(lessThanPassenger(p, (*treePtr)->data) == 1)
		{
			insertPassengerTreeNode(&((*treePtr)->leftPassengerTreeNodePtr), p);
		}
		else if(moreThanPassenger(p, (*treePtr)->data) == 1)
		{
			insertPassengerTreeNode(&((*treePtr)->rightPassengerTreeNodePtr), p);
		}		
	}
}

void updatePassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p1,
 Passenger p2)
{
	PassengerTreeNodePtr tempLeftPassengerTreeNodePtr;
	PassengerTreeNodePtr tempRightPassengerTreeNodePtr;
	
	if(*treePtr != NULL)
	{		
		if(equalPassenger((*treePtr)->data, p1) == 1)
		{			
			tempLeftPassengerTreeNodePtr = (*treePtr)->leftPassengerTreeNodePtr;
			tempRightPassengerTreeNodePtr = (*treePtr)->rightPassengerTreeNodePtr;
			
			if(tempLeftPassengerTreeNodePtr == NULL && 
				tempRightPassengerTreeNodePtr == NULL)
			{
				(*treePtr)->data = p2;
				printf("\nUpdate successful.\n");
				return;
			}
			else if(lessThanPassenger(p1, tempLeftPassengerTreeNodePtr->data) == 1 &&
					tempRightPassengerTreeNodePtr == NULL)
			{
				(*treePtr)->data = p2;		
				printf("\nUpdate successful.\n");
				return;
			}
			else if(tempLeftPassengerTreeNodePtr == NULL && 
					moreThanPassenger(p1, tempRightPassengerTreeNodePtr->data) == 1)
			{
				(*treePtr)->data = p2;
				printf("\nUpdate successful.\n");
				return;
			}		
			else if(lessThanPassenger(p1, tempLeftPassengerTreeNodePtr->data) == 1 && 
					moreThanPassenger(p1, tempRightPassengerTreeNodePtr->data) == 1 ) 
			{
				(*treePtr)->data = p2;	
				printf("\nUpdate successful.\n");
				return;
			}
			else
			{
				printf("\nUpdate unsuccessful.\n");
				return;
			}
		}			
		
		if(lessThanPassenger(p1, (*treePtr)->data) == 1)
		{
			updatePassengerTreeNode(&((*treePtr)->leftPassengerTreeNodePtr), p1, p2);
		}
		else if(moreThanPassenger(p1, (*treePtr)->data) == 1)
		{
			updatePassengerTreeNode(&((*treePtr)->rightPassengerTreeNodePtr), p1, p2);
		}
		else
		{
			printf("\nUpdate unsuccessful.\n");
			return;
		}		
	}
	else
	{
		printf("\nUpdate unsuccessful.\n");
		return;
	}
}

void searchPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p)
{	
	if(*treePtr != NULL)
	{		
		if(equalPassenger((*treePtr)->data, p) == 1)
		{
			printf("\nPassenger with ID %d was found.\n", p.ticketNum);
			return;
		}			
		
		if(lessThanPassenger(p, (*treePtr)->data) == 1)
		{
			searchPassengerTreeNode(&((*treePtr)->leftPassengerTreeNodePtr), p);
		}
		else if(moreThanPassenger(p, (*treePtr)->data) == 1)
		{
			searchPassengerTreeNode(&((*treePtr)->rightPassengerTreeNodePtr), p);
		}
	}
	else
	{
		printf("\nPassenger with ID %d was not found.\n", p.ticketNum);
		return;
	}
}

PassengerTreeNodePtr findPassengerTreeNode(PassengerTreeNodePtr *treePtr, Passenger p)
{
	if(*treePtr != NULL)
	{		
		if(equalPassenger((*treePtr)->data, p) == 1)
		{
			return *treePtr;
		}		
		else if(lessThanPassenger(p, (*treePtr)->data) == 1)
		{
			findPassengerTreeNode(&((*treePtr)->leftPassengerTreeNodePtr), p);
		}
		else if(moreThanPassenger(p, (*treePtr)->data) == 1)
		{
			findPassengerTreeNode(&((*treePtr)->rightPassengerTreeNodePtr), p);
		}
	}
	else
	{
		return NULL;
	}
}

int equalPassenger(Passenger p1, Passenger p2)
{
	return p1.ticketNum == p2.ticketNum ? 1:0;
}

int moreThanPassenger(Passenger p1, Passenger p2)
{
	return p1.ticketNum > p2.ticketNum ? 1:0;
}

int lessThanPassenger(Passenger p1, Passenger p2)
{
	return p1.ticketNum < p2.ticketNum ? 1:0;
}

void populatePassengersTree(PassengerTreeNodePtr *sPtr)
{
	FILE *fPtr;
	Passenger p;
	if((fPtr = fopen("tickets.dat", "rb")) == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{				
		rewind(fPtr);
		while(!feof(fPtr))
		{
			p = readFromTicketsFile(fPtr);
			if(p.ticketNum > 0)
			{		
				insertPassengerTreeNode(sPtr, p);
			}			
		}
		fclose(fPtr);
	}
}

void rePopulatePassengersTree(PassengerTreeNodePtr *sPtr)
{
	FILE *fPtr;
	Passenger p;
	PassengerTreeNodePtr tempPtr;

	if((fPtr = fopen("tickets.dat", "rb")) == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{		
		rewind(fPtr);
		while(!feof(fPtr))
		{
			p = readFromTicketsFile(fPtr);
			if(p.ticketNum > 0)
			{		
				if((tempPtr = findPassengerTreeNode(sPtr, p)) == NULL)
				{
					insertPassengerTreeNode(sPtr, p);
				}
				else
				{
					updatePassengerTreeNode(sPtr, tempPtr->data, p);
				}
			}			
		}
		fclose(fPtr);
	}
}

int promptPassengerInstructions()
{
	int option;
	printf("\n\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an option below to proceed.", 
	"1 - Create a text file for printing all passenger records.",
	"2 - Create and save a new passenger record.",
	"3 - Update an existing passenger record.",
	"4 - Delete an existing passenger record.", 
	"5 - Search an existing passenger record.",
	"6 - View all passenger records.", 
	"0 - Exit.",
	"Enter option: ");
	scanf("%d", &option);
	
	return option;	
}

