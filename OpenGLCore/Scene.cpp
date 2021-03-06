#include "Scene.h"
#include "RenderManager.h"
#include <algorithm>

#define debug 0

const std::unordered_map<GraphicObjectType, int> Scene::LODDistance = {
    {GraphicObjectType::road,         -1},//
    {GraphicObjectType::building,     -1},//
    {GraphicObjectType::vehicle,      500},
    {GraphicObjectType::big_nature,   350},
    {GraphicObjectType::small_nature, 200},
    {GraphicObjectType::big_prop,     400},
    {GraphicObjectType::medium_prop,  300},
    {GraphicObjectType::small_prop,   200}
};

void Scene::init(std::string filename)
{
    modelsDescription = GetJsonDocument(filename);
}

rapidjson::Document* Scene::GetJsonDocument(std::string filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cerr << "Couldn't open file " << filename << "for reading \n";
        return nullptr;
    }
    rapidjson::Document* document = new rapidjson::Document();
    //Read from file
    rapidjson::IStreamWrapper isw(ifs);
    document->ParseStream(isw);
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document->Accept(writer);

    if (document->HasParseError())
    {
        std::cerr << "Filename: " << filename << "\n";
        std::cerr << "Parse error: " << document->GetParseError() << "\n Offset: " << document->GetErrorOffset() << "\n";
        return nullptr;
    }
    //Close the file
    ifs.close();
    return document;
}

bool Scene::loadFromJSON(std::string filename)
{
    rapidjson::Document* sceneDocument = GetJsonDocument(filename);
    if (sceneDocument == nullptr)
        return false;

    sceneFilename = filename;
    std::cout << "Loading scene - " << sceneFilename << " !\n";

    const rapidjson::Value& membersObject = (*sceneDocument)["scene"];
    for (rapidjson::Value::ConstMemberIterator it = (*sceneDocument)["scene"].MemberBegin(); it != (*sceneDocument)["scene"].MemberEnd(); it++)
    {
        std::string id = it->value["Model"]["id"].GetString();
        vec3 position = StrToVec3(it->value["Position"]["value"].GetString());
        float rotation = std::atof(it->value["Rotation"]["value"].GetString());
#if debug
        printf_s("GameObject Id - %s Pos - (%f;%f;%f) Rotation - %f\n", id.c_str(), position.x, position.y, position.z, rotation);
#endif
        GraphicObject graphicObject = createGraphicObject(id);
        graphicObject.setPosition(position);
        graphicObject.setAngleOY(rotation);

        graphicObjects.push_back(graphicObject);
    }
    printf_s("Scene information - %s\n", getSceneDescription().c_str());

    std::sort(graphicObjects.begin(), graphicObjects.end(),
        [](GraphicObject a, GraphicObject b)
        {
            if (a.getMeshId() < b.getMeshId())
                return true;
            if (a.getMeshId() == b.getMeshId() && a.getMaterialId() < b.getMaterialId())
                return true;
            return false;
        }
    );

    return true;
}

// ����� ���� �����
void Scene::draw()
{
    RenderManager& renderManager = RenderManager::instance();

    renderManager.setCamera(camera);
    renderManager.setLight(light);

    glm::vec3 cameraPosition = camera->getPosition();
    glm::mat4 projectionViewMatrix = camera->getProjectionMatrix() * camera->getViewMatrix();

    for (int i = 0; i < graphicObjects.size(); i++)
    {
        if (LODSkip(graphicObjects[i], cameraPosition))
            continue;
        if(FrustrumCullingSkip(graphicObjects[i], projectionViewMatrix))
            continue;

        renderManager.addToRenderQueue(&graphicObjects[i]);
    }
}

bool Scene::LODSkip(GraphicObject& graphicObject, glm::vec3& cameraPosition)
{
    // LOD realisation
    auto it = LODDistance.find(graphicObject.getType());
    if (it != LODDistance.end())
        if (it->second > 0)
        {
            // If distance from camera to object > renderDistance then do NOT render
            vec3 difference = (cameraPosition - graphicObject.getPosition());
            if (glm::pow(difference.x, 2) + glm::pow(difference.y, 2) + glm::pow(difference.z, 2) > glm::pow(it->second, 2))
                return true;
        }
    return false;
}

bool Scene::FrustrumCullingSkip(GraphicObject& graphicObject, Camera& camera)
{
    glm::vec3 dimensions = graphicObject.getDimensions();
    //�������� ������ ������� ������
    glm::vec4 corners[8] = {
        {+dimensions.x / 2, +dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, +dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, -dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, +dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, +dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, -dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2, 1.0 }
    };
    // ������� �������������� � ��������� ������� ��������� (clip space)
    ivec3 side(0);
    glm::mat4 PVM = camera.getProjectionMatrix() * camera.getViewMatrix() * graphicObject.getModelMatrix();
    for (int i = 0; i < 8; i++)
    {
        // convert to clip space
        corners[i] = corners[i] * PVM;
        // a. ���� ��� ������� ����� ������ �� ��������� �������� ���������(x ������ + w), �� OBB �� �����;
        // b. ���� ��� ������� ����� ����� �� ��������� �������� ���������(x ������ - w), �� OBB �� �����;
        side.x += (corners[i].x > corners[i].w ? +1 : -1);
        // c. ����  ���  �������  �����  ����  ���������  ��������  ���������(y ������ + w), �� OBB �� �����;
        // d. ����  ���  �������  �����  ����  ���������  ��������  ���������(y ������ - w), �� OBB �� �����;
        side.y += (corners[i].y > corners[i].w ? +1 : -1);
        // e. ���� ��� ������� ����� �����, ��� ������� ��������� ���������(z ������ - w), �� OBB �� �����;
        // f. ����  ���  �������  �����  ������, ���  �������  ��������� ���������(z ������ + w), �� OBB �� �����;
        side.z += (corners[i].z > corners[i].w ? +1 : -1);
    }

    if (abs(side.x) == 8 || abs(side.y) == 8 || abs(side.z) == 8)
        return true;

    // g. �  ���������  ������  OBB  �����
    return false;
}

bool Scene::FrustrumCullingSkip(GraphicObject& graphicObject, glm::mat4& projectionViewMatrix)
{
    glm::vec3 dimensions = graphicObject.getDimensions();
    //�������� ������ ������� ������
    glm::vec4 corners[8] = {
        {+dimensions.x / 2, +dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, +dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, -dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {+dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, +dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, +dimensions.y / 2, -dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, -dimensions.y / 2, +dimensions.z / 2, 1.0 },
        {-dimensions.x / 2, -dimensions.y / 2, -dimensions.z / 2, 1.0 }
    };
    // ������� �������������� � ��������� ������� ��������� (clip space)
    ivec3 side(0);
    glm::mat4 PVM = projectionViewMatrix * graphicObject.getModelMatrix();
    for (int i = 0; i < 8; i++)
    {
        // convert to clip space
        corners[i] = corners[i] * PVM;
        // a. ���� ��� ������� ����� ������ �� ��������� �������� ���������(x ������ + w), �� OBB �� �����;
        // b. ���� ��� ������� ����� ����� �� ��������� �������� ���������(x ������ - w), �� OBB �� �����;
        side.x += (corners[i].x > corners[i].w ? +1 : (corners[i].x < -corners[i].w)? -1 : 0 );
        // c. ����  ���  �������  �����  ����  ���������  ��������  ���������(y ������ + w), �� OBB �� �����;
        // d. ����  ���  �������  �����  ����  ���������  ��������  ���������(y ������ - w), �� OBB �� �����;
        side.y += (corners[i].y > corners[i].w ? +1 : (corners[i].y < -corners[i].w) ? -1 : 0);
        // e. ���� ��� ������� ����� �����, ��� ������� ��������� ���������(z ������ - w), �� OBB �� �����;
        // f. ����  ���  �������  �����  ������, ���  �������  ��������� ���������(z ������ + w), �� OBB �� �����;
        side.z += (corners[i].z > corners[i].w ? +1 : (corners[i].z < -corners[i].w) ? -1 : 0);
    }

    if (abs(side.x) == 8 || abs(side.y) == 8 || abs(side.z) == 8)
        return true;

    // g. �  ���������  ������  OBB  �����
    return false;
}

vec3 Scene::StrToVec3(std::string str)
{
    std::stringstream stream;
    stream.str(str);
    vec3 output;
    stream >> output.x >> output.y >> output.z;
    return output;
}

vec4 Scene::StrToVec4(std::string str)
{
    std::stringstream stream;
    stream.str(str);
    vec4 output;
    stream >> output.r >> output.g >> output.b >> output.a;
    return output;
}

GraphicObject Scene::createGraphicObject(std::string str)
{
    for (rapidjson::Value::ConstMemberIterator it = (*modelsDescription)["Models"].MemberBegin();
        it != (*modelsDescription)["Models"].MemberEnd(); it++)
    {
        if (it->value["id"].GetString() == str)
            return createGraphicObject(it);
    }
}

Camera* Scene::getCamera()
{
    return camera;
}

void Scene::SetCamera(Camera* camera)
{
    this->camera = camera;
}

void Scene::SetLight(Light* light)
{
    this->light = light;
}

std::string Scene::getSceneDescription()
{
    std::stringstream strStream;
    strStream << "Scene desc: " << sceneFilename << ": " << graphicObjects.size() << " objects";
    std::string str = strStream.str();
    return str;
}

GraphicObject Scene::createGraphicObject(rapidjson::Value::ConstMemberIterator it)
{
#if debug
    printf("Creating graphic object with id: %s\n", it->value["id"].GetString());
#endif
    ResourceManager& manager = ResourceManager::instance();

    std::string objectTypeStr = it->value["type"].GetString();
    auto objectTypeIt = graphicObjectTypeMap.find(objectTypeStr);
    if (objectTypeIt == graphicObjectTypeMap.end())
        throw new std::exception("Can't recognize type");
    GraphicObjectType objectType = objectTypeIt->second;

#if debug
    printf("Object type: %s\n", it->value["type"].GetString());
    printf("Object's mesh path: %s\n", it->value["Mesh"]["path"].GetString());
#endif
    int meshId = manager.loadMesh(it->value["Mesh"]["path"].GetString());
#if debug
    printf("Object's mesh id: %d\n", meshId);
#endif
    vec3 dimensions = StrToVec3(it->value["dimensions"]["value"].GetString());
#if debug
    printf("Object's dimesions: %f %f %f\n", dimensions.x, dimensions.y, dimensions.z);
#endif
    vec4 ambient = StrToVec4(it->value["Material"]["PhongParameters"]["ambient"].GetString());
    vec4 diffuse = StrToVec4(it->value["Material"]["PhongParameters"]["diffuse"].GetString());
    vec4 specular = StrToVec4(it->value["Material"]["PhongParameters"]["specular"].GetString());
    double shininess = std::stod(it->value["Material"]["PhongParameters"]["shininess"].GetString());
#if debug
    printf("Object's ambient: %f %f %f %f\n", ambient.r, ambient.g, ambient.b, ambient.a);
    printf("Object's diffuse: %f %f %f %f\n", diffuse.r, diffuse.g, diffuse.b, diffuse.a);
    printf("Object's specular: %f %f %f %f\n", specular.r, specular.g, specular.b, specular.a);
    printf("Object's shininess: %f\n", shininess);
    printf("Object's texture path: %s\n", it->value["Material"]["Texture"]["path"].GetString());
#endif
    int textureId = manager.loadTexture(it->value["Material"]["Texture"]["path"].GetString());
    int materialId = manager.loadMaterial(new Material(ambient, diffuse, specular, shininess, textureId));

    return GraphicObject(meshId, vec4(1), vec3(0), 0.0f, materialId, objectType, dimensions);
}

/*
struct Region
{
    vec2 max x,z
    vec2 min x,z
    graphicObjects[]
    
    vec3 centerpos
    vec2 localCorners[]
    mat4 modelView

    Region* subRegions
}
*/

// �������� ������ ��������
// ���������� ������� ����� x,z
// ������� ����� ������� ������
// ������ ��� �� ���������
// ������ 