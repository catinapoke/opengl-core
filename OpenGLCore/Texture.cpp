#include "Texture.h"
#include <iostream>
#include <unordered_map>
Texture::Texture()
{
}

Texture::Texture(std::string filename)
{
    load(filename);
}

#if debug // Formats and type to string
std::unordered_map<int, const char*> ilFormats = { 
    { IL_COLOUR_INDEX, "IL_COLOUR_INDEX"},
    { IL_RGB, "IL_RGB"},
    { IL_RGBA, "IL_RGBA"},
    { IL_BGR, "IL_BGR"},
    { IL_BGRA, "IL_BGRA"},
    { IL_LUMINANCE, "IL_LUMINANCE" } };

std::unordered_map<int, const char*> ilTypes = {
    { IL_BYTE, "IL_BYTE"},
    { IL_UNSIGNED_BYTE, "IL_UNSIGNED_BYTE"},
    { IL_SHORT, "IL_SHORT"},
    { IL_UNSIGNED_SHORT, "IL_UNSIGNED_SHORT"},
    { IL_INT, "IL_INT"},
    { IL_UNSIGNED_INT, "IL_UNSIGNED_INT" },
    { IL_FLOAT, "IL_FLOAT"},
    { IL_DOUBLE, "IL_DOUBLE"}};
#endif

void Texture::load(std::string filename)
{
    ILuint IL_imageId = ilGenImage();
    ilBindImage(IL_imageId);
    
    std::wstring widestr(filename.begin(), filename.end());
    if (!ilLoadImage(widestr.c_str()))
    {
        wprintf(L"IL: cannot  load texture image %s\n", widestr.c_str());
        std::cout << "Error: " << ilGetError() << "\n";
        throw new std::exception("Can't load image");
    }
    // Get parameters
    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);

#if debug
    int format = ilGetInteger(IL_IMAGE_FORMAT);
    int type = ilGetInteger(IL_IMAGE_TYPE);
    printf_s("Texture: %s; Width - %d; Height - %d; IL_Format - %s; IL_Type - %s\n", filename.c_str(), width, height, ilFormats[format], ilTypes[type]);
#endif

    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    {
        iluFlipImage();
    }

    GLubyte* pixels = new GLubyte[width * height * 4];
    ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, GL_UNSIGNED_BYTE, pixels);

    ilDeleteImage(IL_imageId);
    ilBindImage(0);

    glActiveTexture(GL_TEXTURE0); // Choise of active texture block
    glGenTextures(1, &texIndex); // Texture generation
    glBindTexture(GL_TEXTURE_2D, texIndex); // Texture binding

    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // Enable mipmap generation
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set alignment

    // Loading pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] pixels;
}

void Texture::bind(GLenum texUnit)
{
    glEnable(texUnit);
    glActiveTexture(texUnit);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texIndex);
}

void Texture::unbind()
{
    int textureUnits = 0;
    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &textureUnits);
    for(int i = 0;i<textureUnits;i++)
        glDisable(GL_TEXTURE0 + i);

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}