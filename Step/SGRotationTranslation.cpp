#include "StdAfx.h"
#include "SGRotationTranslation.h"
#include <gl/gl.h>

CSGRotationTranslation::CSGRotationTranslation(void)
{
	m_angle = 0;
	m_rx = 1;
	m_ry = m_rz = 0;
	m_tx = m_ty = m_tz = 0;
}

CSGRotationTranslation::~CSGRotationTranslation(void)
{
}

void CSGRotationTranslation::Render()
{
	glPushMatrix();
	glTranslated(m_tx, m_ty, m_tz);
	if (m_angle != 0)
		glRotated(m_angle, m_rx, m_ry, m_rz);

	for (std::vector<CSGPtr<CSGNode> >::iterator child = m_children.begin();
		child != m_children.end();  child++)
	{
		(*child)->Render();
	}
	glPopMatrix();
}