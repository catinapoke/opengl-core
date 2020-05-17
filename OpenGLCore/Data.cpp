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
std::string modelInfo = "resources/models.json"; // models, single_model
std::string sceneInfo = "resources/demo_scene.json"; // demo_scene, single_scene

void DataInit()
{
    ShaderInit();
    printf("Shader initialized\n");

    RenderManager::instance().init(shader);

    camera = new Camera();
    printf("Camera initialized\n");
    light = Light(vec4(0.3, 1.0, 0.5, 0), vec4(1.0, 1.0, 1.0, 1), vec4(0.6, 0.6, 0.6, 1), vec4(0.4, 0.4, 0.4, 1));

    SceneInit();
    printf("Scene initialized\n");
}

void ShaderInit()
{
    std::string vertexShaderPath = shaderPath + ".vsh";
    std::string fragmentShaderPath = shaderPath + ".fsh";
    shader.create(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}

void SceneInit()
{
    scene = Scene();
    scene.SetCamera(camera);
    scene.SetLight(&light);
    scene.init(modelInfo);
    scene.loadFromJSON(sceneInfo);
}