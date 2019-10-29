/*
 Name:		PlantCare.ino
 Created:	10/14/2019 7:42:15 PM
 Author:	ihave
*/

#include <Cth.h>
#include <DHT.h> //temp/humidity http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-an-arduino/
#include <NewPing.h> //Sonar https://www.youtube.com/watch?v=6F1B_N6LuKw
#include <Wire.h> //communicate with I2C / TWI devices https://www.arduino.cc/en/reference/wire
#include <LiquidCrystal_I2C.h> //lcd.<> https://www.arduinolibraries.info/libraries/liquid-crystal-i2-c
#include <EEPROM.h>

// Sensor ints
int temperature; // 0-50°C - ±2°C
int light;
int humidity; // 0-100%
int soilmoisture;

int serialreceivedplantnr[10]; //set to max 10 possible plants
int plants = 10;

// RGBled
constexpr auto R_Pin = 7;
constexpr auto G_Pin = 6;
constexpr auto B_Pin = 5;

// Temp/humidity sensor (DHT11)
const int DHT_Pin[10] = { 8 };
const int DHT_Type = DHT11;
DHT* dhtArray[10]; //max 10 DHT sensors

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

void Sensors(int plantid) {
	temperature = dhtArray[plantid]->readTemperature() - 1;
	light = 0; //analogRead(LDR_Pin);
	humidity = dhtArray[plantid]->readHumidity();
	soilmoisture = 0;
};

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

void SerialSettings() {
	while (Serial.available() > 0) {
		// neem het eerste getal als id, tweede als temp, derde als etc. zodat het volgende id op de tweede regel van de array (standaard 5x10 (5 gegevens, 10 planten max)) komt
		// lees de array ofzo idk
		// https://forum.arduino.cc/index.php?topic=396450.0

		//char data = Serial.read();
		//char str[2];
		//str[0] = data;
		//str[1] = '\0';
		//lcdprint(0, 0, String(serialreceivedplantnr[1]));
	}
	Serial.setTimeout(100);
	//setRBGled(0, 0, 0);
}

void SerialWatch() {
	if (Serial.available() > 0) {
		/*setRBGled(0, 255, 0);*/
		char received = Serial.read();
		//char data = Serial.read();
		//char str[2];
		//str[0] = data;
		//str[1] = '\0';
		lcdprint(0, 0, String(received));
	}
	Serial.setTimeout(100);
	//setRBGled(0, 0, 0);
}

void setup() {
	Serial.begin(9600);
	Serial.println("CONNECTED");

	SerialSettings();
	setRBGled(0, 255, 0);
	//delay(500); // wait for data if any or something

	// init amount:plants DHT11 sensors
	for (int i = 0; i < plants; i++) {
		//Serial.print(i), Serial.print("\n");
		dhtArray[i] = new DHT(DHT_Pin[i], DHT_Type); //define a new DHT at pin 11;
		dhtArray[i]->begin();
	};

	// init LCD
	lcd.init();
	lcdclearline(0);
	lcdclearline(1);
	lcd.createChar(0, LCDcharDegree);
	lcd.createChar(1, LCDcharOKHand);
	lcd.backlight(); // or lcd.noBacklight to force off
	lcdprint(15, 1, "+");

	//RBGled https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/
	pinMode(R_Pin, OUTPUT);
	pinMode(G_Pin, OUTPUT);
	pinMode(B_Pin, OUTPUT);
}

unsigned long lasttime = 0;

void loop() {
	//Scheduler.startLoop(LCDwatch);
	SerialWatch();
	if (millis() >= lasttime + 5000) {
		lasttime = millis();
		//setRBGled(0, 255, 0);

		for (unsigned int plantid = 0; plantid < plants; plantid++) {
			Sensors(plantid);
			if (!isnan(temperature)) {
				Serial.print(".");
				Serial.print("sensordata");
				Serial.print(".");
				Serial.print(plantid);
				Serial.print(".");
				Serial.print(temperature);
				Serial.print(".");
				Serial.print(light);
				Serial.print(".");
				Serial.print(humidity);
				Serial.print(".");
				Serial.print(soilmoisture);
				Serial.println();
			}
			else Serial.println("error");
			delay(1500); //wait to prevent readfails
		}

		//LCDcontents();
		//setRBGled(255, 0, 0);
	}
}