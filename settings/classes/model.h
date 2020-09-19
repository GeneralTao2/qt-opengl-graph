#ifndef MODEL_H
#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"
#include "resource_manager.h"
#include "mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "shader_arg_structs.h"
class Model
{
public:
    /*  Model Data  */
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    /*  Functions   */
    Model(std::string path)
    {
        loadModel(path);
    }
    void Draw(PhongModelArgs args);
    void Draw(ColorArgs args);
    void Draw(ADSN_PhongArgs args);
private:
    /*  Functions   */
    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);
};
#endif // MODEL_H
