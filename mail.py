#!/usr/bin/python

import os
import time
import smtplib
from email.message import EmailMessage

sender_email = "demo_id_@gmail.com"
rec_email = "demo_id2_@gmail.com"
password = "demo_password"
msg = EmailMessage()
msg['From'] = sender_email
msg['To'] = rec_email

with open('File Location Goes Here','rb') as f:
    file_data = f.read()
    file_name = f.name

msg.add_attachment(file_data,maintype='application',subtype='octet-stream',filename=file_name)
with smtplib.SMTP_SSL('smtp.gmail.com',465) as smtp:
    smtp.login(sender_email,password)
    smtp.send_message(msg)
