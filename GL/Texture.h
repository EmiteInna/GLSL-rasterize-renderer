#ifndef  EMITEINNA_TEXTURE
#define EMITEINNA_TEXTURE
#include <glad/glad.h>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
class Texture {
public:
	unsigned int ID;

	Texture(const std::string&path);
	
};

#endif // ! EMITEINNA_SHADER
