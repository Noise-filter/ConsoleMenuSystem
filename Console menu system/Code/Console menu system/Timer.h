#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();
	~Timer();

	void Start();

	double ElapsedSecounds();
	double ElapsedMilliseconds();
	double ElapsedMicroseconds();

private:
	unsigned __int64 ticksPerSecond;
	unsigned __int64 startTicks;
	unsigned __int64 currentTicks;

};

#endif