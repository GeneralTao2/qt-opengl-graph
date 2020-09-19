#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"
#include "shader_arg_structs.h"

class framebuffer
{
public:
    framebuffer(GLuint w, GLuint h);
    ~framebuffer();
    GLuint quadVAO, quadVBO,
    textureColorbuffer, fbuffer;
    GLuint width, height;
    void Begin();
    void End();
    void Init();
    void Drow(PostProcessingArgs args);
};

#endif // FRAMEBUFFER_H
