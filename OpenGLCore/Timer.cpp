#include "Timer.h"

Timer::Timer()
{
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time_start);
}

void Timer::Reset()
{
    QueryPerformanceCounter(&time_start);
}

int Timer::ElapsedMiliseconds()
{
    LARGE_INTEGER time_end;
    QueryPerformanceCounter(&time_end);
    int msElapsed = ((time_end.QuadPart - time_start.QuadPart) * 1000 / frequency.QuadPart);
    time_start = time_end;
    return msElapsed;
}