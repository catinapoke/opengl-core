#include "Data.h"
#include <filesystem>
#include <iostream>
#include "ResourceManager.h"
#include "RenderManager.h"
#include "Scene.h"
using vec3 = glm::vec3;
using vec4 = glm::vec4;

namespace fs = std::filesystem;
Timer timer;

GLuint VBO; // ArrayBuffer
GLuint EBO; // ElementBuffer
GLuint VAO; // VertexArray

std::string shaderPath = "resources/shader/lab5";
Shader shader;

Camera camera;

Light light;
Material material;

Scene scene;

void DataInit()
{
    SetUpShader();
    printf("Shader initialized\n");

    RenderManager::instance().init(shader);

    camera = Camera();
    printf("Camera initialized\n");

    scene = Scene();
    scene.init("resources/models.json");
    scene.loadFromJSON("resources/demo_scene.json");

    printf("GraphicObjects initialized\n");
}

void SetUpShader()
{
    std::string vertexShaderPath = shaderPath + ".vsh";
    std::string fragmentShaderPath = shaderPath + ".fsh";
    shader.create(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}