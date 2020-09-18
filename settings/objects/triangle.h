#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <cmath>
#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "../classes/shader.h"
#include "../classes/resource_manager.h"
#include "../classes/texture.h"
#include "../tools/main_tool.h"

using std::cout;
using std::endl;


class triangle
{
public:
    unsigned int triangleVAO;
    unsigned int colorVAO;
    unsigned int triangleVBO;
    unsigned int colorVBO;

    unsigned int VBOs[10];
    unsigned int VAOs[10];

    size_t dephNumber;

    Shader shader;
    triangle();
    ~triangle();
    void Init();
    void genfrac(std::vector<glm::vec3> vs, int i);
    std::vector<float> vertices;
    void updateVAO();
    void setColor(std::vector<std::vector<double> > a);
    std::vector<std::vector<float>> dephArray;
    void collectByDepth(glm::vec3 position, size_t deph);
    void genVertices(glm::vec3 p, double A, int Deph = 0);
    void Drow(glm::vec3 position, size_t deph);
    void bindVertices(size_t deph);

    std::vector<glm::vec4> triangleVertices;
    std::vector<glm::vec2> triangleTexture;
};

#endif // TRIANGLE_H
