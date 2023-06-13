#ifndef EMITEINNA_MATERIAL
#define EMITEINNA_MATERIAL
#include "RenderObject.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include "Camera.h"
#include "shaderh.h"
#include "Light.h"
#include "Texture.h"

class Material {
public:
	int mapCount;
	Shader* shader;
	unsigned int* textures;
	Material(const char* vertexPath, const char* fragmentPath, int inputcount);
	void use();
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setFloat3(const std::string& name, glm::vec3 value)const;
	void setMatrix(const std::string& name, GLfloat* value)const;
	void setTexture(unsigned int target, const std::string& texname, const std::string& path)const;
	void setTexture(unsigned int target, const std::string& texname, Texture inputtexture)const;
	void updateTextures(int n);
	void updateShaderProperties(RenderObject object, Camera camera, Light light);
};

#endif // !EMITEINNA_MATERIAL
