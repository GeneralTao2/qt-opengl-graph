#ifndef PLAIN_NORMAL_MAP_H
#define PLAIN_NORMAL_MAP_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"

class NormalMappedPlain
{
public:
    NormalMappedPlain();
    unsigned int VAO;
    unsigned int VBO;
    void Init();
    void Drow(NormalMapArgs args);
};

#endif // PLAIN_NORMAL_MAP_H
