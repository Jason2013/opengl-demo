#ifndef __DEMO01_H__
#define __DEMO01_H__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GLFW/glfw3.h>

#include "demo.h"
#include "globjs.h"


class Demo01 : public Demo
{
public:
	Demo01(GLFWwindow * win) :Demo(win), vao(false), Texture(false) {}
	virtual void Active() override;
	virtual void Time(double time) override;
	virtual void Prepare() override;
	virtual void Draw();
	virtual void ResizeWindow(int width, int height) override;
	virtual bool Demo01::Key(int key) override;

protected:
	glm::mat4 M() { return ModelMatrix; }
	glm::mat4 V() { return ViewMatrix; }
	glm::mat4 MV() { return ViewMatrix * ModelMatrix; };
	glm::mat4 MVP() { return ProjectionMatrix * ViewMatrix * ModelMatrix; };
	void SetActiveProgram(ProgramObj&);
	ProgramObj& ActiveProgram();


private:
	ProgramObj * active_program;
	ProgramObj program;
	ProgramObj program2;
	VertexArrayObj vao;
	GLuint texture;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	glm::vec3 vEyeLight = { 4.0f, 4.0f, 4.0f };
	glm::vec4 vAmbientColor = { 0.2f, 0.2f, 0.2f, 1.0f };
	glm::vec4 vDiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };


	// Load the texture
	TextureObj Texture;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;

	glm::mat4 ModelMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;

	//GLuint vertexbuffer;
	BufferObj vertexbuffer, uvbuffer;
};

#endif
