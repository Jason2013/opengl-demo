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

	GLuint MatrixID;

	// Load the texture
	TextureObj Texture;

	// Get a handle for our "myTextureSampler" uniform
	GLuint TextureID;

	glm::mat4 ProjectionMatrix;
	glm::mat4 ViewMatrix;
	glm::mat4 ModelMatrix;
	glm::mat4 MVP;

	//GLuint vertexbuffer;
	BufferObj vertexbuffer, uvbuffer;
};

#endif
