#include "RenderManager.h"

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
    // �������� ����� �����
    glClearColor(0.88, 0.88, 0.88, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // �������� ���� ������� (�� ������ ������)
    glEnable(GL_DEPTH_TEST);
    // ��������� �������������� ��������� ����������
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
    // �������� ������� ������
    glm::mat4& viewMatrix = camera->getViewMatrix();

    // ���������� ������, ������������ ��� ������ �������
    shaders[0].use();
    shaders[0].setUniform("projectionMatrix", camera->getProjectionMatrix());

    // ������������� ��������� ��������� �����
    // ��� �������� ������ ��� ���� ��������
    shaders[0].setUniform("lAmbient", light->getAmbient());
    shaders[0].setUniform("lDiffuse", light->getDiffuse());
    shaders[0].setUniform("lSpecular", light->getSpecular());
    // ��� ��������� ����������� �� �������� �����
    // ��� ���������� ������������� � ������� ��������� �����������
    shaders[0].setUniform("lPosition", viewMatrix * light->getDirection());

    // ������� ��� �������
    for (int i = 0; i < graphicObjects.size(); i++) {
        // ������������� ������� ���������� ������
        glm::mat4 modelViewMatrix = viewMatrix * graphicObjects[i]->getModelMatrix();
        shaders[0].setUniform("modelViewMatrix", modelViewMatrix);

        // ������������� ��������� ���������
        Material& material = graphicObjects[i]->getMaterial();
        shaders[0].setUniform("mAmbient", material.getAmbient());
        shaders[0].setUniform("mDiffuse", material.getDiffuse());
        shaders[0].setUniform("mSpecular", material.getSpecular());
        shaders[0].setUniform("mShininess", material.getShininess());

        // ������� ���
        int meshId = graphicObjects[i]->getMeshId();
        Mesh* mesh = ResourceManager::instance().getMesh(meshId);
        if (mesh != nullptr)
            mesh->draw();
    }
    calcFPS();
}

float RenderManager::getFPS()
{
    return FPS;
}