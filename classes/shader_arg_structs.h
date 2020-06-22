#ifndef SHADER_ARG_STRUCTS_H
#define SHADER_ARG_STRUCTS_H

#include <settings/libs/glad/glad.h>
#include <settings/libs/glm/glm.hpp>
#include <settings/libs/glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "resource_manager.h"

struct ColorArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 color;
    Shader shader;
    void Bind();
};

struct SkyBoxArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    CubeMap cubeMap;
    glm::mat4 projection;
    glm::mat4 view;
    Shader shader;
    void Bind();
};

struct PhongArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    std::vector<glm::vec3> lightsPos;
    std::vector<PointLight*> lights;
    glm::vec3 *viewPos;
    ColorMaterial colorMat;
    TextureMaterial textureMat;
    Shader shader;
    void Bind();
};

struct PhongModelArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    std::vector<glm::vec3> lightsPos;
    std::vector<PointLight*> lights;
    glm::vec3 *viewPos;
    ColorMaterial colorMat;
    DepthTesting &depth;
    Shader shader;
    void Bind();
};

struct ShadowMapArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::mat4 lightSpaceMatrix;
    Shader shader;
    void Bind();
};

struct PhongDirectionalShadowArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 lightPos;
    PointLight *light;
    glm::vec3 *viewPos;
    ColorMaterial &colorMat;
    TextureMaterial textureMat;
    Texture2D shadowMap;
    glm::mat4 *lightSpaceMatrix;
    Shader shader;
    void Bind();
};

struct ShadowOmniMapArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 lightPos;
    float near_plane;
    float far_plane;
    std::vector<glm::mat4> shadowTransforms;
    Shader shader;
    void Bind();
};

struct PhongOmniShadowArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 lightPos;
    float near_plane;
    float far_plane;
    bool reverse_normals;
    PointLight *light;
    glm::vec3 *viewPos;
    ColorMaterial &colorMat;
    TextureMaterial textureMat;
    CubeMap shadowMap;
    Shader shader;
    void Bind();
};

struct RefractionArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    CubeMap cubeMap;
    glm::vec3 *viewPos;
    Shader shader;
    void Bind();
};

struct NormalMapArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 *viewPos;
    glm::vec3 lightPos;
    Texture2D diffuseMap;
    Texture2D normalMap;
    PointLight *light;
    Shader shader;
    void Bind();
};

struct ADSN_PhongArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 *viewPos;
    ColorMaterial &colorMat;
    std::vector<glm::vec3> lightsPos;
    std::vector<PointLight*> lights;
    ADSN_TextureMaterial textureMat;
    Shader shader;
    void Bind();
};

struct ADSNH_PhongArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    glm::vec3 *viewPos;
    ColorMaterial &colorMat;
    std::vector<glm::vec3> lightsPos;
    std::vector<PointLight*> lights;
    ADSNH_TextureMaterial textureMat;
    HeightMappingProps &props;
    Shader shader;
    void Bind();
};

struct PostProcessingArgs {
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 axes;
    float angle;
    PostProcessing postProc;
    Shader shader;
    void Bind();
};


#endif // SHADER_ARG_STRUCTS_H
