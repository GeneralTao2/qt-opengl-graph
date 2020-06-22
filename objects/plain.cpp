#include "plain.h"


Plain::Plain(Shader sh) : shader(sh)
{
    Init();
}

void Plain::Init() {
    float vertices[] = {
           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
        };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(1);
}

void Plain::Drow(PhongArgs args) {
    glDisable(GL_CULL_FACE);
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}

void Plain::Drow(ShadowMapArgs args) {
    glDisable(GL_CULL_FACE);
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}

void Plain::Drow(PhongDirectionalShadowArgs args) {
    glDisable(GL_CULL_FACE);
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}


