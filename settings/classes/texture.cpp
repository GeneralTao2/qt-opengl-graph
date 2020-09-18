#include <iostream>

#include "texture.h"
//#include <settings/libs/soil/SOIL.h>

Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_NEAREST)
{
    glGenTextures(1, &ID);
}
Texture2D::Texture2D(int a) {};

void Texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture2D::Generate(GLsizei width, GLsizei height, unsigned char* data)
{
    Width = width;
    Height = height;
    glBindTexture(GL_TEXTURE_2D, ID);
    glTexImage2D(GL_TEXTURE_2D, 0, Internal_Format, width, height, 0, Image_Format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter_Max);
}

CubeMap::CubeMap() : Texture2D() {};
CubeMap::CubeMap(int a) {};

void CubeMap::Bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
}

void CubeMap::Generate(std::vector<unsigned char*> data, std::vector<std::vector<int> > size)
{
    size_arr = size;
    for(GLuint i=0; i<data.size(); i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                 0, GL_RGB, size[i][0], size[i][1], 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]
                    );
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}



