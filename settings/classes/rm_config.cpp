#include "resource_manager.h"

void RM_Init() {
    RM::path = fs::current_path().string() + "/../qt-opengl-graph/";
    RM::toShaders = "settings//shaders//";
    RM::toTextures = "settings//textures//";
    RM::toVertices = "settings//vertices//";

    RM::LoadShader("cube//cube.vert", "cube//cube.frag", "", "cube");
    //RM::LoadShader("model//model.vert", "model//model.frag", "model//model.geom", "model");
    RM::LoadShader("model//model.vert", "model//model.frag", "", "model");
    RM::LoadShader("model_normal//model_normal.vert", "model_normal//model_normal.frag", "", "model_normal");
    RM::LoadShader("model_cluster//model_cluster.vert", "model_cluster//model_cluster.frag", "model_cluster//model_cluster.geom", "model_cluster");
    RM::LoadShader("light//light.vert", "light//light.frag", "", "light");
    RM::LoadShader("stencil//stencil.vert", "stencil//stencil.frag", "", "stencil");
    RM::LoadShader("screen//screen.vert", "screen//screen.frag", "", "screen");
    RM::LoadShader("skybox//skybox.vert", "skybox//skybox.frag", "", "skybox");
    RM::LoadShader("blinn_phong//blinn_phong.vert", "blinn_phong//blinn_phong.frag", "", "blinn_phong");
    RM::LoadShader("refraction//refraction.vert", "refraction//refraction.frag", "", "refraction");
    RM::LoadShader("instance//instance.vert", "instance//instance.frag", "", "instance");
    RM::LoadShader("cluster//cluster.vert", "cluster//cluster.frag", "//cluster//cluster.geom", "cluster");////cluster//cluster.geom
    RM::LoadShader("blinn_phong_shadow//blinn_phong_shadow.vert", "blinn_phong_shadow//blinn_phong_shadow.frag", "", "blinn_phong_shadow");
    RM::LoadShader("shadow_map//shadow_map.vert", "shadow_map//shadow_map.frag", "", "shadow_map");
    RM::LoadShader("normal_mapping//normal_mapping.vert",
                   "normal_mapping//normal_mapping.frag", "", "normal_mapping");
    RM::LoadShader("height_mapping//height_mapping.vert",
                   "height_mapping//height_mapping.frag", "", "height_mapping");
    RM::LoadShader("shadow_omni_map//shadow_omni_map.vert", "shadow_omni_map//shadow_omni_map.frag",
                   "shadow_omni_map//shadow_omni_map.geom", "shadow_omni_map");
    RM::LoadShader("blinn_phong_omni_shadow//blinn_phong_omni_shadow.vert",
                   "blinn_phong_omni_shadow//blinn_phong_omni_shadow.frag", "", "blinn_phong_omni_shadow");
    RM::LoadShader("screen_bloom_mapped//screen_bloom_mapped.vert",
                   "screen_bloom_mapped//screen_bloom_mapped.frag", "", "screen_bloom_mapped");

    RM::LoadTexture("box.png", true, "box");
    RM::LoadTexture("matrix.png", true, "matrix");
    RM::LoadTexture("specbox.png", true, "specbox");
    RM::LoadTexture("grass.png", true, "grass");
    RM::LoadTexture("window.png", true, "window");
    RM::LoadTexture("wood.png", true, "wood");
    RM::LoadTexture("brickwall.jpg", true, "brickwall");
    RM::LoadTexture("brickwall_normal.jpg", true, "brickwall_normal");
    RM::LoadTexture("bricks2.jpg", true, "bricks2");
    RM::LoadTexture("bricks2_disp.jpg", true, "bricks2_disp");
    RM::LoadTexture("bricks2_normal.jpg", true, "bricks2_normal");

    RM::LoadTexture("gate//gate_ambient.jpg", true, "gate_a");
    RM::LoadTexture("gate//gate_diffusion.jpg", true, "gate_d");
    RM::LoadTexture("gate//gate_specular.jpg", true, "gate_s");
    RM::LoadTexture("gate//gate_normal.jpg", true, "gate_n");
    RM::LoadTexture("gate//gate_height_i.png", true, "gate_h");

    RM::LoadTexture("toy_box_normal.png", true, "toy_box_normal");
    RM::LoadTexture("toy_box_disp.png", true, "toy_box_height");

    RM::LoadTextureMaterial("material", {
           RM::GetTexture("window"),
           RM::GetTexture("window"),
           RM::GetTexture("window"),
           40, "textureMaterial"
                                         });

    RM::LoadTextureMaterial("box", {
           RM::GetTexture("box"),
           RM::GetTexture("box"),
           RM::GetTexture("specbox"),
           40, "textureMaterial"
                                         });

    RM::LoadTextureMaterial("grassmat", {
           RM::GetTexture("grass"),
           RM::GetTexture("grass"),
           RM::GetTexture("grass"),
           40, "textureMaterial",
                                         });
    RM::LoadTextureMaterial("woodmat", {
           RM::GetTexture("wood"),
           RM::GetTexture("wood"),
           RM::GetTexture("wood"),
           40, "textureMaterial",
                                         });
    RM::Load_ADSN_TextureMaterial("normal_brickwall", {
           RM::GetTexture("brickwall"),
           RM::GetTexture("brickwall"),
           RM::GetTexture("brickwall"),
           RM::GetTexture("brickwall_normal"),
           40, "textureMaterial",
                                  });
    RM::Load_ADSNH_TextureMaterial("height_brickwall", {
           RM::GetTexture("bricks2"),
           RM::GetTexture("bricks2"),
           RM::GetTexture("bricks2"),
           RM::GetTexture("bricks2_normal"),
           RM::GetTexture("bricks2_disp"),
           40, "textureMaterial",
                                  });
    RM::Load_ADSNH_TextureMaterial("gate", {
           RM::GetTexture("gate_a"),
           RM::GetTexture("gate_d"),
           RM::GetTexture("gate_s"),
           RM::GetTexture("gate_n"),
           RM::GetTexture("gate_h"),
           40, "textureMaterial",
                                  });
    RM::Load_ADSNH_TextureMaterial("toy_box", {
           RM::GetTexture("wood"),
           RM::GetTexture("wood"),
           RM::GetTexture("wood"),
           RM::GetTexture("toy_box_normal"),
           RM::GetTexture("toy_box_height"),
           40, "textureMaterial",
                                  });


    RM::LoadColorMaterial("silver", {
                                      {0.19225, 0.19225,0.19225},
                                      {0.50754, 0.50754, 0.50754},
                                      {0.508273, 0.508273, 0.508273},
                                      40, "colorMaterial"
                                  });

    RM::LoadDirectionLight("light", {
                                      {0.1f, 0.1f, 0.1f},
                                      {0.8f, 0.8f, 0.8f},
                                      {1.0f, 1.0f, 1.0f},
                                       {0,0,0},
                                      glm::cos(glm::radians(17.5f)),
                                      glm::cos(glm::radians(12.5f)),
                                      1, 0.09, 0.032,
                                      "light",
                                  });
    RM::PointLightCollection = {
        new PointLight({
            {0.3f, 0.3f, 0.3f},
            {0.8f, 0.8f, 0.8f},
            {1.0f, 1.0f, 1.0f},
            1, 0.09, 0.032, "pointLights"
        }),
        new PointLight({
            {0.05f, 0.05f, 0.05f},
            {0.8f, 0.8f, 0.8f},
            {1.0f, 1.0f, 1.0f},
            1, 0.09, 0.032, "pointLights"
        }),
        new PointLight({
            {0.05f, 0.05f, 0.05f},
            {0.8f, 0.8f, 0.8f},
            {1.0f, 1.0f, 1.0f},
            1, 0.09, 0.032, "pointLights"
        }),
        new PointLight({
            {0.05f, 0.05f, 0.05f},
            {0.8f, 0.8f, 0.8f},
            {1.0f, 1.0f, 1.0f},
            1, 0.09, 0.032, "pointLights"
        })
    };
    std::string n = std::to_string(19);
    RM::LoadCubeMap({
                                     "textures//Ely"+n+"//Ely"+n+"_px.jpg",
                                     "textures//Ely"+n+"//Ely"+n+"_nx.jpg",
                                     "textures//Ely"+n+"//Ely"+n+"_py.jpg",
                                     "textures//Ely"+n+"//Ely"+n+"_ny.jpg",
                                     "textures//Ely"+n+"//Ely"+n+"_pz.jpg",
                                     "textures//Ely"+n+"//Ely"+n+"_nz.jpg",
                                 },n);
}
