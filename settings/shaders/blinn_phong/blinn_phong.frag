#version 420 core
#define LIGHT_QUANTITY 4
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
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

struct DirLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

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
uniform DirLight dirLight;
uniform float time;
uniform vec3 somecolor;

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec4 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    /*vec4 texColor = texture(textureMaterial.ambient, TexCoord);
    if(texColor.a < 0.1)
        discard;*/

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec4 result = CalcDirLight(dirLight, norm, viewDir);
    //vec4 result = vec4(0,0,0,1);
    // phase 2: Point lights
    for(int i = 0; i < LIGHT_QUANTITY; i++)
        result += CalcPointLight(pointLights[i], lightPos[i], norm, FragPos, viewDir);
    // phase 3: Spot light
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = result;
    //FragColor = texture(textureMaterial.ambient, TexCoord)

}

vec4 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), colorMaterial.shininess);
    vec4 ambient  = vec4(light.ambient, 1)  * vec4(texture(textureMaterial.ambient, TexCoord)) * vec4(colorMaterial.ambient, 1);
    vec4 diffuse  = vec4(light.diffuse, 1)  * diff * vec4(texture(textureMaterial.diffuse, TexCoord))* vec4(colorMaterial.diffuse, 1);
    vec4 specular = vec4(light.specular, 1) * spec * vec4(texture(textureMaterial.specular, TexCoord))* vec4(colorMaterial.specular, 1);
    return (ambient + diffuse + specular);
}


vec4 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), colorMaterial.shininess);
    float distance    = length(pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
    vec4 ambient  = vec4(light.ambient, 1)  * vec4(texture(textureMaterial.ambient, TexCoord)) * vec4(colorMaterial.ambient, 0.1);
    vec4 diffuse  = vec4(light.diffuse, 1)  * diff * vec4(texture(textureMaterial.diffuse, TexCoord)) * vec4(colorMaterial.diffuse, 0.1);
    vec4 specular = vec4(light.specular, 1) * spec * vec4(texture(textureMaterial.specular, TexCoord)) * vec4(colorMaterial.specular, 0.1);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

