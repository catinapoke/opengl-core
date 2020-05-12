#include "Scene.h"
#include "RenderManager.h"


// ¬ывод всей сцены 
void Scene::draw()
{
    // начинаем вывод нового кадра 
    // дл€ удобства определ€ем ссылку на RenderManager
    RenderManager& renderManager = RenderManager::instance(); 

    // передаем указатель на камеру и источник света
    renderManager.setCamera(&camera);
    renderManager.setLight(&light); 

    // добавл€ем в очередь все объекты, которые необходимо вывести
    for (int i = 0; i < graphicObjects.size(); i++) 
    { 
        renderManager.addToRenderQueue(&graphicObjects[i]);
    }
}