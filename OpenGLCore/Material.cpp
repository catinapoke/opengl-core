#include "Material.h"

Material::Material()
{
    ambient = glm::vec4();
    diffuse = glm::vec4();
    specular = glm::vec4();
    shininess = 0;
    textureId = -1;
}

Material::Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, GLfloat shininess, int textureId)
{
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->shininess = shininess;
    this->textureId = textureId;
}

void Material::setAmbient(glm::vec4& ambient)
{
    this->ambient = ambient;
}

void Material::setDiffuse(glm::vec4& diffuse)
{
    this->diffuse = diffuse;
}

void Material::setSpecular(glm::vec4& specular)
{
    this->specular = specular;
}

void Material::setShininess(GLfloat shininess)
{
    this->shininess = shininess;
}

glm::vec4& Material::getAmbient()
{
    return ambient;
}

glm::vec4& Material::getDiffuse()
{
    return diffuse;
}

glm::vec4& Material::getSpecular()
{
    return specular;
}

GLfloat Material::getShininess()
{
    return shininess;
}

void Material::setTextureId(int textureId)
{
    this->textureId = textureId;
}

int Material::getTextureId()
{
    return textureId;
}