struct flight 
{
	int flightNum; 
	int planeId; 
	int deptDay; 
	int deptMon; 
	int deptYr; 
	int deptHour; 
	int deptMin; 
	char deptDayName[20]; 
	char dest[30]; 
	int ticketPrice[2]; 
	int milesToTravel; /* get from airport class */
};
