#ifndef SHADER_HPP
#define SHADER_HPP

#include <vector>
#include "globjs.h"

struct shader_info
{
	GLuint type;
	std::string shader_file_path;
};

ProgramObj LoadShaders(const std::vector<shader_info>&);

#endif
