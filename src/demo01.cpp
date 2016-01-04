#include "demo01.h"
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

void Demo01::Finalize(){}
Demo01::~Demo01(){}


void Demo01::Prepare()
{

	// Create and compile our GLSL program from the shaders
	vector<shader_info> shader_infos2 = { { GL_VERTEX_SHADER, "shaders/TransformVertexShader.vertexshader" },
	{ GL_FRAGMENT_SHADER, "shaders/TextureFragmentShader.fragmentshader" } };
	program = LoadShaders(shader_infos2);

	// Get a handle for our "MVP" uniform
	/*GLuint */MatrixID = glGetUniformLocation(program, "MVP");


	// Load the texture
	/*GLuint */Texture = loadDDS("models/uvmap.DDS");

	// Get a handle for our "myTextureSampler" uniform
	/*GLuint */TextureID = glGetUniformLocation(program, "myTextureSampler");

	// Read our .obj file
	//std::vector<glm::vec3> vertices;
	//std::vector<glm::vec2> uvs;
	//std::vector<glm::vec3> normals; // Won't be used at the moment.
	/*bool res = */loadOBJ("models/suzanne.obj", vertices, uvs, normals);

	glUseProgram(program);

	//computeMatricesFromInputs();
	//glm::mat4 ProjectionMatrix = getProjectionMatrix();
	/*glm::mat4 */ProjectionMatrix = glm::perspective(45.0f, (float)nWinWidth / (float)nWinHeight, 0.1f, 100.0f);
	//glm::mat4 ViewMatrix = getViewMatrix();
	/*glm::mat4 */ViewMatrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	/*glm::mat4 */ModelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0, 0, -4));
	/*glm::mat4 */MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
	//glProgramUniformMatrix4fv();
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Load it into a VBO

	glBindVertexArray(vao);
	//GLuint vertexbuffer;
	//glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);



	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 1);

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

void Demo01::Draw() 
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
