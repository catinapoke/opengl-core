#include "Display.h"

#include "Mesh.h"
#include "RenderManager.h"

using mat4 = glm::mat4;

const float zFar = 1000.0f;
const float yFov = 60.0f;

void DisplayInit()
{
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    camera->setProjectionMatrix(yFov, (float)4 / 3, 1.0f, zFar);
    shader.use();
    Shader::disable();
}

void Reshape(int w, int h)
{
    glViewport(0, 0, static_cast<GLsizei>(w), static_cast<GLsizei>(h));
    camera->setProjectionMatrix(yFov, (float)w / h, 1.0f, zFar);
};

void Display(void)
{
    RenderManager& renderManager = RenderManager::instance();
    renderManager.start();

    scene.draw();

    renderManager.finish();

    glutSwapBuffers();

    char tempStr[128];
    sprintf_s(tempStr, "[%06.2f FPS][DrawCalls: %d][MateralChanges: %d] Lab_06 %s", renderManager.getFPS(), renderManager.getDrawCalls(), renderManager.getMaterialChanges(), scene.getSceneDescription().c_str());
    glutSetWindowTitle(tempStr);
};

// ������� ������ ������ � ������� ��������� �����
void drawCube()
{
    // ���������� ��� ������ ������� (�������������� �� ���� �������������)
    static GLuint VAO_Index = 0; // ������ VAO-������
    static GLuint VBO_Index = 0; // ������ VBO-������
    static int VertexCount = 0;  // ���������� ������
    static bool init = true;

    if (init) {
        // �������� � ���������� VBO
        glGenBuffers(1, &VBO_Index);
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
        GLfloat Verteces[] = {
            // �������� ����� (��� ������������)
            -0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5,
            +0.5, +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5, +0.5,
            // ������ ����� (��� ������������)
            +0.5, +0.5,  -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5,
            -0.5, +0.5,  -0.5, +0.5, -0.5, -0.5, -0.5, -0.5, -0.5,
            // ������ ����� (��� ������������)
            +0.5, -0.5,  +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5,
            +0.5, +0.5,  +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, -0.5,
            // ����� ����� (��� ������������)
            -0.5, +0.5,  +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5,
            -0.5, -0.5,  +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, -0.5,
            // ������� ����� (��� ������������)
            -0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, -0.5,
            +0.5, +0.5, -0.5, -0.5, +0.5, +0.5, +0.5, +0.5, +0.5,
            // ������ ����� (��� ������������)
            -0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, +0.5,
            +0.5, -0.5, +0.5, -0.5, -0.5, -0.5, +0.5, -0.5, -0.5
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(Verteces), Verteces, GL_STATIC_DRAW);

        // �������� VAO
        glGenVertexArrays(1, &VAO_Index);
        glBindVertexArray(VAO_Index);
        // ������������� VAO
        glBindBuffer(GL_ARRAY_BUFFER, VBO_Index);
        int location = 0;
        glVertexAttribPointer(location, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(location);
        // "�������" ������ VAO �� ������ ������, ���� �������� �� ���������
        glBindVertexArray(0);

        // �������� ���������� ������
        VertexCount = 6 * 6;
        init = false;
    }

    // ����� ������ ������ �� �����
    glBindVertexArray(VAO_Index);
    glDrawArrays(GL_TRIANGLES, 0, VertexCount);
    glBindVertexArray(0);
}