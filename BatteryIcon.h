#ifndef __BATICON_H
#define __BATICON_H

class BATICON
{
	public:
		BATICON(void);
		BATICON(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t bdColor, uint16_t norColor, uint16_t lowColor);
		void setParam(uint16_t x, uint16_t y, uint16_t bgColor, uint16_t bdColor, uint16_t norColor, uint16_t lowColor);
		int8_t getBatteryLevel();
		void drawBatteryIcon();
	private:
		TFT_eSprite spimg = TFT_eSprite(&M5.Lcd);
		uint16_t drawX;
		uint16_t drawY;
		uint16_t backColor;
		uint16_t bordColor;
		uint16_t normalColor;
		uint16_t lowlevelColor;
		int8_t currentBatteryLevel;
};

#endif
