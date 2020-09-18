#version 330 core

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
uniform PointLight pointLight;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material colorMaterial;

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

float ShadowCalculation(vec4 fragPosLightSpace);
vec3 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 lighting = CalcPointLight(pointLight, lightPos, fs_in.Normal, fs_in.FragPos, viewPos);
    FragColor = vec4(lighting, 1.0);
}

vec3 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pos - fragPos);
    vec3 nnormal = normalize(normal);
    // diffuse shading
    float diff = max(dot(nnormal, lightDir), 0.0);
    // specular shading
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), colorMaterial.shininess);
    // attenuation
    float distance    = length(pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(textureMaterial.diffuse, fs_in.TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(textureMaterial.diffuse, fs_in.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(textureMaterial.specular, fs_in.TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular));
    //vec3 lighting = diffuse + ambient +specular;
    return lighting;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005); 
     float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    if(projCoords.z > 1.0)
        shadow = 0.0;
    return shadow;
}
