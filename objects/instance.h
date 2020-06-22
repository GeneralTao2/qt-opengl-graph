#ifndef INSTANCE_H
#define INSTANCE_H

#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../classes/model.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"

class instance
{
    public:
    unsigned int VAO;
    unsigned int VBO;
    unsigned int instanceVBO;
    Model model;
    glm::mat4 *modelMatrices;
    unsigned int amount;
    Shader shader;
    instance(Model &m, Shader sh = RM::GetShader("refraction"));
    void calcModels();
    void Init();
    void Drow(glm::vec3 cameraPos);
    void Drow(RefractionArgs args);
};
#endif // INSTANCE_H
