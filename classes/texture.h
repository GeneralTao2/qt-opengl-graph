#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <vector>
#include <settings/libs/glad/glad.h>

// Texture2D is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture2D
{
public:
    // Holds the ID of the texture object, used for all texture operations to reference to this particlar texture
    GLuint ID = -1;
    GLuint MID[3];
    // Texture image dimensions
    GLsizei Width, Height; // Width and height of loaded image in pixels
    // Texture Format
    GLint Internal_Format; // Format of texture object
    GLuint Image_Format; // Format of loaded image
    // Texture configuration
    GLint Wrap_S; // Wrapping mode on S axis
    GLint Wrap_T; // Wrapping mode on T axis
    GLint Filter_Min; // Filtering mode if texture pixels < screen pixels
    GLint Filter_Max; // Filtering mode if texture pixels > screen pixels
    Texture2D();
    Texture2D(int a);
    void Generate(GLsizei width, GLsizei height, unsigned char* data);
    void Bind() const;
};

class CubeMap : public Texture2D
{
public:
    std::vector<std::vector<int>> size_arr;
    CubeMap();
    CubeMap(int a);
    void Generate(std::vector<unsigned char *> data, std::vector<std::vector<int>> size);
    void Bind() const;
};

#endif // TEXTURE_H
