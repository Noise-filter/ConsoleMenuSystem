#include "Timer.h"
#include <Windows.h>

Timer::Timer()
{
	ticksPerSecond = startTicks = currentTicks = 0;
}

Timer::~Timer()
{
}

void Timer::Start()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);
	QueryPerformanceCounter((LARGE_INTEGER*)&startTicks);
}

double Timer::ElapsedSecounds()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTicks);
	return ((double)((__int64)currentTicks - (__int64)startTicks) / ((__int64)ticksPerSecond));
}

double Timer::ElapsedMilliseconds()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTicks);
	return ((double)((__int64)currentTicks - (__int64)startTicks) / ((__int64)ticksPerSecond) * 1000);
}

double Timer::ElapsedMicroseconds()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTicks);
	return ((double)((__int64)currentTicks - (__int64)startTicks) / ((__int64)ticksPerSecond) * 1000000);
}