#ifndef  EMITEINNA_SHADER
#define EMITEINNA_SHADER
#include <glad/glad.h>
#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
class Shader {
public:
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat3(const std::string& name, glm::vec3 value) const;
	void setMatrix(const std::string& name, GLfloat* value);
};

#endif // ! EMITEINNA_SHADER
