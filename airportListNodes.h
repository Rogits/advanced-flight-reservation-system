void insertAirportListNode(AirportListNodePtr *aPtr, Airport a);
void updateAirportListNode(AirportListNodePtr *aPtr, Airport a1, Airport a2);
void deleteAirportListNode(AirportListNodePtr *aPtr, Airport a);
int isAirportListNodeEmpty(AirportListNodePtr aPtr);

void searchAirportListNode(AirportListNodePtr *aPtr, Airport a);

int compareAirports(Airport, Airport);

AirportListNodePtr findAirportListNode(AirportListNodePtr *aPtr, Airport port);

void addPlaneToAirportListNode(AirportListNodePtr *aPtr, int planeId, int airportId);
void removePlaneFromAirportListNode(AirportListNodePtr *aPtr, int planeId, int airportId);

void populateAirportsList(AirportListNodePtr *aPtr, FILE *fPtr);

int promptAirportInstructions();

void processAirportsList(AirportListNodePtr startPtr);

void processAirportsList(AirportListNodePtr startPtr)
{			
	FILE *fPtr;
	
	int choice = 0;
	int input;
	Airport port = {0, "", "", "", 0, 0, {0}};
	Airport newport;
		
	if((fPtr = fopen("airports.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("airports.dat", "wb")) == NULL)
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
		populateAirportsList(&startPtr, fPtr);
		
		while((choice = promptAirportInstructions()) != 0)
		{	
			switch(choice)
			{
				case 1:
					textAirportsFile(fPtr);
					break;
				case 2:					
					if((findAirportListNode(&startPtr, 
						(port = newAirportRecord(fPtr)))) == NULL)
					{
						insertAirportListNode(&startPtr, port);						
					}
					else
					{
						printf("\nInsertion failed.\n");
					}					
					break;
				case 3:
					if(isAirportListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");						
					}
					else
					{
						printf("\nEnter Airport ID: ");
						scanf("%d", &input);
						port.id = input;
						if(findAirportListNode(&startPtr, port) == NULL)
						{
							printf("\nNo record found with ID %d.\n", 
								input);
						}
						else
						{
							if((newport = updateAirportRecord(fPtr)).id == 0)
							{
								printf("\nUpdate failed.\n");
							}
							else
							{
								updateAirportListNode(&startPtr, port, newport);
							}							
						}						
					}
					break;
				case 4:
					if(isAirportListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");						
					}
					else
					{
						if((port = deleteAirportRecord(fPtr)).id == 0)
						{
							printf("\nDelete failed.\n");
						}
						else
						{
							deleteAirportListNode(&startPtr, port);
						}
					}
					break;
				case 5:
					if(isAirportListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");
					}
					else
					{						
						printf("\nEnter Airport ID to be searched: ");
						scanf("\n%d", &input);
						port.id = input;
						searchAirportListNode(&startPtr, port);						
					}
					break;					
				case 6:
					printAllAirports(fPtr);
					break;
				default:
					printf("\nIncorrect choice.\n");
					break;				
			}
		}	
		
		fclose(fPtr);		
	}	
}

int compareAirports(Airport a1, Airport a2)
{
	return (a1.id == a2.id) ? 1 : 0;
}

void insertAirportListNode(AirportListNodePtr *aPtr, Airport a)
{
	AirportListNodePtr newAirportPtr;
	AirportListNodePtr previousAirportPtr;
	AirportListNodePtr currentAirportPtr;
	
	newAirportPtr = malloc(sizeof(AirportListNode));
	
	if(newAirportPtr != NULL)
	{
		newAirportPtr->a = a;
		newAirportPtr->nextAirportListNode = NULL;		
		
		previousAirportPtr = NULL;
		currentAirportPtr = *aPtr;
		
		while(currentAirportPtr != NULL && 
			(compareAirports(a, currentAirportPtr->a) == 1) )
		{
			previousAirportPtr = currentAirportPtr;
			currentAirportPtr = currentAirportPtr->nextAirportListNode;	
		}
		
		if(previousAirportPtr == NULL)
		{
			newAirportPtr->nextAirportListNode = *aPtr;
			*aPtr = newAirportPtr;
		}
		else
		{
			previousAirportPtr->nextAirportListNode = newAirportPtr;
			newAirportPtr->nextAirportListNode = currentAirportPtr;
		}
	}
	else
	{
		printf("Airport with ID %d not inserted. No memory available.\n", a.id);
	}
}

void updateAirportListNode(AirportListNodePtr *aPtr, Airport a1, Airport a2)
{
	AirportListNodePtr tempPtr;
	if((tempPtr = findAirportListNode(aPtr, a1)) == NULL)
	{
		printf("\nUpdate failed.\n");
	}
	else
	{		
		tempPtr->a = a2;
	}
}

void deleteAirportListNode(AirportListNodePtr *aPtr, Airport a)
{
	AirportListNodePtr previousPtr;
	AirportListNodePtr currentPtr;
	AirportListNodePtr tempPtr;
		
	if( compareAirports(a, (*aPtr)->a) == 1 )
	{
		tempPtr = *aPtr;
		*aPtr = (*aPtr)->nextAirportListNode;
		free(tempPtr);		
	}
	else
	{
		previousPtr = *aPtr;
		currentPtr = (*aPtr)->nextAirportListNode;
		
		while(currentPtr != NULL && (compareAirports(currentPtr->a, a) == 1))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextAirportListNode;
		}
		
		if(currentPtr != NULL)
		{
			tempPtr = currentPtr;
			previousPtr->nextAirportListNode = currentPtr->nextAirportListNode;
			free(tempPtr);
		}
	}
}

int isAirportListNodeEmpty(AirportListNodePtr sPtr)
{
	return sPtr == NULL;
}

void searchAirportListNode(AirportListNodePtr *aPtr, Airport a)
{
	AirportListNodePtr currentPtr = *aPtr;
	
	while(currentPtr != NULL)
	{
		if(compareAirports(currentPtr->a, a) == 1)
		{
			printf("\nAirport with ID %d was found.\n", a.id);
			return;
		}
		currentPtr = currentPtr->nextAirportListNode;
	}
	printf("\nAirport with ID %d was not found.\n", a.id);
}

AirportListNodePtr findAirportListNode(AirportListNodePtr *aPtr, Airport a)
{
	AirportListNodePtr currentPtr = *aPtr;
	
	while(currentPtr != NULL)
	{
		if(compareAirports(currentPtr->a, a) == 1)
		{
			return currentPtr; // match found
		}
		currentPtr = currentPtr->nextAirportListNode; // walk through list nodes
	}
	return NULL; // match not found
}

void addPlaneToAirportListNode(AirportListNodePtr *sPtr, int planeId, int airportId)
{
	AirportListNodePtr tempPtr;
	Airport a = {0, "", "", "", 0, 0, {0}};
	a.id = airportId;
	if((tempPtr = findAirportListNode(sPtr, a)) == NULL)
	{
		return;
	}
	else
	{		
		tempPtr->a = a;
		addPlaneToAirport(planeId, airportId);
	}
}

void removePlaneFromAirportListNode(AirportListNodePtr *sPtr, int planeId, int airportId)
{
	AirportListNodePtr tempPtr;
	Airport a = {0, "", "", "", 0, 0, {0}};
	a.id = airportId;
	if((tempPtr = findAirportListNode(sPtr, a)) == NULL)
	{
		return;
	}
	else
	{		
		tempPtr->a = a;
		removePlaneFromAirport(planeId, airportId);
	}
}

void populateAirportsList(AirportListNodePtr *aPtr, FILE *fPtr)
{
	Airport a = {0, "", "", "", 0, 0, {0}}; 
	
	if(fPtr == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{		
		rewind(fPtr);
		while(!feof(fPtr))
		{
			a = readFromAirportsFile(fPtr);
			if(a.id != 0)
			{				
				insertAirportListNode(aPtr, a);
			}			
		}		
	}
}


int promptAirportInstructions()
{
	int option;
	printf("\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an choice below to proceed.", 
	"1 - Create a text file for printing all airport records.",
	"2 - Create and save a new airport record.",
	"3 - Update an existing airport record.",
	"4 - Delete an existing airport record.", 
	"5 - Search an existing airport record.",
	"6 - View all airport records.", 	
	"0 - Exit.",
	"Enter your choice: ");
	scanf("%d", &option);
	
	return option;	
}
