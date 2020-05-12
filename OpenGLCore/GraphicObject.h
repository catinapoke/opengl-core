#pragma once
#include <glm/mat4x2.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Material.h"

using vec3 = glm::vec3;
using vec4 = glm::vec4;
using ivec3 = glm::ivec3;

// ÒÈÏ ÄÀÍÍÛÕ ÃĞÀÔÈ×ÅÑÊÎÃÎ ÎÁÚÅÊÒÀ
enum class GraphicObjectType
{
    road, building, vehicle,  big_nature, small_nature, big_prop, medium_prop, small_prop
};

// ÊËÀÑÑ ÄËß ĞÀÁÎÒÛ Ñ ÃĞÀÔÈ×ÅÑÊÈÌ ÎÁÚÅÊÒÎÌ
class GraphicObject
{
public:
    // êîíñòğóêòîğ ïî óìîë÷àíèş
    GraphicObject();
    GraphicObject(int meshId, Material material, vec3 _position, float _angle, vec4 _color);

    void setMesh(int meshId);
    void setColor(glm::vec4 color);
    void setPosition(glm::vec3 position);
    void setAngleOY(float degree);
    void setMaterial(Material& material);
    void setType(GraphicObjectType type);
    void setDimensions(glm::vec3& dimensions);

    int getMeshId();
    glm::vec4& getColor();
    glm::vec3 getPosition(float degree);
    float getAngleOY(float degree);
    glm::mat4& getModelMatrix();
    Material& getMaterial();
    GraphicObjectType getType();
    glm::vec3& getDimensions();

private:
    void recalculateModelMatrix();
    
    int meshId;
    glm::vec4 color;
    vec3 position;
    float angleOY;
    glm::mat4 modelMatrix;
    Material material;
    GraphicObjectType type;
    // collider (W x H x D)
    glm::vec3 dimensions;
};