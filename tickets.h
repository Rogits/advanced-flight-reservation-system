int promptTicketInstructions();
int promptTicketUpdateInstructions();
Ticket promptTicketDetails();
void printTicketDetails(Ticket t);
void printAllTickets(FILE *fPtr);

void moveTicketsCursor(FILE *fPtr, int pos);
Ticket readFromTicketsFile(FILE *fPtr);
void writeToTicketsSeqFile(FILE *fPtr, Ticket t);
void writeToTicketsFile(FILE *fPtr, Ticket t);

void textTicketsFile(FILE *fPtr);
Ticket newTicketRecord(FILE *fPtr);
Ticket updateTicketRecord(FILE *fPtr);
Ticket deleteTicketRecord(FILE *fPtr);

Ticket promptTicketDetails()
{
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};	
	Customer c = {0, "", "", "", 0,0,0, 0,0,0, ""};
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	Plane p = {0, 0, "", 0, {0}, {0}};
	Airport a = {0, "", "", "", 0, 0, {0}};
	Offer o =  {0, 0, "", 0, 0, 0};
	FILE *readPtr, *writePtr; 
	
	printf("\n%s", "Enter customer ID: ");
	scanf("%d", &t.customerId);	
	c = fetchCustomer(t.customerId);
	if(c.id == 0)
	{
		printf("\n\nCustomer ID %d does not exist.\n%s\n\n", 
		t.customerId,
		"So the system will try to create it.");
		// create a new customer record
		c = createCustomer();		
		printf("\nEnter customer ID again: ");
		scanf("%d", &t.customerId);
		c = fetchCustomer(t.customerId);		
	}
	
	strcpy(t.names, concat(concat(c.fname, " "), c.lname));	
	int customerMileage = c.miles;
	int customerNumOfFlights = c.flights;	
	
	printf("\nEnter flight number: ");
	scanf("%d", &t.flightNum);	
	f = fetchFlight(t.flightNum);
	if(f.flightNum == 0)
	{
		return t;
	}
	p = fetchPlane(f.planeId);
	a = fetchAirport(p.airportId);
	int flightDistance = a.milesFromBeirut;
	customerMileage += flightDistance;
	customerNumOfFlights += 1;
	updateCustomerMileage(c, customerMileage );	
	updateCustomerNumOfFlights(c, customerNumOfFlights);
		
	t.deptDay = f.deptDay;
	t.deptMon = f.deptMon;
	t.deptYr = f.deptYr;
	t.deptHour = f.deptHour;
	t.deptMin = f.deptMin;
		
	if(isPlaneFull(p))
	{
		return t;
	}
	else
	{
		printf("\n%s", "Enter seat number: ");
		scanf("%d", &t.seatNum);
		int flightClass;
		if(checkSeatNumber(p, t.seatNum) == 1)
		{
			flightClass = getSeatNumberClass(p, t.seatNum);
			strcpy(t.ticketType,
				(flightClass == 0 ? "First" : "Second"));		
			t.costOfFlight = f.ticketPrice[flightClass];	
		}
		else
		{
			t.seatNum = reserveSeat(p, t.seatNum);
			flightClass = getSeatNumberClass(p, t.seatNum);
			strcpy(t.ticketType, 
				(flightClass == 0 ? "First" : "Second"));
			t.costOfFlight = f.ticketPrice[flightClass];
		}
	}
	char charinput;
	printf("\nIs ticket for discount(Y/N): ");
	scanf("\n");
	scanf("%c", &charinput);	
	t.discount = matchCharacter(charinput, 'Y');	
	if(t.discount == 1 && checkOffersForCustomer(c) == 1)
	{
		printf("\nEnter reason for discount: ");
		scanf("\n");
		fgets(t.reasonForDiscount, sizeof(t.reasonForDiscount), stdin);
		o = getOfferForCustomer(c);
		strcpy(t.reasonForDiscount, 
			concat("\n\nOffer Type: ", o.offerType));
	}	
	
	return t;
}

void printTicketDetails(Ticket t)
{
	printf("\n\n%s%d\n", "Ticket ID: ", t.ticketNum);
	printf("\n%s%d\n", "Customer ID: ", t.customerId);
	printf("\n%s%s\n", "Customer names: ", t.names);
	printf("\n%s%d\n", "Flight number: ", t.flightNum);
	printf("\n%s%s\n", "Ticket type: ", t.ticketType);
	printf("\n%s%d\n", "Cost of flight: ", t.costOfFlight);
	printf("\n%s%s\n", "Ticket for discount: ", 
	(t.discount == 1 ? concat("Yes.\n\n", t.reasonForDiscount) : "No."));
	printf("\n%s%s\n", "Departure: ", 
	getFullDateAndTime(getDateAndTime(t.deptDay, t.deptMon, t.deptYr,
									  t.deptHour, t.deptMin, 0)) );
	printf("\n%s%d\n\n", "Seat number: ", t.seatNum);
}

void printAllTickets(FILE *fPtr)
{
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
		
	printf("\n\n%-6s%-6s%-9s%-10s%-9s%-10s%-10s%-11s%s\n", 
	"No.", "ID", "Name", "Flight", "Class",
	"Cost($)", "Discount", "Departure", "Seat No." );
	printf("%-6s%-6s%-9s%-10s%-9s%-10s%-10s%-11s%s\n",
	"---", "--", "----", "------", "-----", 
	"-------", "--------", "---------", "--------");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		t = readFromTicketsFile(fPtr);
		if(t.ticketNum != 0)
		{						
			printf("%-6d%-6d%-9s%-10d%-9s%-10d%-10s%d/%d/%-5d%d\n",
			t.ticketNum,
			t.customerId,
			concat(concat(trim(extractTo(t.names, ' '), 1), "."),
				extract(t.names, ' ', 4)), 
			t.flightNum, t.ticketType, 
			t.costOfFlight, (t.discount == 1 ? "Yes" : "No"),
			t.deptDay, t.deptMon, t.deptYr, t.seatNum);			
		}
	}	
}

void moveTicketsCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Ticket)), SEEK_SET);
}

Ticket readFromTicketsFile(FILE *fPtr)
{
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	fread(&t, sizeof(Ticket), 1, fPtr);
	return t;
}

void writeToTicketsSeqFile(FILE *fPtr, Ticket t)
{
	fprintf(fPtr, "%d, %d, %s, %d, %s, %d, %s, %d/%d/%d, %d",
	t.ticketNum, t.customerId, t.names, t.flightNum, 
	t.ticketType, t.costOfFlight, (t.discount == 1 ? "Yes": "No"),
	t.deptDay, t.deptMon, t.deptYr, t.seatNum);
}

void writeToTicketsFile(FILE *fPtr, Ticket t)
{
	fwrite(&t, sizeof(Ticket), 1, fPtr);
}

void textTicketsFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	if((writePtr = fopen("planes.txt", "w")) == NULL )
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			t = readFromTicketsFile(readPtr);
			if(t.ticketNum != 0)
			{
				writeToTicketsSeqFile(writePtr, t);
			}
		}
		fclose(writePtr);
	}
}


Ticket updateTicketRecord(FILE *fPtr)
{
	int id;
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	char * opt;
	
	printf("Enter ticket number to update: ");
	scanf("%d", &id);
	
	moveTicketsCursor(fPtr, id);
	t = readFromTicketsFile(fPtr);
	if(t.ticketNum == 0 )
	{		
		printf("No ticket record found with ID, \"%d\".", id);
		return t;
	}
	else
	{		
		printTicketDetails(t);
		int choice;
		while((choice = promptTicketUpdateInstructions()) !=0)
		{
			switch(choice)
			{
				case 1:
					printf("\n\n");
					t = promptTicketDetails();		
					if(t.seatNum != 0)					
					{
						moveTicketsCursor(fPtr, id);
						writeToTicketsFile(fPtr, t);		
						printf("\nUpdate successful.\n");
					}
					break;
				case 2:					
					printf("\n\n");
					t = promptTicketDetails();		
					if(t.flightNum != 0)					
					{
						moveTicketsCursor(fPtr, id);
						writeToTicketsFile(fPtr, t);		
						printf("\nUpdate successful.\n");
					}
					break;
				case 3:					
					printf("\nDo you wish to cancel your reservation(Yes/No): ");
					scanf("\n%s", opt);
					if(matchString(opt, "Yes", 3) == 1)
					{	
						deleteTicketRecord(fPtr);
						printf("\nReservation canceled.\n");
					}
					else
					{
						printf("\nReservation preserved.\n");
					}
					break;
				default:
					printf("\nInvalid choice.\n");
					break;
			}		
		}		
	}
	return t;
}

Ticket deleteTicketRecord(FILE *fPtr)
{
	Ticket t;
	Ticket blankTicket = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	Customer c = {0, "", "", "", 0,0,0, 0,0,0, ""};
	Flight f = {0, 0, 0, 0, 0, 0, 0, "", "", {0}, 0};
	Plane p = {0, 0, "", 0, {0}, {0}};
	Airport a = {0, "", "", "", 0, 0, {0}};
	int id;
	
	printf("Enter ticket number to delete: ");
	scanf("%d", &id);
	
	moveTicketsCursor(fPtr, id);
	t = readFromTicketsFile(fPtr);
	if(t.ticketNum == 0)
	{
		printf("No ticket record for ID, %d.", id);
		return t;
	}
	else
	{		
		c = fetchCustomer(t.customerId);
		f = fetchFlight(t.flightNum);
		p = fetchPlane(f.planeId);
		a = fetchAirport(p.airportId);
		int flightDistance, flightCount, newCustomerMileage, newCustomerFlightCount;
		flightDistance = a.milesFromBeirut;
		flightCount = c.flights;
		newCustomerMileage = c.miles - flightDistance;
		newCustomerFlightCount = flightCount - 1;
		updateCustomerMileage(c, newCustomerMileage);
		updateCustomerNumOfFlights(c, newCustomerFlightCount);
		if(unreserveSeat(p, t.seatNum) == 1)
		{
			moveTicketsCursor(fPtr, id);
			writeToTicketsFile(fPtr, blankTicket);
			printf("\nDelete successful.\n");
		}
		else
		{
			printf("\nFailed to cancel reservation.\n");
		}
	}
	return t;
}

Ticket newTicketRecord(FILE *fPtr)
{
	Ticket t = {0, 0, "", 0, "", 0, 0, "", 0, 0, 0, 0, 0, 0};
	Ticket temp = t;
	int id;
	
	printf("Enter new ticket number: ");
	scanf("%d", &id);
	
	moveTicketsCursor(fPtr, id);
	t = readFromTicketsFile(fPtr);

	if(t.ticketNum != 0)
	{
		printf("Ticket record with ID \"%d\" contains information.\n", id);
		return temp;
	}	
	else
	{
		t = promptTicketDetails();	
		if(t.flightNum != 0 || t.seatNum != 0)
		{			
			t.ticketNum = id;
			moveTicketsCursor(fPtr, t.ticketNum);
			writeToTicketsFile(fPtr, t);
			printf("\nInsertion successful.\n");	
		}		
	}	
	return t;
}

int promptTicketUpdateInstructions()
{
	int input;
	printf("\n\n%s\n%s\n%s\n%s\n%s\n\n%s", 
	"Please choose an option below.", 
	"1 - Change reservation from seat to seat.", 
	"2 - Change reservation from flight to flight.", 
	"3 - Cancel reservation.", 
	"0 - Exit.", 
	"Enter your option: ");
	scanf("%d", &input);
	
	return input;
}






	