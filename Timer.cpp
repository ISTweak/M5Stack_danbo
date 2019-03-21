#include <M5Stack.h>
#include "Timer.h"

void TIMER::Start(uint16_t t) {
	timerCount = t;
	startTimer = millis();
}

bool TIMER::Execute() {
	int16_t tic = (int)((float)(millis() - startTimer ) / 1000 / timerCount);

	if ( 0 < tic ) {
		startTimer = millis();
		return true;
	}
	return false;
}
