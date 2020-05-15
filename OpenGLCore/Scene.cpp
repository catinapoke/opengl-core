#include "Scene.h"
#include "RenderManager.h"

void Scene::init(std::string filename)
{
    rapidjson::Document* document = GetJsonDocument(filename);
    if (document == nullptr)
        return;

    modelsDescription.CopyFrom(*document, document->GetAllocator());
    delete(document);

    const rapidjson::Value& membersObject = modelsDescription["Models"];
    std::cout << "Scene members: \n";
    int k = 0;
    std::cout<< "array " << membersObject.Capacity() << "\n";
    for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberBegin(); it != membersObject.MemberEnd(); it++)
    {
        std::cout << k << ") ";
        std::cout << it->name.GetString() << " - ";
        std::cout << it->value["id"].GetString() << "\n";
        
        objectInfo[it->value["id"].GetString()] = it;
        //std::cout << it->name.GetString() << "\n";
        k++;
    }
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

    const rapidjson::Value& membersObject = (*sceneDocument)["scene"];
    for (rapidjson::Value::ConstMemberIterator it = membersObject.MemberBegin(); it != membersObject.MemberEnd(); it++)
    {
        std::string id = it->value["Model"]["id"].GetString();
        vec3 position = StrToVec3(it->value["Position"]["value"].GetString());
        float rotation = std::atof(it->value["Rotation"]["value"].GetString());

        GraphicObject graphicObject = createGraphicObject(id);
        graphicObject.setPosition(position);
        graphicObject.setAngleOY(rotation);

        graphicObjects.push_back(graphicObject);
    }
    return true;
}

// Вывод всей сцены
void Scene::draw()
{
    RenderManager& renderManager = RenderManager::instance();

    renderManager.setCamera(&camera);
    renderManager.setLight(&light);

    for (int i = 0; i < graphicObjects.size(); i++)
    {
        renderManager.addToRenderQueue(&graphicObjects[i]);
    }
}

vec3 Scene::StrToVec3(std::string str)
{
    std::stringstream stream;
    stream.str(str);
    printf_s("1");
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
    printf_s("Request graphic object with id: %s\n", str);

    std::unordered_map<std::string, rapidjson::Value::ConstMemberIterator>::const_iterator iterator;
    iterator = objectInfo.find(str);
    if (iterator == objectInfo.end())
        throw new std::exception("Can't find object info");
    return createGraphicObject(iterator->second);
}

Camera* Scene::getCamera()
{
    return &camera;
}

std::string Scene::getSceneDescription()
{
    return sceneFilename + ": " + std::to_string(graphicObjects.size()) + " objects";
}

GraphicObject Scene::createGraphicObject(rapidjson::Value::ConstMemberIterator it)
{
    printf("Creating graphic object with id: %s\n", it->value["id"].GetString());
    ResourceManager& manager = ResourceManager::instance();

    GraphicObjectType objectType = graphicObjectTypeMap[it->value["type"].GetString()];
    printf("Object type: %s\n", it->value["type"].GetString());
    printf("Object's mesh path: %s\n", it->value["Mesh"]["path"].GetString());
    int meshId = manager.loadMesh(it->value["Mesh"]["path"].GetString());
    printf("Object's mesh id: %d\n", meshId);
    vec3 dimensions = StrToVec3(it->value["dimensions"]["value"].GetString());
    printf("Object's dimesions: %f %f %f\n", dimensions.x, dimensions.y, dimensions.z);

    vec4 ambient = StrToVec4(it->value["Material"]["PhongParameters"]["ambient"].GetString());
    vec4 diffuse = StrToVec4(it->value["Material"]["PhongParameters"]["diffuse"].GetString());
    vec4 specular = StrToVec4(it->value["Material"]["PhongParameters"]["specular"].GetString());
    double shininess = std::stod(it->value["Material"]["PhongParameters"]["shininess"].GetString());
    printf("Object's ambient: %f %f %f %f\n", ambient.r, ambient.g, ambient.b, ambient.a);
    printf("Object's diffuse: %f %f %f %f\n", diffuse.r, diffuse.g, diffuse.b, diffuse.a);
    printf("Object's specular: %f %f %f %f\n", specular.r, specular.g, specular.b, specular.a);
    printf("Object's shininess: %f\n", shininess);
    printf("Object's texture path: %s\n", it->value["Material"]["Texture"]["path"].GetString());
    int textureId = manager.loadTexture(it->value["Material"]["Texture"]["path"].GetString());
    Material material = Material(ambient, diffuse, specular, shininess, textureId);

    return GraphicObject(meshId, vec4(1), vec3(0), 0.0f, material, objectType, dimensions);
}