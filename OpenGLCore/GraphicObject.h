#pragma once
#include <unordered_map>
#include <string>

#include "opengl.h"
#include <glm/mat4x2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Material.h"

using vec3 = glm::vec3;
using vec4 = glm::vec4;
using ivec3 = glm::ivec3;

// ÒÈÏ ÄÀÍÍÛÕ ÃĞÀÔÈ×ÅÑÊÎÃÎ ÎÁÚÅÊÒÀ
enum class GraphicObjectType
{
    road, building, vehicle, big_nature, small_nature, big_prop, medium_prop, small_prop
};

extern std::unordered_map<std::string, GraphicObjectType> graphicObjectTypeMap;

// ÊËÀÑÑ ÄËß ĞÀÁÎÒÛ Ñ ÃĞÀÔÈ×ÅÑÊÈÌ ÎÁÚÅÊÒÎÌ
class GraphicObject
{
public:
    // êîíñòğóêòîğ ïî óìîë÷àíèş
    GraphicObject();
    GraphicObject(int meshId, vec4 _color, vec3 _position, float _angle, int materialId, GraphicObjectType type, glm::vec3 dimensions);

    void setMesh(int meshId);
    void setColor(glm::vec4 color);
    void setPosition(glm::vec3 position);
    void setAngleOY(float degree);
    void setMaterial(int materialId);
    void setType(GraphicObjectType type);
    void setDimensions(glm::vec3 dimensions);

    const int& getMeshId();
    const glm::vec4& getColor();
    const glm::vec3& getPosition();
    const float& getAngleOY();
    const glm::mat4& getModelMatrix();
    const int& getMaterialId();
    const GraphicObjectType& getType();
    const glm::vec3& getDimensions();

private:
    void recalculateModelMatrix();

    int meshId;
    glm::vec4 color;
    vec3 position;
    float angleOY;
    glm::mat4 modelMatrix;
    int materialId;
    GraphicObjectType type;
    // collider (W x H x D)
    glm::vec3 dimensions;
};