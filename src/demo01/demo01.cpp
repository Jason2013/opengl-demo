#include "demo01.h"
#include "globjs.h"
#include "shader.h"
#include "texture.h"
#include "objloader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using std::vector;
using namespace glm;

extern const int nWinWidth;
extern const int nWinHeight;

void Demo01::ResizeWindow(int width, int height)
{
	Demo::ResizeWindow(width, height);
	ProjectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Demo01::Prepare()
{
	// Create and compile our GLSL program from the shaders
	vector<shader_info> shader_infos2 = { { GL_VERTEX_SHADER, "shaders/demo01/TransformVertexShader.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo01/TextureFragmentShader.fragmentshader" } };
	program = LoadShaders(shader_infos2);

	// Load the texture
	glActiveTexture(GL_TEXTURE0);
	Texture = loadDDS("models/demo01/uvmap.DDS");

	// Read our .obj file
	loadOBJ("models/demo01/suzanne.obj", vertices, uvs, normals);

	glUseProgram(program);

	ProjectionMatrix = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));

	// Load it into a VBO

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindVertexArray(0);
}

void Demo01::Time(double time)
{
	float angle = (float)(time)* (3.1415926f / 180.f)*30.0f;// / 12.0f;

	glm::mat4x4 RotateMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4)) * RotateMatrix;
	glUniformMatrix4fv(program.GetUniformLocation("MVP"), 1, GL_FALSE, &(MVP())[0][0]);
}

void Demo01::Active()
{
	Demo::Active();

	glfwSetWindowTitle(Window(), "OBJ Model: suzanne");
	glUseProgram(program);
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(program.GetUniformLocation("myTextureSampler"), 0);
}

void Demo01::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
