#pragma once
#include "opengl.h"
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
    glm::vec4& getAmbient() const;
    glm::vec4& getDiffuse() const;
    glm::vec4& getSpecular() const;
    GLfloat getShininess() const;

    // ��������� � ��������� id-�������� � ��������� ��������
    void setTextureId(int textureId);
    int getTextureId() const;

    bool operator==(const Material& mat);

    bool vec4Less(glm::vec4& vec, glm::vec4& vec2) const;
    bool operator<(const Material& mat) const;
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