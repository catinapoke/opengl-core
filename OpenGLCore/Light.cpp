#include "Light.h"

Light::Light()
{
    this->direction = glm::vec4(0);
    this->ambient = glm::vec4(0);
    this->diffuse = glm::vec4(0);
    this->specular = glm::vec4(0);
}

Light::Light(glm::vec4 direction, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular)
{
    this->direction = direction;
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
}

void Light::setDirection(glm::vec4& direction)
{
    this->direction = direction;
}

void Light::setAmbient(glm::vec4& ambient)
{
    this->ambient = ambient;
}

void Light::setDiffuse(glm::vec4& diffuse)
{
    this->diffuse = diffuse;
}

void Light::setSpecular(glm::vec4& specular)
{
    this->specular = specular;
}

glm::vec4& Light::getDirection()
{
    return direction;
}

glm::vec4& Light::getAmbient()
{
    return ambient;
}

glm::vec4& Light::getDiffuse()
{
    return diffuse;
}

glm::vec4& Light::getSpecular()
{
    return specular;
}