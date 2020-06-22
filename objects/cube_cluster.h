#ifndef CUBE_CLUSTER_H
#define CUBE_CLUSTER_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../classes/shader_arg_structs.h"

class CubeCluster
{
public:
    int quantity;
    CubeCluster(Shader sh = RM::GetShader("cluster"));
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    void Init();
    void Drow(PhongArgs args);
};

#endif // CUBE_CLUSTER_H
