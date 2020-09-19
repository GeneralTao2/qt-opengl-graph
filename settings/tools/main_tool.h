#ifndef MAIN_TOOL_H
#define MAIN_TOOL_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

std::ostream &operator<< (std::ostream &out, const glm::vec2 &vec);
std::ostream &operator<< (std::ostream &out, const glm::vec3 &vec);
std::ostream &operator<< (std::ostream &out, const glm::vec4 &vec);

void vecInArray(std::vector<float> &array, glm::vec2 value);
void vecInArray(std::vector<float> &array, glm::vec3 value);
void vecInArray(std::vector<float> &array, glm::vec4 value);

#endif // MAIN_TOOL_H
