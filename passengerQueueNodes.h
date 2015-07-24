void insertPassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p);
void updatePassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p1, Passenger p2);
void deletePassengerQueueNode(PassengerQueueNodePtr *headPtr,
	PassengerQueueNodePtr *tailPtr);
void searchPassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p);
void printAllPassengerQueueNodes(PassengerQueueNodePtr *headPtr);	
	
int isPassengerQueueNodeEmpty(PassengerQueueNodePtr headPtr);

int equalPassengers(Passenger p1, Passenger p2);

PassengerQueueNodePtr findPassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p);

void swapPassengerQueueNodes(PassengerQueueNodePtr headPtr, 
	PassengerQueueNodePtr newHeadPtr);
	
int promptWaitingPassengersInstructions();
/*void processWaitingPassengers(PassengerQueueNodePtr rootPassengerQueueNodePtr);*/

int countNumberOfPassengerQueueNodes(PassengerQueueNodePtr currentPtr);
/**
void processWaitingPassengers(PassengerQueueNodePtr rootPassengerQueueNodePtr)
{
	PassengerQueueNodePtr headPtr = NULL;
	PassengerQueueNodePtr tailPtr = NULL;
	Passenger p = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	int choice;
	int input;
	
	while((choice = promptWaitingPassengersInstructions()) != 0)
	{
		switch(choice)
		{		
			case 1:
				// insert new passenger	
				if(isPassengerQueueNodeEmpty(headPtr))
				{
					printf("\nNo passengers waiting.\n");
				}
				else
				{
					printf("\nInsertion not currently supported.\n");
				}
				break;
			case 2:
				// update passenger
				if(isPassengerQueueNodeEmpty(headPtr))
				{
					printf("\nNo passengers waiting.\n");
				}
				else
				{
					printf("\nUpdate not currently supported.\n");
				}
				break;
			case 3:
				// delete passenger
				if(isPassengerQueueNodeEmpty(headPtr))
				{
					printf("\nNo passengers waiting.\n");
				}
				else
				{
					printf("\nDelete not currently supported.\n");
				}
				break;
			case 4:
				if(isPassengerQueueNodeEmpty(headPtr))
				{
					printf("\nNo passengers waiting.\n");
				}
				else
				{
					printf("\nEnter Passenger ID to be searched: ");
					scanf("\n%d", &input);
					p.ticketNum = input;
					searchPassengerQueueNode(&headPtr, &tailPtr, p);
				}
				break;
			case 5:
				// print all passengers
				printAllPassengerQueueNodes(&headPtr);
				break;				
			default:
				printf("\nInvalid choice.\n\n");
				break;				
		}		
	}	
}
**/

int promptWaitingPassengersInstructions()
{
	int input;
	printf("\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s", 
	"Please choose an option below to proceed.",
	"1 - To insert a passenger to the waiting list.",
	"2 - To update a passenger in the waiting list.",
	"3 - To delete a passenger in the waiting list.",
	"4 - To search a passenger in the waiting list.",
	"5 - To view all passenger in the waiting list.",
	"0 - Exit.",
	"Enter your choice: ");
	scanf("%d", &input);
	
	return input;
}

int equalPassengers(Passenger p1, Passenger p2)
{
	return p1.ticketNum == p2.ticketNum ? 1:0;
}

void insertPassengerQueueNode(PassengerQueueNodePtr *headPtr,
 PassengerQueueNodePtr *tailPtr, Passenger p)
{
	PassengerQueueNodePtr newPtr;
	
	newPtr = malloc(sizeof(PassengerQueueNode));
	
	if(newPtr != NULL)
	{
		newPtr->data = p;
		newPtr->nextPtr = NULL;
		
		if(isPassengerQueueNodeEmpty(*headPtr))
		{
			*headPtr = newPtr;
		}
		else
		{
			(*tailPtr)->nextPtr = newPtr;
		}
		*tailPtr = newPtr;
	}
	else
	{
		printf("Passenger with ID %d not inserted. No memory availabe.\n", 
		p.ticketNum);
	}
}

void deletePassengerQueueNode(PassengerQueueNodePtr *headPtr,
	PassengerQueueNodePtr *tailPtr)
{
	PassengerQueueNodePtr tempPtr;
	Passenger p;
	p = (*headPtr)->data;
	tempPtr = *headPtr;
	*headPtr = (*headPtr)->nextPtr;
	
	if(*headPtr == NULL)
	{
		*tailPtr = NULL;
	}
	
	free(tempPtr);	
	printf("\nPassenger with ID %d dequeued.\n", p.ticketNum);
}

void updatePassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p1, Passenger p2)
{
	PassengerQueueNodePtr tempPtr;
	if((tempPtr = findPassengerQueueNode(&(*headPtr), &(*tailPtr), p1)) == NULL)
	{
		printf("\nUpdate failed.\n");
	}
	else
	{
		tempPtr->data = p2;
	}
}


int isPassengerQueueNodeEmpty(PassengerQueueNodePtr headPtr)
{
	return headPtr == NULL;
}

int countNumberOfPassengerQueueNodes(PassengerQueueNodePtr currentPtr)
{
	int count = 0;
	if(isPassengerQueueNodeEmpty(currentPtr))
	{
		return count;
	}
	else
	{
		while(!(isPassengerQueueNodeEmpty(currentPtr)))
		{
			currentPtr = currentPtr->nextPtr;
			++count;
		}		
	}
	return count;
}

void swapPassengerQueueNodes(PassengerQueueNodePtr headPtr, 
	PassengerQueueNodePtr newHeadPtr)
{
	Passenger temp;
	temp = headPtr->data;
	headPtr->data = newHeadPtr->data;
	newHeadPtr->data = temp;
}

void searchPassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p)
{	
	if(isPassengerQueueNodeEmpty(*headPtr))
	{
		printf("\nPassenger with ID %d was not found.\n",
			p.ticketNum);		
	}
	else
	{			
		if(equalPassengers((*headPtr)->data, p))
		{
			printf("\nPassenger with ID %d was found.\n",
				p.ticketNum);			
		}
		else
		{
			searchPassengerQueueNode(&((*headPtr)->nextPtr), &(*tailPtr), p);	
		}
	}	
}

PassengerQueueNodePtr findPassengerQueueNode(PassengerQueueNodePtr *headPtr, 
	PassengerQueueNodePtr *tailPtr, Passenger p)
{	
	PassengerQueueNodePtr tempPtr = *headPtr;
	if(isPassengerQueueNodeEmpty(*headPtr))
	{
		return tempPtr;
	}
	else
	{	
		tempPtr = *headPtr;
		if(((*headPtr)->data).ticketNum == p.ticketNum)
		{			
			return tempPtr;
		}
		else
		{
			findPassengerQueueNode(&((*headPtr)->nextPtr), &(*tailPtr), p);	
		}
	}	
}

void printAllPassengerQueueNodes(PassengerQueueNodePtr *headPtr)
{
	PassengerQueueNodePtr currentPtr = *headPtr;
	Passenger p;
	if(currentPtr == NULL)
	{
		printf("\nNo passengers waiting.\n\n");
	}
	else
	{
		printf("\n\n%-6s%-6s%-9s%-10s%-9s%-10s%-10s%-11s%s\n", 
			"No.", "ID", "Name", "Flight", "Class",
			"Cost($)", "Discount", "Departure", "Seat No.");
		printf("%-6s%-6s%-9s%-10s%-9s%-10s%-10s%-11s%s\n",
			"---", "--", "----", "------", "-----", 
			"-------", "--------", "---------", "--------");		
		while(currentPtr != NULL)
		{
			p = currentPtr->data;
			printf("%-6d%-6d%-9s%-10d%-9s%-10d%-10s%d/%d/%-11d%d\n",
				p.ticketNum,
				p.customerId,
				p.names, 
				p.flightNum, extractTo(p.ticketType, ' '), 
				p.costOfFlight, (p.discount == 1 ? "Yes" : "No"),
				p.deptDay, p.deptMon, p.deptYr, p.seatNum);
			currentPtr = currentPtr->nextPtr;
		}		
		printf("\n\n");
	}

}

