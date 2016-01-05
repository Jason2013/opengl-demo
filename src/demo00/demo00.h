#ifndef __DEMO00_H__
#define __DEMO00_H__

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "demo.h"
#include "globjs.h"


class Demo00 : public Demo
{
public:
	Demo00():vao(false){}
	virtual void Active() override;
	virtual void Prepare();
	virtual void Draw();
	virtual void Finalize();
	virtual ~Demo00();
private:
	ProgramObj program;
	VertexArrayObj vao;
	BufferObj buffer;
};

#endif
