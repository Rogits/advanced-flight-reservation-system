#define SIZE 1000 /* max total number of seats */

struct plane
{
	int id;
	int airportId; /* identifies plane's airport */
	char name[20];
	int milesTraveled;
	int seatsPerClass[2];
	int seatNum[SIZE];
};
