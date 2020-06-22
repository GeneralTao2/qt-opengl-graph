#include "shader_global_buffer.h"

ShaderGlobalBuffer::ShaderGlobalBuffer(std::vector<std::string> shaders)
{
    for(auto shader: shaders) {
        GLuint id = RM::GetShader(shader).ID;
        GLuint uniformBlockIndex = glGetUniformBlockIndex(id, "Matrices");
        glUniformBlockBinding(id, uniformBlockIndex, 0);
        glGenBuffers(1, &UBO);
        Init();
    }
}
ShaderGlobalBuffer::~ShaderGlobalBuffer() {
    glDeleteBuffers(1, &UBO);
}
void ShaderGlobalBuffer::Init() {
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));
}
void ShaderGlobalBuffer::Bind(glm::mat4 projection, glm::mat4 view) {
    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindBuffer(GL_UNIFORM_BUFFER, UBO);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
