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

// vars/ints
int waterlevel;
int temperature; //C
int humidity; // % RH???
int light; 

// Sonar sensor + LCD activation
#define Trigger_Pin 2
#define Echo_Pin 3
#define Max_Distance 40 //cm (max 400)
int distance,
prevdistance,
time = millis(),
LCDawaketime = 5000;
NewPing sonar(Trigger_Pin, Echo_Pin, Max_Distance);
bool LCDoff, ContentsDisplayed = false;
LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

// RGBled
#define R_Pin 7
#define G_Pin 6
#define B_Pin 5

// Temp/humidity sensor (DHT11)
#define DHT_Pin 8
#define DHT_Type DHT11
DHT dht(DHT_Pin, DHT_Type);

//// Animted guy frames:
//byte custLCDchar0[] = { // https://maxpromer.github.io/LCD-Character-Creator/
//  B00100,
//  B01110,
//  B00100,
//  B01110,
//  B10101,
//  B00100,
//  B01010,
//  B01010
//};
//byte custLCDchar1[] = {
//  B00000,
//  B00100,
//  B01110,
//  B00100,
//  B01110,
//  B10101,
//  B00100,
//  B01010
//};

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

void LCDcontents_static() {

}

void LCDcontents() {
	Serial.println("++++++++ Printing LCD Contents ++++++++");
	//lcdprint(4, 1, "Fortnite");
	lcdprint(12, 1, String((int) dht.readTemperature() - 1 /* Temp correction */));
	lcdwrite(14, 1, 2);
	lcdwrite(15, 1, 'C');
	//// Draw chars
	//lcdwrite(0, 0, rand());
	//lcdwrite(15, 0, rand());
	//lcdwrite(0, 1, rand());
	//lcdwrite(15, 1, rand());

	//// Draw animated guy
	//if (millis() - frametime < 500) {
	//	Serial.println("ANIMATED FRAME");
	//	switch (frame) {
	//	case (0):
	//		lcdwrite(6, 0, 0);
	//		lcdwrite(9, 0, 1);
	//	case (1):
	//		lcdwrite(6, 0, 1);
	//		lcdwrite(9, 0, 0);
	//	default:
	//		int frame = 0;
	//	};
	//	frame = frame++;
	//	frametime = millis();
	//}	
}

void LCDwatch() {
	distance = sonar.ping_cm();
	//Enable LCD
	if (distance <= 15 && distance != 0) {
		//Serial.println(distance + String(" <= 15cm"));
		LCDcontents();
		time = millis();
		lcd.backlight();
		delay(5000);
	}
	else if (millis() < time + LCDawaketime) {
		//LCDcontents(); //If stuff has to be constantly updated
	}
	//Disable LCD
	else if (millis() > time + LCDawaketime) {
		lcdclearline(0);
		lcdclearline(1);
		lcd.noBacklight(); // Disabling backlight causes a slight delay
	};
	prevdistance = distance;
	Scheduler.delay(200);
}

void setRBGled(int red, int green, int blue) { 
	analogWrite(R_Pin, red);
	analogWrite(G_Pin, green);
	analogWrite(B_Pin, blue);
}

// The setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	String starttime = __TIME__;
	Serial.println("------------------------------------------------- " + starttime + " -------------------------------------------------");
	Serial.println("Waterlevel: " + waterlevel);
	Serial.println("Temp: " + temperature);
	Serial.println("Humidity: " + humidity);
	Serial.println("Light: " + light);
	lcd.init();
	lcd.createChar(2, custLCDcharDegree);
	//lcd.createChar(0, custLCDchar0);
	//lcd.createChar(1, custLCDchar1);
	//lcd.backlight(); // or lcd.noBacklight to force off

	//RBGled https://howtomechatronics.com/tutorials/arduino/how-to-use-a-rgb-led-with-arduino/
	pinMode(R_Pin, OUTPUT);
	pinMode(G_Pin, OUTPUT);
	pinMode(B_Pin, OUTPUT);
	setRBGled(0, 255, 0);

	//DHT11
	dht.begin();
};

// The loop function runs over and over again until power down or reset
void loop() {
	Scheduler.startLoop(LCDwatch);
	Serial.println("MAIN LOOP");
	delay(10000);
}

