#ifndef __DEMO01_H__
#define __DEMO01_H__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "demo.h"
#include "globjs.h"


class Demo01 : public Demo
{
public:
	Demo01():vao(false){}
	virtual void Prepare();
	virtual void Draw();
	virtual void Finalize();
	virtual ~Demo01();
private:
	ProgramObj program;
	VertexArrayObj vao;
	GLuint texture;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.



									// Get a handle for our "MVP" uniform
	GLuint MatrixID;// = glGetUniformLocation(program, "MVP");


	// Load the texture
	GLuint Texture;// = loadDDS("models/uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;//  = glGetUniformLocation(program, "myTextureSampler");

	// Read our .obj file


	glm::mat4 ProjectionMatrix;//  = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
	glm::mat4 ViewMatrix;//  = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	glm::mat4 ModelMatrix;//  = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));
	glm::mat4 MVP;//  = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Load it into a VBO

	//GLuint vertexbuffer;
	BufferObj vertexbuffer, uvbuffer;

	//GLuint uvbuffer;

};

#endif
