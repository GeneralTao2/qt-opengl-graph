#ifndef PLAIN_H
#define PLAIN_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"

class Plain
{
public:
    static float width, height;
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    Plain(Shader sh = RM::GetShader("cube"));
    void Init();
    void Drow(PhongArgs args);
    void Drow(ShadowMapArgs args);
    void Drow(PhongDirectionalShadowArgs args);
};

#endif // PLAIN_H
