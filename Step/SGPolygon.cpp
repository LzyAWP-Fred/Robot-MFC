#include "StdAfx.h"
#include "SGPolygon.h"
#include "graphics/GrVector.h"
#include "graphics/GrTexture.h"


using namespace std;

CSGPolygon::CSGPolygon(void) : m_texture(NULL)
{
}

CSGPolygon::~CSGPolygon(void)
{
}

void CSGPolygon::Render()
{
	// Create an iterator for each of the three arrays
	vector<CGrVector>::iterator v = m_vertices.begin();
	vector<CGrVector>::iterator n = m_normals.begin();
	vector<CGrVector>::iterator t = m_tvertices.begin();

	glBegin(GL_POLYGON);
	for (; v != m_vertices.end(); v++)
	{
		// If we have an available normal, use it:
		if (n != m_normals.end())
		{
			glNormal3dv(*n);
			n++;
		}

		// If we have an available texture coordinate, use it:
		if (t != m_tvertices.end())
		{
			glTexCoord2dv(*t);
			t++;
		}

		glVertex3dv(*v);
	}

	glEnd();
}
