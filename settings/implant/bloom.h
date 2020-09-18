#ifndef BLOOM_H
#define BLOOM_H

#include <glfw3.h>

#include "settings/classes/stb_image.h"

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>

#include <settings/classes/shader.h>
#include "settings/objects/camera.h"

#include <iostream>

class Bloom
{
public:
    unsigned int cubeVAO = 0;
    unsigned int cubeVBO = 0;
    unsigned int quadVAO = 0;
    unsigned int quadVBO;
    unsigned int hdrFBO;
    Shader shader;
    Shader shaderLight;
    Shader shaderBlur;
    Shader shaderBloomFinal;
    Camera &camera;
    unsigned int woodTexture;
    unsigned int containerTexture;
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;
    std::vector<glm::vec3> lightPositions;
    std::vector<glm::vec3> lightColors;
    unsigned int pingpongFBO[2];
    unsigned int colorBuffers[2];
    unsigned int pingpongColorbuffers[2];
    bool bloom = true;
    float exposure = 1.0f;
    Bloom(Camera &Camera1);
    void Init();
    void Drow();
    void renderCube();
    void renderQuad();
    unsigned int loadTexture(char const * path, bool gammaCorrection);
};

#endif // BLOOM_H
