#include <M5Stack.h>
#include <Wire.h>
#include "AmazonLogo.h"
#include "BatteryIcon.h"
#include "Timer.h"
#include "Thermometer.h"

const uint8_t eye_left = 0;
const uint8_t eye_right = 1;
const uint8_t mouth = 2;
const uint8_t on = 1;
const uint8_t off = 0;

TFT_eSprite sp_eye_on = TFT_eSprite(&M5.Lcd);
TFT_eSprite sp_eye_off = TFT_eSprite(&M5.Lcd);
TFT_eSprite sp_mouth_on = TFT_eSprite(&M5.Lcd);
TFT_eSprite sp_mouth_off = TFT_eSprite(&M5.Lcd);

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue) {
	return ((red>>3)<<11) | ((green>>2)<<5) | (blue>>3);
}

uint16_t bkColor = getColor(205, 153, 29);  //0xCCC3
uint16_t emColor = getColor(0, 0, 0);
//uint16_t arColor = getColor(198, 94, 2);  	//0xC2E0
uint8_t bpush[3] = {0, 0, 0};

AmazonLogo AmazonLogo;
BATICON BatIcon;
TIMER Timer;
Thermometer Thermo;

void sprite_init() {
	sp_eye_on.createSprite(32, 32);
	sp_eye_on.fillSprite(bkColor);
	sp_eye_on.fillCircle(15, 15, 16, emColor);
	
	sp_eye_off.createSprite(32, 32);
	sp_eye_off.fillSprite(bkColor);
	sp_eye_off.fillRect(0, 14, 32, 3, emColor);
	
	sp_mouth_on.createSprite(44, 26);
	sp_mouth_on.fillSprite(bkColor);
	sp_mouth_on.fillTriangle(0, 26, 44, 26, 22, 0, emColor);
	
	sp_mouth_off.createSprite(44, 26);
	sp_mouth_off.fillSprite(bkColor);
	sp_mouth_off.fillRoundRect(0, 0, 44, 26, 5, emColor);
	sp_mouth_off.fillRoundRect(3, 3, 38, 20, 3, bkColor);
}

void eye_draw(uint8_t onoff, uint8_t rl) {
	uint16_t xy[2][2] = {{87, 94}, {199, 94}};

	if ( onoff==off ) {
		sp_eye_off.pushSprite(xy[rl][0], xy[rl][1]);
	} else {
		sp_eye_on.pushSprite(xy[rl][0], xy[rl][1]);
	}
	bpush[rl] = onoff == off ? on : off;
}

void mouth_draw(uint8_t onoff) {
	uint16_t xy[2] = {138, 168};

	if ( onoff==off ) {
		sp_mouth_off.pushSprite(xy[0], xy[1]);
	} else {
		sp_mouth_on.pushSprite(xy[0], xy[1]);
	}
	bpush[mouth] = onoff == off ? on : off;
}

void initface() {
	M5.Lcd.fillScreen(bkColor);

	eye_draw(on, eye_left);
	eye_draw(on, eye_right);
	mouth_draw(on);

	//AmazonLogo.cojpOff();
	AmazonLogo.drawAmazonLogo();
}

void setup() {
	M5.begin();
	Wire.begin();

	sprite_init();
	initface();
	Timer.Start(60);
	Thermo.drawBothVerticalIcon();
	BatIcon.drawBatteryIcon();
}

void loop() {
	M5.update();

	if ( M5.BtnA.wasReleased() ) {
		eye_draw(bpush[eye_left], eye_left);
	} else if ( M5.BtnC.wasReleased() ) {
		eye_draw(bpush[eye_right], eye_right);
	} else if ( M5.BtnB.wasReleased() ) {
		mouth_draw(bpush[mouth]);
	} else if ( M5.BtnB.wasReleasefor(700) ) {
		eye_draw(on, eye_left);
		eye_draw(on, eye_right);
		mouth_draw(on);
	}

	if ( Timer.Execute() ) {
		Thermo.drawBothVerticalIcon();
	}

	BatIcon.drawBatteryIcon();
}
