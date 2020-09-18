#include "triangle.h"

triangle::triangle()
{
    //Init();
    dephNumber = 5;

    shader = RM::GetShader("triangle");

    dephArray = std::vector<std::vector<float>>(dephNumber, std::vector<float>());
    for(size_t i = 0; i<dephNumber; i++) {
        dephArray[i] = std::vector<float>();
    }

    triangleVertices = {
        glm::vec4(-0.5, 0.5, 0.0, 1),
        glm::vec4(0.5, 0.5, 0.0, 1),
        glm::vec4(0.0, -0.5, 0.0, 1)
    };

    triangleTexture = {
        glm::vec2(0.0, -0.18),
        glm::vec2(0.957, -0.18),
        glm::vec2(0.508, -0.993)
    };

    genVertices(glm::vec3(0, 0, 0), 0.5);
    int k =0;
    for(size_t i=0; i<dephArray[0].size(); i++) {
        if(i%15 == 0)
            cout << endl << "-----------------------" << k++;
        if(i%5 == 0)
            cout << endl;
        cout << dephArray[0][i] << ' ';
    }
    for(size_t i = 0; i<dephNumber; i++) {
        bindVertices(i);
    }
    //bindVertices(0);
}
triangle::~triangle() {
    glDeleteVertexArrays(1, &triangleVAO);
}

void triangle::updateVAO() {

}
void triangle::setColor(std::vector<std::vector<double>> a) {
    for(size_t i=0; i<24; i+=8)
        for(size_t j=0; j<3; j++)
            vertices[i+j+3] = a[i/8][j];

}
void genfrac(std::vector<glm::vec3> vs, int i) {

}
void triangle::Init() {
    vertices = RM::GetVertices("triangle_vertex");
}

void triangle::bindVertices(size_t deph) {

    glGenVertexArrays(1, &VAOs[deph]);
    glGenBuffers(1, &VBOs[deph]);

    //cout << "V: " << &VAOs[deph] << ' ' << &VBOs[deph] << endl;

    glBindVertexArray(VAOs[deph]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[deph]);

    glBufferData(GL_ARRAY_BUFFER, dephArray[deph].size() * sizeof(float), &dephArray[deph][0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(1);
}

void triangle::collectByDepth(glm::vec3 position, size_t deph) {
    if(deph > 4) {
        //cout << "OMG WTF!" << endl;
        return;
    }
    double scale = 0.5;
    for(size_t i=0; i<deph; i++) scale/=2;
    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale) );
    for(size_t i=0; i<3; i++) {
        vecInArray(dephArray[deph], glm::vec2(model * glm::vec4(triangleVertices[i].x, triangleVertices[i].y, 0, 1) ) );
        vecInArray(dephArray[deph], triangleTexture[i]);
        dephArray[deph].push_back(i);
        //cout << deph << glm::vec2(model * glm::vec4(triangleVertices[i].x, triangleVertices[i].y, 0, 1) ) << endl;
    }
}
void triangle::Drow(glm::vec3 position, size_t deph) {
    //cout << "V: " << &VAOs[deph] << ' ' << &VBOs[deph] << endl;
    double time = glfwGetTime();

    glm::mat4 model(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, static_cast<float>(glfwGetTime()+deph*71), glm::vec3(0.0, 1.0, 0.0));
    shader.Use();
    shader.SetMatrix4("transform", model);
    shader.SetVector3fArray("colors", { glm::vec3(2, 2, sin(time*5)+1),
                                        glm::vec3(2, 2, sin(time*5)+1),
                                        glm::vec3(2, 2, cos(time*5)+1) });

    RM::Textures["eye"].Bind();
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAOs[deph]);
    glDrawArrays(GL_TRIANGLES, 0, dephArray[deph].size());
    glBindVertexArray(0);
}
void triangle::genVertices(glm::vec3 p, double A, int Deph) {
    double a = A/2;
    if(a < 0.001)
        return;

    collectByDepth(p, Deph);
    int i, deph = Deph;
    double x, y;
    for(i = 0, y = p.y + a*0.75*2; i<6; i++, y+=a*0.75, a/=2) {
        deph++;
        genVertices(glm::vec3(p.x, y, p.z), a, deph);
    }

    a = A/2;
    deph = Deph;
    for(i = 0, y = p.y - a*0.5, x = p.x + a; i<6; i++, y-=a*0.25, a/=2, x+=a) {
        deph++;
        genVertices(glm::vec3(x, y, p.z), a, deph);
    }
    a = A/2;
    deph = Deph;
    for(i = 0, y = p.y - a*0.5, x = p.x - a; i<6; i++, y-=a*0.25, a/=2, x-=a) {
        deph++;
        genVertices(glm::vec3(x, y, p.z), a, deph);
    }

}
