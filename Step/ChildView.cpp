
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Step.h"
#include "ChildView.h"
#include "SGNode.h"
#include "SGPolygon.h"
#include "SGRotationTranslation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	CreateSceneGraph();
	m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
	
	timeBeginPeriod(1);
	m_lastTime = 0;

	m_spinAngle = 0;
	m_spinTimer = 0;

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
	ON_COMMAND(ID_RUN_DANCE, &CChildView::OnRunDance)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}




void CChildView::OnGLDraw(CDC* pDC)
{

	DWORD newTime = timeGetTime();
	double delta = (newTime - m_lastTime) * 0.001;
	m_lastTime = newTime;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set up the camera
	//

	int width, height;
	GetSize(width, height);
	m_camera.Apply(width, height);

	gluLookAt(20., 10., 50.,    // eye x,y,z
		0., 0., 0.,       // center x,y,z
		0., 1., 0.);      // Up direction

						  //
						  // Some standard parameters
						  //

						  // Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Cull backfacing polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Draw a coordinate axis
	glColor3d(0., 1., 1.);

	glBegin(GL_LINES);
	glVertex3d(0., 0., 0.);
	glVertex3d(12., 0., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 12., 0.);
	glVertex3d(0., 0., 0.);
	glVertex3d(0., 0., 12.);
	glEnd();


	// 
	// INSERT DRAWING CODE HERE
	//
	
	// Animation
	m_hook1->SetTranslate(1.5, 1.5, 1.5);
	m_hook1->SetRotate(m_spinAngle, 0, 1, 0);
	m_hook1->SetTranslate(-1.5, -1.5, -1.5);
	//m_hook2->SetRotate(-m_spinAngle, 0, 0, 1);

	m_scenegraph->Render();
}



CSGPtr<CSGRotationTranslation> CChildView::box(double p_x, double p_y, double p_z) 
{
	CSGPtr<CSGPolygon> poly1 = new CSGPolygon();
	CSGPtr<CSGPolygon> poly2 = new CSGPolygon();
	CSGPtr<CSGPolygon> poly3 = new CSGPolygon();
	CSGPtr<CSGPolygon> poly4 = new CSGPolygon();
	CSGPtr<CSGPolygon> poly5 = new CSGPolygon();
	CSGPtr<CSGPolygon> poly6 = new CSGPolygon();

	CSGPtr<CSGRotationTranslation> rt = new CSGRotationTranslation();

	CGrVector a(0, 0, p_z);
	CGrVector b(p_x, 0, p_z);
	CGrVector c(p_x, p_y, p_z);
	CGrVector d(0, p_y, p_z);
	CGrVector e(0, 0, 0);
	CGrVector f(p_x, 0, 0);
	CGrVector g(p_x, p_y, 0);
	CGrVector h(0, p_y, 0);

	poly1->AddNormal(CGrVector(0.0, 0.0, 1.0));
	poly1->AddVertex(a);
	poly1->AddVertex(b);
	poly1->AddVertex(c);
	poly1->AddVertex(d);

	poly2->AddNormal(CGrVector(1.0, 0.0, 0.0));
	poly2->AddVertex(c);
	poly2->AddVertex(b);
	poly2->AddVertex(f);
	poly2->AddVertex(g);


	poly3->AddNormal(CGrVector(0.0, 0.0, -3.0));
	poly3->AddVertex(h);
	poly3->AddVertex(g);
	poly3->AddVertex(f);
	poly3->AddVertex(e);

	poly4->AddNormal(CGrVector(3.0, 0.0, 0.0));
	poly4->AddVertex(d);
	poly4->AddVertex(h);
	poly4->AddVertex(e);
	poly4->AddVertex(a);

	poly5->AddNormal(CGrVector(0.0, 21.0, 0.0));
	poly5->AddVertex(d);
	poly5->AddVertex(c);
	poly5->AddVertex(g);
	poly5->AddVertex(h);

	poly6->AddNormal(CGrVector(0.0, 15.0, 0.0));
	poly6->AddVertex(e);
	poly6->AddVertex(f);
	poly6->AddVertex(b);
	poly6->AddVertex(a);

	rt->AddChild(poly1);
	rt->AddChild(poly2);
	rt->AddChild(poly3);
	rt->AddChild(poly4);
	rt->AddChild(poly5);
	rt->AddChild(poly6);

	return rt;
}



void CChildView::CreateSceneGraph()
{

	CSGPtr<CSGRotationTranslation> root = new CSGRotationTranslation();
	CSGPtr<CSGRotationTranslation> rt1 = new CSGRotationTranslation();
	CSGPtr<CSGRotationTranslation> rt2 = new CSGRotationTranslation();
	CSGPtr<CSGRotationTranslation> rt = box(3, 3, 3);


	root->AddChild(rt1);
	//root->AddChild(rt2);

	rt1->AddChild(rt);
	//rt2->AddChild(rt);

	//rt1->SetTranslate(1.5, 1.5, 1.5);

	//rt2->SetTranslate(-5, 0, 0);

	m_scenegraph = root;
	//rt1->SetTranslate(-1.5, -1.5, -1.5);
	m_hook1 = rt1;

	//m_hook2 = rt2;
	// dfd
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y);

	COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_camera.MouseMove(point.x, point.y, nFlags))
		Invalidate();
	COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y, 2);

	COpenGLWnd::OnRButtonDown(nFlags, point);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COpenGLWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_lastTime = timeGetTime();

	return 0;
}


void CChildView::OnRunDance()
{
	if (m_spinTimer == 0)
	{
		// Create the timer
		m_spinTimer = SetTimer(1, 30, NULL);
	}
	else
	{
		// Destroy the timer
		KillTimer(m_spinTimer);
		m_spinTimer = 0;
	}
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	m_spinAngle += 5;       // 5 degrees every 30ms about
	Invalidate();

	COpenGLWnd::OnTimer(nIDEvent);
}
