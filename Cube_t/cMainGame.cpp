#include "stdafx.h"
#include "cMainGame.h"


cMainGame::cMainGame() : m_hBitmap(NULL), m_vEye(0,0,-5), m_vLookAt(0,0,0), m_vUp(0,1,0), m_r(0,0,0), m_m(0,0,0), m_c(0,5,-5)
{
}


cMainGame::~cMainGame()
{
	SelectObject(m_memDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_memDC);
}

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);
	m_memDC = CreateCompatibleDC(hdc);
	{
		RECT rc;
		GetClientRect(g_hWnd, &rc);
		m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		m_hOldBitmap = (HBITMAP)SelectObject(m_memDC, m_hBitmap);
		ReleaseDC(g_hWnd, hdc);
	}

	{
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));
	}

	{
		// : front
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);

		// : back
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);

		// : left
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);

		// : right
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);

		// : top
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);

		// : bottom
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);
	}

	//line ����
	for (int i = 0; i <= 10; i++)
	{
		m_vecLineVertex.push_back(cVector3(-5.0f+(float)i, 0.0f, -5.0f));
		m_vecLineVertex.push_back(cVector3(-5.0f + (float)i, 0.0f, 5.0f));
	}
	//line ����
	for (int i = 0; i <= 10; i++)
	{
		m_vecLineVertex.push_back(cVector3(-5.0f, 0.0f, -5.0f + (float)i));
		m_vecLineVertex.push_back(cVector3(5.0f, 0.0f, -5.0f + (float)i));
	}

	m_matWorld = cMatrix::Identity(4);
	m_matWorldl = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}

void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vLookAt = cVector3(m_m.x, m_m.y, m_m.z);
	m_vEye = cVector3(m_c.x+m_m.x, m_c.y+m_m.y, m_c.z+m_m.z);

	m_matWorld = cMatrix::Scale(1.0f, 1.0f, 1.0f) * cMatrix::Rotate(m_r.x, m_r.y, m_r.z) * cMatrix::Translation(m_m.x, m_m.y, m_m.z);
	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	PatBlt(m_memDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);
	
	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	cMatrix matWVPl = m_matWorldl * m_matView * m_matProj;

	//����
	for (int i = 0; i < 22; i+=2)
	{
		cVector3 lv1 = m_vecLineVertex[i];
		cVector3 lv2 = m_vecLineVertex[i+1];
		lv1 = cVector3::TransformCoord(lv1, matWVPl);
		lv2 = cVector3::TransformCoord(lv2, matWVPl);
		lv1 = cVector3::TransformCoord(lv1, m_matViewport);
		lv2 = cVector3::TransformCoord(lv2, m_matViewport);

		MoveToEx(m_memDC, lv1.x, lv1.y, NULL);
		LineTo(m_memDC, lv2.x, lv2.y);
	}
	//����
	for (int i = 22; i < 44; i += 2)
	{
		cVector3 lv1 = m_vecLineVertex[i];
		cVector3 lv2 = m_vecLineVertex[i + 1];
		lv1 = cVector3::TransformCoord(lv1, matWVPl);
		lv2 = cVector3::TransformCoord(lv2, matWVPl);
		lv1 = cVector3::TransformCoord(lv1, m_matViewport);
		lv2 = cVector3::TransformCoord(lv2, m_matViewport);

		MoveToEx(m_memDC, lv1.x, lv1.y, NULL);
		LineTo(m_memDC, lv2.x, lv2.y);
	}

	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		// >> ����
		// ���� ���̶� �ٸ� ������ ���͸� ���ؼ� ���� �ΰ��� �����ϰ� ī�޶�� �����ؼ� ��� , ����

		// << 

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		MoveToEx(m_memDC, v1.x, v1.y, NULL);
		LineTo(m_memDC, v2.x, v2.y);
		LineTo(m_memDC, v3.x, v3.y);
		LineTo(m_memDC, v1.x, v1.y);
	}

	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_memDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case 0x41: // ȸ�� ���� a
			m_r.y -= 0.1f;
			break;
		case 0x44: // ȸ�� ������ d
			m_r.y += 0.1f;
			break;
		case 0x57: // �̵� w
			m_m = m_m + cVector3(m_matWorld[2][0] * 0.1f,m_matWorld[2][1] * 0.1f, m_matWorld[2][2] * 0.1f);
			break;
		case 0x53: // �̵� s
			m_m = m_m - cVector3(m_matWorld[2][0] * 0.1f, m_matWorld[2][1] * 0.1f, m_matWorld[2][2] * 0.1f);
			break;
		}
	}
		break;
	}
}



/*
	1. Ű�� ȸ�� .. a,d - Y��
	2. �׸��� �׸��� Z, X �� ǥ��
	3. �̵� w, s �̵�
	4. ī�޶� �̵� �ϴ� ������Ʈ�� ���� �ٴ�.
	5. �ĸ����� backface calling
	6. ���콺 ��Ŭ������ ������Ʈ �߽����� ī�޶� ȸ�� �̵�
	7. ũ�� ���� q,e
	8. ī�޶�� ������Ʈ ���� �Ÿ� ���� �ٸ��콺
*/