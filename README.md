# OpenGL 3.3 core mode application

**Used libraries**:
1. [freeglut](http://freeglut.sourceforge.net/) - open-source alternative to the OpenGL Utility Toolkit (GLUT) library
2. [GLM](https://glm.g-truc.net/0.9.9/index.html) - C++ mathematics library for graphics software based on the OpenGL Shading Language (GLSL) specifications
3. [GLEW](http://glew.sourceforge.net/) - The OpenGL Extension Wrangler Library (GLEW) is a cross-platform open-source C/C++ extension loading library.
4. [RapidJson](https://github.com/Tencent/rapidjson/) - A fast JSON parser/generator for C++ with both SAX/DOM style API

**Program in action**
1. Header:
    1. FPS
    1. drawcalls and material changes count
    1. ScenePath 
    1. Objects count
2. Instanced DrawCalls
3. Loading models info and scene configuration from .json files
4. Orbital camera with moving center
5. Level-of-details: unload object if it's further than render distance
6. Phong lightning with textures support

Controls:  
<kbd>Mouse Wheel</kbd> - Camera zoom*(close/further)*  
<kbd>LBM</kbd> -  Camera rotation *(hold and move)*  
<kbd>WASD</kbd> - Camera movement  

![](https://raw.githubusercontent.com/catinapoke/opengl-core/master/app.gif)
