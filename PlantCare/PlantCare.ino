/*
 Name:		PlantCare.ino
 Created:	10/14/2019 7:42:15 PM
 Author:	ihave
*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // Set the LCD address to 0x27 for a 16 chars and 2 line display

// vars/ints
int waterlevel;
int temp;
int humidity; 
int light;
String starttime = __TIME__;

byte animframe0[] = { // https://maxpromer.github.io/LCD-Character-Creator/
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010,
  B01010
};

byte animframe1[] = {
  B00000,
  B00100,
  B01110,
  B00100,
  B01110,
  B10101,
  B00100,
  B01010
};

// The setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("------------------------------------------------- " + starttime + " -------------------------------------------------");
	Serial.println("Waterlevel: " + waterlevel);
	Serial.println("Temp: " + temp);
	Serial.println("Humidity: " + humidity);
	Serial.println("Light: " + light);

	lcd.init();
	lcd.createChar(0, animframe0);
	lcd.createChar(1, animframe1);
	lcd.backlight(); // or lcd.noBacklight
	lcd.setCursor(4, 1);
	lcd.print("Fortnite");
};

void animchar() {
	lcd.setCursor(6, 0);
	lcd.write(0);
	lcd.setCursor(9, 0);
	lcd.write(1);
	delay(500);
	lcd.setCursor(6, 0);
	lcd.write(1);
	lcd.setCursor(9, 0);
	lcd.write(0);
}

void lcdwrites() {
	lcd.setCursor(0, 0);
	lcd.write(rand());
	lcd.setCursor(15, 0);
	lcd.write(rand());
	lcd.setCursor(0, 1);
	lcd.write(rand());
	lcd.setCursor(15, 1);
	lcd.write(rand());
	delay(500); // Wait 100 ms
}
// The loop function runs over and over again until power down or reset
void loop() {
	animchar();
	lcdwrites();
}