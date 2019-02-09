#include "stdafx.h"
#include "SceneSelectMenu_2D.h"
#include "Draw_2D.h"
#include "GameFrameWork_2D.h"
#include "RenderManager_2D.h"

#include <math.h>

CSceneSelectMenu_2D::CSceneSelectMenu_2D(std::string name) : CGameState_2D(name)
{
}

CSceneSelectMenu_2D::~CSceneSelectMenu_2D()
{
	delete this;
}

void CSceneSelectMenu_2D::enter(HWND hWnd, HINSTANCE hInstance, int nWndClientWidth, int nWndClientHeight)
{
	m_width = nWndClientWidth;
	m_height = nWndClientHeight;

	m_hWnd = hWnd;
	m_hInstance = hInstance;
	mx = my = 0;

	m_x = 500;
	m_y = 150;
	m_s = 150;
	m_r = 0;

}

void CSceneSelectMenu_2D::exit()
{
}

void CSceneSelectMenu_2D::pause()
{
}

void CSceneSelectMenu_2D::resume()
{
}

//Render & Logic
void CSceneSelectMenu_2D::OnDraw(HDC hdc)
{

	Draw_2D::drawCicle(hdc, m_x, m_y, 10, RED, RED, 10);

	float x = m_s * cos(RADAIN(m_r));
	float y = m_s * sin(RADAIN(m_r));
	Draw_2D::drawCicle(hdc, m_x + x, m_y + y, 10, RED, RED, 10);

	m_r+=35;

}


void CSceneSelectMenu_2D::OnUpdate(float fTimeElapsed)
{
}

void CSceneSelectMenu_2D::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CSceneSelectMenu_2D::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (nMessageID == WM_KEYDOWN)
	{
		switch (wParam)
		{
			case 'a' - 32:
				SOUNDMGR->Play("코인");
				break;
			case 's' - 32:
				SOUNDMGR->Play("로딩");
				break;
			case 'd' - 32:
				SOUNDMGR->VolumUp();
				break;
			case 'f' - 32:
				SOUNDMGR->VolumDown();
				break;
		}
	}
}

void CSceneSelectMenu_2D::SetWindowsSizeChange(int width, int height)
{
}

void CSceneSelectMenu_2D::CallMenu(WPARAM wParam)
{
}


