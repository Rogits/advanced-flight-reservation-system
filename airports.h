Airport promptAirportDetails();
void printAirportDetails(Airport port);
void printAllAirports(FILE *fPtr);
void moveAirportsCursor(FILE *fPtr, int pos);
Airport readFromAirportsFile(FILE *fPtr);
void writeToAirportsSeqFile(FILE *fPtr, Airport port);
void writeToAirportsFile(FILE *fPtr, Airport port);

void textAirportsFile(FILE *fPtr);
Airport newAirportRecord(FILE *fPtr);
Airport updateAirportRecord(FILE *fPtr);
Airport deleteAirportRecord(FILE *fPtr);

int getNumberOfPlanes(Airport port);
Airport fetchAirport(int airportId);

void addPlaneToAirport(int planeId, int airportId);
void removePlaneFromAirport(int planeId, int airportId);

Airport promptAirportDetails()
{
	Airport port = {0, "", "", "", 0, 0, {0}};
	printf("\nPlease enter airport details below.\n");
	
	printf("\nEnter airport name: ");
	fscanf(stdin, "%s", port.airportName);
	printf("\nEnter country: ");
	fscanf( stdin, "%s", port.country);
	printf("\nEnter usual weather: ");
	fscanf( stdin, "%s", port.usualWeather);
	printf("\nEnter time from Beirut(Hours): ");
	fscanf( stdin, "%d", &port.timeFromBeirut);
	printf("\nEnter miles from Beirut: ");
	fscanf( stdin, "%d", &port.milesFromBeirut);
	
	return port;
}

void printAirportDetails(Airport port)
{
	printf("\nID: %d", port.id);
	printf("\nAirport Name: %s", port.airportName);
	printf("\nCountry: %s", port.country);
	printf("\nUsual Weather: %s", port.usualWeather);
	printf("\nTime from Beirut(Hours): %d", port.timeFromBeirut);
	printf("\nMiles from Beirut: %d", port.milesFromBeirut);
	printf("\nNumber of planes: %d", getNumberOfPlanes(port));
	printf("\n\n");
}

void printAllAirports(FILE *fPtr)
{
	Airport port = {0, "", "", "", 0, 0, {0}};
		
	printf("\n%-5s%-10s%-15s%-10s%-9s%-7s%s\n", 
	"ID", "Name", "Country", "Weather", "Time", "Miles", "Planes");
	printf("%-5s%-10s%-15s%-10s%-9s%-7s%s\n",
	"--", "----", "-------", "-------", "----", "-----", "------");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		port = readFromAirportsFile(fPtr);
		if(port.id != 0)
		{
			printf("\n%-5d", port.id);	
			printf("%-10s", port.airportName);
			printf("%-15s", port.country);		
			printf("%-10s", port.usualWeather);			
			printf("%-9d", port.timeFromBeirut);
			printf("%-7d", port.milesFromBeirut);
			printf("%d", getNumberOfPlanes(port));
		}		
	}
	
	printf("\n\n");
}

void moveAirportsCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Airport)), SEEK_SET);
}

Airport readFromAirportsFile(FILE *fPtr)
{
	Airport port = {0, "", "", "", 0, 0, {0}};
	fread(&port, sizeof(Airport), 1, fPtr);
	return port;
}

void writeToAirportsSeqFile(FILE *fPtr, Airport port)
{
	fprintf(fPtr, "%s, %s, %s, %d, %d, %d\n",
        port.airportName, port.country, port.usualWeather, 
		port.timeFromBeirut, port.milesFromBeirut, 
		getNumberOfPlanes(port)); 
}

void writeToAirportsFile(FILE *fPtr, Airport port)
{
	fwrite(&port, sizeof(Airport), 1, fPtr);
}

void textAirportsFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Airport port = {0, "", "", "", 0, 0, {0}};
	
	if( (writePtr = fopen("airports.txt", "w")) == NULL )
	{
		printf("\nFile could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			port = readFromAirportsFile(readPtr);
			if(port.id != 0)
			{
				writeToAirportsSeqFile(writePtr, port);
			}
		}
		fclose(writePtr);
	}
}

Airport updateAirportRecord(FILE *fPtr)
{
	int num;
	Airport port = {0, "", "", "", 0, 0, {0}};
	
	printf("\nEnter Airport ID to update: ");
	scanf("%d", &num);
	
	moveAirportsCursor(fPtr, num);
	port = readFromAirportsFile(fPtr);
	if(port.id == 0)
	{
		printf("\nNo airport record found with airport ID, \"%d\".\n", num);		
	}
	else
	{
		printAirportDetails(port);
		port = promptAirportDetails();
		port.id = num;
		moveAirportsCursor(fPtr, num);
		writeToAirportsFile(fPtr, port);		
		printf("\nUpdate successful.\n");		
	}
	return port;
}

Airport deleteAirportRecord(FILE *fPtr)
{
	Airport port;
	Airport emptyPort = {0, "", "", "", 0, 0, {0}};
	int num;
	
	printf("\nEnter Airport ID to delete: ");
	scanf("%d", &num);
	
	moveAirportsCursor(fPtr, num);
	port = readFromAirportsFile(fPtr);
	if(port.id == 0)
	{
		printf("\nNo airport record with ID, %d.\n", num);		
	}
	else
	{
		moveAirportsCursor(fPtr, num);
		writeToAirportsFile(fPtr, emptyPort);
		printf("\nDelete successful.\n");		
	}	
	return port;
}

Airport newAirportRecord(FILE *fPtr)
{
	Airport port = {0, "", "", "", 0, 0, {0}};
	int id;
	
	printf("\nEnter new Airport ID: ");
	scanf("%d", &id);
	
	moveAirportsCursor(fPtr, id);
	port = readFromAirportsFile(fPtr);
	
	if(port.id != 0)
	{
		printf("\nAirport with ID \"%d\" contains information.\n", id);		
	}
	else
	{
		port = promptAirportDetails();
		port.id = id;
		moveAirportsCursor(fPtr, id);
		writeToAirportsFile(fPtr, port);
		printf("\nInsertion successful.\n");		
	}		
	return port;
}

int getNumberOfPlanes(Airport port)
{
	int i, count;
	for(i = count = 0; i < MAX_PLANES; ++i)
	{
		if(port.planes[i] > 0)
		{
			++count;
		}
	}
	return count;
}

Airport fetchAirport(int airportId)
{
	FILE *fPtr;
	Airport port = {0, "", "", "", 0, 0, {0}};
	if((fPtr = fopen("airports.dat", "rb")) == NULL)
	{
		printf("\nFailed to open file.\n");
	}
	else
	{
		moveAirportsCursor(fPtr, airportId);
		port = readFromAirportsFile(fPtr);
		fclose(fPtr);
	}
	return port;
}

void addPlaneToAirport(int planeId, int airportId)
{
	Airport port = {0, "", "", "", 0, 0, {0}};
	int i, j;
	FILE *fPtr;
	if((fPtr = fopen("airports.dat", "rb+")) == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{					
		moveAirportsCursor(fPtr, airportId);
		port = readFromAirportsFile(fPtr);
		if(port.id == 0)
		{
			printf("\nFailed to add plane to Airport.\n");
		}
		else
		{
			for(i = 0; i < 50; i++)
			{
				if(port.planes[i] == planeId)
				{
					break;
				}
				else if(i == 49 & port.planes[i] != planeId) 
				{
					for(j = 0; j > 0; --j)
					{
						if(port.planes[j] == 0)
						{
							port.planes[j] = planeId; // added
							break;
						}
					}
				}
			}
			writeToAirportsFile(fPtr, port);			
		}
		fclose(fPtr);
	} 			
}

void removePlaneFromAirport(int planeId, int airportId)
{
	Airport port = {0, "", "", "", 0, 0, {0}};
	int i;
	FILE *fPtr;
	if((fPtr = fopen("airports.dat", "rb+")) == NULL)
	{		
		printf("\nFile could not be opened.\n");		
	}
	else
	{					
		moveAirportsCursor(fPtr, airportId);
		port = readFromAirportsFile(fPtr);
		if(port.id == 0)
		{
			printf("\nFailed to remove plane from Airport.\n");
		}
		else
		{
			for(i = 0; i < 50; i++)
			{
				if(port.planes[i] == planeId)
				{
					port.planes[i] = 0;
				}
			}
			writeToAirportsFile(fPtr, port);
		}	
		fclose(fPtr);
	} 	
}



