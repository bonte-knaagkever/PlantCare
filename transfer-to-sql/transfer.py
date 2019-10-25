import time
import datetime
import serial
import MySQLdb
import os

arduino = serial.Serial("COM7",9600)
print("COM connection success!")
#serialread = arduino.readline() #read once
time.sleep(1)

def sendserial():
    connection = MySQLdb.connect('localhost', 'root', '', 'plantcare')
    with connection.cursor() as cursor: # https://pynative.com/python-mysql-select-query-to-fetch-data/
        result = cursor.execute("SELECT * from `settings`")
        records = cursor.fetchall()

        for row in records:
            dbplantid = row[0]
            dbtemperature = row[3]
            dblight = row[4]
            dbhumidity = row[5]
            dbsoilmoisture = row[6]

            # https://www.programiz.com/python-programming/methods/built-in/open
            if not os.path.exists("lastmodified.txt"):
                open("lastmodified.txt", 'w')
            
            with open("lastmodified.txt", 'r+') as f: 
                lines = f.readlines()
            f.close()
            if any (str(row[0]) + "=" in t for t in lines): # https://stackoverflow.com/questions/19211828/python-using-any-and-all-to-check-if-a-list-contains-one-set-of-values-or-an
                for line in lines:
                    if line.startswith(str(row[0])):
                        if int(line.strip("\n").split('=', 1)[1]) < row[1]:
                            with open("lastmodified.txt", 'w') as f:
                                for row in records:
                                    f.write(line.replace(line, ""))
                                    f.write(str(row[0]) + "=" + str(row[1]) + "\n")
                            f.close()
                            serialsend = "setting:" + " " + str(dbplantid) + " " + str(dbtemperature) + " " + str(dblight) + " " + str(dbhumidity) + " " + str(dbsoilmoisture)
                            arduino.write(serialsend.encode())
                            print("Sent serial data" + serialsend)
                            print(line.strip("\n").split('=', 1))
                            with open("lastmodified.txt", 'r') as f:
                                lines = f.readlines()
                            f.close()
            else:
                with open("lastmodified.txt", 'a') as f:
                    f.write(str(row[0]) + "=" + str(row[1]) + "\n")
                f.close()
                serialsend = "setting:" + " " + str(dbplantid) + " " + str(dbtemperature) + " " + str(dblight) + " " + str(dbhumidity) + " " + str(dbsoilmoisture)
                arduino.write(serialsend.encode())
                print("Sent serial data" + serialsend)
            #time.sleep(0.5)
    cursor.close()

def readserial():
	#arduino.flushInput() #clear serial

	serialread = arduino.readline()
	values = serialread.split(b" ")

	#print(values[1],values[2],values[3],values[4])

	temperature = values[2] #values[0] = "sensordata: ", values[1] = "plantnr"
	light = values[3]
	humidity = values[4]
	soilmoisture = values[5]

	connection = MySQLdb.connect('localhost', 'root', '', 'plantcare')

	with connection.cursor() as cursor:
		cursor.execute("""INSERT INTO sensordata (temperature, light, humidity, soilmoisture) VALUES(%s,%s,%s,%s)""", (temperature, light, humidity, soilmoisture))
		connection.commit()
		cursor.close()
	print("Read serial data " + str(datetime.datetime.now()))

while 1:

    sendserial() # https://stackoverflow.com/questions/5771925/python-how-to-get-notifications-for-mysql-database-changes
    time.sleep(0.1)
    #readserial()
    time.sleep(0.1)

#Multiple options to do a loop https://stackoverflow.com/questions/34589347/run-python-script-every-10-seconds, cron is also an option or https://askubuntu.com/questions/396654/how-to-run-a-python-program-in-the-background-even-after-closing-the-terminal