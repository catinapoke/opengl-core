#pragma once
#include <GL/glew.h>
#include "freeglut/freeglut.h"
#include "Data.h"
#include "glm/glm.hpp"
#include "ResourceManager.h"

extern void DisplayInit();
extern void Reshape(int width, int height);
extern void Display();
extern void DrawObject();
extern void drawCube();