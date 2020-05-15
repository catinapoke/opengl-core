#include "GraphicObject.h"

std::unordered_map<std::string, GraphicObjectType> graphicObjectTypeMap
(
    {
        { "road", GraphicObjectType::road},
        { "building", GraphicObjectType::building },
        { "vehicle", GraphicObjectType::vehicle },
        { "big_nature", GraphicObjectType::big_nature },
        { "small_nature", GraphicObjectType::small_nature },
        { "big_prop", GraphicObjectType::big_prop },
        { "medium_prop", GraphicObjectType::medium_prop },
        { "small_prop", GraphicObjectType::small_prop }
    }
);

GraphicObject::GraphicObject() :meshId(0), position(0), angleOY(0), color(0), modelMatrix(1), type(GraphicObjectType()), dimensions(glm::vec3())
{
}

GraphicObject::GraphicObject(int meshId, vec4 color, vec3 position, float angle, Material material, GraphicObjectType type, glm::vec3 dimensions) : modelMatrix(1)
{
    this->meshId = meshId;
    this->position = position;
    this->angleOY = angle;
    this->color = color;
    this->material = material;
    this->type = type;
    this->dimensions = dimensions;
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

void GraphicObject::setMaterial(Material material)
{
    this->material = material;
}

void GraphicObject::setType(GraphicObjectType type)
{
    this->type = type;
}

void GraphicObject::setDimensions(glm::vec3 dimensions)
{
    this->dimensions = dimensions;
}

const Material& GraphicObject::getMaterial()
{
    return material;
}

const GraphicObjectType& GraphicObject::getType()
{
    return type;
}

const glm::vec3& GraphicObject::getDimensions()
{
    return dimensions;
}

const int& GraphicObject::getMeshId()
{
    return meshId;
}

const glm::vec4& GraphicObject::getColor()
{
    return color;
}

const glm::vec3& GraphicObject::getPosition()
{
    return position;
}

const float& GraphicObject::getAngleOY()
{
    return angleOY;
}

const glm::mat4& GraphicObject::getModelMatrix()
{
    return modelMatrix;
}

void GraphicObject::recalculateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1), position) * glm::rotate(glm::mat4(1), glm::radians(angleOY), vec3(0, 1, 0));
};