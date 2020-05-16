#include "Texture.h"
#include <iostream>
Texture::Texture()
{
}

Texture::Texture(std::string filename)
{
    load(filename);
}

void Texture::load(std::string filename)
{
    glActiveTexture(GL_TEXTURE0); // Choise of active texture block
    glGenTextures(1, &texIndex); // Texture generation
    glBindTexture(GL_TEXTURE_2D, texIndex); // Texture binding
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE); // Enable mipmap generation
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Set alignment
    GLubyte* pixels;

    // ilInit();
    ILuint imageId = ilGenImage();
    ilBindImage(imageId);
    
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
    int format = ilGetInteger(IL_IMAGE_FORMAT);
    int type = ilGetInteger(IL_IMAGE_TYPE);

#if debug
    printf_s("Texture: %s; Width - %d; Height - %d; IL_Format - %d; IL_Type - %d\n", filename.c_str(), width, height, format, type);
#endif

    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    {
        iluFlipImage();
    }

    pixels = new GLubyte[width * height * 4];
    ilCopyPixels(0, 0, 0, width, height, 1, IL_RGBA, GL_UNSIGNED_BYTE, pixels);
    // Loading pixels into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    ilBindImage(0);
    ilDeleteImage(imageId);

}

void Texture::bind(GLenum texUnit)
{
    glActiveTexture(texUnit);
    glEnable(texUnit);
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