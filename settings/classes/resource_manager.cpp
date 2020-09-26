#include "resource_manager.h"


std::map<std::string, Texture2D>           RM::Textures;
std::map<std::string, Shader>              RM::Shaders;
std::map<std::string, std::vector<float>>  RM::Vertices;
std::map<std::string, ColorMaterial>       RM::ColorMaterials;
std::map<std::string, TextureMaterial>     RM::TextureMaterials;
std::map<std::string, ADSN_TextureMaterial> RM::ADSN_TextureMaterials;
std::map<std::string, ADSNH_TextureMaterial> RM::ADSNH_TextureMaterials;
std::map<std::string, PointLight*>         RM::PointLights;
std::vector<PointLight*>                   RM::PointLightCollection;
std::map<std::string, DirectionLight>      RM::DirectionLights;
std::map<std::string, CubeMap>             RM::CubeMaps;
std::string                                RM::path;
std::string                                RM::toShaders;
std::string                                RM::toVertices;
std::string                                RM::toTextures;
Shader RM::LoadShader(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile, std::string name)
{
    Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return Shaders[name];
}

ColorMaterial RM::LoadColorMaterial(std::string name, ColorMaterial mat) {
    ColorMaterials[name] = mat;
    return ColorMaterials[name];
}
TextureMaterial RM::LoadTextureMaterial(std::string name, TextureMaterial mat) {
    TextureMaterials[name] = mat;
    return TextureMaterials[name];
}
ADSN_TextureMaterial RM::Load_ADSN_TextureMaterial(std::string name, ADSN_TextureMaterial mat) {
    ADSN_TextureMaterials[name] = mat;
    return ADSN_TextureMaterials[name];
}
ADSNH_TextureMaterial RM::Load_ADSNH_TextureMaterial(std::string name, ADSNH_TextureMaterial mat) {
    ADSNH_TextureMaterials[name] = mat;
    return ADSNH_TextureMaterials[name];
}
PointLight RM::LoadPointLight(std::string name, PointLight light) {
    PointLights[name] = new PointLight(light);
    return *PointLights[name];
}
DirectionLight RM::LoadDirectionLight(std::string name, DirectionLight light) {
    DirectionLights[name] = light;
    return DirectionLights[name];
}

Shader &RM::GetShader(std::string name)
{
    if(!Shaders.count(name))
        std::cout << "Error! Shaders doesn't has " << name << std::endl;
    return Shaders[name];
}

Texture2D RM::LoadTexture(std::string file, GLboolean alpha, std::string name)
{
    Textures[name] = loadTextureFromFile(file, alpha);
    return Textures[name];
}
Texture2D &RM::GetTexture(std::string name)
{
    if(!Textures.count(name))
        std::cout << "Error! Textures doesn't has " << name << std::endl;
    return Textures[name];
}

CubeMap RM::LoadCubeMap(std::vector<std::string> faces, std::string name)
{
    CubeMaps[name] = loadCubemap(faces);
    return CubeMaps[name];
}

CubeMap &RM::GetCubeMap(std::string name)
{
    if(!CubeMaps.count(name))
        std::cout << "Error! CubeMaps doesn't has " << name << std::endl;
    return CubeMaps[name];
}

std::vector<float> RM::LoadVertices(std::string file, std::string name) {
    Vertices[name] = loadVerticesFromFile(file);
    return Vertices[name];
}
std::vector<float>  &RM::GetVertices(std::string name) {
    if(!Vertices.count(name))
        std::cout << "Error! Vertices doesn't has " << name << std::endl;
    return Vertices[name];
}
ColorMaterial &RM::GetColorMaterial(std::string name) {
    if(!ColorMaterials.count(name))
        std::cout << "Error! ColorMaterials doesn't has " << name << std::endl;
    return ColorMaterials[name];
}
TextureMaterial &RM::GetTextureMaterial(std::string name) {
    if(!TextureMaterials.count(name))
        std::cout << "Error! TextureMaterials doesn't has " << name << std::endl;
    return TextureMaterials[name];
}
ADSN_TextureMaterial &RM::Get_ADSN_TextureMaterial(std::string name) {
    if(!ADSN_TextureMaterials.count(name))
        std::cout << "Error! Texture_ADSN_Materials doesn't has " << name << std::endl;
    return ADSN_TextureMaterials[name];
}
ADSNH_TextureMaterial &RM::Get_ADSNH_TextureMaterial(std::string name) {
    if(!ADSNH_TextureMaterials.count(name))
        std::cout << "Error! Texture_ADSNH_Materials doesn't has " << name << std::endl;
    return ADSNH_TextureMaterials[name];
}
PointLight *RM::GetPointLight(std::string name) {
    if(!PointLights.count(name))
        std::cout << "Error! PointLights doesn't has " << name << std::endl;
    return PointLights[name];
}
DirectionLight &RM::GetDirectionLight(std::string name) {
    if(!DirectionLights.count(name))
        std::cout << "Error! DirectionLights doesn't has " << name << std::endl;
    return DirectionLights[name];
}
void RM::Clear()
{
    // (Properly) delete all shaders
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (Properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader RM::loadShaderFromFile(std::string vShaderFile, std::string fShaderFile, std::string gShaderFile)
{
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // Open files
        std::ifstream vertexShaderFile(path + toShaders + vShaderFile);
        std::ifstream fragmentShaderFile(path + toShaders + fShaderFile);
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "")
        {
            std::ifstream geometryShaderFile(path + toShaders + gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    Shader shader;
    shader.Compile(vShaderCode, fShaderCode, gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

Texture2D RM::loadTextureFromFile(std::string file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    file = path + toTextures + file;
    int width, height;
    unsigned char* image = stbi_load(file.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
    if(!image) {
        std::cout << "Error! Failed to load texture from " << file << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
    }
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}

Texture2D RM::loadTextureFromFileMat(std::string file, GLboolean alpha)
{
    Texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    file = path + toTextures + file;
    int width, height;
    unsigned char* image = stbi_load(file.c_str(), &width, &height, 0, texture.Image_Format == GL_RGBA ? GL_RGBA : GL_RGB);
    texture.Generate(width, height, image);
    stbi_image_free(image);
    return texture;
}
std::vector<float>  RM::loadVerticesFromFile(std::string file) {
    std::vector<float> vertices;
    try {
        std::ifstream in(path + toVertices + file);
        if(!in.is_open())
            throw std::exception();
        float v;
        while(in >> v) {
            vertices.push_back(v);
        }
    } catch (std::exception e) {
        std::cout << "ERROR::VERTICES: Failed to read shader files" << std::endl;
    }
    return vertices;
}
unsigned int RM::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + "/" + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    //unsigned char* data = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_AUTO);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        std::cout << stbi_failure_reason() << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

CubeMap RM::loadCubemap(std::vector<std::string> faces)
{
    CubeMap map;
    map.Bind();
    std::vector<unsigned char*> data_arr(faces.size());
    std::vector<std::vector<int>> size_arr(faces.size(), std::vector<int>(2));
    int width, height, nrChannels;
    for (size_t i=0; i<faces.size(); i++) {
        faces[i] = path + toTextures + faces[i];
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            data_arr[i] = data;
            size_arr[i] = { width, height };
        } else {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    map.Generate(data_arr, size_arr);
    for(unsigned char* data: data_arr) {
        stbi_image_free(data);
    }
    return map;
}
