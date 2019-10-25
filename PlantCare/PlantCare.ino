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
#include <EEPROM.h>

// Sensor ints
int temperature; // 0-50°C - ±2°C
int light;
int humidity; // 0-100%
int soilmoisture;

int plants = 5;

// RGBled
constexpr auto R_Pin = 7;
constexpr auto G_Pin = 6;
constexpr auto B_Pin = 5;

// Temp/humidity sensor (DHT11)
const int DHT_Pin[5] = { 8, 9, 10, 11, 12 };
const int DHT_Type = DHT11;
DHT* dhtArray[5]; //max 5 DHT sensors

// LDR
constexpr auto LDR_Pin = 3;

// LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16 chars and 2 line display
byte LCDcharDegree[] = { // https://maxpromer.github.io/LCD-Character-Creator/
  B00000,
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B00000,
  B00000
};
byte LCDcharOKHand[] = {
  B00010,
  B00110,
  B00111,
  B01111,
  B10011,
  B11011,
  B01110,
  B01110
};

void Sensors(int plantnr) {
	temperature = dhtArray[plantnr]->readTemperature() - 1;
	light = analogRead(LDR_Pin);
	humidity = dhtArray[plantnr]->readHumidity();
	soilmoisture = 0;
};

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
	if (!(temperature = 0)) { // only print if temp is not 0 (readfailure)
		lcdprint(0, 0, "Temp:");
		lcdprint(6, 0, String(temperature));
		lcdwrite(8, 0, 0);
		lcdwrite(9, 0, 'C');
		lcdprint(0, 1, "Plant is");
		lcdwrite(9, 1, 1);
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
//	else if (millis() <= time + LCDawaketime) {
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

void SerialWatch() {
	if (String(Serial.read()) == "setting:") { //https://forum.arduino.cc/index.php?topic=78392.0
		//Serial.print();
		setRBGled(0, 255, 0);
		lcdprint(0, 0, String(Serial.read()));
	};
	Serial.setTimeout(100);
}

void setup() {
	Serial.begin(9600);
	SerialWatch();
	//plants = EEPROM.read(0);

	//dhtArray = new DHT[7];
	//for (unsigned int i = 0; i < sizeof(DHT_Pin); i++) {
	//	dhtArray[i] = new dht(DHT_Pin[i], DHT_Type);
	//};

	//LCD
	lcd.init();
	lcdclearline(0);
	lcdclearline(1);
	lcd.createChar(0, LCDcharDegree);
	lcd.createChar(1, LCDcharOKHand);
	lcd.backlight(); // or lcd.noBacklight to force off

	//RBGled https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/
	pinMode(R_Pin, OUTPUT);
	pinMode(G_Pin, OUTPUT);
	pinMode(B_Pin, OUTPUT);

	//DHT11
	for (int i = 0; i < 5; i++) {
		//Serial.print(i), Serial.print("\n");
		dhtArray[i] = new DHT(DHT_Pin[i], DHT_Type); //define a new DHT at pin 11;
		dhtArray[i]->begin();
	};
}

unsigned long lasttime = 0;

void loop() {
	//Scheduler.startLoop(LCDwatch);
	SerialWatch();
	if (millis() >= lasttime + 10000) {
		lasttime = millis();
		//setRBGled(0, 255, 0);
		Sensors(0);
		
		Serial.print("sensordata:");
		Serial.print(" ");
		Serial.print(plantnr);
		Serial.print(" ");
		Serial.print(temperature);
		Serial.print(" ");
		Serial.print(light);
		Serial.print(" ");
		Serial.print(humidity);
		Serial.print(" ");
		Serial.print(soilmoisture);
		Serial.println();
		
		//for (unsigned int plantnr = 0; plantnr < sizeof(plants); plantnr++) {
		//	Sensors(plantnr);
		//	Serial.print("sensordata:");
		//	Serial.print(" ");
		//	Serial.print(plantnr);
		//	Serial.print(" ");
		//	Serial.print(temperature);
		//	Serial.print(" ");
		//	Serial.print(light);
		//	Serial.print(" ");
		//	Serial.print(humidity);
		//	Serial.print(" ");
		//	Serial.print(soilmoisture);
		//	Serial.println();
		//}

		//LCDcontents();
		//setRBGled(255, 0, 0);
	}
	delay(900);
}