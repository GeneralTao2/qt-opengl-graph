#ifndef SKYBOX_H
#define SKYBOX_H


#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"

class SkyBox
{
public:
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;
    SkyBox(Shader sh = RM::GetShader("skybox"));
    void Init();
    void Drow(SkyBoxArgs args);
    void Drow(glm::mat4 view, glm::mat4 projection, std::string skyboxMap);
};

#endif // SKYBOX_H
