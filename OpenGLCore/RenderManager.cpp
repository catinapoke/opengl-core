#include "RenderManager.h"
#include <algorithm>

#define debug true
#define MAX_INSTANCES = 20;

void RenderManager::init(Shader shader)
{
    shaders.clear();
    shaders.push_back(shader);
    frames = 0;
    elapsedTime = 0;
    startTime = clock();
}

void RenderManager::start()
{
    graphicObjects.clear();
    // отчищаем буфер кадра
    glClearColor(0.88, 0.88, 0.88, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // включаем тест глубины (на всякий случай)
    glEnable(GL_DEPTH_TEST);
    // некоторые дополнительные параметры рендеринга
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void RenderManager::setCamera(Camera* camera)
{
    this->camera = camera;
}

void RenderManager::setLight(Light* light)
{
    this->light = light;
}

void RenderManager::calcFPS()
{
    elapsedTime += clock() - startTime;
    startTime = clock();
    frames++;
    if (elapsedTime / CLOCKS_PER_SEC > 1)
    {
        FPS = frames / (elapsedTime / CLOCKS_PER_SEC);
        elapsedTime = 0;
        frames = 0;
    }
}

void RenderManager::addToRenderQueue(GraphicObject* graphicObject)
{
    graphicObjects.push_back(graphicObject);
}

void RenderManager::finish()
{
    drawCalls = 0;
    materialChanges = 0;

    // получаем матрицу камеры
    glm::mat4& viewMatrix = camera->getViewMatrix();
    glm::vec3 cameraPosition = camera->getPosition();

    // активируем шейдер, используемый для вывода объекта
    shaders[0].use();

    shaders[0].setUniform("texture_0", 0);
    shaders[0].setUniform("projectionMatrix", camera->getProjectionMatrix());

    // устанавливаем параметры источника света
    // они являются общими для всех объектов
    shaders[0].setUniform("lAmbient", light->getAmbient());
    shaders[0].setUniform("lDiffuse", light->getDiffuse());
    shaders[0].setUniform("lSpecular", light->getSpecular());
    // при установке направления на источник света
    // его необходимо преобразовать в систему координат наблюдателя
    shaders[0].setUniform("lPosition", viewMatrix * light->getDirection());

    ResourceManager& manager = ResourceManager::instance();

    std::sort(graphicObjects.begin(), graphicObjects.end(),
        [](GraphicObject* a, GraphicObject* b)
        {
            if (a->getMeshId() < b->getMeshId())
                return true;
            if (a->getMeshId() == b->getMeshId() && a->getMaterialId() < b->getMaterialId())
                return true;
            return false;
        }
    );
    Texture::unbind();

    // ModelView Matrices
    std::vector<glm::mat4> models;
    models.clear();

    // установить текущий меш и текущий материал
    int renderMeshId = graphicObjects[0]->getMeshId();
    int renderMaterialId = graphicObjects[0]->getMaterialId();
    Mesh* renderMesh = manager.getMesh(renderMeshId);
    Material* renderMaterial = manager.getMaterial(renderMaterialId);
    SetRenderMaterial(renderMaterial);
    models.push_back(viewMatrix * graphicObjects[0]->getModelMatrix());

    // начать счетчик с 1
    int i = 1;
    int size = graphicObjects.size();

    if (size == 1) {
        DrawInstanced(shaders[0], models, renderMesh);
    }

    int currentMaterialId = graphicObjects[i]->getMaterialId();;
    int currentMeshId = graphicObjects[i]->getMeshId();

    while (i < size)
    {
        // пока материал и меш совпадают и счетчик < макс 
        //      увеличиваем счетчик
        //      добавляем матрицы моделей 
        while (currentMaterialId == renderMaterialId && currentMeshId == renderMeshId && (models.size() < 20))
        {
            models.push_back(viewMatrix * graphicObjects[i]->getModelMatrix());
            i++;
            if (i >= size)
                break;
            currentMaterialId = graphicObjects[i]->getMaterialId();
            currentMeshId = graphicObjects[i]->getMeshId();
        } 

        // отрисовываем Instanced
        // DrawSingle(shaders[0], models, renderMesh);
        DrawInstanced(shaders[0], models, renderMesh);

        // очищаем массив матриц
        models.clear();

        // если материал другой, то
        //      ставим новый материал
        if (renderMaterialId != currentMaterialId)
        {
            renderMaterialId = currentMaterialId;
            renderMaterial = manager.getMaterial(renderMaterialId);
            SetRenderMaterial(renderMaterial);
        }

        // если меш другой, то 
        //      ставим новый материал
        if (renderMeshId != currentMeshId)
        {
            renderMeshId = currentMeshId;
            renderMesh = manager.getMesh(renderMeshId);
        }
    }

    calcFPS();
}

void RenderManager::DrawSingle(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh)
{
    for (int i = 0; i < modelView.size(); i++)
    {
        shader.setUniform("modelViewMatrix", modelView[i]);
        if (mesh != nullptr)
        {
            mesh->drawSingle();
            drawCalls++;
        }
    }
}

void RenderManager::DrawInstanced(Shader& shader, std::vector<glm::mat4>& modelView, Mesh* mesh)
{
    shader.setUniform("modelViewMatrix", modelView);

    if (mesh != nullptr)
    {
        mesh->drawInstanced(modelView.size());
        drawCalls++;
    }
}

void RenderManager::SetRenderMaterial(Material* material)
{
    shaders[0].setUniform("mAmbient", material->getAmbient());
    shaders[0].setUniform("mDiffuse", material->getDiffuse());
    shaders[0].setUniform("mSpecular", material->getSpecular());
    shaders[0].setUniform("mShininess", material->getShininess());
    ResourceManager::instance().getTexture(material->getTextureId())->bind();
    materialChanges++;
}

float RenderManager::getFPS()
{
    return FPS;
}

int RenderManager::getDrawCalls()
{
    return drawCalls;
}

int RenderManager::getMaterialChanges()
{
    return materialChanges;
}