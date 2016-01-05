#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////
#include "sphere.h"
// Make a sphere

void MakeSphere(GLfloat fRadius, GLint iSlices, GLint iStacks,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
	);

#endif // __SPHERE_H__
