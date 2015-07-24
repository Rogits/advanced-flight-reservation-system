Plane promptPlaneDetails();
void printPlaneDetails(Plane p);
void printAllPlanes(FILE *fPtr);

void movePlanesCursor(FILE *fPtr, int pos);
Plane readFromPlanesFile(FILE *fPtr);
void writeToPlanesSeqFile(FILE *fPtr, Plane p);
void writeToPlanesFile(FILE *fPtr, Plane p);

void textPlanesFile(FILE *fPtr);
Plane newPlaneRecord(FILE *fPtr);
Plane updatePlaneRecord(FILE *fPtr);
Plane deletePlaneRecord(FILE *fPtr);

int checkSeatNumber(Plane p, int num); 
int getSeatNumberClass(Plane p, int seatNum); 
int getTotalNumberOfFirstClassSeats(Plane p);
int getTotalNumberOfSecondClassSeats(Plane p);
int getTotalNumberOfReservedSeats(Plane p);
int getTotalNumberOfFirstClassReservedSeats(Plane p);
int getTotalNumberOfSecondClassReservedSeats(Plane p);
int getTotalNumberOfSeats(Plane p);

int reserveSeat(Plane p, int seatNum);
int unreserveSeat(Plane p, int seatNum);

Plane fetchPlane(int planeId);

int isPlaneFull(Plane p);

int isPlaneFull(Plane p)
{
	int i;
	for(i = 0; i < 50; ++i)
	{
		if(p.seatNum[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

int checkSeatNumber(Plane p, int num)
{
	int i;
	for(i = 0; i < 50; ++i)
	{
		if(num > 0)
		{
			if(p.seatNum[i] == num)
			{
				return 1;
			}			
		}
	}
	return 0;
}

int getTotalNumberOfReservedSeats(Plane p)
{
	int i, count;
	count = 0;
	for(i = 0; i < 50; ++i)
	{
		if(p.seatNum[i] > 0)
		{
			++count;
		}
	}
	return count;
}

int getTotalNumberOfFirstClassReservedSeats(Plane p)
{
	int i, count;
	count = 0;
	for(i = 0; i < p.seatsPerClass[0]; ++i)
	{
		if(p.seatNum[i] > 0)
		{
			++count;
		}
	}
	return count;
}

int getTotalNumberOfSecondClassReservedSeats(Plane p)
{
	int i, count;
	count = 0;
	for(i = 0; i < 50; ++i)
	{
		if(i > p.seatsPerClass[0])
		{
			if(p.seatNum[i] > 0)
			{
				++count;
			}
		}
	}
	return count;
}

int getSeatNumberClass(Plane p, int seatNum)
{
	if(seatNum > 0)
	{
		if(seatNum < getTotalNumberOfFirstClassSeats(p))
		{
			return 0;
		}
		else if( seatNum > getTotalNumberOfFirstClassSeats(p) &
				 seatNum < getTotalNumberOfSecondClassSeats(p))
		{
			return 1;
		}	
	}
	
	return -1;
}

int getTotalNumberOfSeats(Plane p)
{
	return p.seatsPerClass[0] + p.seatsPerClass[1];
}

int getTotalNumberOfFirstClassSeats(Plane p)
{
	return p.seatsPerClass[0];
}

int getTotalNumberOfSecondClassSeats(Plane p)
{
	return p.seatsPerClass[1];
}

int reserveSeat(Plane p, int seatNum)
{	
	int i, j;
	int seats = p.seatsPerClass[0] + p.seatsPerClass[1];
	for(i = 0; i < 50; i++)
	{
		if(seatNum > 0)
		{
			if(i < seats)
			{
				if(p.seatNum[i] == 0)
				{
					if(i == seatNum)
					{
						p.seatNum[i] = seatNum;
						return seatNum;
					}
					else if(i == (seats - 1))
					{
						for(j = (seats - 1); j > 0; --j)
						{
							if(p.seatNum[j] == 0)
							{
								p.seatNum[j] = j;
								return j;
							}
						}
					}					
				}				
			}
		}
	}
	return 0;
}

int unreserveSeat(Plane p, int seatNum)
{	
	int i;
	for(i = 0; i < 50; i++)
	{
		if(seatNum > 0)
		{			
			if(p.seatNum[i] == 0)
			{
				if(i == seatNum)
				{
					p.seatNum[i] = 0;
					return 1;
				}										
			}			
		}
	}
	return 0;
}

Plane promptPlaneDetails()
{
	srand(850);
	int seats = (rand() % 10) * 100;
	seats = seats == 0 || seats >= 900 ? 850 : seats;
	Plane p = {0, 0, "", 0, {seats * 0.2, seats * 0.8}, {0}};
	
	printf("\nPlease enter plane details below.");
	printf("\nEnter Airport ID: ");
	fscanf( stdin, "%d", &p.airportId);		
	printf("\nEnter name: ");
	fscanf( stdin, "%s", p.name);	
			
	return p;
}

void printPlaneDetails(Plane p)
{
	printf("\n");
	printf("\nID: %d", p.id);
	printf("\nAirport ID: %d", p.airportId);
	printf("\nPlane Name: %s", p.name);
	printf("\nNumber of Miles traveled: %d", 
	p.milesTraveled);
	printf("\nTotal First Class Reserved seats: %d", 
	getTotalNumberOfFirstClassReservedSeats(p));
	printf("\nTotal Second Class Reserved seats: %d",
	getTotalNumberOfSecondClassReservedSeats(p));
	printf("\nTotal Reserved seats: %d", 
	getTotalNumberOfReservedSeats(p));
	printf("\nTotal First class seats: %d", 
	getTotalNumberOfFirstClassSeats(p));
	printf("\nTotal Second class seats: %d", 
	getTotalNumberOfSecondClassSeats(p));
	printf("\nTotal Number of seats: %d", 
	getTotalNumberOfSeats(p));
	printf("\n\n");
}

void printAllPlanes(FILE *fPtr)
{
	Plane p = {0, 0, "", 0, {0}, {0}};
	printf("\n\n\n%-6s%-14s%-8s%-9s%-10s%-10s%-6s\n", 
	"ID", "Airport ID", "Name", "Miles", "First", 
	"Second", "Seats");
	/* print underline */
	printf("%-6s%-14s%-8s%-9s%-10s%-10s%-6s\n",
	"--", "----------", "----", "-----", "-----",
	"------", "-----");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		p = readFromPlanesFile(fPtr);
		if(p.id != 0)
		{
			printf("\n%-6d", p.id);
			printf("%-14d", p.airportId);
			printf("%-8s", p.name);
			printf("%-9d", p.milesTraveled);
			printf("%-10d", getTotalNumberOfFirstClassSeats(p));		
			printf("%-10d", getTotalNumberOfSecondClassSeats(p));			
			printf("%-6d", getTotalNumberOfSeats(p));
		}		
	}
	
	printf("\n\n\n\n");
}

void movePlanesCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Plane)), SEEK_SET);
}

Plane readFromPlanesFile(FILE *fPtr)
{
	Plane p = {0, 0, "", 0, {0}, {0}};
	fread(&p, sizeof(Plane), 1, fPtr);
	return p;
}

void writeToPlanesSeqFile(FILE *fPtr, Plane p)
{
	fprintf(fPtr, "%d, %d, %s, %d, %d, %d\n",
        p.id, p.airportId, p.name, p.milesTraveled, 
		p.seatsPerClass[0], p.seatsPerClass[1]); 
}

void writeToPlanesFile(FILE *fPtr, Plane p)
{
	fwrite(&p, sizeof(Plane), 1, fPtr);
	printf("\nWriting successful.\n");
}

void textPlanesFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Plane p = {0, 0, "", 0, {0}, {0}};

	if( (writePtr = fopen("planes.txt", "w")) == NULL )
	{
		printf("\nFile could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			p = readFromPlanesFile(readPtr);
			if(p.id != 0)
			{
				writeToPlanesSeqFile(writePtr, p);
			}
		}
		fclose(writePtr);
	}
}

Plane updatePlaneRecord(FILE *fPtr)
{
	int id;	
	Plane p = {0, 0, "", 0, {0}, {0}};
	
	printf("Enter ID to update: ");
	scanf("%d", &id);
	
	movePlanesCursor(fPtr, id);
	p = readFromPlanesFile(fPtr);
	if(p.id == 0 )
	{		
		printf("No plane record found with ID, \"%d\".", id);
	}
	else
	{
		printPlaneDetails(p);
		p = promptPlaneDetails();		
		removePlaneFromAirport(p.airportId, p.id);
		addPlaneToAirport(p.airportId, p.id);
		movePlanesCursor(fPtr, p.id);
		writeToPlanesFile(fPtr, p);		
		printf("\nUpdate successful.\n");		
	}
	return p;
}

Plane deletePlaneRecord(FILE *fPtr)
{
	Plane p;
	Plane blankPlane = {0, 0, "", 0, {0}, {0}};
	int id;
	
	printf("Enter ID to delete: ");
	scanf("%d", &id);
	
	movePlanesCursor(fPtr, id);
	p = readFromPlanesFile(fPtr);
	if(p.id == 0)
	{
		printf("No customer record for ID, %d.", p.id);
	}
	else
	{
		removePlaneFromAirport(p.airportId, p.id);
		movePlanesCursor(fPtr, p.id);
		writeToPlanesFile(fPtr, blankPlane);
		printf("\nDelete successful.\n");
	}
	return p;
}

Plane newPlaneRecord(FILE *fPtr)
{
	Plane p = {0, 0, "", 0, {0}, {0}};
	Plane temp = p;
	int id;
	
	printf("Enter new ID: ");
	scanf("%d", &id);
		
	movePlanesCursor(fPtr, id);
	p = readFromPlanesFile(fPtr);
	
	if(p.id != 0)
	{		
		printf("Plane with ID \"%d\" contains information.\n", p.id);
		p = temp;
	}	
	else
	{		
		p = promptPlaneDetails();	
		p.id = id;		
		addPlaneToAirport(p.airportId, p.id);
		movePlanesCursor(fPtr, p.id);
		writeToPlanesFile(fPtr, p);
		printf("\nInsertion successful.\n");		
	}	
	return p;
}

Plane fetchPlane(int planeId)
{
	FILE *fPtr;
	Plane p = {0, 0, "", 0, {0}, {0}};
	if((fPtr = fopen("planes.dat", "rb")) == NULL)
	{
		return p;
	}
	else
	{
		movePlanesCursor(fPtr, planeId);
		p = readFromPlanesFile(fPtr);
	}
	return p;
}