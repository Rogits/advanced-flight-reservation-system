#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "customer.h"

typedef struct customer Customer;

#include "date.h"
#include "util.h"
#include "customers.h"
#include "customerTreeNode.h"

typedef struct customerTreeNode CustomerTreeNode;
typedef CustomerTreeNode *CustomerTreeNodePtr;

#include "customerTreeNodes.h"

#include "airport.h"

typedef struct airport Airport;

#include "airports.h"
#include "airportListNode.h"

typedef struct airportListNode AirportListNode;
typedef AirportListNode *AirportListNodePtr;

#include "airportListNodes.h"


#include "plane.h"

typedef struct plane Plane;

#include "planes.h"
#include "planeListNode.h"

typedef struct planeListNode PlaneListNode;
typedef PlaneListNode *PlaneListNodePtr;

#include "planeListNodes.h"

#include "ticket.h"

typedef struct ticket Ticket;

#include "flight.h"

typedef struct flight Flight;

#include "flights.h"

#include "offer.h"

typedef struct offer Offer;

#include "offers.h"

#include "tickets.h"

typedef Ticket Passenger;

#include "passengerTreeNode.h"

typedef struct passengerTreeNode PassengerTreeNode;
typedef PassengerTreeNode *PassengerTreeNodePtr;

#include "flightListNode.h"

typedef struct flightListNode FlightListNode;
typedef FlightListNode *FlightListNodePtr;

#include "flightListNodes.h"

#include "passengerQueueNode.h"

typedef struct passengerQueueNode PassengerQueueNode;
typedef PassengerQueueNode *PassengerQueueNodePtr;

#include "passengerQueueNodes.h"

#include "passengerTreeNodes.h"

void processMainInstructions();
int promptMainInstructions();
void printArt();
void printHeader();

int main()
{
	printArt();
	printHeader();
	processMainInstructions();
	
	return 0;
}

void processMainInstructions()
{	
	AirportListNodePtr rootAirportListNodePtr = NULL;
	CustomerTreeNodePtr rootCustomerTreeNodePtr = NULL;
	PlaneListNodePtr rootPlaneListNodePtr = NULL;
	FlightListNodePtr rootFlightListNodePtr = NULL;
	PassengerTreeNodePtr rootPassengerTreeNodePtr = NULL;
	PassengerQueueNodePtr headPassengerQueueNodePtr = NULL;
	PassengerQueueNodePtr tailPassengerQueueNodePtr = NULL;
	int choice;
	
	while((choice = promptMainInstructions()) != 0)
	{
		switch(choice)
		{
			case 1:
				processAirportsList(rootAirportListNodePtr);
				break;
			case 2:
				processCustomersTree(rootCustomerTreeNodePtr);
				break;
			case 3:
				processPlanesList(rootPlaneListNodePtr, rootAirportListNodePtr);
				break;
			case 4:
				processFlightsList(rootFlightListNodePtr);
				break;
			case 5:
				processPassengersTree(rootPassengerTreeNodePtr,
				headPassengerQueueNodePtr, tailPassengerQueueNodePtr);
				break;			
			case 6:
				processOffers();
				break;
			default:
				printf("\nInvalid choice.\n");
				break;
		}
	}
}

int promptMainInstructions()
{
	int input;
	printf("\n\n%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s", 
	"Please choose an option below to proceed.", 
	"1 - To process Airports.", 
	"2 - To process Customers.",
	"3 - To process Planes.",
	"4 - To process Flights.",
	"5 - To process Passengers.",
	"6 - To process Offers.",
	"0 - To exit.",
	"Enter your option: ");
	scanf("%d", &input);
	
	return input;
}

void printArt()
{
	printf("\n\n\n");	
	
	printf("\n Your Company Logo goes here \n");
	printf("\n\n");
}

void printHeader()
{
	printf("\nWelcome to Beirut Flight Reservation System.\n");
}
