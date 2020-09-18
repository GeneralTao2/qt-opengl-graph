#ifndef LIGHT_H
#define LIGHT_H
#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../classes/shader_arg_structs.h"

class Light
{
public:
    //static float width, height;
    unsigned int VAO;
    unsigned int VBO;
    Shader shader;

    struct props {
        glm::vec3 position;
        glm::vec3 color;
    } Prop;

    Light();
    void Init();
    void Drow(ColorArgs args);
};

#endif // LIGHT_H
