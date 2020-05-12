#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;
using ivec3 = glm::ivec3;

// Структура, описывающая одну вершину полигональной сетки
// каждая вершина имеет геометрические координаты,
// вектор нормали и текстурные координаты
struct Vertex
{
    // геометрические координаты
    GLfloat coord[3];
    // вектор нормали
    GLfloat normal[3];
    // текстурные координаты нулевого текстурного блока
    GLfloat textureCoord[3];
};

// КЛАСС ДЛЯ РАБОТЫ С МЕШЕМ
class Mesh
{
public:
    // конструктор
    Mesh();
    Mesh(std::string filename);
    // загрузка меша из внешнего obj-файла
    bool load(std::string filename);
    // вывод меша
    void draw();

private:
    GLuint VAO;
    GLuint vertexBufferObject;
    GLuint indexBufferObject;

    std::vector<Vertex> vertices;
    std::vector<int> indices;
};