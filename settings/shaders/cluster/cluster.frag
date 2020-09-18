#version 440 core
#define LIGHT_QUANTITY 5
out vec4 FragColor;

in GS_OUT {
    vec2 texCoords;
    vec3 normal;
    vec3 pos;
    vec3 color;
} gs_in; 

uniform vec3 viewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material colorMaterial;

struct TextureMaterial {
    sampler2D ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
uniform TextureMaterial textureMaterial;

struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLights[LIGHT_QUANTITY];
uniform vec3 lightPos[LIGHT_QUANTITY];

vec4 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(gs_in.normal);
    vec3 viewDir = normalize(viewPos - gs_in.pos);
    vec4 result = vec4(0,0,0,1);
    for(int i = 0; i < LIGHT_QUANTITY; i++)
        result += CalcPointLight(pointLights[i], lightPos[i], norm, gs_in.pos, viewDir);

    FragColor = result;
}

vec4 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), colorMaterial.shininess);
    float distance    = length(pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
    vec4 ambient  = vec4(light.ambient, 1)  * vec4(texture(textureMaterial.ambient, gs_in.texCoords)) * vec4(colorMaterial.ambient, 0.1);
    vec4 diffuse  = vec4(light.diffuse, 1)  * diff * vec4(texture(textureMaterial.diffuse, gs_in.texCoords)) * vec4(colorMaterial.diffuse, 0.1);
    vec4 specular = vec4(light.specular, 1) * spec * vec4(texture(textureMaterial.specular, gs_in.texCoords)) * vec4(colorMaterial.specular, 0.1);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
