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
	if (!isnan(temperature)) { // only print if temp is not 0 (readfailure)
		lcdprint(0, 0, "Temp:");
		lcdprint(6, 0, String(temperature));
		lcdwrite(8, 0, 0);
		lcdwrite(9, 0, 'C');
		lcdprint(0, 1, "Plant is");
		lcdwrite(9, 1, 1);
	}
}