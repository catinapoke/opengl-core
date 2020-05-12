#include "GraphicObject.h"

GraphicObject::GraphicObject() :meshId(0), position(0), angleOY(0), color(0), modelMatrix(1)
{
};

GraphicObject::GraphicObject(int meshId, Material material, vec3 _position, float _angle, vec4 _color = vec4(0)) : modelMatrix(1)
{
    this->meshId = meshId;
    this->material = material;
    position = _position;
    angleOY = _angle;
    color = _color;
    recalculateModelMatrix();
};

void GraphicObject::setMesh(int meshId)
{
    this->meshId = meshId;
}

void GraphicObject::setColor(glm::vec4 color)
{
    this->color = color;
}

void GraphicObject::setPosition(glm::vec3 _position)
{
    position = _position;
    recalculateModelMatrix();
}

void GraphicObject::setAngleOY(float degree)
{
    angleOY = degree;
    recalculateModelMatrix();
}

void GraphicObject::setMaterial(Material& material)
{
    this->material = material;
}

Material& GraphicObject::getMaterial()
{
    return material;
}

int GraphicObject::getMeshId()
{
    return meshId;
}

glm::vec4& GraphicObject::getColor()
{
    return color;
}

glm::mat4& GraphicObject::getModelMatrix()
{
    return modelMatrix;
}

void GraphicObject::recalculateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1), position) * glm::rotate(glm::mat4(1), glm::radians(angleOY), vec3(0, 1, 0));
};