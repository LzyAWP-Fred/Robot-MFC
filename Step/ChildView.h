
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"
#include "SGNode.h"
#include "graphics/GrCamera.h"
#include "SGRotationTranslation.h"

#include <MMSystem.h>
#pragma comment(lib, "winmm")


// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();
	
	

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC* pDC);

	CSGPtr<CSGRotationTranslation> box(double p_x, double p_y, double p_z);

private:
	void CreateSceneGraph();

	CSGPtr<CSGNode> m_scenegraph;

	CGrCamera m_camera;

	CSGPtr<CSGRotationTranslation> m_hook1;
	CSGPtr<CSGRotationTranslation> m_hook2;

	DWORD m_lastTime;

	

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);

private:
	double  m_spinAngle;
	UINT_PTR m_spinTimer;

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRunDance();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

