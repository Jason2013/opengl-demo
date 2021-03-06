#ifndef __DEMO00_H__
#define __DEMO00_H__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <GLFW/glfw3.h>

#include "demo.h"
#include "globjs.h"


class Demo00 : public Demo
{
public:
	Demo00(GLFWwindow * win) :Demo(win), vao(false) {}
	virtual void Active() override;
	//virtual void ResizeWindow(int width, int height) override;
	virtual void Prepare() override;
	virtual void Draw() override;
	virtual void Finalize() override;
	virtual ~Demo00() override;
private:
	ProgramObj program;
	VertexArrayObj vao;
	BufferObj buffer;
};

#endif
