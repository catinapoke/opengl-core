#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp";
// КЛАСС ДЛЯ РАБОТЫ С МАТЕРИАЛОМ
class Material
{
public:
    // конструктор по умолчанию
    Material();
    Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, GLfloat shininess, int textureId = -1);

    // задание различных параметров источника света
    void setAmbient(glm::vec4& ambient);
    void setDiffuse(glm::vec4& diffuse);
    void setSpecular(glm::vec4& specular);
    void setShininess(GLfloat shininess);

    // получение различных параметров источника света
    glm::vec4& getAmbient();
    glm::vec4& getDiffuse();
    glm::vec4& getSpecular();
    GLfloat getShininess();

    // установка и получение id-текстуры в менеджере ресурсов
    void setTextureId(int textureId);
    int getTextureId();

private:
    // id-текстуры в менеджере ресурсов
    int textureId;
    // фоновая составляющая
    glm::vec4 ambient;
    // диффузная составляющая
    glm::vec4 diffuse;
    // зеркальная составляющая
    glm::vec4 specular;
    // степень отполированности
    GLfloat shininess;
};