#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec2 aBitangent;

#define LIGHT_QUANTITY 4
out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos[LIGHT_QUANTITY];
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} gs_out;

uniform vec3 viewPos;

uniform vec3 lightPos[LIGHT_QUANTITY];

uniform mat4 model;
layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
};

void main()
{
    gs_out.FragPos = vec3(model * vec4(aPos, 1.0));   
    gs_out.TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    
    gs_out.TangentViewPos  = TBN * viewPos;
    gs_out.TangentFragPos  = TBN * gs_out.FragPos;

    for(int i=0; i<LIGHT_QUANTITY; i++) {
        gs_out.TangentLightPos[i] = TBN * lightPos[i];
    }
        
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

