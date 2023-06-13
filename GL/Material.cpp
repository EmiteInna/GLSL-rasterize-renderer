#include "Material.h"

Material::Material(const char* vertexPath, const char* fragmentPath, int inputcount) {
	textures = (unsigned int*)malloc(15 * sizeof(unsigned int));
	shader = new Shader(vertexPath, fragmentPath);
	mapCount = inputcount;
}
void Material::use() {
	shader->use();
}
void Material::setBool(const std::string& name, bool value) const
{
	shader->use();
	shader->setBool(name, value);
}
void Material::setInt(const std::string& name, int value) const
{
	shader->use();
	shader->setInt(name, value);
}
void Material::setFloat(const std::string& name, float value) const
{
	shader->use();
	shader->setFloat(name, value);
}
void Material::setFloat3(const std::string& name, glm::vec3 value)const
{
	shader->use();
	shader->setFloat3(name, value);
}
void Material::setMatrix(const std::string& name, GLfloat* value)const
{
	shader->use();
	shader->setMatrix(name, value);
}
void Material::setTexture(unsigned int target, const std::string& texname, const std::string& path)const {
	shader->use();
	Texture texture(path);
	textures[target] = texture.ID;
	shader->setInt(texname.c_str(), target);

}
void Material::setTexture(unsigned int target, const std::string& texname, Texture inputtexture)const {
	shader->use();
	textures[target] = inputtexture.ID;
	shader->setInt(texname.c_str(), target);

}
void Material::updateTextures(int n) {
	use();
	for (int i = 0; i < n; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
	}
}
void Material::updateShaderProperties(RenderObject object, Camera camera, Light light) {
	updateTextures(mapCount);
	glm::mat4 M = glm::mat4(1);
	//	std::cout << glm::to_string(M) << std::endl;
	M = glm::rotate(M, glm::radians(object.rotation[0]), glm::vec3(1, 0, 0));
	M = glm::rotate(M, glm::radians(object.rotation[1]), glm::vec3(0, 1, 0));
	M = glm::rotate(M, glm::radians(object.rotation[2]), glm::vec3(0, 0, 1));
	M = glm::scale(M, object.scale);
	M = glm::translate(M, object.position);

	setMatrix("M", glm::value_ptr(M));
	glm::mat4 V = camera.GetV();
	setMatrix("V", glm::value_ptr(V));

	glm::mat4 P = glm::mat4(1);;
	P = glm::perspective(glm::radians(camera.FOV), camera.aspect, camera.nearPlane, camera.farPlane);
	setMatrix("P", glm::value_ptr(P));

	glm::vec4 v = glm::vec4(5, -0.5, 0, 0);
	v = P * V * M * v;

	//camera.showinfo();
	setFloat3("LightDirection", light.lightDir);
	setFloat3("LightColor", light.lightColor);
	setFloat3("WorldSpaceCameraPos", camera.position);

}