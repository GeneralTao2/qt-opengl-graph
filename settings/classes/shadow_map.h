#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"

class ShadowMap
{
public:
    GLuint width, height;
    GLuint depthMapFBO, depthMap;
    ShadowMap();
    void Init();
    void Begin();
    void End(GLint width_t, GLint height_t);

};

#endif // SHADOW_MAP_H
