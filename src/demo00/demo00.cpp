#include "demo00.h"
#include "globjs.h"
#include "shader.h"
#include "texture.h"
#include "objloader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using std::vector;

extern const int nWinWidth;
extern const int nWinHeight;

void Demo00::Finalize() {}
Demo00::~Demo00() {}

void Demo00::Active()
{
	Demo::Active();

	glfwSetWindowTitle(Window(), "Two Trianges");
	glUseProgram(program);
	glBindVertexArray(vao);
	glDisable(GL_DEPTH_TEST);
}

void Demo00::Prepare()
{
	vector<shader_info> shader_infos = { { GL_VERTEX_SHADER, "shaders/demo00/Simple.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo00/Simple.fragmentshader" } };

	program = LoadShaders(shader_infos);

	static GLfloat vertexBuffer[] = {
		-0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f,
		0.6f,  0.5f,
		-0.5f, -0.5f,
		0.5f, -0.5f
	};

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Demo00::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
