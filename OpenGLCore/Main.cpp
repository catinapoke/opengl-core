#include <iostream>
#include <GL/glew.h>
#include "freeglut/freeglut.h"
#include "Data.h"
#include "Display.h"
#include "Simulation.h"

const std::string TitleName = "OpenGLCore";

void OpenGLInit(int argc, char** argv)
{
    // GLUT library initialization
    glutInit(&argc, argv);
    // Display initialization
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
    glutInitContextVersion(3, 3);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    // Set up window
    glutInitWindowPosition(200, 200);
    glutInitWindowSize(800, 600);
    glutCreateWindow(TitleName.c_str());

    // GLEW initialization
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf_s(stderr, "Glew error: %s\n", glewGetErrorString(err));
        exit(0);
    }

    // OpenGL information
    printf("GLEW version - %s\n", glewGetString(GLEW_VERSION));
    printf("OpenGL version - %s\n", glGetString(GL_VERSION));
    printf("Vendor - %s\n", glGetString(GL_VENDOR));
}

int main(int argc, char** argv)
{
    OpenGLInit(argc, argv);
    DataInit();
    printf("Data initialized\n");
    DisplayInit();
    printf("Display initialized\n");
    SimulationInit();
    printf("Simulation initialized\n");
    return 0;
}