import time
import datetime
import serial
import MySQLdb
import os

arduino = serial.Serial("COM7",9600)
print("COM connecting...")
serialread = arduino.readline() #only continue when connection is success
print("COM connection success!")
time.sleep(1)

lastmodified = []

# Clear file(s) i.o.t. send plant data to serial on every boot
open("lastmodified.txt", 'w')
open("serialread.txt", 'w')

def sendserial():
    connection = MySQLdb.connect('localhost', 'root', '', 'plantcare')
    with connection.cursor() as cursor: # https://pynative.com/python-mysql-select-query-to-fetch-data/
        result = cursor.execute("SELECT * from `settings`")
        records = cursor.fetchall()

        for row in records:
            dbplantid = row[0]
            dblastmodified = row[1]
            #dbplantname = row[2]
            dbtemperature = row[3]
            dblight = row[4]
            dbhumidity = row[5]
            dbsoilmoisture = row[6]
            
            # https://www.programiz.com/python-programming/methods/built-in/open
            
            with open("lastmodified.txt", 'r+') as f: 
                lines = f.readlines()
            f.close()

            if dblastmodified == 0:
                for line in lines:
                    if line.startswith(str(dbplantid)):
                        if int(line.strip("\n").split('=', 1)[1]) != 0:
                            with open("lastmodified.txt", 'w') as f:
                                  for row in records:
                                      f.write(line.replace(line, ""))
                                      f.write(str(row[0]) + "=" + str(row[1]) + "\n")
                            f.close()
                            serialsend = "setting: " + str(dbplantid) + " " + str(dbtemperature) + " " + str(dblight) + " " + str(dbhumidity) + " " + str(dbsoilmoisture)
                            arduino.write(serialsend.encode('utf-8'))
                            print(serialsend)
                            with open("lastmodified.txt", 'r') as f:
                                lines = f.readlines()
                            f.close()

            if any (str(dbplantid) + "=" in t for t in lines): # https://stackoverflow.com/questions/19211828/python-using-any-and-all-to-check-if-a-list-contains-one-set-of-values-or-an
                for line in lines:
                    if line.startswith(str(dbplantid)):
                        if int(line.strip("\n").split('=', 1)[1]) < dblastmodified:
                            print("edit")
                            with open("lastmodified.txt", 'w') as f:
                                for row in records:
                                    f.write(line.replace(line, ""))
                                    f.write(str(row[0]) + "=" + str(row[1]) + "\n")
                            f.close()
                            serialsend = "setting: " + str(dbplantid) + " " + str(dbtemperature) + " " + str(dblight) + " " + str(dbhumidity) + " " + str(dbsoilmoisture)
                            arduino.write(serialsend.encode('utf-8'))
                            print(serialsend)
                            with open("lastmodified.txt", 'r') as f:
                                lines = f.readlines()
                            f.close()

            else:
                with open("lastmodified.txt", 'a') as f:
                    f.write(str(dbplantid) + "=" + str(dblastmodified) + "\n")
                f.close()
                serialsend = "setting: " + str(dbplantid) + " " + str(dbtemperature) + " " + str(dblight) + " " + str(dbhumidity) + " " + str(dbsoilmoisture)
                arduino.write(serialsend.encode('utf-8'))
                print(serialsend)
            time.sleep(0.5)

            #time.sleep(0.5)
    cursor.close()

def readserial():
	serialread = arduino.readline()
	values = serialread.decode("utf-8").strip("\r\n").split(".")

	with open("serialread.txt", 'a') as f:
		f.write(serialread.decode("utf-8").strip("\r\n") + "\n")
	f.close()

	if values[0] == "Read fail": #values[0] contains a message (if there is one)
		print("++++++++++ SENSOR ERROR / SENSOR NOT CONNECTED TO PLANT '" + str(int(values[2])) + "' ++++++++++")
	elif values[0] == "":
	    plantid = values[2]
	    temperature = values[3]
	    light = values[4]
	    humidity = values[5]
	    soilmoisture = values[6]   
	    

	    connection = MySQLdb.connect('localhost', 'root', '', 'plantcare')

	    with connection.cursor() as cursor:
	    	cursor.execute("""CREATE TABLE IF NOT EXISTS plant_{plantid} (date DATETIME DEFAULT CURRENT_TIMESTAMP, temperature INT, light INT, humidity INT, soilmoisture INT)""".format(plantid=int(plantid)))
	    	cursor.execute("""INSERT INTO plant_{plantid} (temperature, light, humidity, soilmoisture) VALUES(%s,%s,%s,%s)""".format(plantid=int(plantid)), (temperature, light, humidity, soilmoisture))
	    	connection.commit()
	    	cursor.close()
	    print("Read/sent serial data - " + str(datetime.datetime.now()) + " - DATA: " + plantid, temperature, light, humidity, soilmoisture)
	elif values[0] == "CONNECTED":
		print("?????????? CONNECTED ??????????")
	else:
		print("!!!!!!!!!! UNKNOWN ERROR !!!!!!!!!!")

while 1:
    sendserial() # https://stackoverflow.com/questions/5771925/python-how-to-get-notifications-for-mysql-database-changes
    time.sleep(0.1)
    readserial()
    time.sleep(0.1)

#Multiple options to do a loop https://stackoverflow.com/questions/34589347/run-python-script-every-10-seconds, cron is also an option or https://askubuntu.com/questions/396654/how-to-run-a-python-program-in-the-background-even-after-closing-the-terminal