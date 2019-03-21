#include <M5Stack.h>
#include <Wire.h>
#include "BatteryIcon.h"

BATICON::BATICON(void) {
	setParam(286, 2, BLACK, 0xCCC3, WHITE, RED);
}

BATICON::BATICON(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t bdColor, uint16_t norColor, uint16_t lowColor) {
	setParam(x, y, bgColor, bdColor, norColor, lowColor);
}

void BATICON::setParam(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t bdColor, uint16_t norColor, uint16_t lowColor) {
	drawX = x;
	drawY = y;
	backColor = bgColor;
	bordColor = bdColor;
	normalColor = norColor;
	lowlevelColor = lowColor;
	currentBatteryLevel = -1;
}

int8_t BATICON::getBatteryLevel() {
	Wire.beginTransmission(0x75);
	Wire.write(0x78);
	if (Wire.endTransmission(false) == 0 && Wire.requestFrom(0x75, 1)) {
		switch (Wire.read() & 0xF0) {
			case 0xE0: return 25;
			case 0xC0: return 50;
			case 0x80: return 75;
			case 0x00: return 100;
			default: return 0;
		}
	}
	return -1;
}

void BATICON::drawBatteryIcon() {
	int bl = getBatteryLevel();
	if ( currentBatteryLevel != bl ) {
		spimg.createSprite(30, 15);
		spimg.fillSprite(bordColor);
		spimg.fillRoundRect(0, 0, 30, 15, 1, backColor);
		spimg.fillRoundRect(28, 4, 4, 7, 1, backColor);

		if ( bl <= 25 ) {
			spimg.setTextColor(lowlevelColor);
		} else {
			spimg.setTextColor(normalColor);
		}
		spimg.setCursor(3, 4);
		spimg.setTextSize(1);
		spimg.printf("%3d%%", bl);
		spimg.pushSprite(drawX, drawY);
		spimg.deleteSprite();
		currentBatteryLevel = bl;
	}
}
