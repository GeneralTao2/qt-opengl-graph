#ifndef SHADOW_OMNI_MAP_H
#define SHADOW_OMNI_MAP_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "resource_manager.h"

class ShadowOmniMap
{
public:
    GLuint width, height;
    GLuint depthMapFBO, depthMap;
    ShadowOmniMap();
    void Init();
    void Begin();
    void End(GLint width_t, GLint height_t);
};

#endif // SHADOW_OMNI_MAP_H
