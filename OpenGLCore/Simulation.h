#pragma once
#include <GL/glew.h>
#include "freeglut/freeglut.h"
#include <cstdio>
#include "Timer.h"
#include "Data.h"
#include <glm/glm.hpp>

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