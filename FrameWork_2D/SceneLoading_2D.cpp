#include "stdafx.h"
#include "GameFrameWork_2D.h"

#include "SceneLoading_2D.h"
#include "SceneSelectMenu_2D.h"


CSceneLoading_2D::CSceneLoading_2D(std::string name) : CGameState_2D(name)
{
}

CSceneLoading_2D::~CSceneLoading_2D()
{
	delete this;
}

void CSceneLoading_2D::enter(HWND hWnd, HINSTANCE hInstance, int nWndClientWidth, int nWndClientHeight)
{
	m_width = nWndClientWidth;
	m_height = nWndClientHeight;

	m_hWnd = hWnd;
	m_hInstance = hInstance;
	mx = my = 0;

	m_logo.Init("로고");
	m_logo.OnCreate(m_width / 2, m_height / 2, m_width, m_height);
	m_alpha = 255;

}

void CSceneLoading_2D::exit()
{
}

void CSceneLoading_2D::pause()
{
}

void CSceneLoading_2D::resume()
{
}

//Render & Logic
void CSceneLoading_2D::OnDraw(HDC hdc)
{
	Draw_2D::drawRect(hdc, 1250, 750, 540, 480, BRIGHT_BLUE_3, true);

	m_logo.OnDrawAlpha(hdc, m_alpha -= 3);

}


void CSceneLoading_2D::OnUpdate(float fTimeElapsed)
{
	if (m_alpha < 255)
		FRAMEWORK_2D->change_state(new CSceneSelectMenu_2D("SceneRanking"));
}

//Call
void CSceneLoading_2D::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
}

void CSceneLoading_2D::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (nMessageID == WM_KEYDOWN)
	{

	}
}

void CSceneLoading_2D::SetWindowsSizeChange(int width, int height)
{
}

void CSceneLoading_2D::CallMenu(WPARAM wParam)
{
}

/*

void CSceneLoading_2D::LoadReplay()
{
//-------------Read----------
m_vReplay.clear();
//-------------Read----------

POINT mPt;


while (true)
{
CReplay replay;
char msg[100] = { NULL };
m_fStreamIn >> msg;
m_fStreamIn >> mPt.x >> mPt.y;
m_fStreamIn >> msg;
SetCursorPos(mPt.x, mPt.y);    // move

//-------------Read----------
replay.first = mPt;
//-------------Read----------

if (mPt.x == -1 && mPt.y == -1)
{
//SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);

//-------------Read----------
break;
//-------------Read----------
return;
}

int key = 0;
while (key + 1)
{
m_fStreamIn >> key;

if (key == 1)
{
mouse_event(MOUSEEVENTF_LEFTDOWN, mPt.x, mPt.y, 0, 0);
mouse_event(MOUSEEVENTF_LEFTUP, mPt.x, mPt.y, 0, 0);
}
else if (key == 2)
{
mouse_event(MOUSEEVENTF_RIGHTDOWN, mPt.x, mPt.y, 0, 0);
mouse_event(MOUSEEVENTF_RIGHTDOWN, mPt.x, mPt.y, 0, 0);
}
else
{
keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY, 0);
keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
}

//-------------Read----------
replay.second.push_back(key);
//-------------Read----------
}

//종료 조건
if (GetAsyncKeyState(VK_F12) & 0x8000)
{



m_bLoad = false;
m_fStreamIn.close();
::MessageBox(NULL, L"Load Exit", L"Load", MB_OK);
}


}

}
*/

