#ifndef ANTI_ALIASING_H
#define ANTI_ALIASING_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"
#include "shader_arg_structs.h"

class AntiAliasing
{
public:
    AntiAliasing(GLuint w, GLuint h);
    ~AntiAliasing();
    GLuint quadVAO, quadVBO,
    textureColorbuffer, fbuffer, intermediateFBO;
    GLuint width, height;
    void Begin();
    void End();
    void Init();
    void Drow(PostProcessingArgs args);
};

#endif // ANTI_ALIASING_H
