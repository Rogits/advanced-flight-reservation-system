Customer promptCustomerDetails();
void printCustomerDetails(Customer client);
void moveCustomersCursor(FILE *fPtr, int pos);
Customer readFromCustomersFile(FILE *fPtr);
void writeToCustomersFile(FILE *fPtr, Customer client);
void writeToCustomersSeqFile(FILE *fPtr, Customer client);

void printAllCustomers(FILE *fPtr);

void textCustomersFile(FILE *fPtr);
Customer newCustomerRecord(FILE *fPtr);
Customer updateCustomerRecord(FILE *fPtr);
Customer deleteCustomerRecord(FILE *fPtr);

Customer fetchCustomer(int customerId);
Customer createCustomer();
void updateCustomerMileage(Customer c, int miles);
void updateCustomerNumOfFlights(Customer c, int flights);

Customer promptCustomerDetails()
{
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
	printf("\nPlease enter customer details below.");
	printf("\nEnter First name: ");
	fscanf( stdin, "%s", client.fname);
	printf("\nEnter Last name: ");
	fscanf(stdin, "%s", client.lname);
	printf("\nEnter Day of Birth: ");
	fscanf( stdin, "%d", &client.d);
	printf("\nEnter Month of Birth: ");
	fscanf( stdin, "%d", &client.m);
	printf("\nEnter Year of Birth: ");
	fscanf( stdin, "%d", &client.y);
	printf("\nEnter Country: ");
	fscanf( stdin, "%s", client.country);
	printf("\nEnter Phone: ");
	fscanf( stdin, "%d", &client.phone);
	printf("\nEnter Country Code(+XXX): ");
	fscanf( stdin, "%s", &client.ccode);
	
	return client;
}

void printCustomerDetails(Customer client)
{
	printf("\nID: %d", client.id);
	printf("\nFirst Name: %s", client.fname);
	printf("\nLast Name: %s", client.lname);
	printf("\nDate of Birth: %s", 
	getFormattedDate(getDate(client.d, client.m, client.y), "%a, %B %Y")
	/* %d/%d/%d - client.d, client.m, client.y*/);
	printf("\nCountry: %s", client.country);
	printf("\nPhone: %s %d", client.ccode, client.phone);
	printf("\nFlights: %d", client.flights);
	printf("\nMiles: %d", client.miles);
	printf("\n");
}

void moveCustomersCursor(FILE *fPtr, int pos)
{
	fseek(fPtr, ((pos - 1) * sizeof(Customer)), SEEK_SET);
}

Customer readFromCustomersFile(FILE *fPtr)
{
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
	fread(&client, sizeof(Customer), 1, fPtr);
	return client;
}

void writeToCustomersFile(FILE *fPtr, Customer client)
{
	fwrite(&client, sizeof(Customer), 1, fPtr);
}

void writeToCustomersSeqFile(FILE *fPtr, Customer client)
{
	fprintf(fPtr, "%d, %s %s, %d/%d/%d, %s, %s %d, %d, %d\n",
        client.id, client.fname, client.lname, 
		client.d, client.m, client.y, client.country, 
		client.ccode, client.phone, client.flights, client.miles);	
}

void printAllCustomers(FILE *fPtr)
{
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
		
	printf("\n%-6s%-9s%-12s%-10s%-7s%19s%10s\n", 
	"ID", "Names", "DOB", "Country", "Phone",	
	"Flights", "Miles" );
	/* print underline */
	printf("%-6s%-9s%-12s%-10s%-7s%19s%10s\n",
	"--", "-----", "---", "-------", "-----", "-------", "-----");
	rewind(fPtr);
	while(!feof(fPtr))
	{
		client = readFromCustomersFile(fPtr);
		if(client.id != 0)
		{			
			printf("\n%-6d%s %-5s%2d/%2d/%-6d%-10s%s %-14d%-12d%d",
			client.id, trim(client.fname, 3),
			concat(trim(client.lname, 1), "."),
			client.d, client.m, client.y, client.country,
			client.ccode, client.phone, client.flights, client.miles
			);
		}		
	}
	
	printf("\n\n");
}

void textCustomersFile(FILE *readPtr)
{
	FILE *writePtr;
	
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
	
	if( (writePtr = fopen("customers.txt", "w")) == NULL )
	{
		printf("File could not be opened.\n");
	}
	else
	{
		rewind(readPtr);
		while(!feof(readPtr))
		{
			client = readFromCustomersFile(readPtr);
			if(client.id != 0)
			{
				writeToCustomersSeqFile(writePtr, client);
			}
		}
		fclose(writePtr);
	}
}

Customer updateCustomerRecord(FILE *fPtr)
{
	int id;
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
	
	printf("Enter ID to update: ");
	scanf("%d", &id);
	
	moveCustomersCursor(fPtr, id);
	client = readFromCustomersFile(fPtr);
	if(client.id == 0)
	{
		printf("No customer record found with ID, \"%d\".", id);
	}
	else
	{
		printCustomerDetails(client);
		client = promptCustomerDetails();
		client.id = id;
		moveCustomersCursor(fPtr, id);
		writeToCustomersFile(fPtr, client);		
		printf("\nUpdate successful.\n");
	}
	return client;
}

Customer deleteCustomerRecord(FILE *fPtr)
{
	Customer client;
	Customer blankClient = {0, "", "", "", 0,0,0, 0,0,0, ""};
	int id;
	
	printf("Enter ID to delete: ");
	scanf("%d", &id);
	
	moveCustomersCursor(fPtr, id);
	client = readFromCustomersFile(fPtr);
	if(client.id == 0)
	{
		printf("No customer record for ID, %d.", id);
	}
	else
	{
		moveCustomersCursor(fPtr, id);
		writeToCustomersFile(fPtr, blankClient);
		printf("\nDelete successful.\n");
	}
	return client;
}

Customer newCustomerRecord(FILE *fPtr)
{
	Customer client = {0, "", "", "", 0,0,0, 0,0,0, ""};
	Customer temp = client;
	int id;
	
	printf("Enter new ID: ");
	scanf("%d", &id);
	
	moveCustomersCursor(fPtr, id);
	client = readFromCustomersFile(fPtr);
	
	if(client.id != 0)
	{
		printf("Customer with ID \"%d\" contains information.\n", client.id);
		client = temp;
	}
	else
	{
		client = promptCustomerDetails();
		client.id = id;
		moveCustomersCursor(fPtr, id);
		writeToCustomersFile(fPtr, client);
		printf("\nInsertion successful.\n");
	}
	return client;
}

void updateCustomerMileage(Customer c, int miles)
{	
	FILE *fPtr;
	if((fPtr = fopen("customers.dat", "rb+")) == NULL)
	{
		printf("File could not be opened.\n");		
	}
	else
	{	
		c.miles = miles;
		moveCustomersCursor(fPtr, c.id);
		writeToCustomersFile(fPtr, c);	
		fclose(fPtr);
	}	
}

void updateCustomerNumOfFlights(Customer c, int flights)
{
	FILE *fPtr;
	if((fPtr = fopen("customers.dat", "rb+")) == NULL)
	{
		printf("File could not be opened.\n");		
	}
	else
	{	
		c.flights = flights;
		moveCustomersCursor(fPtr, c.id);
		writeToCustomersFile(fPtr, c);	
		fclose(fPtr);		
	}
}

Customer fetchCustomer(int customerId)
{
	FILE *fPtr;
	Customer c = {0, "", "", "", 0,0,0, 0,0,0, ""};
	if((fPtr = fopen("customers.dat", "rb")) == NULL)
	{
		return c;
	}
	else
	{
		moveCustomersCursor(fPtr, customerId);
		c = readFromCustomersFile(fPtr);
	}
	return c;
}

Customer createCustomer()
{
	FILE *fPtr;
	Customer c = {0, "", "", "", 0,0,0, 0,0,0, ""};
	int id;
	printf("Enter new ID: ");
	scanf("%d", &id);
	if((fPtr = fopen("customers.dat", "rb+")) == NULL)
	{
		return c;
	}
	else
	{
		moveCustomersCursor(fPtr, id);
		c = readFromCustomersFile(fPtr);
		
		if(c.id != 0)
		{			
			return c;
		}
		else
		{
			c = promptCustomerDetails();
			c.id = id;
			moveCustomersCursor(fPtr, id);
			writeToCustomersFile(fPtr, c);
			printf("\nInsertion successful.\n");
		}
	}
	return c;
}
