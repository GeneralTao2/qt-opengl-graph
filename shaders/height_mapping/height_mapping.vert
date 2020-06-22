#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

#define LIGHT_QUANTITY 5
out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos[LIGHT_QUANTITY];
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};
uniform mat4 model;


uniform vec3 viewPos;

uniform vec3 lightPos[LIGHT_QUANTITY];

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;

    for(int i=0; i<LIGHT_QUANTITY; i++) {
        vs_out.TangentLightPos[i] = TBN * lightPos[i];
    }
        
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}