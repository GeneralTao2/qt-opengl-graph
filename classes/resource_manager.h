#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
//#include <settings/libs/soil/SOIL.h>
#include "stb_image.h"
#include <settings/libs/glad/glad.h>
#include "texture.h"
#include "shader.h"
#include "decor.h"

class RM
{
public:
    //configs
    static std::string path;
    static std::string toShaders;
    static std::string toVertices;
    static std::string toTextures;
    //shader
    static std::map<std::string, Shader>    Shaders;
    static Shader   LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name);
    static Shader   &GetShader(std::string name);
    //texture
    static std::map<std::string, Texture2D> Textures;
    static Texture2D LoadTexture(std::string file, GLboolean alpha, std::string name);
    static Texture2D &GetTexture(std::string name);
    //color material
    static std::map<std::string, ColorMaterial> ColorMaterials;
    static ColorMaterial LoadColorMaterial(std::string name, ColorMaterial mat);
    static ColorMaterial &GetColorMaterial(std::string name);
    //texture material
    static std::map<std::string, TextureMaterial> TextureMaterials;
    static TextureMaterial LoadTextureMaterial(std::string name, TextureMaterial mat);
    static TextureMaterial &GetTextureMaterial(std::string name);
    static std::map<std::string, ADSN_TextureMaterial> ADSN_TextureMaterials;
    static ADSN_TextureMaterial Load_ADSN_TextureMaterial(std::string name, ADSN_TextureMaterial mat);
    static ADSN_TextureMaterial &Get_ADSN_TextureMaterial(std::string name);
    static std::map<std::string, ADSNH_TextureMaterial> ADSNH_TextureMaterials;
    static ADSNH_TextureMaterial Load_ADSNH_TextureMaterial(std::string name, ADSNH_TextureMaterial mat);
    static ADSNH_TextureMaterial &Get_ADSNH_TextureMaterial(std::string name);
    //point light
    static std::map<std::string, PointLight*> PointLights;
    static std::vector<PointLight*> PointLightCollection;
    static PointLight LoadPointLight(std::string name, PointLight light);
    static PointLight *GetPointLight(std::string name);
    //direction light
    static std::map<std::string, DirectionLight> DirectionLights;
    static DirectionLight LoadDirectionLight(std::string name, DirectionLight light);
    static DirectionLight &GetDirectionLight(std::string name);
    //vertices
    static std::map<std::string, std::vector<float>> Vertices;
    static std::vector<float> LoadVertices(std::string file, std::string name);
    static std::vector<float> &GetVertices(std::string name);
    //private
    static void      Clear();
    static Shader    loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile = nullptr);
    static std::vector<float> loadVerticesFromFile(std::string file);
    static Texture2D loadTextureFromFile(std::string file, GLboolean alpha);
    static Texture2D loadTextureFromFileMat(std::string file, GLboolean alpha);
    static unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = 0);
    //skubox
    static CubeMap loadCubemap(std::vector<std::string> faces);
    static std::map<std::string, CubeMap> CubeMaps;
    static CubeMap LoadCubeMap(std::vector<std::string> faces, std::string name);
    static CubeMap &GetCubeMap(std::string name);
private:
    RM() { }
};

#endif // RESOURCE_MANAGER_H
