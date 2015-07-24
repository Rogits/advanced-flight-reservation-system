void insertCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c);
void updateCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c1, Customer c2);
void searchCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c);
CustomerTreeNodePtr findCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c);

int equalCustomer(Customer c1, Customer c2);
int lessThanCustomer(Customer c1, Customer c2);
int moreThanCustomer(Customer c1, Customer c2);

void populateCustomersTree(CustomerTreeNodePtr *sPtr);
void repopulateCustomersTree(CustomerTreeNodePtr *sPtr);

int promptCustomerInstructions();

void processCustomersTree(CustomerTreeNodePtr rootPtr); 

void processCustomersTree(CustomerTreeNodePtr rootPtr)
{
	FILE *fPtr;
	CustomerTreeNodePtr tempPtr = NULL;
	Customer c = {0, "", "", "", 0,0,0, 0,0,0, ""};
	int choice;
	int input;
	
	if((fPtr = fopen("customers.dat", "rb+")) == NULL)
	{
		if((fPtr = fopen("customers.dat", "wb")) == NULL)
		{
			printf("\nFile could not be opened.\n\n");
		}
		else
		{
			printf("\nNew file created.\n");
		}
	}
	else
	{
		populateCustomersTree(&rootPtr);
		
		while((choice = promptCustomerInstructions()) != 0)
		{
			switch(choice)
			{
				case 1:
					textCustomersFile(fPtr);
					break;
				case 2:					
					c = newCustomerRecord(fPtr);
					if(c.id > 0)
					{						
						insertCustomerTreeNode(&rootPtr, c);
					}
					break;
				case 3:					
					c = updateCustomerRecord(fPtr);
					if(c.id > 0)
					{
						if((tempPtr = findCustomerTreeNode(&rootPtr, c)) != NULL)
						{						
							updateCustomerTreeNode(&rootPtr, tempPtr->data, c);
						}						
					}
					break;
				case 4:				
					c = deleteCustomerRecord(fPtr);
					if(c.id > 0)
					{
						repopulateCustomersTree(&rootPtr);
					}
					break;
				case 5:
					printf("\nEnter Customer ID to be searched: ");
					scanf("\n%d", &input);
					c.id = input;
					searchCustomerTreeNode(&rootPtr, c);
					break;
				case 6:
					printAllCustomers(fPtr);
					break;
				default:
					printf("Incorrect choice.\n");
					break;				
			}
		}
		
		fclose(fPtr);
	}
}

void insertCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c)
{
	if(*treePtr == NULL)
	{
		*treePtr = malloc(sizeof(CustomerTreeNode));
		if(*treePtr != NULL)
		{
			(*treePtr)->data = c;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else
		{
			printf(
			"Customer with ID %d not inserted. No memory available.\n",
				c.id);
		}		
	}
	else
	{
		if(lessThanCustomer(c, (*treePtr)->data) == 1)
		{
			insertCustomerTreeNode(&((*treePtr)->leftPtr), c);
		}
		else if(moreThanCustomer(c, (*treePtr)->data) == 1)
		{
			insertCustomerTreeNode(&((*treePtr)->rightPtr), c);
		}		
	}
}

void updateCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c1,
 Customer c2)
{
	CustomerTreeNodePtr tempLeftPtr;
	CustomerTreeNodePtr tempRightPtr;
	
	if(*treePtr != NULL)
	{		
		if(equalCustomer((*treePtr)->data, c1) == 1)
		{			
			tempLeftPtr = (*treePtr)->leftPtr;
			tempRightPtr = (*treePtr)->rightPtr;
			
			if(tempLeftPtr == NULL && tempRightPtr == NULL)
			{
				(*treePtr)->data = c2;
				printf("\nUpdate successful.\n");
				return;
			}
			else if(lessThanCustomer(c1, tempLeftPtr->data) == 1 &&
					tempRightPtr == NULL)
			{
				(*treePtr)->data = c2;		
				printf("\nUpdate successful.\n");
				return;
			}
			else if(tempLeftPtr == NULL && 
					moreThanCustomer(c1, tempRightPtr->data) == 1)
			{
				(*treePtr)->data = c2;
				printf("\nUpdate successful.\n");
				return;
			}		
			else if(lessThanCustomer(c1, tempLeftPtr->data) == 1 && 
					moreThanCustomer(c1, tempRightPtr->data) == 1 ) 
			{
				(*treePtr)->data = c2;	
				printf("\nUpdate successful.\n");
				return;
			}
			else
			{
				printf("\nUpdate unsuccessful.\n");
				return;
			}
		}			
		
		if(lessThanCustomer(c1, (*treePtr)->data) == 1)
		{
			updateCustomerTreeNode(&((*treePtr)->leftPtr), c1, c2);
		}
		else if(moreThanCustomer(c1, (*treePtr)->data) == 1)
		{
			updateCustomerTreeNode(&((*treePtr)->rightPtr), c1, c2);
		}
		else
		{
			printf("\nUpdate unsuccessful.\n");
			return;
		}		
	}
	else
	{
		printf("\nUpdate unsuccessful.\n");
		return;
	}
}

void searchCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c)
{	
	if(*treePtr != NULL)
	{		
		if(equalCustomer((*treePtr)->data, c) == 1)
		{
			printf("\nCustomer with ID %d was found.\n", c.id);
			return;
		}			
		
		if(lessThanCustomer(c, (*treePtr)->data) == 1)
		{
			searchCustomerTreeNode(&((*treePtr)->leftPtr), c);
		}
		else if(moreThanCustomer(c, (*treePtr)->data) == 1)
		{
			searchCustomerTreeNode(&((*treePtr)->rightPtr), c);
		}
	}
	else
	{
		printf("\nCustomer with ID %d was not found.\n", c.id);
		return;
	}
}

CustomerTreeNodePtr findCustomerTreeNode(CustomerTreeNodePtr *treePtr, Customer c)
{
	if(*treePtr != NULL)
	{		
		if(equalCustomer((*treePtr)->data, c) == 1)
		{
			return *treePtr;
		}		
		else if(lessThanCustomer(c, (*treePtr)->data) == 1)
		{
			findCustomerTreeNode(&((*treePtr)->leftPtr), c);
		}
		else if(moreThanCustomer(c, (*treePtr)->data) == 1)
		{
			findCustomerTreeNode(&((*treePtr)->rightPtr), c);
		}
	}
	else
	{
		return NULL;
	}
}

int equalCustomer(Customer c1, Customer c2)
{
	return c1.id == c2.id ? 1:0;
}

int moreThanCustomer(Customer c1, Customer c2)
{
	return c1.id > c2.id ? 1:0;
}

int lessThanCustomer(Customer c1, Customer c2)
{
	return c1.id < c2.id ? 1:0;
}

void populateCustomersTree(CustomerTreeNodePtr *sPtr)
{
	FILE *fPtr;
	
	if((fPtr = fopen("customers.dat", "rb")) == NULL)
	{		
		printf("File could not be opened.\n");		
	}
	else
	{
		Customer c = {0, "", "", "", 0, 0, 0, 0, 0, 0, ""};
		rewind(fPtr);
		while(!feof(fPtr))
		{
			c = readFromCustomersFile(fPtr);
			if(c.id > 0)
			{		
				insertCustomerTreeNode(sPtr, c);
			}			
		}
		fclose(fPtr);
	}
}

void repopulateCustomersTree(CustomerTreeNodePtr *sPtr)
{
	FILE *fPtr;
	CustomerTreeNodePtr tempPtr;

	if((fPtr = fopen("customers.dat", "rb")) == NULL)
	{		
		printf("File could not be opened.\n");		
	}
	else
	{
		Customer c = {0, "", "", "", 0, 0, 0, 0, 0, 0, ""};
		/* read from file and populate list */
		rewind(fPtr);
		while(!feof(fPtr))
		{
			c = readFromCustomersFile(fPtr);
			if(c.id > 0)
			{		
				if((tempPtr = findCustomerTreeNode(sPtr, c)) == NULL)
				{
					insertCustomerTreeNode(sPtr, c);
				}
				else
				{
					updateCustomerTreeNode(sPtr, tempPtr->data, c);
				}
			}			
		}
		fclose(fPtr);
	}
}

int promptCustomerInstructions()
{
	int option;
	printf("\n\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s",
	"Please choose an option below to proceed.", 
	"1 - Create a text file for printing all records.",
	"2 - Create and save a new customer record.",
	"3 - Update an existing customer record.",
	"4 - Delete an existing customer record.", 
	"5 - Search an existing customer record.",
	"6 - View all customer records.", 
	"0 - Exit.",
	"Enter option: ");
	scanf("%d", &option);
	
	return option;	
}


