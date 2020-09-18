#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

#define LIGHT_QUANTITY 4
out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 Normal;
} gs_out;

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    gs_out.TexCoords = vec2(aTexCoords.x, aTexCoords.y);
    gs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    gs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
}

