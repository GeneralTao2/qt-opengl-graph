#ifndef SHADOW_OMNI_MAP_H
#define SHADOW_OMNI_MAP_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
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
