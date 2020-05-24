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

glm::vec4& Material::getAmbient() const
{
    return (glm::vec4&)ambient;
}

glm::vec4& Material::getDiffuse() const
{
    return (glm::vec4&)diffuse;
}

glm::vec4& Material::getSpecular() const
{
    return (glm::vec4&)specular;
}

GLfloat Material::getShininess() const
{
    return shininess;
}

void Material::setTextureId(int textureId)
{
    this->textureId = textureId;
}

int Material::getTextureId() const
{
    return textureId;
}

bool Material::operator==(const Material& mat)
{
    return (this->ambient == mat.ambient &&
        this->diffuse == mat.diffuse &&
        this->shininess == mat.shininess &&
        this->specular == mat.specular &&
        this->textureId == mat.textureId);
}

bool Material::vec4Less(glm::vec4& vec, glm::vec4& vec2) const
{
    return (vec.r < vec2.r && vec.g < vec2.g && vec.b < vec2.b && vec.a < vec2.a);
}

bool Material::operator<(const Material& mat) const
{
    return vec4Less((glm::vec4&)this->ambient, (glm::vec4&)mat.ambient)
        && vec4Less((glm::vec4&)this->diffuse, (glm::vec4&)mat.diffuse)
        && vec4Less((glm::vec4&)this->specular, (glm::vec4&)mat.specular)
        && (this->shininess < mat.shininess)
        && this->textureId < mat.textureId;
}