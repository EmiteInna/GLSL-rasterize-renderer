#include "Camera.h"
Camera::Camera(glm::vec3 inputposition, glm::vec3 inputtarget, glm::vec3 inputup, float inputfov, float inputaspect, float inputnearplane, float inputfarplane) {
	Right = glm::vec3(0);
	V = glm::mat4(1);
	position = inputposition;
	target = glm::normalize(inputtarget);
	up = inputup;
	FOV = inputfov;
	aspect = inputaspect;
	nearPlane = inputnearplane;
	farPlane = inputfarplane;
}
glm::mat4 Camera::GetV() {
	V = glm::lookAt(position, position + target, up);
	Right = glm::normalize(glm::cross(up, target));
	/*
		GPT生成的不能用的代码，（坐标系错了）。
		glm::vec3 cameraFront = target;
		Right = glm::normalize(glm::cross(up, cameraFront));
		glm::vec3 cameraUp = glm::normalize(glm::cross(cameraFront, Right));
		V=glm::mat4(1.0f);
		V[0][0] = Right.x;
		V[1][0] = Right.y;
		V[2][0] = Right.z;
		V[0][1] = cameraUp.x;
		V[1][1] = cameraUp.y;
		V[2][1] = cameraUp.z;
		V[0][2] = -cameraFront.x;
		V[1][2] = -cameraFront.y;
		V[2][2] = -cameraFront.z;
		V[3][0] = -glm::dot(Right, position);
		V[3][1] = -glm::dot(cameraUp, position);
		V[3][2] = glm::dot(cameraFront, position);*/
	return V;
}
void Camera::UpdateCamera() {
	V = GetV();
}
void Camera::showinfo() {
	std::cout << "-------------Camera info:-------------" << std::endl;
	std::cout << "Position:" << std::endl;
	std::cout << "  " << glm::to_string(position) << std::endl;

	std::cout << "Target:" << std::endl;
	std::cout << "  " << glm::to_string(target) << std::endl;

	std::cout << "Up:" << std::endl;
	std::cout << "  " << glm::to_string(up) << std::endl;

	std::cout << "FOV:" << std::endl;
	std::cout << "  " << FOV << std::endl;
	std::cout << "nearPlane:" << std::endl;
	std::cout << "  " << nearPlane << std::endl;
	std::cout << "farPlane:" << std::endl;
	std::cout << "  " << farPlane << std::endl;
	std::cout << "aspect:" << std::endl;
	std::cout << "  " << aspect << std::endl;
	std::cout << "Right:" << std::endl;
	std::cout << "  " << glm::to_string(Right) << std::endl;
}