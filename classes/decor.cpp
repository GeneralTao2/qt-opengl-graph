#include "decor.h"

void ColorMaterial::bind(Shader &s) {
    s.SetVector3f((var + ".ambient").c_str(), ambient);
    s.SetVector3f((var + ".diffuse").c_str(), diffuse);
    s.SetVector3f((var + ".specular").c_str(), specular);
    s.SetFloat((var + ".shininess").c_str(), shininess);
}

TextureMaterial::TextureMaterial(Texture2D Ambient, Texture2D Diffuse,
                                 Texture2D Specular,
                                 float Shininess, std::string Var) :
ambient(Ambient), diffuse(Diffuse), specular(Specular), shininess(Shininess), var(Var) {}

/*TextureMaterial::TextureMaterial(TextureMaterial &a) :
ambient(a.ambient), diffuse(a.diffuse), specular(a.specular), shininess(a.shininess), var(a.var){}
*/

void TextureMaterial::init(Shader &s, std::vector<int> List) {
    list = List;
    s.SetInteger((var + ".ambient").c_str(), list[0]);
    s.SetInteger((var + ".diffuse").c_str(), list[1]);
    s.SetInteger((var + ".specular").c_str(), list[2]);
}

void TextureMaterial::bind(Shader &s) {
    glActiveTexture(GL_TEXTURE0 + list[0]);
    ambient.Bind();
    glActiveTexture(GL_TEXTURE0 + list[1]);
    diffuse.Bind();
    glActiveTexture(GL_TEXTURE0 + list[2]);
    specular.Bind();
    s.SetFloat((var + ".shininess").c_str(), shininess);
}

ADSN_TextureMaterial::ADSN_TextureMaterial(Texture2D Ambient, Texture2D Diffuse,
                                 Texture2D Specular, Texture2D Normal,
                                 float Shininess, std::string Var) :
ambient(Ambient), diffuse(Diffuse), specular(Specular), normal(Normal), shininess(Shininess), var(Var) {}

void ADSN_TextureMaterial::init(Shader &s, std::vector<int> List) {
    list = List;
    s.SetInteger((var + ".ambient").c_str(), list[0]);
    s.SetInteger((var + ".diffuse").c_str(), list[1]);
    s.SetInteger((var + ".specular").c_str(), list[2]);
    s.SetInteger((var + ".normal").c_str(), list[3]);
}

void ADSN_TextureMaterial::bind(Shader &s) {
    glActiveTexture(GL_TEXTURE0 + list[0]);
    ambient.Bind();
    glActiveTexture(GL_TEXTURE0 + list[1]);
    diffuse.Bind();
    glActiveTexture(GL_TEXTURE0 + list[2]);
    specular.Bind();
    glActiveTexture(GL_TEXTURE0 + list[3]);
    normal.Bind();
    s.SetFloat((var + ".shininess").c_str(), shininess);
}

ADSNH_TextureMaterial::ADSNH_TextureMaterial(Texture2D Ambient, Texture2D Diffuse,
                                 Texture2D Specular, Texture2D Normal, Texture2D Height,
                                 float Shininess, std::string Var) :
ambient(Ambient), diffuse(Diffuse), specular(Specular), normal(Normal),
  height(Height), shininess(Shininess), var(Var) {}

void ADSNH_TextureMaterial::init(Shader &s, std::vector<int> List) {
    list = List;
    s.SetInteger((var + ".ambient").c_str(), list[0]);
    s.SetInteger((var + ".diffuse").c_str(), list[1]);
    s.SetInteger((var + ".specular").c_str(), list[2]);
    s.SetInteger((var + ".normal").c_str(), list[3]);
    s.SetInteger((var + ".height").c_str(), list[4]);
}

void ADSNH_TextureMaterial::bind(Shader &s) {
    glActiveTexture(GL_TEXTURE0 + list[0]);
    ambient.Bind();
    glActiveTexture(GL_TEXTURE0 + list[1]);
    diffuse.Bind();
    glActiveTexture(GL_TEXTURE0 + list[2]);
    specular.Bind();
    glActiveTexture(GL_TEXTURE0 + list[3]);
    normal.Bind();
    glActiveTexture(GL_TEXTURE0 + list[4]);
    height.Bind();
    s.SetFloat((var + ".shininess").c_str(), shininess);
}

void PointLight::bind(Shader &s) {
    s.SetVector3f((var + ".ambient").c_str(), ambient);
    s.SetVector3f((var + ".diffuse").c_str(), diffuse);
    s.SetVector3f((var + ".specular").c_str(), specular);
    s.SetFloat((var + ".constant").c_str(), constant);
    s.SetFloat((var + ".linear").c_str(), linear);
    s.SetFloat((var + ".quadratic").c_str(), quadratic);
}
void PointLight::bind(Shader &s, std::string var) {
    s.SetVector3f((var + ".ambient").c_str(), ambient);
    s.SetVector3f((var + ".diffuse").c_str(), diffuse);
    s.SetVector3f((var + ".specular").c_str(), specular);
    s.SetFloat((var + ".constant").c_str(), constant);
    s.SetFloat((var + ".linear").c_str(), linear);
    s.SetFloat((var + ".quadratic").c_str(), quadratic);
}

void PointLight::bind(Shader &s, GLuint i) {
    s.SetVector3f((var + "[" + std::to_string(i) + "].ambient").c_str(), ambient);
    s.SetVector3f((var + "[" + std::to_string(i) + "].diffuse").c_str(), diffuse);
    s.SetVector3f((var + "[" + std::to_string(i) + "].specular").c_str(), specular);
    s.SetFloat((var + "[" + std::to_string(i) + "].constant").c_str(), constant);
    s.SetFloat((var + "[" + std::to_string(i) + "].linear").c_str(), linear);
    s.SetFloat((var + "[" + std::to_string(i) + "].quadratic").c_str(), quadratic);
}

PointLight PointLight::mixWithColor(glm::vec3 color) {
    glm::vec3 diffuseColor = color * diffuse;
    return {
        ambient, diffuseColor,
        diffuseColor * ambient,
        constant, linear, quadratic, var
    };
}

void DirectionLight::bind(Shader &s) {
    s.SetVector3f((var + ".ambient").c_str(), ambient);
    s.SetVector3f((var + ".diffuse").c_str(), diffuse);
    s.SetVector3f((var + ".specular").c_str(), specular);
    s.SetVector3f((var + ".direction").c_str(), direction);
    s.SetFloat((var + ".outerCutOff").c_str(), outerCutOff);
    s.SetFloat((var + ".cutOff").c_str(), cutOff);
    s.SetFloat((var + ".constant").c_str(), constant);
    s.SetFloat((var + ".linear").c_str(), linear);
    s.SetFloat((var + ".quadratic").c_str(), quadratic);
}

DirectionLight DirectionLight::mixWithColor(glm::vec3 color) {
    glm::vec3 diffuseColor = color * diffuse;
    return {
        ambient, diffuseColor,
        diffuseColor * ambient,
        direction, cutOff, outerCutOff,
        constant, linear, quadratic, var
    };
}
