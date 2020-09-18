#version 440 core
out vec4 FragColor;
#define LIGHT_QUANTITY 5
in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos[LIGHT_QUANTITY];
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} fs_in;

struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLight;

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
    sampler2D normal;
    float shininess;
};
uniform TextureMaterial textureMaterial;

uniform PointLight pointLights[LIGHT_QUANTITY];

uniform vec3 lightPos;
uniform vec3 viewPos;
vec3 CalcPointLight(PointLight light, vec3 lightPos, vec3 normal, vec3 fragPos, vec3 viewDir);
void main()
{           
    vec3 normal = texture(textureMaterial.normal, fs_in.TexCoords).rgb;
    normal = normalize(normal * 2.0 - 1.0);  
   
    vec3 viewDir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
    vec3 result = vec3(0);
    for(int i = 0; i < LIGHT_QUANTITY; i++)
        result += CalcPointLight(pointLights[i], fs_in.TangentLightPos[i], normal, fs_in.TangentFragPos, viewDir);
    FragColor = vec4(result, 1);

}

vec3 CalcPointLight(PointLight light, vec3 lightPos, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // ambient
    vec3 ambient = light.ambient * vec3(texture(textureMaterial.ambient, fs_in.TexCoords));
    // diffuse
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(textureMaterial.diffuse, fs_in.TexCoords));
    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), colorMaterial.shininess);

    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));

    vec3 specular = light.specular * spec;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

