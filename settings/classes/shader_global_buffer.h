#ifndef SHADER_GLOBAL_BUFFER_H
#define SHADER_GLOBAL_BUFFER_H

#include "resource_manager.h"

class ShaderGlobalBuffer
{
public:
    GLuint UBO;
    ShaderGlobalBuffer(std::vector<std::string> shaders);
    ~ShaderGlobalBuffer();
    void Init();
    void Bind(glm::mat4 projection, glm::mat4 view);
};

#endif // SHADER_GLOBAL_BUFFER_H
