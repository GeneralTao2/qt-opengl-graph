#include "main_tool.h"

std::ostream &operator<< (std::ostream &out, const glm::vec2 &vec) {
    out << "{" << vec.x << " " << vec.y << "}";
    return out;
}
std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec) {
    out << "{" << vec.x << " " << vec.y << " "<< vec.z<< "}";
    return out;
}
std::ostream &operator<< (std::ostream &out, const glm::vec4 &vec) {
    out << "{" << vec.x << " " << vec.y << " "<< vec.z<< " " << vec.w << "}";
    return out;
}
#include <iostream>
void vecInArray(std::vector<float> &array, glm::vec2 value) {
    array.push_back(value.x);
    array.push_back(value.y);
}
void vecInArray(std::vector<float> &array, glm::vec3 value) {
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
}
void vecInArray(std::vector<float> &array, glm::vec4 value) {
    array.push_back(value.x);
    array.push_back(value.y);
    array.push_back(value.z);
    array.push_back(value.w);
}
