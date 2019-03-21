#include <M5Stack.h>
#include "AmazonLogo.h"

AmazonLogo::AmazonLogo(void) {
	setParam(4, 4, BLACK, 0xC2E0, 0xCCC3);
}

AmazonLogo::AmazonLogo(uint16_t x, uint16_t y, uint16_t ftColor, uint16_t arColor, uint16_t bkColor) {
	setParam(x, y, ftColor, arColor, bkColor);
}

void AmazonLogo::setParam(uint16_t x, uint16_t y, uint16_t ftColor, uint16_t arColor, uint16_t bkColor) {
	drawX = x;
	drawY = y;
	foreColor = ftColor;
	arrowColor = arColor;
	backColor = bkColor;
}

void AmazonLogo::cojpOff() {
	blcojp = false;
}

void AmazonLogo::drawAmazonLogo() {
	int i;
	spimg.createSprite(172, 38);
	spimg.fillSprite(backColor);
  
	for(i = 0; i < 19; i++) {
		spimg.drawPixel(logo_p[i][0], logo_p[i][1], foreColor);
	}
	for(i = 0; i < 36; i++) {
		spimg.drawLine(logo_l[i][0], logo_l[i][1], logo_l[i][2], logo_l[i][3], foreColor);
	}
	for(i = 0; i < 40; i++) {
		spimg.fillRect(logo_r[i][0], logo_r[i][1], logo_r[i][2], logo_r[i][3], foreColor);
	}
 
	if ( blcojp ) {
		for(i = 0; i < 6; i++) {
			spimg.drawPixel(domain_p[i][0], domain_p[i][1], foreColor);
		}
		for(i = 0; i < 13; i++) {
			spimg.drawLine(domain_l[i][0], domain_l[i][1], domain_l[i][2], domain_l[i][3], foreColor);
		}
		for(i = 0; i < 16; i++) {
			spimg.fillRect(domain_r[i][0], domain_r[i][1], domain_r[i][2], domain_r[i][3], foreColor);
		}
	}

	for(i = 0; i < 3; i++) {
		spimg.drawPixel(arrow_p[i][0], arrow_p[i][1], arrowColor);
	}
	for(i = 0; i < 12; i++) {
		spimg.drawLine(arrow_l[i][0], arrow_l[i][1], arrow_l[i][2], arrow_l[i][3], arrowColor);
	}
	for(i = 0; i < 13; i++) {
		spimg.fillRect(arrow_r[i][0], arrow_r[i][1], arrow_r[i][2], arrow_r[i][3], arrowColor);
	}
	spimg.pushSprite(drawX, drawY);
	spimg.deleteSprite();
}
