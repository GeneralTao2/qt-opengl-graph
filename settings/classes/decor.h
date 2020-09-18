#ifndef DECOR_H
#define DECOR_H

#include "shader.h"
#include "texture.h"

struct ColorMaterial {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    std::string var;
    void bind(Shader &s);
};

struct TextureMaterial {
    Texture2D ambient;
    Texture2D diffuse;
    Texture2D specular;
    float shininess;
    std::string var;
    std::vector<int> list;
    TextureMaterial(Texture2D Ambient, Texture2D Diffuse, Texture2D Specular,
                    float Shininess, std::string Var);
    TextureMaterial(const TextureMaterial &a) = default;
    TextureMaterial() = default;
    void init(Shader &s, std::vector<int> list = {0, 1, 2});
    void bind(Shader &s);
};

struct ADSN_TextureMaterial {
    Texture2D ambient;
    Texture2D diffuse;
    Texture2D specular;
    Texture2D normal;
    float shininess;
    std::string var;
    std::vector<int> list;
    ADSN_TextureMaterial(Texture2D Ambient, Texture2D Diffuse, Texture2D Specular, Texture2D Normal,
                    float Shininess, std::string Var);
    ADSN_TextureMaterial(const ADSN_TextureMaterial &a) = default;
    ADSN_TextureMaterial() = default;
    void init(Shader &s, std::vector<int> list = {0, 1, 2, 4});
    void bind(Shader &s);
};

struct ADSNH_TextureMaterial {
    Texture2D ambient;
    Texture2D diffuse;
    Texture2D specular;
    Texture2D normal;
    Texture2D height;
    float shininess;
    std::string var;
    std::vector<int> list;
    ADSNH_TextureMaterial(Texture2D Ambient, Texture2D Diffuse, Texture2D Specular, Texture2D Normal,
                    Texture2D Height, float Shininess, std::string Var);
    ADSNH_TextureMaterial(const ADSNH_TextureMaterial &a) = default;
    ADSNH_TextureMaterial() = default;
    void init(Shader &s, std::vector<int> list = {0, 1, 2, 4, 5});
    void bind(Shader &s);
};


struct PointLight {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    std::string var;
    void bind(Shader &s);
    void bind(Shader &s, std::string var);
    void bind(Shader &s, GLuint i);
    PointLight mixWithColor(glm::vec3 color);
};

struct DirectionLight {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 direction;
    float outerCutOff;
    float cutOff;
    float constant;
    float linear;
    float quadratic;
    std::string var;
    void bind(Shader &s);
    DirectionLight mixWithColor(glm::vec3 color);
};

struct DepthTesting {
    float Near;
    float Far;
    bool enabled;
};

struct HeightMappingProps {
    float minLayers;
    float maxLayers;
    float height_scale;
};

struct PostProcessing {
    float exposure = 0.5;
    int mode = 0;
    float gamma = 1.53;
    float offset = 0.03;
    std::vector<float> kernelMat = {
        -1, -1, -1,
        -1, 9, -1,
        -1, -1, -1
    };
    int currentMat = 0;
    std::vector<const char*> kernelNames = {
        "sharpen",
        "blur",
        "endgeDetection"
    };
    std::vector<std::vector<float>> kernelMats = {
        {
            -1, -1, -1,
            -1, 9, -1,
            -1, -1, -1
        },{
            1.0 / 16, 2.0 / 16, 1.0 / 16,
            2.0 / 16, 4.0 / 16, 2.0 / 16,
            1.0 / 16, 2.0 / 16, 1.0 / 16
        },{
            1, 1, 1,
            1, -8, 1,
            1, 1, 1
        }
    };
};



#endif // DECOR_H
