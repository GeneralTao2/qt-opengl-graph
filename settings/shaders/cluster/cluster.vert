#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out VS_OUT {
    vec3 pos;
    vec3 color;
    mat4 proj_view;
} vs_out;
uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
void main()
{
    gl_Position = vec4(aPos, 1.0);
    vs_out.proj_view = projection * view * model;
    vs_out.pos = aPos;
    vs_out.color = aColor;
}

