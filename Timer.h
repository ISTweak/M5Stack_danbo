#ifndef __TIMER_H
#define __TIMER_H

class TIMER
{
	public:
		void Start(uint16_t t);
		bool Execute();
	private:
		float startTimer;
		uint16_t timerCount;
};

#endif
