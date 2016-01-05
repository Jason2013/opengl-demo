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
	)
	{
    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;
    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;
	GLfloat ds = 1.0f / (GLfloat) iSlices;
	GLfloat dt = 1.0f / (GLfloat) iStacks;
	GLfloat t = 1.0f;	
	GLfloat s = 0.0f;
    GLint i, j;     // Looping variables
    
	for (i = 0; i < iStacks; i++) 
		{
		GLfloat rho = (GLfloat)i * drho;
		GLfloat srho = (GLfloat)(sin(rho));
		GLfloat crho = (GLfloat)(cos(rho));
		GLfloat srhodrho = (GLfloat)(sin(rho + drho));
		GLfloat crhodrho = (GLfloat)(cos(rho + drho));
		
        // Many sources of OpenGL sphere drawing code uses a triangle fan
        // for the caps of the sphere. This however introduces texturing 
        // artifacts at the poles on some OpenGL implementations
        s = 0.0f;

		vec3 vVertex[4];
		vec3 vNormal[4];
		vec2 vTexture[4];

		for ( j = 0; j < iSlices; j++) 
			{
			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
			GLfloat stheta = (GLfloat)(-sin(theta));
			GLfloat ctheta = (GLfloat)(cos(theta));
			
			GLfloat x = stheta * srho;
			GLfloat y = ctheta * srho;
			GLfloat z = crho;
        
			vTexture[0][0] = s;
			vTexture[0][1] = t;
			vNormal[0][0] = x;
			vNormal[0][1] = y;
			vNormal[0][2] = z;
			vVertex[0][0] = x * fRadius;
			vVertex[0][1] = y * fRadius;
			vVertex[0][2] = z * fRadius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[1][0] = s;
			vTexture[1][1] = t - dt;
			vNormal[1][0] = x;
			vNormal[1][1] = y;
			vNormal[1][2] = z;
			vVertex[1][0] = x * fRadius;
			vVertex[1][1] = y * fRadius;
			vVertex[1][2] = z * fRadius;
			

			theta = ((j+1) == iSlices) ? 0.0f : (j+1) * dtheta;
			stheta = (GLfloat)(-sin(theta));
			ctheta = (GLfloat)(cos(theta));
			
			x = stheta * srho;
			y = ctheta * srho;
			z = crho;
        
            s += ds;
			vTexture[2][0] = s;
			vTexture[2][1] = t;

			vNormal[2][0] = x;
			vNormal[2][1] = y;
			vNormal[2][2] = z;

			vVertex[2][0] = x * fRadius;
			vVertex[2][1] = y * fRadius;
			vVertex[2][2] = z * fRadius;
			
            x = stheta * srhodrho;
			y = ctheta * srhodrho;
			z = crhodrho;

 			vTexture[3][0] = s;
			vTexture[3][1] = t - dt;
			
			vNormal[3][0] = x;
			vNormal[3][1] = y;
			vNormal[3][2] = z;

			vVertex[3][0] = x * fRadius;
			vVertex[3][1] = y * fRadius;
			vVertex[3][2] = z * fRadius;
		
			static int vIndex[6] = { 0,1,2,2,1,3 };
			for (auto i : vIndex)
			{
				out_vertices.push_back(vVertex[i]);
				out_uvs.push_back(vTexture[i]);
				out_normals.push_back(vNormal[i]);
			}
			}
        t -= dt;
        }
    }
    