#ifndef SHADER_HPP
#define SHADER_HPP


struct shader_info
{
	GLuint type;
	std::string shader_file_path;
};

GLuint LoadShaders(const vector<shader_info>&);

#endif
