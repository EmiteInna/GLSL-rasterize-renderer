#ifndef EMITEINNA_LIGHT
#define EMITEINNA_LIGHT
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include "RenderObject.h"
class Light {
public:
	glm::vec3 lightDir;
	glm::vec3 lightColor;
	Light(glm::vec3 inputlightDir, glm::vec3 inputlightColor);
};

#endif // !EMITEINNA_LIGHT
