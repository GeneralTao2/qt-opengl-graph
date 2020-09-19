#include <iostream>
//#include <windows.h>
#include <cmath>
#ifdef _WIN32
    #define APIENTRY __stdcall
#endif
#include <src/glad.c>
#ifdef _WINDOWS_
#endif
#define GLEW_STATIC
#include <glad/glad.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <settings/classes/shader.h>
#include <settings/classes/resource_manager.h>
#include "settings/classes/display.h"
#include "settings/classes/imgu_manager.h"
#include "settings/objects/cube.h"
#include "settings/objects/camera.h"
#include "settings/objects/light.h"
#include "settings/classes/model.h"
#include "settings/classes/decor.h"
#include "settings/objects/plain.h"
#include "settings/objects/skybox.h"
#include "settings/classes/framebuffer.h"
#include "settings/classes/shader_global_buffer.h"
#include "settings/classes/anti_aliasing.h"
#include "settings/objects/cube_cluster.h"
#include "settings/objects/instance.h"
#include "settings/classes/shadow_map.h"
#include "settings/classes/rm_config.cpp"
#include "settings/classes/shader_arg_structs.h"
#include "settings/classes/shadow_omni_map.h"
#include "settings/objects/plain_normal_map.h"
#include "settings/objects/cube_normal_mapped.h"
#include "settings/classes/bloom_mapping.h"
#include "settings/implant/bloom.h"

#include <filesystem>


static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
glm::vec3 getSinColor() {
    return {sin(glfwGetTime())/2 + 0.5, sin(glfwGetTime()*3)/2 + 0.5, sin(glfwGetTime()*5)/2 + 0.5};
}

glm::vec3 globalPos(-10,10,0);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool cursorFlag = false;
float lastCursorReaction = 0;

void renderOmniShadowScene(ShadowOmniMapArgs args, Cube cube);
void renderOmniShadowScene(PhongOmniShadowArgs args, Cube cube);

#include <irrKlang.h>

#if defined(WIN32)
#include <conio.h>
#else
//#include "../common/conio.h"
#endif

using namespace irrklang;

int main()
{
    std::cout << "Start..." << std::endl;
    ISoundEngine* engine = createIrrKlangDevice();
    if (!engine) {
        printf("Could not startup enginen");
        return 0; // error starting up the engine
    }
    engine->play2D("/home/tao/qt-projects/new-graph/qt-opengl-graph/irrKlang-64bit-1.6.0/media/getout.ogg", true);

    glm::vec3(0.0f, 0.0f, 3.0f);
    //-------------------------------------------- GLFW CONFIGS ---------------
    camera.MovementSpeed = 6;
    // Setup window
    //glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER  , GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    glfwWindowHint(GLFW_SAMPLES, 4);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OPENGL", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSwapInterval(1); // Enable vsync

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    bool err = gladLoadGL() == 0;

    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    //------------------------------------------------------------ DATA ---------------
    RM_Init();
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };
    std::vector<glm::vec3> pointLightPositions = {
        { 0.7f,  0.2f,  2.0f},
        { 2.3f, -3.3f, -4.0f},
        {-4.0f,  2.0f, -12.0f},
        { 0.0f,  0.0f, -3.0f}
    };
    int k = 1;
    for(int i=0; i<k; i++) {
        for(int j=0; j<k; j++) {
            for(int l=0; l<k; l++) {
                pointLightPositions.push_back({i*6 + 4, j*6 +0.5, l*6 +0.5});
                glm::vec3 color = glm::vec3((rand()%10 + 5)/5,(rand()%5 + 5)/5,(rand()%10 + 5)/5);
                RM::PointLightCollection.push_back(new PointLight({
                 {0.05f, 0.05f, 0.05f},
                 {1, 1, 0},
                 {1.0f, 1.0f, 1.0f},
                 1, 0.09, 0.032, "pointLights"
                   }) );
            }
        }
    }

    glm::vec3 *viewPos = new glm::vec3();

    std::vector<PointLight*> pointLightArray = RM::PointLightCollection;
    ColorArgs colorArgs {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, glm::vec3(0.5),
        RM::GetShader("light")
    };

    SkyBoxArgs skyBoxArgs {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, RM::GetCubeMap("19"),
        glm::mat4(), glm::mat4(),
        RM::GetShader("skybox")
    };

    DepthTesting depth = {0.1, 100, false};
    HeightMappingProps heightProps = {8, 32, 0.1};
    PhongModelArgs phongModelArgs = {
        glm::vec3(0),
        glm::vec3(0.2),
        glm::vec3(1),
        0, pointLightPositions,
        pointLightArray,
        viewPos,
        RM::GetColorMaterial("silver"),
        depth, RM::GetShader("model")
    };

    std::vector<glm::vec3> shadowCubesPos = {
        {-3.0f, 1.5f, 0.0},
        {-2.0f, 0.0f, 1.0}
    };
    PhongArgs phongArgs = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, pointLightPositions,
        RM::PointLightCollection,
        viewPos,
        RM::GetColorMaterial("silver"),
        RM::GetTextureMaterial("material"),
        RM::GetShader("cube")
    };

    size_t PDS_lightIndex = pointLightArray.size();
    pointLightPositions.push_back( {-3.0f, 4.0f, -1.0f} );
    pointLightArray.push_back(RM::PointLightCollection[0]);
    ShadowMapArgs shadowMapArgs = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0,glm::mat4(0),
        RM::GetShader("shadow_map")
    };
    PhongDirectionalShadowArgs PDShadowArgsCube = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, pointLightPositions[PDS_lightIndex],
        pointLightArray[PDS_lightIndex],
        viewPos, RM::GetColorMaterial("silver"),
        RM::GetTextureMaterial("woodmat"),
        NULL, new glm::mat4(0),
        RM::GetShader("blinn_phong_shadow")
    };
    PhongDirectionalShadowArgs PDShadowArgsPlane = PDShadowArgsCube;
    PDShadowArgsPlane.position = {0,-0.5, 0};
    PDShadowArgsPlane.scale = glm::vec3(35);
    PDShadowArgsPlane.axes = {1, 0, 0};
    PDShadowArgsPlane.angle = 3.14/2;

    float POS_near_plane = 1, POS_far_plane = 30;
    size_t POS_lightIndex = pointLightArray.size();
    pointLightPositions.push_back( glm::vec3(0) + globalPos );
    pointLightArray.push_back(RM::PointLightCollection[0]);
    ShadowOmniMapArgs shadowOmniMapArgs = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, pointLightPositions[POS_lightIndex],
        POS_near_plane,
        POS_far_plane, std::vector<glm::mat4>(6),
        RM::GetShader("shadow_omni_map")
    };
    PhongOmniShadowArgs POShadowArgsCube = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, pointLightPositions[POS_lightIndex],
        POS_near_plane, POS_far_plane, 0,
        pointLightArray[POS_lightIndex],
        viewPos, RM::GetColorMaterial("silver"),
        RM::GetTextureMaterial("woodmat"),
        NULL,
        RM::GetShader("blinn_phong_omni_shadow")
    };

    RefractionArgs refractionArgs = {
        glm::vec3(0),
        glm::vec3(1),
        glm::vec3(1),
        0, RM::GetCubeMap("19"),
        viewPos,
        RM::GetShader("refraction")
    };

    NormalMapArgs normalMapArgs = {
        glm::vec3(0,0,0.6),
        glm::vec3(1),
        glm::vec3(1),
        0, viewPos,
        pointLightPositions[0],
        RM::GetTexture("brickwall"),
        RM::GetTexture("brickwall_normal"),
        pointLightArray[0],
        RM::GetShader("normal_mapping")
    };

    ADSN_PhongArgs ADSN_phongArgs = {
        glm::vec3(0,0,0.6),
        glm::vec3(1),
        glm::vec3(1),
        0, viewPos,
        RM::GetColorMaterial("silver"),
        pointLightPositions,
        RM::PointLightCollection,
        RM::Get_ADSN_TextureMaterial("normal_brickwall"),
        RM::GetShader("normal_mapping")
    };

    ADSNH_PhongArgs ADSNH_phongArgs = {
        glm::vec3(0,0,0.6),
        glm::vec3(1),
        glm::vec3(1),
        0, viewPos,
        RM::GetColorMaterial("silver"),
        pointLightPositions,
        RM::PointLightCollection,
        RM::Get_ADSNH_TextureMaterial("gate"),
        heightProps,
        RM::GetShader("height_mapping")
    };

    PostProcessingArgs postProcessingArgs = {
        glm::vec3(0,0,0.6),
        glm::vec3(1),
        glm::vec3(1),
        0, PostProcessing(),
        RM::GetShader("screen")
    };


    //-------------------------------------------------------- OBJECTS -----------------
    Cube box;
    Plain sheet;
    NormalMappedPlain normalMappedPlain;
    NormalMappedCube normalMappedCube;
    Light source;
    ShadowOmniMap shadowOmniMap;
    SkyBox sky;
    CubeCluster cluster;
    AntiAliasing screen(SCR_WIDTH, SCR_HEIGHT);
    //framebuffer screen(SCR_WIDTH, SCR_HEIGHT);
    //framebuffer test(SCR_WIDTH, SCR_HEIGHT);
    //BloomMapping screen(SCR_WIDTH, SCR_HEIGHT);
    RM::GetShader("model").Use();
    Model nanosoult(std::filesystem::current_path().string() + "/../qt-opengl-graph/settings//models//nanosuit//nanosuit.obj");
    //Model nanosoult("C://Users//ar725//Documents//qt//graph//settings//models//sponza//sponza.obj");
    //Model nanosoult("C://Users//ar725//Documents//qt//graph//settings//models//black_girl//girl.obj");
    Model rock(std::filesystem::current_path().string() + "/../qt-opengl-graph//settings//models//rock//rock.obj");
    imgu_manager interf(window);
    ShaderGlobalBuffer shProjView({ "cube", "light", "stencil",
                                    "model", "cluster", "instance",
                                  "refraction", "blinn_phong_shadow",
                                  "blinn_phong_omni_shadow", "normal_mapping"});

    instance inst(rock);

    ShadowMap shadowMap;

    //----------------------------------------------------------- CONFIGS -----------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glDepthFunc(GL_ALWAYS);
    glDepthFunc(GL_LESS);
    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);
    glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glEnable(GL_FRAMEBUFFER_SRGB);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();
        processInput(window);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.1f, 1.0f, 1.0f);

        shProjView.Bind(projection, view);
        *viewPos = camera.Position;
        //----------------------------------------------- DIRECTIONAL SHADOW -----------


        float near_plane = 1.0f, far_plane = 7.5f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
        glm::mat4 lightView = glm::lookAt(pointLightPositions[PDS_lightIndex], glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        shadowMapArgs.lightSpaceMatrix = lightSpaceMatrix;
        *PDShadowArgsCube.lightSpaceMatrix = lightSpaceMatrix;
        shadowMap.Begin();

        shadowMapArgs.position = shadowCubesPos[0];
        box.Drow(shadowMapArgs);
        shadowMapArgs.position = shadowCubesPos[1];
        box.Drow(shadowMapArgs);
        shadowMapArgs.position = PDShadowArgsPlane.position;
        sheet.Drow(shadowMapArgs);

        shadowMap.End(SCR_WIDTH, SCR_HEIGHT);

        PDShadowArgsCube.shadowMap.ID = PDShadowArgsPlane.shadowMap.ID = shadowMap.depthMap;

        //---------------------------------------------- POINT SHADOW -----------------------
        glm::mat4 shadowProj = glm::perspective(glm::radians(90.0f), (float)shadowOmniMap.width / (float)shadowOmniMap.height, shadowOmniMapArgs.near_plane, shadowOmniMapArgs.far_plane);
        shadowOmniMapArgs.shadowTransforms[0] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f));
        shadowOmniMapArgs.shadowTransforms[1] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f));
        shadowOmniMapArgs.shadowTransforms[2] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f));
        shadowOmniMapArgs.shadowTransforms[3] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f));
        shadowOmniMapArgs.shadowTransforms[4] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f));
        shadowOmniMapArgs.shadowTransforms[5] = shadowProj * glm::lookAt(shadowOmniMapArgs.lightPos, shadowOmniMapArgs.lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f));
        shadowOmniMap.Begin();
        renderOmniShadowScene(shadowOmniMapArgs, box);
        shadowOmniMap.End(SCR_WIDTH, SCR_HEIGHT);

        //----------------------------------------------- POST PROC ----------------------
        screen.Begin();
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glStencilMask(0x00);

        //std::cout << RM::GetCubeMap("19").ID << ' ' << shadowOmniMap.depthMap << std::endl;
        //RM::GetCubeMap("19").ID = shadowOmniMap.depthMap;
        //RM::GetCubeMap("19").ID = RM::GetCubeMap("18").ID;
        //--------------------------------------------------- SKYBOX-------------
        skyBoxArgs.view = glm::mat4(glm::mat3(view));
        skyBoxArgs.projection = projection;
        sky.Drow(skyBoxArgs);

        //-------------------------------------------------- NORMAL CUBE -----
        ADSN_phongArgs.position = {0, 0.5, -7};
        ADSN_phongArgs.scale = glm::vec3(1);
        ADSN_phongArgs.shader = RM::GetShader("normal_mapping");
        normalMappedCube.Drow(ADSN_phongArgs);

        //--------------------------------------------------- HEIGHT CUBE -----
        ADSNH_phongArgs.position = {2, 0.5, -7};
        normalMappedCube.Drow(ADSNH_phongArgs);

        //--------------------------------------------------- DIR SHADOW CUBES ----
        PDShadowArgsCube.position = shadowCubesPos[0];
        box.Drow(PDShadowArgsCube);
        PDShadowArgsCube.position = shadowCubesPos[1];
        box.Drow(PDShadowArgsCube);
        sheet.Drow(PDShadowArgsPlane);

        //-------------------------------------------------- POINT SHADOW CUBES ---
        POShadowArgsCube.shadowMap.ID = shadowOmniMap.depthMap;
        renderOmniShadowScene(POShadowArgsCube, box);

        //--------------------------------------------------- INSTANCE -----------
        inst.Drow(refractionArgs);

        //--------------------------------------------------- LIGHTS ---------
        colorArgs.scale = glm::vec3(0.2);
        colorArgs.shader = RM::GetShader("light");
        for(size_t i=0; i<pointLightPositions.size();i++) {
            colorArgs.position = pointLightPositions[i];
            colorArgs.color = pointLightArray[i]->diffuse;
            source.Drow(colorArgs);
        }

        //---------------------------------------------------- CLUSTER --------
        phongArgs.shader = RM::GetShader("cluster");
        phongArgs.position = {3,0,0};
        phongArgs.textureMat = RM::GetTextureMaterial("box");
        cluster.Drow(phongArgs);

        //---------------------------------------------------------- CUBES ----------
        phongArgs.shader = RM::GetShader("cube");
        phongArgs.textureMat = RM::GetTextureMaterial("material");
        glEnable(GL_BLEND);
        for(auto a: cubePositions) {
            phongArgs.position = a;
            box.Drow(phongArgs);
        }
        //---------------------------------------------------- GRASS ------------
        phongArgs.textureMat = RM::GetTextureMaterial("grassmat");
        phongArgs.position = {0,0,-4};
        sheet.Drow(phongArgs);
        glDisable(GL_BLEND);

        //------------------------------------------------------- MODEL -------------
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        ADSN_phongArgs.shader = RM::GetShader("model_normal");
        ADSN_phongArgs.position = colorArgs.position = {0,0,-2};
        ADSN_phongArgs.scale = colorArgs.scale = glm::vec3(0.2);
        nanosoult.Draw(ADSN_phongArgs);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        colorArgs.shader = RM::GetShader("stencil");
        //colorArgs.color = getSinColor();
        nanosoult.Draw(colorArgs);

        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);

        screen.End();

        screen.Drow(postProcessingArgs);

        //----------------------------------------------------- INTERFACE -----------
        if(cursorFlag) {
            interf.Begin();
            interf.drowDepthTesting(depth);
            interf.drowPostProcessing(postProcessingArgs.postProc);
            interf.drowColorMaterial(RM::ColorMaterials["silver"]);
            interf.drowHeightMappingProps(heightProps);
            for(int i=0; i<4; i++)
                interf.drowPointLight(*RM::PointLightCollection[i], std::to_string(i));
            interf.End();
        }

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
void renderOmniShadowScene(ShadowOmniMapArgs args, Cube cube) {
    args.scale = glm::vec3(10);
    args.angle = 0;
    args.axes = glm::vec3(1);
    args.position = glm::vec3(0)+globalPos;
    glDisable(GL_CULL_FACE);
    cube.Drow(args);
    glEnable(GL_CULL_FACE);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(4.0f, -3.5f, 0.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(0.5);
    args.position = glm::vec3(2.0f, 3.0f, 1.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(-3.0f, -1.0f, 0.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(-1.5f, 1.0f, 1.5)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(0.5);
    args.position = glm::vec3(-1.5f, 2.0f, -3.0)+globalPos;
    args.angle = glm::radians(60.0f);
    args.axes = glm::normalize(glm::vec3(1.0, 0.0, 1.0));
    cube.Drow(args);
}

void renderOmniShadowScene(PhongOmniShadowArgs args, Cube cube) {
    args.scale = glm::vec3(10);
    args.angle = 0;
    args.axes = glm::vec3(1);
    args.position = glm::vec3(0)+globalPos;
    glDisable(GL_CULL_FACE);
    args.reverse_normals = true;
    cube.Drow(args);
    args.reverse_normals = false;
    glEnable(GL_CULL_FACE);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(4.0f, -3.5f, 0.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(0.5);
    args.position = glm::vec3(2.0f, 3.0f, 1.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(-3.0f, -1.0f, 0.0)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(1);
    args.position = glm::vec3(-1.5f, 1.0f, 1.5)+globalPos;
    cube.Drow(args);
    args.scale = glm::vec3(0.5);
    args.position = glm::vec3(-1.5f, 2.0f, -3.0)+globalPos;
    args.angle = glm::radians(60.0f);
    args.axes = glm::normalize(glm::vec3(1.0, 0.0, 1.0));
    cube.Drow(args);
}

void processInput(GLFWwindow *window)
{
    bool cursorEnabling = (glfwGetTime() - lastCursorReaction) > 0.3;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if ( ( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ) && cursorEnabling) {
        if(cursorFlag) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cursorFlag = !cursorFlag;
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            cursorFlag = !cursorFlag;
        }
        lastCursorReaction = glfwGetTime();
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if(cursorFlag)
        return;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(cursorFlag)
        return;
    camera.ProcessMouseScroll(yoffset);
}
