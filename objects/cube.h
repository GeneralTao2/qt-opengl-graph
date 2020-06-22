#ifndef CUBE_H
#define CUBE_H
#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"


class Cube
{
public:
    static float width, height;
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    Cube(Shader sh = RM::GetShader("cube"));
    void Init();
    void Drow(PhongArgs args);
    void Drow(ShadowMapArgs args);
    void Drow(PhongDirectionalShadowArgs args);
    void Drow(ShadowOmniMapArgs args);
    void Drow(PhongOmniShadowArgs args);
};

#endif // CUBE_H
