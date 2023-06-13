#include "Light.h"
Light::Light(glm::vec3 inputlightDir, glm::vec3 inputlightColor) {
	lightDir = glm::normalize(inputlightDir);
	lightColor = inputlightColor;
}