int promptOfferInstructions();
Offer promptOfferDetails();
void printOfferDetails(Offer o);
void printAllOffers(FILE *fPtr);

void moveOffersCursor(FILE *fPtr, int pos);
Offer readFromOffersFile(FILE *fPtr);
void writeToOffersSeqFile(FILE *fPtr, Offer o);
void writeToOffersFile(FILE *fPtr, Offer o);

void textOffersFile(FILE *fPtr);
void newOfferRecord(FILE *fPtr);
void updateOfferRecord(FILE *fPtr);
void deleteOfferRecord(FILE *fPtr);

void processOffers();

int checkOffersForCustomer(Customer c);
Offer getOfferForCustomer(Customer c);

void processOffers()
{
	FILE *fPtr;
	int choice = 0;
	
	if((fPtr = fopen("offers.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("offers.dat", "wb")) == NULL)
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
		while((choice = promptOfferInstructions()) != 0)
		{
			switch(choice)
			{
				case 1:
					textOffersFile(fPtr);
					break;
				case 2:
					newOfferRecord(fPtr);
					break;
				case 3:
					updateOfferRecord(fPtr);
					break;
				case 4:
					deleteOfferRecord(fPtr);
					break;
				case 5:
					printAllOffers(fPtr);
					break;
				default:
					printf("Incorrect choice.\n");
					break;				
			}
		}
		
		fclose(fPtr);
		printf("\nExiting...\n");		
	}
}

int promptOfferInstructions()
{
	int option;
	printf("\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an option below to proceed.", 
	"1 - Create a text file for printing all records.",
	"2 - Create and save a new offer record.",
	"3 - Update an existing offer record.",
	"4 - Delete an existing offer record.", 
	"5 - View all offer records.", 
	"0 - Exit.",
	"Enter option: ");
	scanf("%d", &option);
	
	return option;	
}

Offer promptOfferDetails()
{
	Offer client = {0, 0, "", 0, 0, 0};
	printf("\nPlease enter offer details below.");
	printf("\nEnter Flight Number: ");
	fscanf( stdin, "%d", &client.flightNum);
	/* counter check from existing records */
	printf("\nEnter Offer Type: ");
	fscanf(stdin, "%s", client.offerType);
	printf("\nEnter Discount Amount: ");
	fscanf( stdin, "%d", &client.discountAmount);
	printf("\nEnter Mileage to be given Offer: ");
	fscanf( stdin, "%d", &client.milesOffer);
	printf("\nEnter Number of Flights traveled to be given Offer: ");
	fscanf( stdin, "%d", &client.flightsOffer);
		
	return client;
}

void printOfferDetails(Offer client)
{
	printf("\nID: %d", client.offerId);
	printf("\nFlight Number: %d", client.flightNum);
	printf("\nOffer Type: %s", client.offerType);
	printf("\nDiscount Amount: $%d", client.discountAmount);
	printf("\nMileage: %d", client.milesOffer);
	printf("\nFlights: %d", client.flightsOffer);
	
	printf("\n");
}

void printAllOffers(FILE *fPtr)
{
	Offer client = {0, 0, "", 0, 0, 0};
		
	printf("\n%-5s%-13s%-13s%-21s%-10s%s\n", 
	"ID", "Flight No.", "Offer Type", "Discount Amount($)", 	
	"Flights", "Mileage" );
	/* print underline */
	printf("%-5s%-13s%-13s%-21s%-10s%s\n",
	"--", "----------", "----------", "------------------",
	"-------", "-------");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		client = readFromOffersFile(fPtr);
		if(client.offerId != 0)
		{
			printf("%-5d%-13d%-13s%-21d%-10d%d\n",
			client.offerId, client.flightNum, 
			client.offerType, client.discountAmount, 
			client.milesOffer, client.flightsOffer);
		}		
	}
	
	printf("\n\n");
}

void moveOffersCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Offer)), SEEK_SET);
}

Offer readFromOffersFile(FILE *fPtr)
{
	Offer client = {0, 0, "", 0, 0, 0};
	fread(&client, sizeof(Offer), 1, fPtr);
	return client;
}

void writeToOffersSeqFile(FILE *fPtr, Offer client)
{
	fprintf(fPtr, "%d, %d, %s, $%d, %d, %d\n",
        client.offerId, client.flightNum, client.offerType, 
		client.discountAmount, client.milesOffer, 
		client.flightsOffer); 
}

void writeToOffersFile(FILE *fPtr, Offer client)
{
	fwrite(&client, sizeof(Offer), 1, fPtr);
	//printf("\nWriting successful.\n");
}

void textOffersFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Offer client = {0, 0, "", 0, 0, 0};
	
	if( (writePtr = fopen("offers.txt", "w")) == NULL )
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			client = readFromOffersFile(readPtr);
			if(client.offerId != 0)
			{
				writeToOffersSeqFile(writePtr, client);
			}
		}
		fclose(writePtr);
	}
}

void updateOfferRecord(FILE *fPtr)
{
	int id;
	Offer client = {0, 0, "", 0, 0, 0};
	
	printf("Enter ID to update: ");
	scanf("%d", &id);
	
	moveOffersCursor(fPtr, id);
	client = readFromOffersFile(fPtr);
	if(client.offerId == 0)
	{
		printf("No Offer record found with ID, \"%d\".", id);
	}
	else
	{
		printOfferDetails(client);
		client = promptOfferDetails();
		client.offerId = id;
		moveOffersCursor(fPtr, client.offerId);
		writeToOffersFile(fPtr, client);		
		printf("\nUpdate successful.\n");
	}
}

void deleteOfferRecord(FILE *fPtr)
{
	Offer client;
	Offer blankClient = {0, 0, "", 0, 0, 0};
	int id;
	
	printf("Enter ID to delete: ");
	scanf("%d", &id);
	
	moveOffersCursor(fPtr, id);
	client = readFromOffersFile(fPtr);
	if(client.offerId == 0)
	{
		printf("No Offer record for ID, %d.", id);
	}
	else
	{
		moveOffersCursor(fPtr, id);
		writeToOffersFile(fPtr, blankClient);
		printf("\nDelete successful.\n");
	}
}

void newOfferRecord(FILE *fPtr)
{
	Offer client = {0, 0, "", 0, 0, 0};
	int id;
	
	printf("Enter new ID: ");
	scanf("%d", &id);
	
	moveOffersCursor(fPtr, id);
	client = readFromOffersFile(fPtr);
	
	if(client.offerId != 0)
	{
		printf("Offer with ID \"%d\" contains information.\n", id);
	}
	else
	{
		client = promptOfferDetails();
		client.offerId = id;
		moveOffersCursor(fPtr, id);
		writeToOffersFile(fPtr, client);
		printf("\nInsertion successful.\n");
	}	
}

int checkOffersForCustomer(Customer c)
{
	FILE *fPtr;
	Offer client = {0, 0, "", 0, 0, 0};
	if(c.id != 0)
	{
		if((fPtr = fopen("offers.dat", "rb")) == NULL)
		{			
			return 0;
		}
		else
		{
			rewind(fPtr);
			while(!feof(fPtr))
			{
				client = readFromOffersFile(fPtr);
				if(client.offerId != 0)
				{
					if(client.milesOffer <= c.miles &&
					   client.flightsOffer <= c.flights)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

Offer getOfferForCustomer(Customer c)
{
	FILE *fPtr;
	Offer client = {0, 0, "", 0, 0, 0};
	if(c.id != 0)
	{
		if((fPtr = fopen("offers.dat", "rb")) == NULL)
		{			
			return client;
		}
		else
		{
			rewind(fPtr);
			while(!feof(fPtr))
			{
				client = readFromOffersFile(fPtr);
				if(client.offerId != 0)
				{
					if(client.milesOffer <= c.miles &&
					   client.flightsOffer <= c.flights)
					{
						return client;
					}
				}
			}
		}
	}
	return client;
}


