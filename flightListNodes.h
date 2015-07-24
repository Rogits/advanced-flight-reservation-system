void insertFlightListNode(FlightListNodePtr *sPtr, Flight f);
void updateFlightListNode(FlightListNodePtr *aPtr, Flight f1, Flight f2);
void deleteFlightListNode(FlightListNodePtr *aPtr, Flight f);
void searchFlightListNode(FlightListNodePtr *sPtr, Flight f);

int isFlightListNodeEmpty(FlightListNodePtr sPtr);

int compareFlights(Flight f1, Flight f2);

FlightListNodePtr findFlightListNode(FlightListNodePtr *sPtr, Flight f);

void updatePassengerTreeNodeInFlightListNode(FlightListNodePtr *sPtr,	 
	PassengerTreeNodePtr rootPassengerTreeNodePtr, Flight f);

void populateFlightsList(FlightListNodePtr *sPtr, FILE *fPtr);

int promptFlightInstructions();
void processFlightsList(FlightListNodePtr startPtr);

void processFlightsList(FlightListNodePtr startPtr)
{
	FILE *fPtr;	
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	Flight newf;
	int choice;	
	int input;
	
	if((fPtr = fopen("flights.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("flights.dat", "wb")) == NULL)
		{					
			printf("\nFile could not be opened.\n");
		}
		else
		{	
			printf("\nNew file created.\n");
		}
	}
	else
	{
		
		populateFlightsList(&startPtr, fPtr);
		
		while((choice = promptFlightInstructions()) != 0)
		{
			switch(choice)
			{		
				case 1:					
					textFlightsFile(fPtr);
					break;
				case 2:
					if((findFlightListNode(&startPtr, 
						(f = newFlightRecord(fPtr)))) == NULL)
					{
						insertFlightListNode(&startPtr, f);						
						printf("\nInsertion successful.\n");
					}
					else
					{
						printf("\nInsert failed.\n");
					}
					break;
				case 3:
					if(isFlightListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");
					}
					else
					{
						printf("\nEnter Flight Number to be searched: ");
						scanf("\n%d", &input);
						f.flightNum = input;
						if(findFlightListNode(&startPtr, f) == NULL)
						{
							printf("No flight record with ID %d.\n", 
								f.flightNum);
						}
						else
						{			
							if((newf = newFlightRecord(fPtr)).flightNum == 0)
							{
								printf("\nUpdate failed.\n");
							}
							else
							{
								updateFlightListNode(&startPtr, f, newf);
								printf("\nUpdate successful.\n");
							}
						}
					}
					break;
				case 4:
					if(isFlightListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");
					}
					else
					{
						if((f = deleteFlightRecord(fPtr)).flightNum == 0)
						{
							printf("\nDelete failed.\n");
						}
						else
						{
							deleteFlightListNode(&startPtr, f);
							printf("\nDelete successful.\n");
						}
					}
					break;				
				case 5:
					if(isFlightListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");
					}
					else
					{					
						int input;
						printf("\nEnter Flight ID to be searched: ");
						scanf("\n%d", &input);
						f.flightNum = input;						
						searchFlightListNode(&startPtr, f);						
					}
					break;
				case 6:
					printAllFlights(fPtr);
					break;
				default:
					printf("\nInvalid choice.\n\n");				
					break;
			}		
		}
		fclose(fPtr);		
	}	
}

int compareFlights(Flight f1, Flight f2)
{
	return f1.flightNum == f2.flightNum ? 1 : 0;
}

void insertFlightListNode(FlightListNodePtr *sPtr, Flight f)
{
	FlightListNodePtr newPtr;
	FlightListNodePtr previousPtr;
	FlightListNodePtr currentPtr;
	
	newPtr = malloc(sizeof(FlightListNode));
	
	if(newPtr != NULL)
	{
		newPtr->data = f;
		newPtr->rootPassengerTreeNodePtr = NULL;
		newPtr->nextFlightListNodePtr = NULL;		
		
		previousPtr = NULL;
		currentPtr = *sPtr;
		
		while(currentPtr != NULL && compareFlights(f, currentPtr->data))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextFlightListNodePtr;	
		}
		
		if(previousPtr == NULL)
		{
			newPtr->nextFlightListNodePtr = *sPtr;
			*sPtr = newPtr;
		}
		else
		{
			previousPtr->nextFlightListNodePtr = newPtr;
			newPtr->nextFlightListNodePtr = currentPtr;
		}
	}
	else
	{
		printf("%c not inserted. No memory available.\n", f.flightNum);
	}
}

void updateFlightListNode(FlightListNodePtr *aPtr, Flight a1, Flight a2)
{
	FlightListNodePtr tempPtr;
	if((tempPtr = findFlightListNode(aPtr, a1)) == NULL)
	{
		printf("\nUpdate failed.\n");
	}
	else
	{		
		tempPtr->data = a2;
	}
}

void deleteFlightListNode(FlightListNodePtr *aPtr, Flight f)
{
	FlightListNodePtr previousPtr;
	FlightListNodePtr currentPtr;
	FlightListNodePtr tempPtr;
		
	if( compareFlights(f, (*aPtr)->data) == 1 )
	{
		tempPtr = *aPtr;
		*aPtr = (*aPtr)->nextFlightListNodePtr;
		free(tempPtr);		
	}
	else
	{
		previousPtr = *aPtr;
		currentPtr = (*aPtr)->nextFlightListNodePtr;
		
		while(currentPtr != NULL && (compareFlights(currentPtr->data, f) == 1))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextFlightListNodePtr;
		}
		
		if(currentPtr != NULL)
		{
			tempPtr = currentPtr;
			previousPtr->nextFlightListNodePtr = currentPtr->nextFlightListNodePtr;
			free(tempPtr);
		}
	}
}



int isFlightListNodeEmpty(FlightListNodePtr sPtr)
{
	return sPtr == NULL;
}

void searchFlightListNode(FlightListNodePtr *sPtr, Flight f)
{
	FlightListNodePtr currentPtr = *sPtr;
	
	while(currentPtr != NULL)
	{
		if(compareFlights(currentPtr->data, f) == 1)
		{
			printf("\nFlight with flight number %d was found.\n", 
				f.flightNum);
			return; 
		}
		/*
		else
		{
			printf("\n%d\n", (currentPtr->data).flightNum);
		}
		*/
		currentPtr = currentPtr->nextFlightListNodePtr; 
	}
	printf("\nFlight with flight number %d was not found.\n", 
			f.flightNum);
}

FlightListNodePtr findFlightListNode(FlightListNodePtr *sPtr, Flight f)
{
	FlightListNodePtr currentPtr = *sPtr;
	
	while(currentPtr != NULL)
	{
		if(compareFlights(currentPtr->data, f) == 1)
		{
			return currentPtr; 
		}
		currentPtr = currentPtr->nextFlightListNodePtr; 
	}
	return NULL;
}

void updatePassengerTreeNodeInFlightListNode(FlightListNodePtr *sPtr,	 
	PassengerTreeNodePtr rootPassengerTreeNodePtr, Flight f)
{
	FlightListNodePtr tempPtr;
	if((tempPtr = findFlightListNode(sPtr, f)) == NULL)
	{
		return;
	}
	else
	{
		tempPtr->rootPassengerTreeNodePtr = rootPassengerTreeNodePtr;
	}
}


void populateFlightsList(FlightListNodePtr *aPtr, FILE *fPtr)
{	
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	if(fPtr == NULL)
	{		
		printf("File could not be opened.\n");		
	}
	else
	{		
		rewind(fPtr);
		while(!feof(fPtr))
		{
			f = readFromFlightsFile(fPtr);
			if(f.flightNum != 0)
			{				
				insertFlightListNode(aPtr, f);
			}			
		}
	}
}

int promptFlightInstructions()
{
	int option;
	printf("\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an option below to proceed.", 
	"1 - Create a text file for printing all records.",
	"2 - Create and save a new flight record.",
	"3 - Update an existing flight record.",
	"4 - Delete an existing flight record.", 
	"5 - Search an existing flight record.",
	"6 - View all flight records.", 
	"0 - Exit.",
	"Enter option: ");
	scanf("%d", &option);
	
	return option;	
}


