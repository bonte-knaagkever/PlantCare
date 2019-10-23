import time
import schedule
import logging
import serial
import MySQLdb

arduino = serial.Serial("COM7",9600)

def transferdata():
	#arduino.flushInput() #clear serial
	data = arduino.readline()
	time.sleep(1)
	data = arduino.readline()
	values = data.split(b" ")

	print(values[1],values[2],values[3],values[4])

	temperature = values[1]
	light = values[2]
	humidity = values[3]
	soilmoisture = values[4]

	connection = MySQLdb.connect('localhost', 'root', '', 'plantcare')

	with connection.cursor() as cursor:
		insertion = cursor.execute("""INSERT INTO sensordata (temperature, light, humidity, soilmoisture) VALUES(%s,%s,%s,%s)""", (temperature, light, humidity, soilmoisture))
		connection.commit()
		#cursor.execute("SELECT * FROM `sensordata`")
		#result = cursor.fetchone() #Read single record
		#print(result)
		cursor.close()


time = datetime.utcnow()
print(datetime.utcnow())

while 1:

	sum = now.time + 10000
	if datetime.utcnow() > sum
		time = gmttime()
		transferdata()
		print("Tranfered data")
	time.sleep(.1)	

#Multiple options to do a loop https://stackoverflow.com/questions/34589347/run-python-script-every-10-seconds, cron is also an option or https://askubuntu.com/questions/396654/how-to-run-a-python-program-in-the-background-even-after-closing-the-terminal