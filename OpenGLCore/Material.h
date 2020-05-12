#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp";
// ����� ��� ������ � ����������
class Material
{
public:
    // ����������� �� ���������
    Material();
    Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, GLfloat shininess, int textureId = -1);

    // ������� ��������� ���������� ��������� �����
    void setAmbient(glm::vec4& ambient);
    void setDiffuse(glm::vec4& diffuse);
    void setSpecular(glm::vec4& specular);
    void setShininess(GLfloat shininess);

    // ��������� ��������� ���������� ��������� �����
    glm::vec4& getAmbient();
    glm::vec4& getDiffuse();
    glm::vec4& getSpecular();
    GLfloat getShininess();

    // ��������� � ��������� id-�������� � ��������� ��������
    void setTextureId(int textureId);
    int getTextureId();

private:
    // id-�������� � ��������� ��������
    int textureId;
    // ������� ������������
    glm::vec4 ambient;
    // ��������� ������������
    glm::vec4 diffuse;
    // ���������� ������������
    glm::vec4 specular;
    // ������� ����������������
    GLfloat shininess;
};