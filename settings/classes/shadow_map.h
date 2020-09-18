#ifndef SHADOW_MAP_H
#define SHADOW_MAP_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
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
