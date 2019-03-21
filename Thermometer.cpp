#include <M5Stack.h>
#include "Thermometer.h"

Thermometer::Thermometer() {
	setParam(272, 208, BLACK, WHITE, 0xCCC3);
	//setParam(222, 223, BLACK, WHITE, 0xCCC3);
	//setParam(272, 223, BLACK, WHITE, 0xCCC3);
}

Thermometer::Thermometer(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t ftColor, uint16_t bdColor) {
	setParam(x, y, bgColor, ftColor, bdColor);
}

void Thermometer::setParam(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t ftColor, uint16_t bdColor) {
	drawX = x;
	drawY = y;
	backColor = bgColor;
	foreColor = ftColor;
	bordColor = bdColor;
}

uint8_t Thermometer::read() {
	Wire.beginTransmission(_ID);
	Wire.write(0);
	if ( Wire.endTransmission() != 0 ) {
		return 1;
	}
	Wire.requestFrom(_ID, (uint8_t) 5);
	for (int i = 0; i < 5; i++) {
		datos[i] = Wire.read();
	}
	delay(50);
	if ( Wire.available() != 0 ) {
		return 2;
	}
	if ( datos[4] != (datos[0] + datos[1] + datos[2] + datos[3]) ) {
		return 3;
	}
	return 0;
}

float Thermometer::readData(uint8_t type) {
	uint8_t c1 = (type != _TEMPERATURE) ? 0 : 2;
	uint8_t c2 = (type != _TEMPERATURE) ? 1 : 3;
	float resultado = 0;
	uint8_t error = read();
	if (error != 0) {
		return -999;
	}
	resultado = (datos[c1] + (float) datos[c2] / 10);
	return resultado;
}

float Thermometer::readDataCache(uint8_t type) {
	uint8_t c1 = (type != _TEMPERATURE) ? 0 : 2;
	uint8_t c2 = (type != _TEMPERATURE) ? 1 : 3;
	float resultado = 0;
	resultado = (datos[c1] + (float) datos[c2] / 10);
	return resultado;
}

void Thermometer::drawTemperatureIcon() {
	float tempvalue = readData(_TEMPERATURE);
	spimg.createSprite(46, 15);
	spimg.fillSprite(bordColor);
	spimg.fillRoundRect(0, 0, 46, 15, 1, backColor);
	spimg.fillRect(35, 3, 2, 2, foreColor);
	spimg.setCursor(3, 4);
	spimg.setTextColor(foreColor);
	spimg.setTextSize(1);
	if ( tempvalue < -250 ) {
		spimg.print(" --.- C");
	} else {
		spimg.printf("%5.1f C", tempvalue);
	}
	spimg.pushSprite(drawX, drawY);
	spimg.deleteSprite();
}

void Thermometer::drawHumidityIcon() {
	float humivalue = readData(_HUMIDITY);
	spimg.createSprite(46, 15);
	spimg.fillSprite(bordColor);
	spimg.fillRoundRect(0, 0, 46, 15, 1, backColor);
	spimg.setCursor(3, 4);
	spimg.setTextColor(foreColor);
	spimg.setTextSize(1);
	if ( humivalue < -250 ) {
		spimg.print(" --.- %");
	} else {
		spimg.printf("%5.1f %%", humivalue);
	}
	spimg.pushSprite(drawX, drawY);
	spimg.deleteSprite();
}

void Thermometer::drawBothVerticalIcon() {
	float tempvalue = readData(_TEMPERATURE);
	float humivalue = readDataCache(_HUMIDITY);
	spimg.createSprite(46, 28);
	spimg.fillSprite(bordColor);
	spimg.fillRoundRect(0, 0, 46, 28, 1, backColor);
	spimg.fillRect(35, 3, 2, 2, foreColor);
	spimg.setCursor(3, 4);
	spimg.setTextColor(foreColor);
	spimg.setTextSize(1);
	if ( tempvalue < -250 ) {
		spimg.print(" --.- C");
		spimg.setCursor(3, 17);
		spimg.print(" --.- %");
	} else {
		spimg.printf("%5.1f C", tempvalue);
		spimg.setCursor(3, 17);
		spimg.printf("%5.1f %%", humivalue);
	}
	spimg.pushSprite(drawX, drawY);
	spimg.deleteSprite();
}

void Thermometer::drawBothSideIcon() {
	float tempvalue = readData(_TEMPERATURE);
	float humivalue = readDataCache(_HUMIDITY);
	spimg.createSprite(96, 15);
	spimg.fillSprite(bordColor);
	spimg.fillRoundRect(0, 0, 94, 15, 1, backColor);
	spimg.fillRect(35, 3, 2, 2, foreColor);
	spimg.setCursor(3, 4);
	spimg.setTextColor(foreColor);
	spimg.setTextSize(1);
	if ( tempvalue < -250 ) {
		spimg.print(" --.- C/ --.- %");
	} else {
		spimg.printf("%5.1f C/%5.1f %%", tempvalue, humivalue);
	}
	spimg.pushSprite(drawX, drawY);
	spimg.deleteSprite();
}

