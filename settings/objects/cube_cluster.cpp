#include "cube_cluster.h"

CubeCluster::CubeCluster(Shader sh) : shader(sh)
{
   Init();
}
void CubeCluster::Init() {
    int q = 3;
    quantity = q*q*q;
    int f=0;
    float vertices[quantity*6];
    for(int i=0; i<q; i++) {
        for(int j=0; j<q; j++) {
            for(int l=0; l<q; l++) {
                vertices[f] = i;
                vertices[f+1] = j;
                vertices[f+2] = l;
                vertices[f+3] = i/5.;
                vertices[f+4] = j/5.;
                vertices[f+5] = l/5.;
                f+=6;
            }
        }
    }
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(1);

    shader.Use();
    RM::TextureMaterials["box"].init(shader);
}

void CubeCluster::Drow(PhongArgs args) {
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, quantity);
    glBindVertexArray(0);
}
