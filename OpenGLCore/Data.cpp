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

Camera* camera;

Light light;
Material material;

Scene scene;
std::string modelInfo = "resources/models.json";// "resources/single_model.json";
std::string sceneInfo = "resources/demo_scene.json";// "resources/single_scene.json";

void DataInit()
{
    SetUpShader();
    printf("Shader initialized\n");

    RenderManager::instance().init(shader);

    camera = new Camera();
    printf("Camera initialized\n");
    light = Light(vec4(0.3, 1.0, 0.5, 0), vec4(1.0, 1.0, 1.0, 1), vec4(0.6, 0.6, 0.6, 1), vec4(0.4, 0.4, 0.4, 1));

    scene = Scene();
    scene.SetCamera(camera);
    scene.SetLight(&light);
    scene.init(modelInfo);
    scene.loadFromJSON(sceneInfo);

    printf("GraphicObjects initialized\n");
}

void SetUpShader()
{
    std::string vertexShaderPath = shaderPath + ".vsh";
    std::string fragmentShaderPath = shaderPath + ".fsh";
    shader.create(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}