#define MAX_PLANES 50

struct airport
{
	int id; /* unique id */
	char airportName[50]; 
	char country[30]; 
	char usualWeather[30]; 
	int timeFromBeirut; /* time in hours to be traveled from Beirut to destination */
	int milesFromBeirut; /* distance to be traveled */
	int planes[MAX_PLANES]; /* holds all plane IDs belonging to an airport */
};
