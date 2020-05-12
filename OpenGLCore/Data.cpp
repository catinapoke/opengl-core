#include "Data.h"
#include <filesystem>
#include <iostream>
#include "ResourceManager.h"
#include "RenderManager.h"
using vec3 = glm::vec3;
using vec4 = glm::vec4;

namespace fs = std::filesystem;
Timer timer;

GLuint VBO; // ArrayBuffer
GLuint EBO; // ElementBuffer
GLuint VAO; // VertexArray

std::string shaderPath = "resources/shader/phong";
Shader shader;

Camera camera;

Light light;
Material material;

std::vector<GraphicObject> graphicObjects;

void DataInit()
{
    SetUpShader();
    printf("Shader initialized\n");

    RenderManager::instance().init(shader);

    camera = Camera();
    printf("Camera initialized\n");
    initGraphicObjects();
    printf("GraphicObjects initialized\n");
}

void SetUpShader()
{
    std::string vertexShaderPath = shaderPath + ".vsh";
    std::string fragmentShaderPath = shaderPath + ".fsh";
    shader.create(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
}

// вспомогательная  функция для инициализации графических объектов
void initGraphicObjects()
{
    // ссылка на менеджер ресурсов (для удобства)
    ResourceManager& rm = ResourceManager::instance();
    // временная переменная для хранения идентификаторов меша
    int meshId = -1;
    light = Light(vec4(0.3, 1.0, 0.5, 0), vec4(1.0, 1.0, 1.0, 1), vec4(0.6, 0.6, 0.6, 1), vec4(0.4, 0.4, 0.4, 1));
    material = Material(vec4(0.35, 0.35, 0.35, 1), vec4(0.85, 0.85, 0.85, 1), vec4(0.25, 0.25, 0.25, 1), 64.0, -1);

    // добавление графического объекта
    meshId = rm.loadMesh("resources/meshes/buildings/house_2.obj"); // "buildings/house_2.obj"
    printf("MeshId = %d\n", meshId);
    printf("First mesh loaded\n");
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(0, 0, 0),
        0.0f,
        vec4(0.2, 0.2, 0.2, 1)
    ));
    printf("First graphicObject initialized\n");

    // добавление графического объекта
    meshId = rm.loadMesh("resources/meshes/natures/fir_tree.obj"); // natures/big_tree.obj
    printf("MeshId = %d\n", meshId);
    printf("Second mesh loaded\n");
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(7.5, -0.75, 2.5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(5.5, -0.75, -5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(2.8, -0.75, -5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(0.9, -0.75, -5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(-1.5, -0.75, -5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));

    printf("Second graphicObject initialized\n");

    // добавление графического объекта
    meshId = rm.loadMesh("resources/meshes/natures/cube_tree.obj"); // natures/big_tree.obj
    printf("MeshId = %d\n", meshId);
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(-7.5, -0.75, 2.5),
        0.0f,
        vec4(0.2, 0.8, 0.2, 1)
    ));
    printf("Third graphicObject initialized\n");

    // добавление графического объекта
    meshId = rm.loadMesh("resources/meshes/vehicles/police_car.obj"); // vehicles/police_car.obj
    printf("MeshId = %d\n", meshId);
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(+4.5, -2.15, +6.5),
        -115.0f,
        vec4(0.2, 0.2, 1.0, 1)
    ));
    printf("Forth graphicObject initialized\n");

    // добавление графического объекта
    //meshId = rm.loadMesh("resources/meshes/vehicles/police_car.obj"); // vehicles/police_car.obj
    printf("MeshId = %d\n", meshId);
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(+4.25, -2.15, +10.5),
        +105.0f,
        vec4(0.23, 0.23, 1.0, 1)
    ));
    printf("Fifth graphicObject initialized\n");

    // добавление графического объекта
    meshId = rm.loadMesh("resources/meshes/vehicles/jeep.obj"); // vehicles/jeep.obj
    printf("MeshId = %d\n", meshId);
    graphicObjects.push_back(GraphicObject(
        meshId,
        material,
        vec3(-1.25, -2.15, +9.0),
        +170.0f,
        vec4(0.95, 0.13, 0.13, 1)
    ));
    printf("Sixth graphicObject initialized\n");
}