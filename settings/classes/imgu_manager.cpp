#include "imgu_manager.h"

imgu_manager::imgu_manager(GLFWwindow* Window) : window(Window)
{
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(Window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Our state
    show_demo_window = true;
    show_another_window = false;
    clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

imgu_manager::~imgu_manager() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void imgu_manager::Init() {

}

void imgu_manager::Begin() {
    glDisable(GL_STENCIL_TEST);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}
void imgu_manager::End() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glEnable(GL_STENCIL_TEST);
}

void imgu_manager::drowColorMaterial(ColorMaterial &m) {
    ImGui::Begin(("material: " + m.var).c_str());
    ImGui::ColorEdit3("ambient", (float*)&m.ambient);
    ImGui::ColorEdit3("diffuse", (float*)&m.diffuse);
    ImGui::ColorEdit3("specular", (float*)&m.specular);
    ImGui::SliderFloat("shininess", &m.shininess, 0.0f, 100.0f);
    ImGui::End();
}
void imgu_manager::drowPointLight(PointLight &pl, std::string a) {
    ImGui::Begin((a +"material: " + pl.var).c_str());
    ImGui::ColorEdit3("ambient", (float*)&pl.ambient);
    ImGui::ColorEdit3("diffuse", (float*)&pl.diffuse);
    ImGui::ColorEdit3("specular", (float*)&pl.specular);
    ImGui::SliderFloat("constant", &pl.constant, 0.0f, 1.0f);
    ImGui::SliderFloat("linear", &pl.linear, 0.0f, 1.0f);
    ImGui::SliderFloat("quadratic", &pl.quadratic, 0.0f, 1.0f);
    ImGui::End();
}
void imgu_manager::drowDirectionLight(DirectionLight &dl) {
    ImGui::Begin(("material: " + dl.var).c_str());
    ImGui::ColorEdit3("ambient", (float*)&dl.ambient);
    ImGui::ColorEdit3("diffuse", (float*)&dl.diffuse);
    ImGui::ColorEdit3("specular", (float*)&dl.specular);
    ImGui::ColorEdit3("direction", (float*)&dl.direction);
    ImGui::SliderFloat("outerCutOff", &dl.outerCutOff, 0.0f, 1.0f);
    ImGui::SliderFloat("cutOff", &dl.cutOff, 0.0f, 1.0f);
    ImGui::SliderFloat("constant", &dl.constant, 0.0f, 1.0f);
    ImGui::SliderFloat("linear", &dl.linear, 0.0f, 1.0f);
    ImGui::SliderFloat("quadratic", &dl.quadratic, 0.0f, 1.0f);
    ImGui::End();
}
void imgu_manager::drowTextureMaterial(TextureMaterial &m) {
    ImGui::Begin(("material: " + m.var).c_str());
    ImGui::SliderFloat("shininess", &m.shininess, 0.0f, 100.0f);
    ImGui::End();
}
void imgu_manager::drowDepthTesting(DepthTesting &data) {
    ImGui::Begin("Deph testing");
    ImGui::SliderFloat("near", &data.Near, 0.0f, 100.0f);
    ImGui::SliderFloat("far", &data.Far, 0.0f, 100.0f);
    ImGui::Checkbox("enabled", &data.enabled);
    ImGui::End();
}

void imgu_manager::drowPostProcessing(PostProcessing &data) {
    ImGui::Begin("Post processing");
    ImGui::BeginGroup();
    ImGui::SliderFloat("exposure", &data.exposure, 0.0f, 0.5f);
    ImGui::RadioButton("off", &data.mode, 0);
    ImGui::RadioButton("kernel", &data.mode, 1);
    ImGui::RadioButton("grayscale", &data.mode, 2);
    ImGui::RadioButton("inversion", &data.mode, 3);
    ImGui::SliderFloat("offset", &data.offset, 0.0f, 0.1f);
    ImGui::InputFloat3("1",&data.kernelMats[data.currentMat][0], 3);
    ImGui::InputFloat3("2",&data.kernelMats[data.currentMat][3], 3);
    ImGui::InputFloat3("3",&data.kernelMats[data.currentMat][6], 3);
    ImGui::Combo("Matrix", &data.currentMat, &data.kernelNames[0], data.kernelMats.size());
    ImGui::SliderFloat("gamma", &data.gamma, 1.0f, 3.0f);
    ImGui::EndGroup();
    ImGui::End();
}
void drowBool(bool &data) {
    ImGui::Begin("bool tab");
    ImGui::Checkbox("enabled", &data);
}
void imgu_manager::drowHeightMappingProps(HeightMappingProps &data) {
    ImGui::Begin("Hight mapping");
    ImGui::SliderFloat("minLayers", &data.minLayers, 0.0f, 100.0f);
    ImGui::SliderFloat("maxLayers", &data.maxLayers, 0.0f, 100.0f);
    ImGui::SliderFloat("height_scale", &data.height_scale, 0, 1);
    ImGui::End();
}

