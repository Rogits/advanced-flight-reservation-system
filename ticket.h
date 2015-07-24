struct ticket
{
	int ticketNum;
	int customerId;
	char names[40];
	int flightNum;
	char ticketType[15];
	int costOfFlight;
	int discount; /* boolean value 0 or 1 */
	char reasonForDiscount[100]; 
	int deptDay;
	int deptMon;
	int deptYr;
	int deptHour;
	int deptMin;
	int seatNum;
};
