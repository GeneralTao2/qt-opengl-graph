#ifndef SHADER_H
#define SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <settings/libs/glad/glad.h>
#include <glfw3.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/type_ptr.hpp>


class Shader
{
public:
    GLuint ID;
    Shader() { }
    Shader(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr);
    Shader  &Use();
    void    Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); // Note: geometry source code is optional
    void    SetFloat    (const GLchar *name, GLfloat value, GLboolean useShader = false);
    void    SetFloatArray(const GLchar *name, GLfloat *array, GLsizei quantity , GLboolean useShader = false);
    void    SetInteger  (const GLchar *name, GLint value, GLboolean useShader = false);
    void    SetVector2f (const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
    void    SetVector2f (const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
    void    SetVector3f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
    void    SetVector3f (const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
    void    SetVector4f (const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
    void    SetVector4f (const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
    void    SetVector3fArray(std::string name, const std::vector<glm::vec3> &array, GLboolean useShader = false);
    void    SetVector2fArray(std::string name, const std::vector<glm::vec2> &array, GLboolean useShader = false);
    void    SetVector1iArray(std::string name, const std::vector<int> &array, GLboolean useShader = false);
    void    SetVector1fArray(std::string name, const std::vector<float> &array, GLboolean useShader = false);
    void    SetMatrix4  (const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
    void    SetMatrix3  (const GLchar *name, const glm::mat3 &matrix, GLboolean useShader = false);
    void    SetMatrix4Array(std::string name, const std::vector<glm::mat4> &array, GLboolean useShader = false);
private:
    void    checkCompileErrors(GLuint object, std::string type);
};


#endif // SHADER_H
