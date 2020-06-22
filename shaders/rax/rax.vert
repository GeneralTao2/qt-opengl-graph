#version 440 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in float indexes;

out vec3 ourColor;
out vec2 TexCoord;
uniform vec3 colors[3];
uniform mat4 transform;

void main()
{
        gl_Position = transform * vec4(aPos.x, aPos.y, 0.0, 1.0);
        ourColor = colors[int(indexes)];
        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
