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

// ���������, ����������� ���� ������� ������������� �����
// ������ ������� ����� �������������� ����������,
// ������ ������� � ���������� ����������
struct Vertex
{
    // �������������� ����������
    GLfloat coord[3];
    // ������ �������
    GLfloat normal[3];
    // ���������� ���������� �������� ����������� �����
    GLfloat textureCoord[3];
};

// ����� ��� ������ � �����
class Mesh
{
public:
    // �����������
    Mesh();
    Mesh(std::string filename);
    // �������� ���� �� �������� obj-�����
    bool load(std::string filename);
    // ����� ����
    void draw();

private:
    GLuint VAO;
    GLuint vertexBufferObject;
    GLuint indexBufferObject;

    std::vector<Vertex> vertices;
    std::vector<int> indices;
};