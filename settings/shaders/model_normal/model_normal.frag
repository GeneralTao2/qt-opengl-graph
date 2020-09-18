#version 440 core
#define LIGHT_QUANTITY 4
out vec4 FragColor;
in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos[LIGHT_QUANTITY];
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} gs_in;

uniform vec3 viewPos;

struct ModelMaterial {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_normal1;
};
uniform ModelMaterial material;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material colorMaterial;


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
uniform float time;

vec3 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir);
uniform float near;
uniform float far;
uniform int depthEnabled;


float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}
void main()
{
        /*vec4 textureColour = texture(texture_diffuse1, gs_in.texCoords);
        if(textureColour.a < 0.5) {
            discard;
        }*/

        vec3 normal = normalize(texture(material.texture_normal1, gs_in.TexCoords).rgb);
        normal = normalize(normal * 2.0 - 1.0); 

        vec3 viewDir = normalize(gs_in.TangentViewPos - gs_in.TangentFragPos);

        vec3 result = vec3(0);
        for(int i = 0; i < LIGHT_QUANTITY; i++)
            result += CalcPointLight(pointLights[i], gs_in.TangentLightPos[i], normal, gs_in.TangentFragPos, viewDir);
        float depth = LinearizeDepth(gl_FragCoord.z) / far;
        if(depthEnabled == 1) {
            FragColor = vec4(vec3(depth), 1.0);
        } else {
            FragColor = vec4(result, 1.0);
        }
}
vec3 CalcPointLight(PointLight light, vec3 pos, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(pos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32);
    float distance    = length(pos - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
                             light.quadratic * (distance * distance));
    vec3 ambient  = light.ambient  * vec3(texture(material.texture_diffuse1, gs_in.TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.texture_diffuse1, gs_in.TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.texture_specular1, gs_in.TexCoords));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

