#ifndef __DEMO02_H__
#define __DEMO02_H__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "demo.h"
#include "globjs.h"


class Demo02 : public Demo
{
public:
	Demo02(GLFWwindow * win) :Demo(win), vao(false), Texture(false), Texture2(false) {}
	virtual void Active() override;
	virtual void Time(double time) override;
	virtual void Prepare() override;
	virtual void Draw();
	virtual void ResizeWindow(int width, int height) override;
	virtual bool Key(int key) override;


private:
	ProgramObj program;
	VertexArrayObj vao;
	GLuint texture;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	// Load the texture
	TextureObj Texture;
	TextureObj Texture2;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat3 NormalMatrix;
	glm::mat4 MVP;

	//GLuint vertexbuffer;
	BufferObj vertexbuffer, normalbuffer, uvbuffer;


	GLint locAmbient;
	GLint locDiffuse;
	GLint locLight;
	GLint locMVP;
	GLint locMV;
	GLint locNM;
	GLint locColorMap;
	GLint locNormalMap;

};

#endif
