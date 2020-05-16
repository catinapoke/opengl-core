#pragma once
#include <string>
#include <vector>

#include "opengl.h"
#include "Timer.h"
#include "Shader.h"
#include "Camera.h"
#include "GraphicObject.h"
#include "Light.h"
#include "Material.h"
#include "Scene.h"

using vec3 = glm::vec3;

extern Timer timer;

extern GLuint VBO;
extern GLuint EBO;
extern GLuint VAO;

extern std::string shaderName;
extern std::string shaderPath;
extern Shader shader;

extern Camera* camera;

extern Light light;
extern Material material;

extern Scene scene;
extern std::string modelInfo;
extern std::string sceneInfo;

extern void DataInit();
extern void SetUpShader();