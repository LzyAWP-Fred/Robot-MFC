#pragma once
#include "sgnode.h"
#include <vector>

class CSGRotationTranslation :
	public CSGNode
{
public:
	CSGRotationTranslation(void);
	~CSGRotationTranslation(void);

	void SetRotate(double angle, double rx, double ry, double rz) { m_angle = angle; m_rx = rx; m_ry = ry; m_rz = rz; }
	void SetTranslate(double tx, double ty, double tz) { m_tx = tx; m_ty = ty; m_tz = tz; }
	void AddChild(CSGNode *child) { m_children.push_back(child); }

	virtual void Render();

private:
	double  m_angle, m_rx, m_ry, m_rz;      // Rotation definition
	double  m_tx, m_ty, m_tz;               // Translation definition
	std::vector<CSGPtr<CSGNode> > m_children;
};