#include "Arduino.h"
#include "Wire.h"

#ifndef __THERMO_H 
#define __THERMO_H 

#define _TEMPERATURE	1
#define _HUMIDITY		2
#define _ID 			0x5c

class Thermometer
{
	public:
		Thermometer();
		Thermometer(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t ftColor, uint16_t bdColor);
		void setParam(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t ftColor, uint16_t bdColor);
		float readData(uint8_t type);
		void drawTemperatureIcon();
		void drawHumidityIcon();
		void drawBothVerticalIcon();
		void drawBothSideIcon();
	private:
		TFT_eSprite spimg = TFT_eSprite(&M5.Lcd);
		float readDataCache(uint8_t type);
		uint8_t read();
		uint8_t datos[5];
		uint16_t drawX;
		uint16_t drawY;
		uint16_t backColor;
		uint16_t foreColor;
		uint16_t bordColor;
};

#endif
