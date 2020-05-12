#pragma once
#include <string>
#include <vector>
#include "Timer.h"
#include <GL/glew.h>

#include "freeglut/freeglut.h"
#include "glm/glm.hpp";
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Material.h"

using vec3 = glm::vec3;

extern Timer timer;

extern GLuint VBO;
extern GLuint EBO;
extern GLuint VAO;

extern std::string shaderName;
extern std::string shaderPath;
extern Shader shader;

extern Camera camera;

extern Light light;
extern Material material;

extern std::vector<GraphicObject> graphicObjects;

extern void DataInit();
extern void SetUpShader();
extern void initGraphicObjects();