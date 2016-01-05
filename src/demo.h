#ifndef __DEMO_H__
#define __DEMO_H__
#include <cassert>
#include <GLFW/glfw3.h>

class Demo
{
public:
	virtual void Time(double time) {}
	virtual void Active() {}
	virtual void ResizeWindow(int width, int height) { glViewport(0, 0, width, height); }
	virtual void Key(int key) {}
	virtual void Prepare(GLFWwindow* win) { window = win; assert(window); };
	virtual void Draw() {};
	virtual void Finalize() {};
	virtual ~Demo() {};

	GLFWwindow* Window() { assert(window); return window; }

private:
	GLFWwindow* window = 0;
};

#endif
