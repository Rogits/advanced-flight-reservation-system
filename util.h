#include <stdarg.h>
#include <ctype.h>

int len(char * str);
int compareCharacter(char, char);
void printUntil(char *, char);
void printFrom(char *, char);
void printWithout(char *, char);
void printTo(char *,char,int);
char * concat(char *, char *);
char * extract(char *, char, int);
char * extractTo(char *, char);
char * join(int, ...);
char * trim(char *, int);
int matchString(char * s1, char * s2, int limit); 
int matchCharacter(char c1, char c2);
char * maxString(char *, char *);
char * minString(char *, char *);
int equalString(char *, char *);

int len(char * str)
{
	int i = 0;
	while(str[++i] != '\0');
	
	return i;
}

int compareCharacter(char c1, char c2)
{
	return c1 == c2 ? 1 : 0;
}

void printUntil(char * str, char sp)
{
	int i;
	for(i = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], sp) == 1)
		{
			break;
		}
		printf("%c", str[i]);
	}	
}

void printFrom(char * str, char c)
{
	int i, count;
	
	for(i = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], c) == 1)
		{
			count = i;
		}
		if(i > count)
		{
			printf("%c", str[i]);
		}
	}
}

void printWithout(char * str, char c)
{
	int i, count;
	
	for(i = count = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], c) == 1)
		{
			continue;
		}
		else
		{
			printf("%c", str[i]);
		}
	}
}


void printTo(char * str, char c, int limit)
{
	int i, j, count;
	
	for(i = j = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], c) == 1)
		{
			count = i;
		}
		if(i > count & j < limit)
		{
			printf("%c", str[i]);
			++j;
		}
	}
}

char * concat(char * arg1, char * arg2)
{
	int i, count;
	static char str[40];
	
	for(i = count = 0; i < len(arg1); ++i)
	{
		str[count] = arg1[i];
		++count;
	}
	for(i = 0; i < len(arg2); ++i)
	{
		str[count] = arg2[i];
		++count;
	}
	
	return str;
}

char * extract(char * str, char c, int limit)
{
	int i,j, count;
	static char s1[15];
	for(i = j = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], c) == 1)
		{
			count = i;
		}
		if(i >= count & j < limit)
		{
			s1[j] = str[i];
			++j;
		}
	}
	return s1;
}

char * extractTo(char * str, char c)
{
	int i;
	static char s1[15]; 
	for(i = 0; i < len(str); ++i)
	{
		if(compareCharacter(str[i], c) == 1)
		{
			break;
		}
		s1[i] = str[i];		
	}
	return s1;
}

char * join(int num, ...)
{
	int i, j, count;
	static char str[20];
	char * arg;
	count = 0;
	va_list valist; 
	va_start(valist, num); 
	for (i = 0; i < num; i++)
	{ 
		arg = va_arg(valist, char *); 
		for( j = 0; j < len(arg); ++j)
		{			
			str[count] = arg[j];
			++count;
		}
	} 
	/* clean memory reserved for valist */ 
	va_end(valist); 
	
	return str;	
}

char * trim(char * str, int sub)
{
	int i;
	static char s1[20];
	for(i = 0; i < len(str); ++i)
	{
		if(i == sub)
		{
			break;
		}
		s1[i] = str[i];
	}
	return s1;
}


int matchString(char * s1, char * s2, int limit)
{
	int i;
	for(i = 0; i < limit; i++)
	{
		if(!matchCharacter(s1[i], s2[i]))
		{		
			return 0;
		}
	}
	return 1;
}

int matchCharacter(char c1, char c2)
{
	char c3, c4;
	c3 = c1;
	c4 = c2;
	if(c1 == c2)
	{
		return 1;
	}
	else
	{
		c3 = toupper(c3);
		c4 = toupper(c4);		
		return c3 == c4 ? 1 : 0;
	}
}

char * maxString(char * s1, char * s2)
{
	return len(s1) > len(s2) ? s1:s2;
}

char * minString(char * s1, char * s2)
{
	return len(s1) < len(s2) ? s1:s2;
}

int equalString(char * s1, char * s2)
{
	return len(s1) == len(s2) ? 1 : 0;
}




