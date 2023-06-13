#ifndef EMITEINNA_CAMERA
#define EMITEINNA_CAMERA
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
class Camera {
public:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 V;
	glm::vec3 Right;

	float FOV;
	float nearPlane;
	float farPlane;
	float aspect;
	Camera(glm::vec3 inputposition, glm::vec3 inputtarget, glm::vec3 inputup, float inputfov, float inputaspect, float inputnearplane, float inputfarplane);
	glm::mat4 GetV();
	void UpdateCamera();
	void showinfo();
};

#endif // !EMITEINNA_CAMERA
