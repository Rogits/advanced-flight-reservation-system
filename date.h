#include <time.h>

struct tm getDate(int d, int m, int y);
struct tm getTime(int h, int m, int s);
struct tm getDateAndTime(int day, int mon, int yr, int hr, int min, int sec);

int getYear(struct tm date);
int getMonth(struct tm date);
int getYearDay(struct tm date);
int getMonthDay(struct tm date);
int getWeekDay(struct tm date);
int getHour(struct tm date);
int getMinute(struct tm date);
int getSecond(struct tm date);

char * getDay(struct tm date);
char * getMonthName(struct tm date);

void setYear(struct tm *date, int y);
void setMonth(struct tm *date, int m);
void setYearDay(struct tm *date, int yd);
void setMonthDay(struct tm *date, int md);
void setWeekDay(struct tm *date, int wd);
void setHour(struct tm *date, int h);
void setMinute(struct tm *date, int m);
void setSecond(struct tm *date, int s);

void printDate(struct tm date);
void printFormattedDate(struct tm date, char *dateformat);
char * getFormattedDate(struct tm date, char *dateformat);

void printTime(struct tm date);
char * getFormattedTime(struct tm date, char * timeformat);
void printFormattedTime(struct tm date, char * timeformat);

void printFullDateAndTime(struct tm date);
char * getFullDateAndTime(struct tm date);

struct tm getDate(int d, int m, int y)
{
	static struct tm dt;
	dt.tm_isdst = 0;
	dt.tm_yday = 0;	
	dt.tm_wday = 0;
	dt.tm_hour = 0;
	dt.tm_min = 0;
	dt.tm_sec = 0;
	dt.tm_mday = (d < 0 & d > 31 ? 0:d);
	dt.tm_mon = (m < 0 & m > 11 ? 0:(m - 1));
	dt.tm_year = (y < 1900 & y > 2015 ? 1900:(y - 1900));	
		
	return dt;	
}

struct tm getTime(int h, int m, int s)
{
	static struct tm dt;
	dt.tm_isdst = 0;
	dt.tm_yday = 0;	
	dt.tm_wday = 0;
	dt.tm_hour = (h < 0 & h > 23 ? 0:h);
	dt.tm_min = (m < 0 & m > 59 ? 0:m);
	dt.tm_sec = (s < 0 & s > 59 ? 0:s);
	dt.tm_mday = 0;
	dt.tm_mon = 0;
	dt.tm_year = 0;	
	
	return dt;
}

struct tm getDateAndTime(int day, int mon, int yr, int hr, int min, int sec)
{
	static struct tm dt;
	dt.tm_isdst = 0;
	dt.tm_yday = 0;	
	dt.tm_wday = 0;
	dt.tm_hour = (hr < 0 & hr > 23 ? 0:hr);
	dt.tm_min = (min < 0 & min > 59 ? 0:min);
	dt.tm_sec = (sec < 0 & sec > 50 ? 0:sec);
	dt.tm_mday = (day < 0 & day > 31 ? 0:day);
	dt.tm_mon = (mon < 0 & mon > 11 ? 0:mon);
	dt.tm_year = (yr < 1900 & yr > 2015 ? 1900:(yr - 1900));	
	
	return dt;
}

int getYear(struct tm date)
{
	return date.tm_year;
}

int getMonth(struct tm date)
{
	return date.tm_mon;
}

int getYearDay(struct tm date)
{
	return date.tm_yday;
}

int getMonthDay(struct tm date)
{
	return date.tm_mday;
}

int getWeekDay(struct tm date)
{
	return date.tm_wday;
}

int getHour(struct tm date)
{
	return date.tm_hour;
}

int getMinute(struct tm date)
{
	return date.tm_min;
}

int getSecond(struct tm date)
{
	return date.tm_sec;
}

void setYear(struct tm *date, int y)
{
	(*date).tm_year = (y < 1900 & y > 2015 ? 1900:(y - 1900));	
}

void setMonth(struct tm *date, int m)
{
	(*date).tm_mon = (m < 0 & m > 11 ? 0:(m - 1));	
}

void setYearDay(struct tm *date, int d)
{
	(*date).tm_yday = (d < 0 & d > 365 ? 0:d);	
}

void setMonthDay(struct tm *date, int d)
{
	(*date).tm_mday = (d < 0 & d > 31 ? 0:d);
}

void setWeekDay(struct tm *date, int d)
{
	(*date).tm_wday = (d < 0 & d > 6 ? 0:d);
}

void setHour(struct tm *date, int h)
{
	(*date).tm_hour = (h < 0 & h > 23 ? 0:h);
}

void setMinute(struct tm *date, int m)
{
	(*date).tm_min = (m < 0 & m > 59 ? 0:m);
}

void setSecond(struct tm *date, int s)
{
	(*date).tm_sec = (s < 0 & s > 59 ? 0:s);
}

void printDate(struct tm date)
{
	struct tm dt = date;
	dt.tm_isdst = 0;
	dt.tm_yday = 0;	
	dt.tm_wday = 0;
	dt.tm_hour = 0;
	dt.tm_min = 0;
	dt.tm_sec = 0;
	dt.tm_mday = date.tm_mday;
	dt.tm_mon = date.tm_mon;
	dt.tm_year = date.tm_year;	
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	
	printf("%s", ctime(ttPtr));
}

void printFormattedDate(struct tm date, char * dateformat)
{
	struct tm dt = date;
	
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;

	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;
	char mydate[100];
	char * df = dateformat;
	strftime(mydate, 100, df, dt2Ptr);
	
	printf("%s", mydate);	
}

char * getFormattedDate(struct tm date, char *dateformat)
{
	static char mydate[100];	
	struct tm dt = date;	
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char *df = dateformat;
	strftime(mydate, 100, df, dt2Ptr);
	
	return mydate;
}

void printTime(struct tm date)
{	
	static char mydate[100];	
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char * tf = "%I:%M:%S %p";	
	strftime(mydate, 100, tf, dt2Ptr);
	
	printf("%s", mydate);
}

void printFormattedTime(struct tm date, char * timeformat)
{	
	static char mydate[100];	
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char * tf = timeformat;	
	strftime(mydate, 100, tf, dt2Ptr);
	
	printf("%s", mydate);
}

char * getFormattedTime(struct tm date, char * timeformat)
{
	static char mydate[100];	
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char * tf = timeformat;	
	strftime(mydate, 100, tf, dt2Ptr);
	
	return mydate;
}

char * getDay(struct tm date)
{
	static char mydate[20];	
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char * tf = "%A";	
	strftime(mydate, 100, tf, dt2Ptr);
	
	return mydate;
}

char * getMonthName(struct tm date)
{
	static char mydate[30];
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	const struct tm dt2 = dt;
	const struct tm *dt2Ptr = &dt2;	
	char * tf = "%B";	
	strftime(mydate, 100, tf, dt2Ptr);
	
	return mydate;
}

void printFullDateAndTime(struct tm date)
{
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	
	printf("%s", ctime(ttPtr));	
}

char * getFullDateAndTime(struct tm date)
{
	struct tm dt = date;
	struct tm *dtPtr = &dt;
	const time_t tt = mktime(dtPtr);
	const time_t *ttPtr = &tt;
	
	return ctime(ttPtr);	
}






