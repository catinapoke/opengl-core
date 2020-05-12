#include "Display.h"

#include "Mesh.h"
#include "RenderManager.h"

using mat4 = glm::mat4;

void DisplayInit()
{
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    camera.setProjectionMatrix(60.0f, (float)4 / 3, 1.0f, 100.0f);
    shader.use();
    Shader::disable();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    // устанавливаем матрицу проекции
    camera.setProjectionMatrix(60.0f, (float)w / h, 1.0f, 100.0f);
};

// функци€ вызываетс€ при перерисовке окна
void Display(void)
{
    // начинаем вывод нового кадра
    // дл€ удобства определ€ем ссылку на RenderManager
    RenderManager& renderManager = RenderManager::instance();
    renderManager.start();

    // передаем указатель на камеру и источник света
    renderManager.setCamera(&camera);
    renderManager.setLight(&light);

    // добавл€ем в очередь все объекты, которые необходимо вывести
    for (int i = 0; i < graphicObjects.size(); i++)
    {
        renderManager.addToRenderQueue(&graphicObjects[i]);
    }

    // завершаем построение кадра
    renderManager.finish();

    // мен€ем передний и задний буферы цвета
    glutSwapBuffers();

    // выводим количество FPS
    char tempStr[128];
    sprintf_s(tempStr, "[%06.2f FPS] Laba_04", renderManager.getFPS());  glutSetWindowTitle(tempStr);
};

// функци€ вывода кубика с ребрами единичной длины
void drawCube()
{
    // переменные дл€ вывода объекта (пр€моугольника из двух треугольников)
    static GLuint VAO_Index = 0; // индекс VAO-буфера
    static GLuint VBO_Index = 0; // индекс VBO-буфера
    static int VertexCount = 0;  // количество вершин
    static bool init = true;

    if (init) {
        // создание и заполнение VBO
        glGenBuffers(1, &VBO_Index);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
        GLfloat Verteces[] = {
            // передн€€ грань (два треугольника)
            -0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
            +0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5,
            // задн€€ грань (два треугольника)
            +0.5, +0.5,  -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
            -0.5, +0.5,  -0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
            // права€ грань (два треугольника)
            +0.5, -0.5,  +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
            +0.5, +0.5,  +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
            // лева€ грань (два треугольника)
            -0.5, +0.5,  +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
            -0.5, -0.5,  +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
            // верхн€€ грань (два треугольника)
            -0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
            +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
            // нижн€€ грань (два треугольника)
            -0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
            +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

        // создание VAO
        glGenVertexArrays(1, &VAO_Index);
        glBindVertexArray(VAO_Index);
        // инициализаци€ VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
        int location = 0;
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        // "отв€зка" буфера VAO на вс€кий случай, чтоб случайно не испортить
        glBindVertexArray(0);

        // указание количество вершин
        VertexCount = 6 * 6;
        init = false;
    }

    // вывод модели кубика на экран
    glBindVertexArray(VAO_Index);
    glDrawArrays(GL_TRIANGLES, 0, VertexCount);
    glBindVertexArray(0);
}