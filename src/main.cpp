

#include <iostream>
#include <vector>
#include <memory>
using namespace std;
using std::vector;
using std::unique_ptr;


#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "globjs.h"
#include "conio.h"
#include "objloader.h"
#include "texture.h"

#include "demo.h"
#include "demo00.h"
#include "demo01.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

extern const int nWinWidth = 1024;
extern const int nWinHeight = 768;

int main()
{

	try {

		glfwEnv glfw;

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GlfwWinObj window(nWinWidth, nWinHeight, "OpenGL DEMO");

		glfwMakeContextCurrent(window);

		glewEnv glew;

		//vector<shader_info> shader_infos = { {GL_VERTEX_SHADER, "shaders/SimpleVertexShader.vertexshader" },
		//	{ GL_FRAGMENT_SHADER, "shaders/SimpleFragmentShader.fragmentshader" } };

		//ProgramObj programID = LoadShaders(shader_infos);
		//glUseProgram(programID);

		glfwSetKeyCallback(window, key_callback);

		glClearColor(0.0f, 0.0f, 0.2f, 0.0f);

		//static GLfloat vertexBuffer[] = {
		//	-0.5f, -0.5f,
		//	 0.5f,  0.5f,
		//	-0.5f,  0.5f,
		//	 0.6f,  0.5f,
		//	-0.5f, -0.5f,
		//	 0.5f, -0.5f
		//};

		//VertexArrayObj vao;

		//BufferObj buffer;

		//glBindBuffer(GL_ARRAY_BUFFER, buffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), vertexBuffer, GL_STATIC_DRAW);

		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		//glEnableVertexAttribArray(0);

		unique_ptr<Demo> demo00(new Demo00);
		demo00->Prepare();

		unique_ptr<Demo> demo1(new Demo01);
		demo1->Prepare();


		//// Create and compile our GLSL program from the shaders
		//vector<shader_info> shader_infos2 = { { GL_VERTEX_SHADER, "shaders/TransformVertexShader.vertexshader" },
		//{ GL_FRAGMENT_SHADER, "shaders/TextureFragmentShader.fragmentshader" } };
		//ProgramObj programID2 = LoadShaders(shader_infos2);

		//// Get a handle for our "MVP" uniform
		//GLuint MatrixID = glGetUniformLocation(programID2, "MVP");


		//// Load the texture
		//GLuint Texture = loadDDS("models/uvmap.DDS");

		//// Get a handle for our "myTextureSampler" uniform
		//GLuint TextureID = glGetUniformLocation(programID2, "myTextureSampler");

		//// Read our .obj file
		//std::vector<glm::vec3> vertices;
		//std::vector<glm::vec2> uvs;
		//std::vector<glm::vec3> normals; // Won't be used at the moment.
		//bool res = loadOBJ("models/suzanne.obj", vertices, uvs, normals);

		//glUseProgram(programID2);

		////computeMatricesFromInputs();
		////glm::mat4 ProjectionMatrix = getProjectionMatrix();
		//glm::mat4 ProjectionMatrix = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
		////glm::mat4 ViewMatrix = getViewMatrix();
		//glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
		////glm::mat4 ModelMatrix = glm::mat4(1.0);
		//glm::mat4 ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));
		//glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
		////glProgramUniformMatrix4fv();
		//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		//// Load it into a VBO

		//GLuint vertexbuffer;
		//glGenBuffers(1, &vertexbuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		//GLuint uvbuffer;
		//glGenBuffers(1, &uvbuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);



		//// Bind our texture in Texture Unit 0
		//glActiveTexture(GL_TEXTURE1);
		//glBindTexture(GL_TEXTURE_2D, Texture);
		//// Set our "myTextureSampler" sampler to user Texture Unit 0
		//glUniform1i(TextureID, 1);

		//// 1rst attribute buffer : vertices
		//glEnableVertexAttribArray(0);
		//glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		//glVertexAttribPointer(
		//	0,                  // attribute
		//	3,                  // size
		//	GL_FLOAT,           // type
		//	GL_FALSE,           // normalized?
		//	0,                  // stride
		//	(void*)0            // array buffer offset
		//	);

		//// 2nd attribute buffer : UVs
		//glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		//glVertexAttribPointer(
		//	1,                                // attribute
		//	2,                                // size
		//	GL_FLOAT,                         // type
		//	GL_FALSE,                         // normalized?
		//	0,                                // stride
		//	(void*)0                          // array buffer offset
		//	);


		//glDisableVertexAttribArray(0);
		//glDisableVertexAttribArray(1);



		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			demo00->Draw();
			demo1->Draw();
			// Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, vertices.size());
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	catch (const FileNotFound& ex)
	{
		err_hander(string("Impossible to open ") + ex.filename + string(". Are you in the right directory?"));
	}
	catch (const ShaderCompileError& ex)
	{
		err_hander(string("Shader compilation error: ") + ex.err_msg);
	}
	catch (const ProgramCompileError& ex)
	{
		err_hander(string("Program compilation error: ") + ex.err_msg);
	}
	catch (const glfwEnvInitExcept& /*e*/)
	{
		err_hander("Failed to initialize GLFW!");
	}
	catch (const glewEnvInitExcept& /*e*/)
	{
		err_hander("Failed to initialize GLEW!");
	}
	catch (const glfwWinExcept& /*e*/)
	{
		err_hander("Failed to create window!");
	}

	return 0;
}
