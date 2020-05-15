#pragma once
#include <cstdio>

#include "opengl.h"

#include "Timer.h"
#include "Data.h"

extern void SimulationInit();
extern void Simulate();
extern void HandleInput(float milliseconds);
extern void MouseHandler(int button, int state, int x, int y);
extern void KeyboardHandler(unsigned char key, int x, int y);
extern void MouseMove(int x, int y);
extern void mouseWheel(int button, int dir, int x, int y);

extern bool leftClick;
extern glm::vec2 mousePosition;

extern const float moveSpeed;
extern const float rotationSpeed;