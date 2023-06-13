#ifndef EMITEINNA_RENDEROBJECT
#define EMITEINNA_RENDEROBJECT

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
class Material;
class Camera;
class Light;
class RenderObject {
public:
	struct Vertex {
		glm::vec4 Position;
		glm::vec4 UV;
		glm::vec4 Normal;
		glm::vec4 Tangent;
		glm::vec4 Vertexcolor;
	};
	Material* material;
	Camera* cam;
	Light* light;
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	RenderObject(float* inputVertices, unsigned int* inputIndices, int size1, int size2, float* inputposition, float* inputrotation, float* inputscale, Material* inputmaterial, Camera* inputcam, Light* inputlight);
	RenderObject(const std::string& path, Material* inputmaterial, glm::vec3 inputposition, glm::vec3 inputrotation, glm::vec3 inputscale, Camera* inputcamera, Light* inputlight,bool flipUV);
	RenderObject(const std::string& path, Material* inputmaterial, Camera* inputcamera, Light* inputlight, bool flipUV);

	void processMesh(aiMesh* mesh, const aiScene* scene);
	void processNode(aiNode* node, const aiScene* scene);
	void InstantiateWithData();
	void use();
	void Render();
	void DeleteObject();
	void showInfo(int num);
};

#endif