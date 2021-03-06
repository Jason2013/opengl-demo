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

void Demo01::OnLightPosChanged(const vec3& lightPos)
{
	char buf[100];
	sprintf(buf, "%s - %s - light position: (%.1f,%.1f,%.1f)", caption.c_str(), mode.c_str(), lightPos.x, lightPos.y, lightPos.z);

	glfwSetWindowTitle(Window(), buf);
	glUniform3fv(ActiveProgram().GetUniformLocation("LightPosition_worldspace"), 1, &vEyeLight[0]);
}

bool Demo01::Key(int key)
{
	float step = 0.5f;

	switch (key)
	{
	case GLFW_KEY_A:
		SetActiveProgram(program);
		glUseProgram(ActiveProgram());
		mode = "Texture";
		break;
	case GLFW_KEY_B:
		SetActiveProgram(program3);
		glUseProgram(ActiveProgram());
		mode = "Gouraud";
		break;
	case GLFW_KEY_C:
		SetActiveProgram(program2);
		glUseProgram(ActiveProgram());
		mode = "Phong";
		break;
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


void Demo01::Prepare()
{
	// Create and compile our GLSL program from the shaders
	vector<shader_info> shader_infos = { { GL_VERTEX_SHADER, "shaders/demo01/Texture.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo01/Texture.fragmentshader" } };
	program = LoadShaders(shader_infos);

	vector<shader_info> shader_infos2 = { { GL_VERTEX_SHADER, "shaders/demo01/StandardShadingPhong.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo01/StandardShadingPhong.fragmentshader" } };
	program2 = LoadShaders(shader_infos2);

	vector<shader_info> shader_infos3 = { { GL_VERTEX_SHADER, "shaders/demo01/StandardShadingGouraud.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/demo01/StandardShadingGouraud.fragmentshader" } };
	program3 = LoadShaders(shader_infos3);

	// Load the texture
	glActiveTexture(GL_TEXTURE0);
	Texture = loadDDS("models/demo01/uvmap.DDS");

	// Read our .obj file
	loadOBJ("models/demo01/suzanne.obj", vertices, uvs, normals);

	ProjectionMatrix = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
	ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));

	// Load it into a VBO
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

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

	// 3nd attribute buffer : Normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindVertexArray(0);
}

void Demo01::Time(double time)
{
	float angle = (float)(time)* (3.1415926f / 180.f)* 10.0f;

	glm::mat4x4 RotateMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));

	ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4)) * RotateMatrix;
	glUniformMatrix4fv(ActiveProgram().GetUniformLocation("MVP"), 1, GL_FALSE, &(MVP())[0][0]);
	glUniformMatrix4fv(ActiveProgram().GetUniformLocation("M"), 1, GL_FALSE, &(M())[0][0]);
	glUniformMatrix4fv(ActiveProgram().GetUniformLocation("V"), 1, GL_FALSE, &(V())[0][0]);
	glUniformMatrix4fv(ActiveProgram().GetUniformLocation("MV"), 1, GL_FALSE, &(MV())[0][0]);
	glUniformMatrix3fv(ActiveProgram().GetUniformLocation("MN"), 1, GL_FALSE, &(mat3(RotateMatrix))[0][0]);
	glUniform3fv(ActiveProgram().GetUniformLocation("LightPosition_worldspace"), 1, &vEyeLight[0]);
}

void Demo01::SetActiveProgram(ProgramObj& prog)
{
	active_program = &prog;
}
ProgramObj& Demo01::ActiveProgram()
{
	return *active_program;
}


void Demo01::Active()
{
	Demo::Active();

	char buff[100];
	sprintf(buff, "%s - %s", caption.c_str(), mode.c_str());
	glfwSetWindowTitle(Window(), buff);
	SetActiveProgram(program);
	glUseProgram(ActiveProgram());
	glBindVertexArray(vao);
	glEnable(GL_DEPTH_TEST);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	glUniform1i(ActiveProgram().GetUniformLocation("myTextureSampler"), 0);
}

void Demo01::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
