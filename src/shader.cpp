#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#include <stdlib.h>
#include <cassert>

#include <GL/glew.h>

#include "globjs.h"
#include "shader.h"

#ifdef _DEBUG

void check_shader_type(GLenum type)
{
	static vector<GLenum> valid_shaders = { GL_COMPUTE_SHADER, GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER,
		GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER };

	auto result = find(valid_shaders.cbegin(), valid_shaders.cend(), type);
	assert(result != valid_shaders.cend());
}

#define check_shader_type(t) check_shader_type(t)

#else

#define check_shader_type(t)

#endif // _DEBUG


GLuint LoadShader(GLenum type, string shader_file_path)
{
	check_shader_type(type);

	// Create the shader
	GLuint ShaderID = glCreateShader(type);

	// Read the Shader code from the file
	std::string ShaderCode;
	std::ifstream ShaderStream(shader_file_path, std::ios::in);
	if (ShaderStream.is_open()) {
		std::string Line = "";
		while (getline(ShaderStream, Line))
			ShaderCode += "\n" + Line;
		ShaderStream.close();
	}
	else {
		throw FileNotFound(shader_file_path);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Shader
	printf("Compiling shader : %s\n", shader_file_path.c_str());
	char const * VertexSourcePointer = ShaderCode.c_str();
	glShaderSource(ShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(ShaderID);

	// Check Shader
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		if (!Result)
			throw ShaderCompileError(&VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	return ShaderID;
}

GLuint LoadShaders(const vector<shader_info>& shaders) {

	vector<GLuint> shader_ids;

	for_each(shaders.cbegin(), shaders.cend(), [&shader_ids](const shader_info& info) {
		shader_ids.push_back(LoadShader(info.type, info.shader_file_path));
	});

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();

	for (GLuint id : shader_ids)
	{
		glAttachShader(ProgramID, id);
	}

	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		if (!Result)
			throw ProgramCompileError(&ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	for (GLuint id : shader_ids)
	{
		glDetachShader(ProgramID, id);
		glDeleteShader(id);
	}

	return ProgramID;
}


