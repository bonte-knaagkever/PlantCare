/*
 Name:		PlantCare.ino
 Created:	10/14/2019 7:42:15 PM
 Author:	ihave
*/

#include <Cth.h>
#include <DHT.h> //temp/humidity http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
#include <Wire.h> //communicate with I2C / TWI devices https://www.arduino.cc/en/reference/wire
#include <LiquidCrystal_I2C.h> //lcd.<> https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
#include <NewPing.h> //Sonar https://www.youtube.com/watch?v=6F1B_N6LuKw

// RGBled
#define R_Pin 7
#define G_Pin 6
#define B_Pin 5

// Temp/humidity sensor (DHT11)
#define DHT_Pin 8
#define DHT_Type DHT11
DHT dht(DHT_Pin, DHT_Type);

int temperature; // 0-50°C - ±2°C
int light;
int humidity; // 0-100%
int soilmoisture;
void Sensors() {
	temperature = dht.readTemperature();
	light = 0;
	humidity = dht.readHumidity();
	soilmoisture = 0;
};


byte custLCDcharDegree[] = { // https://maxpromer.github.io/LCD-Character-Creator/
  B00000,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16 chars and 2 line display
void lcdwrite(int x, int y, int character) { // for single characters
	lcd.setCursor(x, y);
	lcd.write(character);
}

void lcdprint(int x, int y, String string) { // for strings
	lcd.setCursor(x, y);
	lcd.print(string);
}

void lcdclearline(int line) {
	lcd.setCursor(0, line);
	for (int i = 0; i < 16; ++i)
	{
		lcd.write(' ');
	}
}

void LCDcontents() {	
	if (!isnan(temperature)) {
		lcdprint(0, 0, "Temp:");
		lcdprint(6, 0, String(temperature - 1));
		lcdwrite(8, 0, 2);
		lcdwrite(9, 0, 'C');
	}
}

// Sonar sensor + LCD activation
//#define Trigger_Pin 2
//#define Echo_Pin 3
//#define Max_Distance 40 //cm (max 400)
//int distance,
//prevdistance,
//time = millis(),
//LCDawaketime = 5000;
//NewPing sonar(Trigger_Pin, Echo_Pin, Max_Distance);
//void LCDwatch() {
//	distance = sonar.ping_cm();
//	//Enable LCD
//	if (distance <= 15 && distance != 0) {
//		//Serial.println(distance + String(" <= 15cm"));
//		time = millis();
//		lcd.backlight();
//		LCDcontents();
//	}
//	else if (millis() < time + LCDawaketime) {
//		//LCDcontents(); //If stuff has to be constantly updated
//	}
//	//Disable LCD
//	else if (millis() > time + LCDawaketime) {
//		lcdclearline(0);
//		lcdclearline(1);
//		lcd.noBacklight(); // Disabling backlight causes a slight delay
//	};
//	prevdistance = distance;
//}

void setRBGled(int red, int green, int blue) { 
	analogWrite(R_Pin, red);
	analogWrite(G_Pin, green);
	analogWrite(B_Pin, blue);
}

void setup() {
	Serial.begin(9600);
	String starttime = __TIME__;
	//Serial.println("---------" + starttime + "--------- "); //~~space to make it identifiable by the transfer python script~~
	lcd.init();
	lcd.createChar(2, custLCDcharDegree);
	lcd.backlight(); // or lcd.noBacklight to force off

	//RBGled https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/
	pinMode(R_Pin, OUTPUT);
	pinMode(G_Pin, OUTPUT);
	pinMode(B_Pin, OUTPUT);

	//DHT11
	dht.begin();
}

void loop() {
	//Scheduler.startLoop(LCDwatch);
	setRBGled(0, 255, 0);
	Sensors();
	Serial.print("sensordata: ");
	Serial.print(temperature);
	Serial.print(" ");
	Serial.print(light);
	Serial.print(" ");
	Serial.print(humidity);
	Serial.print(" ");
	Serial.print(soilmoisture);
	Serial.println(" ");

	LCDcontents();
	setRBGled(255, 0, 0);
	delay(10000);
}