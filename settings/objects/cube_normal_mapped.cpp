#include "cube_normal_mapped.h"

NormalMappedCube::NormalMappedCube()
{
    Init();
}

void NormalMappedCube::calcPlane(std::vector<glm::vec3> &pos, std::vector<glm::vec2> &uv, glm::vec3 nm) {
    // calculate tangent/bitangent vectors of both triangles
    glm::vec3 tangent1, bitangent1;
    glm::vec3 tangent2, bitangent2;
    // triangle 1
    // ----------
    glm::vec3 edge1 = pos[1] - pos[0];
    glm::vec3 edge2 = pos[2] - pos[0];
    glm::vec2 deltaUV1 = uv[1] - uv[0];
    glm::vec2 deltaUV2 = uv[2] - uv[0];

    GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = glm::normalize(tangent1);

    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = glm::normalize(bitangent1);

    // triangle 2
    // ----------
    edge1 = pos[4] - pos[3];
    edge2 = pos[5] - pos[3];
    deltaUV1 = uv[4] - uv[3];
    deltaUV2 = uv[5] - uv[3];

    f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

    tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent2 = glm::normalize(tangent2);


    bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent2 = glm::normalize(bitangent2);

    std::vector<float> quadVertices = {
        // poss            // normal         // texcoords  // tangent                          // bitangent
        pos[0].x, pos[0].y, pos[0].z, nm.x, nm.y, nm.z, uv[0].x, uv[0].y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos[1].x, pos[1].y, pos[1].z, nm.x, nm.y, nm.z, uv[1].x, uv[1].y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
        pos[2].x, pos[2].y, pos[2].z, nm.x, nm.y, nm.z, uv[2].x, uv[2].y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

        pos[3].x, pos[3].y, pos[3].z, nm.x, nm.y, nm.z, uv[3].x, uv[3].y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos[4].x, pos[4].y, pos[4].z, nm.x, nm.y, nm.z, uv[4].x, uv[4].y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
        pos[5].x, pos[5].y, pos[5].z, nm.x, nm.y, nm.z, uv[5].x, uv[5].y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
    };
    vertices.insert(vertices.end(), quadVertices.begin(), quadVertices.end());
}

void NormalMappedCube::Init() {
    std::vector<std::vector<glm::vec3> > positions = {
        {
            {-0.5f, -0.5f, -0.5f},
            { 0.5f,  0.5f, -0.5f},
            { 0.5f, -0.5f, -0.5f},
            { 0.5f,  0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
            {-0.5f,  0.5f, -0.5f}
        },
        {
            {-0.5f, -0.5f,  0.5f},
            { 0.5f, -0.5f,  0.5f},
            { 0.5f,  0.5f,  0.5f},
            { 0.5f,  0.5f,  0.5f},
            {-0.5f,  0.5f,  0.5f},
            {-0.5f, -0.5f,  0.5f}
        },
        {
            {-0.5f,  0.5f,  0.5f},
            {-0.5f,  0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f, -0.5f},
            {-0.5f, -0.5f,  0.5f},
            {-0.5f,  0.5f,  0.5f}
        },
        {
            {0.5f,  0.5f,  0.5f},
            {0.5f, -0.5f, -0.5f},
            {0.5f,  0.5f, -0.5f},
            {0.5f, -0.5f, -0.5f},
            {0.5f,  0.5f,  0.5f},
            {0.5f, -0.5f,  0.5f}
        },
        {
            {-0.5f, -0.5f, -0.5f},
            { 0.5f, -0.5f, -0.5f},
            { 0.5f, -0.5f,  0.5f},
            { 0.5f, -0.5f,  0.5f},
            {-0.5f, -0.5f,  0.5f},
            {-0.5f, -0.5f, -0.5f}
        },
        {
            {-0.5f,  0.5f, -0.5f},
            { 0.5f,  0.5f , 0.5f},
            { 0.5f,  0.5f, -0.5f},
            { 0.5f,  0.5f,  0.5f},
            {-0.5f,  0.5f, -0.5f},
            {-0.5f,  0.5f,  0.5f}
        },
    };
    std::vector<std::vector<glm::vec2> > texCords = {
        {
            //back
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {0.0f, 1.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f}
        },
        {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f}
        },
        {
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f}
        },
        //right
        {
            {0.0f, 0.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 0.0f},
            {1.0f, 0.0f},

        },
        //bottom
        {
            {0.0f, 0.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {1.0f, 1.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f}
        },
        {
            {0.0f, 1.0f},
            {1.0f, 0.0f},
            {1.0f, 1.0f},
            {1.0f, 0.0f},
            {0.0f, 1.0f},
            {0.0f, 0.0f}
        },
    };

    std::vector<glm::vec3> normals = {
        {0.0f,  0.0f, -1.0f},
        {0.0f,  0.0f,  1.0f},
        {-1.0f,  0.0f,  0.0f},
        {1.0f,  0.0f,  0.0f},
        {0.0f, -1.0f,  0.0f},
        {0.0f,  1.0f,  0.0f}
    };


    for(size_t i=0; i<positions.size(); i++) {
        calcPlane(positions[i], texCords[i], normals[i]);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(1);
}
void NormalMappedCube::Drow(NormalMapArgs args) {
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
void NormalMappedCube::Drow(ADSN_PhongArgs args) {
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
void NormalMappedCube::Drow(ADSNH_PhongArgs args) {
    glDisable(GL_CULL_FACE);
    args.Bind();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    glEnable(GL_CULL_FACE);
}
