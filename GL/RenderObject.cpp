#include "RenderObject.h"
#include "Material.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

RenderObject::RenderObject(float* inputVertices, unsigned int* inputIndices, int size1, int size2, float* inputposition, float* inputrotation, float* inputscale, Material* inputmaterial, Camera* inputcam, Light* inputlight) {
	material = inputmaterial;
	light = inputlight;
	cam = inputcam;
	vertices.clear();
	indices.clear();
	if (material == NULL) {
		std::cout << "输入材质产生错误" << std::endl;
	}
	size1 *= 20;
	//	std::cout << "size1=" << size1 << " size2=" << size2 << std::endl;
	for (int i = 0; i < size1; i++) {
		int start = 0;
		Vertex vertex;
		for (int j = start, k = 0; k < 4; j++, k++) {
			vertex.Position[k] = inputVertices[i*20+j];
		}
		start += 4;
		for (int j = start, k = 0; k < 4; j++, k++) {
			vertex.Normal[k] = inputVertices[i * 20 + j];
		}
		start += 4;
		for (int j = start, k = 0; k < 4; j++, k++) {
			vertex.UV[k] = inputVertices[i * 20 + j];
		}
		start += 4;
		for (int j = start, k = 0; k < 4; j++, k++) {
			vertex.Tangent[k] = inputVertices[i * 20 + j];
		}
		start += 4;
		for (int j = start, k = 0; k < 4; j++, k++) {
			vertex.Vertexcolor[k] = inputVertices[i * 20 + j];
		}
		start += 4;
		vertices.push_back(vertex);
	}
	for (int i = 0; i < size2; i++) {
		indices.push_back(inputIndices[i]);
	}
	for (int i = 0; i < 3; i++) {
		position[i] = inputposition[i];
		rotation[i] = inputrotation[i];
		scale[i] = inputscale[i];
	}
	InstantiateWithData();
	

}
void RenderObject::processMesh(aiMesh* mesh, const aiScene* scene) {
	for (int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;
		vertex.Position.w = 1;
		if (mesh->HasNormals()) {
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
			vertex.Normal.w = 0;
		}
		else {
			vertex.Normal = glm::vec4(0);
		}
		if (mesh->HasTextureCoords(0)) {
			vertex.UV.x = mesh->mTextureCoords[0][i].x;
			vertex.UV.y = mesh->mTextureCoords[0][i].y;
			vertex.UV.z = 0;
			vertex.UV.w = 0;
		}
		else {
			vertex.UV = glm::vec4(0);
		}

		if (mesh->HasTangentsAndBitangents()) {
			vertex.Tangent.x = mesh->mTangents[i].x;
			vertex.Tangent.y = mesh->mTangents[i].y;
			vertex.Tangent.z = mesh->mTangents[i].z;
			vertex.Tangent.w = 1;
		}
		else {
			vertex.Tangent = glm::vec4(0);
		}
		if (mesh->HasVertexColors(0)) {
			vertex.Tangent.x = mesh->mColors[0][i].r;
			vertex.Tangent.y = mesh->mColors[0][i].g;
			vertex.Tangent.z = mesh->mColors[0][i].b;
			vertex.Tangent.w = mesh->mColors[0][i].a;
		}
		else {
			vertex.Vertexcolor = glm::vec4(0);
		}
		vertices.push_back(vertex);
	}
	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
}
void RenderObject::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}
RenderObject::RenderObject(const std::string& path, Material* inputmaterial,glm::vec3 inputposition,glm::vec3 inputrotation,glm::vec3 inputscale, Camera* inputcam, Light* inputlight,bool flipUV) {
	material = inputmaterial;
	light = inputlight;
	cam = inputcam;
	position = inputposition;
	rotation = inputrotation;
	scale = inputscale;
	Assimp::Importer importer;
	const aiScene* scene;
	if(flipUV)
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	else
		scene = importer.ReadFile(path, aiProcess_Triangulate);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP"<<importer.GetErrorString() << std::endl;
	}
	
	processNode(scene->mRootNode, scene);
	InstantiateWithData();
	//showInfo(10);
}
RenderObject::RenderObject(const std::string& path, Material* inputmaterial, Camera* inputcam, Light* inputlight, bool flipUV) {
	material = inputmaterial;
	light = inputlight;
	cam = inputcam;
	position = glm::vec3(0,0,0);
	rotation = glm::vec3(-90,0,0);
	scale = glm::vec3(0.2,0.2,0.2);
	Assimp::Importer importer;
	const aiScene* scene;
	if (flipUV)
		scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	else
		scene = importer.ReadFile(path, aiProcess_Triangulate);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP" << importer.GetErrorString() << std::endl;
	}

	processNode(scene->mRootNode, scene);
	InstantiateWithData();
	//showInfo(10);
}
void RenderObject::InstantiateWithData() {
	std::cout << "vertice have " << vertices.size() << " indices have " << indices.size() << std::endl;
	//简单的声明一下VAO、VBO和EBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	//接下来链接属性，只考虑到顶点、UV、法线、切线、顶点色五个元素，每个元素都是vec4，讲究的就是一个奢侈。
	//第0号元素是顶点
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//第1号元素是UV
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,UV));
	glEnableVertexAttribArray(1);
	//第2号元素是法线
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(2);
	//第3号元素是切线
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(3);
	//第4号元素是顶点色
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertexcolor));
	glEnableVertexAttribArray(4);
	//解绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void RenderObject::use() {
	glBindVertexArray(VAO);
}
void RenderObject::Render() {
	use();
	material->use();
	if (this == NULL) {
		std::cout << "me" << std::endl;
	}
	if (cam == NULL) {
		std::cout << "cam" << std::endl;
	}
	if (light == NULL) {
		std::cout << "light" << std::endl;
	}
	material->updateShaderProperties(*this, *cam, *light);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//std::cout << " Rendering with " << indices.size() << std::endl;
}

void RenderObject::DeleteObject() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
void RenderObject::showInfo(int n) {
	for (int i = 0; i < std::min(n, (int)vertices.size()); i++) {
		std::cout<<"Vertices:" << glm::to_string(vertices[i].Position) << std::endl;
		std::cout << "Normal:" << glm::to_string(vertices[i].Normal) << std::endl;
		std::cout << "UV:" << glm::to_string(vertices[i].UV) << std::endl;
		std::cout << std::endl;
	}
	for (int i = 0; i < std::min(n, (int)indices.size()); i++) {
		std::cout << "Link have " << indices[i] << std::endl;
	}
}
