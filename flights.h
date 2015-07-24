Flight promptFlightDetails();
void printFlightDetails(Flight f);
void printAllFlights(FILE *fPtr);

void moveFlightsCursor(FILE *fPtr, int pos);
Flight readFromFlightsFile(FILE *fPtr);
void writeToFlightsSeqFile(FILE *fPtr, Flight f);
void writeToFlightsFile(FILE *fPtr, Flight f);

void textFlightsFile(FILE *fPtr);
Flight newFlightRecord(FILE *fPtr);
Flight updateFlightRecord(FILE *fPtr);
Flight deleteFlightRecord(FILE *fPtr);

Flight fetchFlight(int flightNum);

Flight promptFlightDetails()
{
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	Airport a = {0, "", "", "", 0, 0, {0}};
	printf("\nPlease enter flight details below.\n");
	
	printf("\nEnter plane ID: ");
	fscanf(stdin, "%d", &f.planeId);
	
	if((a = fetchAirport(f.planeId)).id > 0)
	{
		printf("\nEnter departure date(Day): ");
		fscanf( stdin, "%d", &f.deptDay);
		printf("\nEnter departure date(Month): ");
		fscanf( stdin, "%d", &f.deptMon);
		printf("\nEnter departure date(Year): ");
		fscanf( stdin, "%d", &f.deptYr);
		printf("\nEnter departure time(Hour): ");
		fscanf( stdin, "%d", &f.deptHour);
		printf("\nEnter departure time(Minute): ");
		fscanf( stdin, "%d", &f.deptMin);		
		printf("\nEnter cost of flight(First Class): ");	
		fscanf( stdin, "%d", &f.ticketPrice[0]);
		printf("\nEnter cost of flight(Second Class): ");
		fscanf(stdin, "%d", &f.ticketPrice[1]);		
		strcpy(f.deptDayName, getDay(getDate(f.deptDay, f.deptMon, f.deptYr)));		
		strcpy(f.dest, a.airportName);
		f.milesToTravel = a.milesFromBeirut;		
	}
	else
	{
		printf("\nPlane ID %d does not exist.\n", f.planeId);		
	}
	
	return f;
}

void printFlightDetails(Flight f)
{
	printf("\nFlight Number: %d", f.flightNum);
	printf("\nPlane ID: %d", f.planeId);
	printf("\nDeparture Date: %d/%d/%d", f.deptDay, f.deptMon, f.deptYr);
	printf("\nDeparture Time: %d:%d", f.deptHour, f.deptMin);
	printf("\nDeparture Day: %s", f.deptDayName);
	printf("\nDeparture Month: %s", getMonthName(getDate(0,f.deptMon,0)) );
	printf("\nDeparture Full Date and Time: %s", 
	getFullDateAndTime(
	getDateAndTime(f.deptDay, f.deptMon, f.deptYr, f.deptHour, f.deptMin, 0)));
	printf("\nDestination: %s", f.dest);
	printf("\nFirst Class Cost: $%d", f.ticketPrice[0]);
	printf("\nSecond Class Cost: $%d", f.ticketPrice[1]);
	printf("\nDistance(miles): %d", f.milesToTravel);
	printf("\n");
}

void printAllFlights(FILE *fPtr)
{
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	printf("\n%-9s%-8s%-13s%-7s%-14s%-8s%-9s%s\n", 
	"Flight", "Plane", "Dept. Date", "Time", "Destination",
	"First", "Second", "Distance");
	/* print underline */
	printf("%-9s%-8s%-13s%-7s%-14s%-8s%-9s%s\n",
	"------", "-----", "----------", "----", "-----------", 
	"-----", "------", "--------");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		f = readFromFlightsFile(fPtr);
		if(f.flightNum != 0)
		{		
			/*
			printf("\n%-9d%-8d%d/%d/%-7d%d:%-4d%-14s$%-7d$%-9d%d\n",
			f.flightNum, f.planeId, f.deptDay, f.deptMon, f.deptYr,
			f.deptTimeHour, f.deptTimeMin, trim(f.dest, 11), 
			f.ticketPrice[0], f.ticketPrice[1], 
			f.milesToTravel);	
			*/
			printf("\n%-9d", f.flightNum);
			printf("%-8d", f.planeId);
			printf("%d/", f.deptDay);
			printf("%d/", f.deptMon);
			printf("%-7d", f.deptYr);
			printf("%d:", f.deptHour);
			printf("%-4d", f.deptMin);
			printf("%-14s", trim(f.dest, 11));
			printf("$%-7d", f.ticketPrice[0]);
			printf("$%-9d", f.ticketPrice[1]);
			printf("%d", f.milesToTravel);
		}		
	}
	
	printf("\n\n");
}

void moveFlightsCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Flight)), SEEK_SET);
}

Flight readFromFlightsFile(FILE *fPtr)
{
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	fread(&f, sizeof(Flight), 1, fPtr);
	return f;
}

void writeToFlightsSeqFile(FILE *fPtr, Flight f)
{
	fprintf(fPtr, "%d, %d, %s, %d:%d, %d/%d/%d, %s, %d, %d, %d\n",
        f.flightNum, f.planeId, f.deptDayName, f.deptHour, 
		f.deptMin, f.deptDay, f.deptMon, f.deptYr, f.dest, 
		f.ticketPrice[0], f.ticketPrice[1], f.milesToTravel); 
}

void writeToFlightsFile(FILE *fPtr, Flight f)
{
	fwrite(&f, sizeof(Flight), 1, fPtr);
}

void textFlightsFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	
	if( (writePtr = fopen("flights.txt", "w")) == NULL )
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			f = readFromFlightsFile(readPtr);
			if(f.flightNum != 0)
			{
				writeToFlightsSeqFile(writePtr, f);
			}
		}
		fclose(writePtr);
	}
}

Flight updateFlightRecord(FILE *fPtr)
{
	int num;
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	
	printf("Enter Flight number to update: ");
	scanf("%d", &num);
	
	moveFlightsCursor(fPtr, num);
	f = readFromFlightsFile(fPtr);
	if(f.flightNum == 0)
	{
		printf("No flight record found with flight number, \"%d\".", num);
	}
	else
	{
		printFlightDetails(f);
		f = promptFlightDetails();		
		moveFlightsCursor(fPtr, num);
		writeToFlightsFile(fPtr, f);		
		//printf("\nUpdate successful.\n");
	}
	return f;
}

Flight deleteFlightRecord(FILE *fPtr)
{
	Flight f;
	Flight emptyFlight = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	int num;
	
	printf("Enter Flight number to delete: ");
	scanf("%d", &num);
	
	moveFlightsCursor(fPtr, num);
	f = readFromFlightsFile(fPtr);
	if(f.flightNum == 0)
	{
		printf("No flight record with flight number, %d.", num);
	}
	else
	{
		moveFlightsCursor(fPtr, num);
		writeToFlightsFile(fPtr, emptyFlight);
		//printf("\nDelete successful.\n");
	}
	return f;
}

Flight newFlightRecord(FILE *fPtr)
{
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	
	int id;
	
	printf("Enter Flight Number: ");
	scanf("%d", &id);
	
	moveFlightsCursor(fPtr, id);
	f = readFromFlightsFile(fPtr);
	
	if(f.flightNum != 0)
	{
		printf("Flight with ID \"%d\" contains information.\n", f.flightNum);
	}
	else
	{		
		f = promptFlightDetails();	
		f.flightNum = id;
		moveFlightsCursor(fPtr, id);
		writeToFlightsFile(fPtr, f);
		//printf("\nInsertion successful.\n");
	}	
	return f;
}

Flight fetchFlight(int flightNum)
{
	FILE *fPtr;
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	if((fPtr = fopen("flights.dat", "rb")) == NULL)
	{
		return f;
	}
	else
	{
		moveFlightsCursor(fPtr, flightNum);
		f = readFromFlightsFile(fPtr);
	}
	return f;
}



