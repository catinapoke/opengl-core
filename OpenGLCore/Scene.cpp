#include "Scene.h"
#include "RenderManager.h"


// ����� ���� ����� 
void Scene::draw()
{
    // �������� ����� ������ ����� 
    // ��� �������� ���������� ������ �� RenderManager
    RenderManager& renderManager = RenderManager::instance(); 

    // �������� ��������� �� ������ � �������� �����
    renderManager.setCamera(&camera);
    renderManager.setLight(&light); 

    // ��������� � ������� ��� �������, ������� ���������� �������
    for (int i = 0; i < graphicObjects.size(); i++) 
    { 
        renderManager.addToRenderQueue(&graphicObjects[i]);
    }
}