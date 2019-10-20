/*
 Name:		PlantCare.ino
 Created:	10/14/2019 7:42:15 PM
 Author:	ihave
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

// vars/ints
int waterlevel;
int temp;
int humidity;
int light;
String starttime = __TIME__;

// sonar
const int
Trigger_Pin = 2,
Echo_Pin = 3,
Max_Distance = 40; //cm (max 400)
int distance, prevdistance;
unsigned long time = millis(), cooldown = 1000, keepawake = 5000;

NewPing sonar(Trigger_Pin, Echo_Pin, Max_Distance);

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

// Animted guy frames:
byte custLCDchar0[] = { // https://maxpromer.github.io/LCD-Character-Creator/
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B01010
};
byte custLCDchar1[] = {
  B00000,
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010
};

void lcdwrite(int x, int y, int character) {
	lcd.setCursor(x, y);
	lcd.write(character);
}

void lcdprint(int x, int y, String string) {
	lcd.setCursor(x, y);
	lcd.print(string);
}

void LCDbacklight() {
	distance = sonar.ping_cm();
	if (distance <= 15 && distance != 0) {
		Serial.println(distance + String(" <= 15"));
		lcd.backlight();
		time = millis();
	}
	if (millis() > time + keepawake) { // Turn off LCD after specified amout of time
		lcd.noBacklight();
	};
	prevdistance = distance;
}

// The setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("------------------------------------------------- " + starttime + " -------------------------------------------------");
	Serial.println("Waterlevel: " + waterlevel);
	Serial.println("Temp: " + temp);
	Serial.println("Humidity: " + humidity);
	Serial.println("Light: " + light);
	lcd.init();
	lcd.createChar(0, custLCDchar0);
	lcd.createChar(1, custLCDchar1);
	//lcd.backlight(); // or lcd.noBacklight to force off
	lcdprint(4, 1, "Fortnite");
};

// The loop function runs over and over again until power down or reset
void loop() {
	LCDbacklight();
	// Draw animated guy
	lcdwrite(6, 0, 0);
	lcdwrite(9, 0, 1);
	delay(100);
	lcdwrite(6, 0, 1);
	lcdwrite(9, 0, 0);
	// Draw chars
	lcdwrite(0, 0, rand());
	lcdwrite(15, 0, rand());
	delay(100);
	lcdwrite(0, 1, rand());
	lcdwrite(15, 1, rand());
}