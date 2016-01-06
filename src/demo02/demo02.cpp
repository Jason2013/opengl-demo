#include "demo02.h"
#include "globjs.h"
#include "shader.h"
#include "texture.h"
#include "objloader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
using std::vector;
using namespace glm;
#include <string>
using namespace std;
#include "texture.h"
#include "sphere.h"

extern const int nWinWidth;
extern const int nWinHeight;

void Demo02::ResizeWindow(int width, int height)
{
	Demo::ResizeWindow(width, height);
	ProjectionMatrix = glm::perspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
}

void Demo02::OnLightPosChanged(const vec3& lightPos)
{
	char buf[100];
	sprintf(buf, "%s - light position: (%.1f,%.1f,%.1f)", caption.c_str(), lightPos.x, lightPos.y, lightPos.z);

	glfwSetWindowTitle(Window(), buf);
	glUniform3fv(locLight, 1, &vEyeLight[0]);
}

bool Demo02::Key(int key)
{
	float step = 0.5f;

	switch (key)
	{
	case GLFW_KEY_LEFT:
		vEyeLight.x -= step;
		break;
	case GLFW_KEY_RIGHT:
		vEyeLight.x += step;
		break;
	case GLFW_KEY_UP:
		vEyeLight.y += step;
		break;
	case GLFW_KEY_DOWN:
		vEyeLight.y -= step;
		break;
	default:
		// ignore the key
		return false;
	}
	vEyeLight = glm::clamp(vEyeLight, vec3(-10.0f, -10.0f, 0.0f), vec3(10.0f, 10.0f, 2.0f));
	OnLightPosChanged(vEyeLight);

	// has processed
	return true;
}

void Demo02::Prepare()
{
	// Create and compile our GLSL program from the shaders
	vector<shader_info> shader_infos2 = { { GL_VERTEX_SHADER, "shaders/demo02/NormalMapped.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo02/NormalMapped.fragmentshader" } };

	program = LoadShaders(shader_infos2);
	glUseProgram(program);

	// Get a handle for our "MVP" uniform
	locMVP = glGetUniformLocation(program, "mvpMatrix");
	assert(locMVP != -1);

	glActiveTexture(GL_TEXTURE0);
	Texture = LoadTGATexture("models/demo02/IceMoon.tga");

	glActiveTexture(GL_TEXTURE1);
	Texture2 = LoadTGATexture("models/demo02/IceMoonBump.tga");

	MakeSphere(1.0f, 52, 26, vertices, uvs, normals);



	ProjectionMatrix = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	glUniformMatrix4fv(locMVP, 1, GL_FALSE, &MVP[0][0]);

	// Load it into a VBO

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

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

	// 2nd attribute buffer : Normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		1,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindVertexArray(0);

	locAmbient = glGetUniformLocation(program, "ambientColor");
	assert(locAmbient != -1);

	locDiffuse = glGetUniformLocation(program, "diffuseColor");
	assert(locDiffuse != -1);

	locLight = glGetUniformLocation(program, "vLightPosition");
	assert(locLight != -1);
	locMVP = glGetUniformLocation(program, "mvpMatrix");

	locMV = glGetUniformLocation(program, "mvMatrix");
	assert(locMV != -1);

	locNM = glGetUniformLocation(program, "normalMatrix");
	assert(locNM != -1);

	locColorMap = glGetUniformLocation(program, "colorMap");
	assert(locColorMap != -1);

	locNormalMap = glGetUniformLocation(program, "normalMap");
	assert(locNormalMap != -1);

	glUniform4fv(locAmbient, 1, &vAmbientColor[0]);
	glUniform4fv(locDiffuse, 1, &vDiffuseColor[0]);
	glUniform3fv(locLight, 1, &vEyeLight[0]);

	glm::mat3 nm = glm::mat3(ModelMatrix);

	glUniformMatrix4fv(locMV, 1, GL_FALSE, &ModelMatrix[0][0]);
	glUniformMatrix3fv(locNM, 1, GL_FALSE, &nm[0][0]);
	glUniform1i(locColorMap, 0);
	glUniform1i(locNormalMap, 1);
}

void Demo02::Time(double time)
{
	float angle = (float)(time)* (3.1415926f / 180.f)*30.0f;

	glm::mat4x4 RotateMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4x4 TranslateMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -4.0f));

	ModelMatrix = TranslateMatrix * RotateMatrix;
	glm::mat4 MVMatrix = ViewMatrix * ModelMatrix;
	glm::mat4 NMMatrix = ViewMatrix * RotateMatrix;
	MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	NormalMatrix = mat3(ViewMatrix) * mat3(RotateMatrix);
	glUniformMatrix4fv(locMVP, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(locMV, 1, GL_FALSE, &MVMatrix[0][0]);
	glUniformMatrix3fv(locNM, 1, GL_FALSE, &NormalMatrix[0][0]);

	glUniform4fv(locAmbient, 1, &vAmbientColor[0]);
	glUniform4fv(locDiffuse, 1, &vDiffuseColor[0]);
}

void Demo02::Active()
{
	Demo::Active();

	glfwSetWindowTitle(Window(), caption.c_str());
	glUseProgram(program);
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(locColorMap, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture2);
	glUniform1i(locNormalMap, 1);

	OnLightPosChanged(vEyeLight);
}

void Demo02::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
