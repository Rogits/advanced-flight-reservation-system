void insertPlaneListNode(PlaneListNodePtr *aPtr, Plane data);
void updatePlaneListNode(PlaneListNodePtr *aPtr, Plane p1, Plane p2);
void deletePlaneListNode(PlaneListNodePtr *aPtr, Plane data);
int isPlaneListNodeEmpty(PlaneListNodePtr aPtr);
void searchPlaneListNode(PlaneListNodePtr *aPtr, Plane p);

int comparePlanes(Plane, Plane);

PlaneListNodePtr findPlaneListNode(PlaneListNodePtr *aPtr, Plane p);

void populatePlanesList(PlaneListNodePtr *aPtr);

int promptPlaneInstructions();
void processPlanesList(PlaneListNodePtr startPtr, AirportListNodePtr rootPtr);

void processPlanesList(PlaneListNodePtr startPtr, AirportListNodePtr rootAirportNodePtr)
{			
	FILE *fPtr;
	
	int choice = 0;
	int input;
	Plane p, newp;
	Airport a = {0, "", "", "", 0, 0, {0}};
		
	if((fPtr = fopen("planes.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("planes.dat", "wb")) == NULL)
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
		populatePlanesList(&startPtr);
		
		while((choice = promptPlaneInstructions()) != 0)
		{	
			switch(choice)
			{
				case 1:
					textPlanesFile(fPtr);
					break;
				case 2:
					p = newPlaneRecord(fPtr);
					if(findPlaneListNode(&startPtr, p) == NULL)
					{
						insertPlaneListNode(&startPtr, p);
						addPlaneToAirportListNode(&rootAirportNodePtr, 
							p.id, p.airportId);
						//a = fetchAirport(p.airportId);
						//updateAirportListNode(&rootAirportPtr, a, a);						
					}
					else
					{
						printf("\nInsertion failed.\n");						
					}					
					break;
				case 3:
					if(isPlaneListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");						
					}
					else
					{
						printf("\nEnter Plane ID to be updated: ");
						scanf("\n%d", &input);
						p.id = input;
						if((newp = updatePlaneRecord(fPtr)).id == 0)
						{
							printf("\nUpdate failed.\n");
						}
						else
						{
							updatePlaneListNode(&startPtr, p, newp);
							removePlaneFromAirportListNode(&rootAirportNodePtr, 
								p.id, p.airportId);
							addPlaneToAirportListNode(&rootAirportNodePtr, 
								p.id, p.airportId);							
							//a = fetchAirport(newp.airportId);
							//updateAirportListNode(&rootAirportPtr, a, a);
						}
					}
					break;
				case 4:
					if(!(isPlaneListNodeEmpty(startPtr)))
					{
						if((p = deletePlaneRecord(fPtr)).id == 0)
						{
							printf("\nDelete failed.\n");
						}
						else
						{
							deletePlaneListNode(&startPtr, p);
							removePlaneFromAirportListNode(&rootAirportNodePtr, 
								p.id, p.airportId);
							//a = fetchAirport(p.airportId);
							//updateAirportListNode(&rootAirportPtr, a, a);
						}
					}
					else
					{
						printf("\nNo records found.\n");
					}
					break;
				case 5:
					if(isPlaneListNodeEmpty(startPtr))
					{
						printf("\nNo records found.\n");
					}
					else
					{						
						printf("\nEnter Plane ID to be searched: ");
						scanf("\n%d", &input);
						p.id = input;
						searchPlaneListNode(&startPtr, p);						
					}
					break;					
				case 6:
					printAllPlanes(fPtr);
					break;
				default:
					printf("\nIncorrect choice.\n");
					break;				
			}
		}	
		
		fclose(fPtr);		
	}	
}

int comparePlanes(Plane p1, Plane p2)
{
	return (p1.id == p2.id) ? 1 : 0; // returns 1 as equal
}

void insertPlaneListNode(PlaneListNodePtr *aPtr, Plane data)
{
	PlaneListNodePtr newPlanePtr;
	PlaneListNodePtr previousPlanePtr;
	PlaneListNodePtr currentPlanePtr;
	
	newPlanePtr = malloc(sizeof(PlaneListNode));
	
	if(newPlanePtr != NULL)
	{
		newPlanePtr->data = data;
		newPlanePtr->nextPlaneListNode = NULL;		
		
		previousPlanePtr = NULL;
		currentPlanePtr = *aPtr;
		
		while(currentPlanePtr != NULL && 
			(comparePlanes(data, currentPlanePtr->data) == 1) )
		{
			previousPlanePtr = currentPlanePtr;
			currentPlanePtr = currentPlanePtr->nextPlaneListNode;	
		}
		
		if(previousPlanePtr == NULL)
		{
			newPlanePtr->nextPlaneListNode = *aPtr;
			*aPtr = newPlanePtr;
		}
		else
		{
			previousPlanePtr->nextPlaneListNode = newPlanePtr;
			newPlanePtr->nextPlaneListNode = currentPlanePtr;
		}
	}
	else
	{
		printf("Plane with ID %d not inserted. No memory available.\n", data.id);
	}
}

void updatePlaneListNode(PlaneListNodePtr *aPtr, Plane p1, Plane p2)
{
	PlaneListNodePtr tempPtr;
	if((tempPtr = findPlaneListNode(aPtr, p1)) == NULL)
	{
		printf("\nUpdate failed.\n");
	}
	else
	{		
		tempPtr->data = p2;
	}
}

void deletePlaneListNode(PlaneListNodePtr *aPtr, Plane data)
{
	PlaneListNodePtr previousPtr;
	PlaneListNodePtr currentPtr;
	PlaneListNodePtr tempPtr;
		
	if( comparePlanes(data, (*aPtr)->data) == 1 )
	{
		tempPtr = *aPtr;
		*aPtr = (*aPtr)->nextPlaneListNode;
		free(tempPtr);		
	}
	else
	{
		previousPtr = *aPtr;
		currentPtr = (*aPtr)->nextPlaneListNode;
		
		while(currentPtr != NULL && (comparePlanes(currentPtr->data, data) == 1))
		{
			previousPtr = currentPtr;
			currentPtr = currentPtr->nextPlaneListNode;
		}
		
		if(currentPtr != NULL)
		{
			tempPtr = currentPtr;
			previousPtr->nextPlaneListNode = currentPtr->nextPlaneListNode;
			free(tempPtr);
		}
	}
}

int isPlaneListNodeEmpty(PlaneListNodePtr sPtr)
{
	return sPtr == NULL;
}

void searchPlaneListNode(PlaneListNodePtr *aPtr, Plane data)
{
	PlaneListNodePtr currentPtr = *aPtr;
	
	while(currentPtr != NULL)
	{
		if(comparePlanes(currentPtr->data, data) == 1)
		{
			printf("\nPlane with ID %d was found.\n", data.id);
			return;
		}
		currentPtr = currentPtr->nextPlaneListNode; // walk through list nodes
	}
	printf("\nPlane with ID %d was not found.\n", data.id);
}

PlaneListNodePtr findPlaneListNode(PlaneListNodePtr *aPtr, Plane data)
{
	PlaneListNodePtr currentPtr = *aPtr;
	
	while(currentPtr != NULL)
	{
		if(comparePlanes(currentPtr->data, data) == 1)
		{
			return currentPtr; // match found
		}
		currentPtr = currentPtr->nextPlaneListNode; // walk through list nodes
	}
	return NULL; // match not found
}

void populatePlanesList(PlaneListNodePtr *aPtr)
{
	FILE *fPtr;
	
	if((fPtr = fopen("planes.dat", "rb")) == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{
		Plane p; 
		/* read from file and populate list */
		rewind(fPtr);
		while(!feof(fPtr))
		{
			p = readFromPlanesFile(fPtr);
			if(p.id != 0)
			{				
				insertPlaneListNode(aPtr, p);
			}			
		}
		fclose(fPtr);
	}
}

int promptPlaneInstructions()
{
	int option;
	printf("\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an choice below to proceed.", 
	"1 - Create a text file for printing all plane records.",
	"2 - Create and save a new plane record.",
	"3 - Update an existing plane record.",
	"4 - Delete an existing plane record.", 
	"5 - Search an existing plane record.",
	"6 - View all plane records.", 	
	"0 - Exit.",
	"Enter your choice: ");
	scanf("%d", &option);
	
	return option;	
}
