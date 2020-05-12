#pragma once
#include <windows.h>

class Timer {
    LARGE_INTEGER time_start;
    LARGE_INTEGER frequency;
public:
    Timer();
    void Reset();
    int ElapsedMiliseconds();
};