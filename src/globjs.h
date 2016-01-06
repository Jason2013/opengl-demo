#ifndef __GLOBJS_H_
#define __GLOBJS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>
#include <cassert>
#include <iostream>

void err_hander(const std::string&);

class MyExcept {};

class glfwEnvInitExcept : public MyExcept {};

class glfwWinExcept : public MyExcept {};

class glewEnvInitExcept : public MyExcept {};

class FileNotFound : public MyExcept
{
public:
	FileNotFound(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class ShaderCompileError : public MyExcept
{
public:
	ShaderCompileError(const std::string& msg) : err_msg(msg) {}
	const std::string err_msg;
};

class ProgramCompileError : public MyExcept
{
public:
	ProgramCompileError(const std::string& msg) : err_msg(msg) {}
	const std::string err_msg;
};

class ObjModelFormatError : public MyExcept
{
public:
	ObjModelFormatError(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class BmpFormatError : public MyExcept
{
public:
	BmpFormatError(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class DdsFormatError : public MyExcept
{
public:
	DdsFormatError(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class TgaFormatError : public MyExcept
{
public:
	TgaFormatError(const std::string& fname) : filename(fname) {}
	const std::string filename;
};

class glfwEnv
{
public:
	glfwEnv()
	{
		if (glfwInit() != GL_TRUE)
			throw glfwEnvInitExcept();
	}
	~glfwEnv() { glfwTerminate(); }
};

class glewEnv
{
public:
	glewEnv()
	{
		if (glewInit() != GLEW_OK)
			throw glewEnvInitExcept();
	}
};

class GlfwWinObj
{
public:
	GlfwWinObj(int width, int height, const char * title)
	{
		_win = glfwCreateWindow(width, height, title, 0, 0);
		if (!_win)
			throw glfwWinExcept();
	}
	~GlfwWinObj() { glfwDestroyWindow(_win); }
	operator GLFWwindow * () { return _win; }

private:
	GLFWwindow * _win;
};

class VertexArrayObj
{
public:
	VertexArrayObj(bool immediate = true)
	{
		glGenVertexArrays(1, &id);
		if (immediate)
			glBindVertexArray(id);
	}
	~VertexArrayObj() { glDeleteVertexArrays(1, &id); }
	operator GLuint() { return id; }
private:
	GLuint id;
};

class BufferObj
{
public:
	BufferObj() { glGenBuffers(1, &id); }
	~BufferObj() { glDeleteBuffers(1, &id); }
	operator GLuint() { return id; }
private:
	GLuint id;
};

class TextureObj
{
public:
	TextureObj(const TextureObj&) = delete;
	TextureObj& operator=(const TextureObj&) = delete;
	TextureObj(TextureObj && rhs)
	{
		id = rhs.id;
		rhs.id = 0;
	}
	TextureObj& operator=(TextureObj && rhs)
	{
		clean();
		id = rhs.id;
		rhs.id = 0;
		return *this;
	}
	TextureObj(bool immediate = true)
	{
		if (immediate)
			glGenTextures(1, &id);
	}
	~TextureObj() { clean(); }
	operator GLuint() { return id; }
private:
	void clean()
	{
		if (id)
			glDeleteTextures(1, &id);
	}
	GLuint id = 0;
};

class ShaderObj
{
	friend class ProgramObj;
public:
	ShaderObj(const ShaderObj&) = delete;
	ShaderObj & operator=(const ShaderObj&) = delete;
	ShaderObj(GLuint shader_id = 0) :id(shader_id) {}
	ShaderObj(ShaderObj && rhs)
	{
		this->id = rhs.id;
		this->prog_id = rhs.prog_id;
		rhs.id = 0;
		rhs.prog_id = 0;
	}
	ShaderObj& operator=(ShaderObj && rhs)
	{
		clean();
		this->id = rhs.id;
		this->prog_id = rhs.prog_id;
		rhs.id = 0;
		rhs.prog_id = 0;
		return *this;
	}
	~ShaderObj() { clean(); }
	operator GLuint() { return id; }
private:
	void clean()
	{
		if (id)
		{
			if (prog_id)
				glDetachShader(prog_id, id);
			glDeleteShader(id);
		}
	}
	GLuint id, prog_id;

};

class ProgramObj
{
public:
	ProgramObj(const ProgramObj&) = delete;
	ProgramObj & operator=(const ProgramObj&) = delete;
	ProgramObj(GLuint id = 0) :prog_id(id) {}
	ProgramObj(ProgramObj && rhs)
	{
		this->prog_id = rhs.prog_id;
		rhs.prog_id = 0;
		uniforms = std::move(rhs.uniforms);
	}
	ProgramObj& operator=(ProgramObj && rhs)
	{
		clean();
		this->prog_id = rhs.prog_id;
		rhs.prog_id = 0;
		uniforms = std::move(rhs.uniforms);
		return *this;
	}
	~ProgramObj() { clean(); }
	operator GLuint() { return prog_id; }
	void AttachShader(ShaderObj& shader)
	{
		glAttachShader(prog_id, shader);
		shader.prog_id = prog_id;
	}
	int GetUniformLocation(std::string name)
	{
		auto uniform = uniforms.find(name);
		int loc = -1;
		if (uniform == uniforms.end())
		{
			loc = glGetUniformLocation(prog_id, name.c_str());
			//assert(loc != -1);
			uniforms.insert(make_pair(name, loc));
			return loc;
		}
		loc = uniform->second;
		return loc;
	}
private:
	std::map<std::string, int> uniforms;
	void clean()
	{
		if (prog_id)
			glDeleteProgram(prog_id);
	}
	GLuint prog_id = 0;
};

#endif // __GLOBJS_H_
