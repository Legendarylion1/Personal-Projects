from email.message import EmailMessage
from emailAccounts import *
import ssl
import smtplib
import sys

if (len(sys.argv) != 2):
    print("Invalid Arguments")
    exit(-1)

subject = 'Error Detected'

body = ""
emailList = sys.argv[1].split("\\n")

for section in emailList:
    body += section + '\n'

print(body)

em = EmailMessage()
em['From'] = email
em['To'] = emailReciever
em['Subject'] = subject
em.set_content(body)

context = ssl.create_default_context()

with smtplib.SMTP_SSL('smtp.gmail.com', 465, context = context) as smtp:
    smtp.login(email, appPassword)
    smtp.sendmail(email, emailReciever, em.as_string())