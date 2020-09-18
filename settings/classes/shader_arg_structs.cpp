#include "shader_arg_structs.h"

void ColorArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("color", color);
    shader.SetMatrix4("model", model);
}

void SkyBoxArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("model", model);
    shader.SetInteger("skybox", 0, true);
    glActiveTexture(GL_TEXTURE0);
    cubeMap.Bind();
}

void PhongArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    textureMat.init(shader);
    textureMat.bind(shader);
    colorMat.bind(shader);
    for(size_t i=0; i<lights.size(); i++)
        lights[i]->bind(shader, i);
    shader.SetMatrix4("model", model);
    shader.SetVector3fArray("lightPos", lightsPos);
    shader.SetVector3f("viewPos", *viewPos);
}

void PhongModelArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    colorMat.bind(shader);
    for(size_t i=0; i<lights.size(); i++)
        lights[i]->bind(shader, i);
    shader.SetMatrix4("model", model);
    shader.SetVector3fArray("lightPos", lightsPos);
    shader.SetVector3f("viewPos", *viewPos);
    shader.SetFloat("near", depth.Near);
    shader.SetFloat("far", depth.Far);
    shader.SetFloat("time", glfwGetTime());
    RM::DirectionLights["light"].bind(shader);
    shader.SetInteger("depthEnabled", depth.enabled);
}

void ShadowMapArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
}

void PhongDirectionalShadowArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetInteger("shadowMap", 3);
    shader.SetMatrix4("model", model);
    shader.SetMatrix4("lightSpaceMatrix", *lightSpaceMatrix);
    shader.SetVector3f("viewPos", *viewPos);
    shader.SetVector3f("lightPos", lightPos);
    light->bind(shader, "pointLight");
    colorMat.bind(shader);
    textureMat.init(shader);
    textureMat.bind(shader);
    glActiveTexture(GL_TEXTURE3);
    shadowMap.Bind();
}

void ShadowOmniMapArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetFloat("far_plane", far_plane);
    shader.SetVector3f("lightPos", lightPos);
    shader.SetMatrix4Array("shadowMatrices", shadowTransforms);
}

void PhongOmniShadowArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetInteger("depthMap", 3);
    shader.SetMatrix4("model", model);
    shader.SetVector3f("viewPos", *viewPos);
    shader.SetVector3f("lightPos", lightPos);
    shader.SetFloat("far_plane", far_plane);
    shader.SetInteger("reverse_normals", reverse_normals);
    light->bind(shader, "pointLight");
    colorMat.bind(shader);
    textureMat.init(shader);
    textureMat.bind(shader);
    glActiveTexture(GL_TEXTURE3);
    shadowMap.Bind();
}

void RefractionArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("cameraPos", *viewPos);
    shader.SetMatrix4("model", model);
    shader.SetInteger("skybox", 0, true);
    glActiveTexture(GL_TEXTURE0);
    cubeMap.Bind();
}

void NormalMapArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("cameraPos", *viewPos);
    shader.SetMatrix4("model", model);
    light->bind(shader, "pointLight");
    shader.SetVector3f("viewPos", *viewPos);
    shader.SetInteger("diffuseMap", 0);
    shader.SetVector3f("lightPos", lightPos);
    shader.SetInteger("normalMap", 1);
    glActiveTexture(GL_TEXTURE0);
    diffuseMap.Bind();
    glActiveTexture(GL_TEXTURE1);
    normalMap.Bind();
}

void ADSN_PhongArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("cameraPos", *viewPos);
    shader.SetMatrix4("model", model);
    shader.SetVector3f("viewPos", *viewPos);
    for(size_t i=0; i<lights.size(); i++)
        lights[i]->bind(shader, i);
    shader.SetVector3fArray("lightPos", lightsPos);
    colorMat.bind(shader);
    textureMat.init(shader);
    textureMat.bind(shader);
}

void ADSNH_PhongArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetVector3f("cameraPos", *viewPos);
    shader.SetMatrix4("model", model);
    shader.SetVector3f("viewPos", *viewPos);
    for(size_t i=0; i<lights.size(); i++)
        lights[i]->bind(shader, i);
    shader.SetVector3fArray("lightPos", lightsPos);
    shader.SetFloat("minLayers", props.minLayers);
    shader.SetFloat("maxLayers", props.maxLayers);
    shader.SetFloat("height_scale", props.height_scale);
    colorMat.bind(shader);
    textureMat.init(shader);
    textureMat.bind(shader);
}

void PostProcessingArgs::Bind() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, angle, axes);
    model = glm::scale(model, scale);
    shader.Use();
    shader.SetMatrix4("model", model);
    shader.SetInteger("mode", postProc.mode);
    shader.SetFloat("exposure", postProc.exposure);
    shader.SetFloat("offset", postProc.offset);
    shader.SetFloat("gamma", postProc.gamma);
    shader.SetVector1fArray("kernelMat",
           postProc.kernelMats[postProc.currentMat]);
}










