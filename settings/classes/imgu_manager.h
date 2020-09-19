#ifndef IMGU_MANAGER_H
#define IMGU_MANAGER_H

#include <iostream>
//#include <glfw3.h>
#include "decor.h"

//#define IMGUI_IMPL_OPENGL_LOADER_GLEW

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>


class imgu_manager
{
public:
    GLFWwindow* window;
    ImVec4 clear_color;

    imgu_manager(GLFWwindow* Window);
    ~imgu_manager();
    void Init();
    void Begin();
    void End();

    void drowColorMaterial(ColorMaterial &m);
    void drowTextureMaterial(TextureMaterial &m);
    void drowPointLight(PointLight &pl, std::string a="");
    void drowDirectionLight(DirectionLight &dl);
    void drowDepthTesting(DepthTesting &data);
    void drowPostProcessing(PostProcessing &data);
    void drowHeightMappingProps(HeightMappingProps &data);
    void drowBool(bool &data);

    bool show_demo_window;
    bool show_another_window;
};

#endif // IMGU_MANAGER_H

