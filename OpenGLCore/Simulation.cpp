#include "Simulation.h"

bool leftClick = false;
glm::vec2 mousePosition = glm::vec2(0);
const float moveSpeed = 20.0f;
const float rotationSpeed = 0.25f;

void SimulationInit()
{
    glutMouseFunc(MouseHandler);
    glutMotionFunc(MouseMove);
    glutMouseWheelFunc(mouseWheel);

    glutIdleFunc(Simulate);
    glutMainLoop();
}

void Simulate()
{
    int elapsedTime = timer.ElapsedMiliseconds();
    HandleInput(elapsedTime);
    glutPostRedisplay();
};

void HandleInput(float milliseconds)
{
    vec2 movement = { 0,0 };
    if (GetAsyncKeyState(0x57)) // W
        movement.y += 1;
    if (GetAsyncKeyState(0x53)) // S
        movement.y -= 1;
    if (GetAsyncKeyState(0x41)) // A
        movement.x -= 1;
    if (GetAsyncKeyState(0x44)) // D
        movement.x += 1;

    if (movement == vec2(0))
        return;

    camera->moveCenter(vec3(movement.x, 0, movement.y) * (milliseconds / 1000.0f) * moveSpeed);
}

void MouseHandler(int button, int state, int x, int y)
{
    glm::vec2 delta;
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == 0)
        {
            mousePosition = glm::vec2(x, y);
            leftClick = true;
        }
        else
            leftClick = false;
    }
}

void MouseMove(int x, int y)
{
    glm::vec2 delta;
    if (leftClick)
    {
        delta = glm::vec2(x, y) - mousePosition;
        delta.y *= -1;
    }
    else
        return;
    mousePosition = glm::vec2(x, y);
    camera->rotate(delta * rotationSpeed);
}

void mouseWheel(int button, int dir, int x, int y)
{
    if (dir > 0) // Zoom in
    {
        camera->zoomInOut(true);
    }
    else // Zoom out
    {
        camera->zoomInOut(false);
    }
}