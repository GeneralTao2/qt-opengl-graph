#ifndef BLOOM_MAPPING_H
#define BLOOM_MAPPING_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"
#include "shader_arg_structs.h"

class BloomMapping
{
public:
    BloomMapping(GLuint w, GLuint h);
    ~BloomMapping();
    GLuint quadVAO, quadVBO,
    textureColorbuffers[2], fbuffer, intermediateFBO;
    GLuint width, height;
    void Begin();
    void End();
    void Init();
    void Drow(PostProcessingArgs args);
};

#endif // BLOOM_MAPPING_H
