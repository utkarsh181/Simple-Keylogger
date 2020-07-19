# Simple Keylogger
This is just a simple keylogger for windows 10 and GNU/Linux, which captures keystrokes with the time of key press

# Features
1. Can send key logs via mail
2. You can automate key-logging process and mail with systemD( for which service file are provided)and Task Scheduler in windows 10
3. Written in C


- Default path are not suitable for use on GNU/Linux so I would recommend to change path in fopen() function in linux.c
- Binaries for all the program are provided, but again I would recommend you to change source code.
- Source Code also contains reference from where I shamelessly copied code and put it together for this program
