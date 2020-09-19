#ifndef CUBE_NORMAL_MAPPED_H
#define CUBE_NORMAL_MAPPED_H

#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "light.h"
#include "../classes/shader_arg_structs.h"


class NormalMappedCube
{
public:
    NormalMappedCube();
    unsigned int VAO;
    unsigned int VBO;
    std::vector<float> vertices;
    void calcPlane(std::vector<glm::vec3> &position, std::vector<glm::vec2> &texPos, glm::vec3 normal);
    void Init();
    void Drow(NormalMapArgs args);
    void Drow(ADSN_PhongArgs args);
    void Drow(ADSNH_PhongArgs args);
};

#endif // CUBE_NORMAL_MAPPED_H
