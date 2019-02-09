
#include "stdafx.h"
#include "GameFrameWork_2D.h"
#include "SceneLoading_2D.h"
#include <time.h>

//#define _CONSOL_

CGameFrameWork_2D::CGameFrameWork_2D()
{

	m_hdc	 = NULL;		
	m_hBitmapFrameBuffer = NULL;		
	m_hBitmapSelect		 = NULL;		
	m_hInstance			 = NULL;		
	m_hWnd				 = NULL;
	m_bBackgroundColor = 0x00FFFFFF;
	
}

CGameFrameWork_2D::~CGameFrameWork_2D()
{
	while (!states.empty()) {
		states.back()->exit();
		states.pop_back();
	}
}


//State

void CGameFrameWork_2D::enter(CGameState_2D *state)
{
	srand((unsigned int)time(NULL));
	states.push_back(state);
	states.back()->enter(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);
}

void CGameFrameWork_2D::change_state(CGameState_2D *state)
{

	if (!states.empty()) 
	{
		states.back()->exit();
		states.pop_back();
	}
	
	states.push_back(state);

	states.back()->enter(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);
	
}

void CGameFrameWork_2D::exit()
{
	RENDERMGR_2D->ReleseInstance();
	//SOUNDMGR->ReleseInstance();
	TIMEMGR->ReleseInstance();

#ifdef _CONSOL_
	FreeConsole(); // Free Console Window
#endif 
}

void CGameFrameWork_2D::pushState(CGameState_2D* state)
{
	// pause current state
	if (!states.empty()) {
		states.back()->pause();
	}
	// store and init the new state
	states.push_back(state);
	states.back()->enter(m_hWnd, m_hInstance, m_nWndClientWidth, m_nWndClientHeight);

}

void CGameFrameWork_2D::popState()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->exit();
		states.pop_back();
	}
	// resume previous state
	if (!states.empty()) {
		states.back()->resume();
	}
}



//Render & Logic & Init

void CGameFrameWork_2D::OnCreate(HINSTANCE hInstance, HWND hMainWnd)
{
	m_hWnd = hMainWnd;
	m_hInstance = hInstance;

	srand((unsigned int)time(NULL));

	//제일 먼저
	TIMEMGR->Tick();						//타이머
	RENDERMGR_2D->LoadCImage();				//랜더매니저
	SOUNDMGR->LoadSound();					//사운드매니저
	SOUNDMGR->VoulamInit();					//사운드매니저
	INPUT->Load();							//인풋매니저
	m_nWndClientWidth = WIDTH;
	m_nWndClientHeight = HEIGHT;


	this->enter(new CSceneLoading_2D("CSceneLoading_2D"));
}

void CGameFrameWork_2D::PreDraw(DWORD dwColor)
{
	HBRUSH hBrush = ::CreateSolidBrush(dwColor);
	HBRUSH hOldBrush = (HBRUSH)::SelectObject(m_hdc, hBrush);
	::Rectangle(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, hOldBrush);
	::DeleteObject(hBrush);
}

void CGameFrameWork_2D::BeginDraw()
{
	HDC hDC = ::GetDC(m_hWnd);

	if (!m_hdc) 
		m_hdc = ::CreateCompatibleDC(hDC);
	if (m_hBitmapFrameBuffer)
	{
		::SelectObject(m_hdc, NULL);
		::DeleteObject(m_hBitmapFrameBuffer);
		m_hBitmapFrameBuffer = NULL;
	}

	m_hBitmapFrameBuffer = ::CreateCompatibleBitmap(hDC, m_nWndClientWidth, m_nWndClientHeight);
	::SelectObject(m_hdc, m_hBitmapFrameBuffer);

	::ReleaseDC(m_hWnd, hDC);
	::SetBkMode(m_hdc, TRANSPARENT);

}

void CGameFrameWork_2D::OnDraw()
{
	this->BeginDraw();

	//drawRect
	Draw_2D::drawRect(m_hdc, 0, 0, m_nWndClientWidth, m_nWndClientHeight, BRUSH2, true);


	if (!states.empty()) 
	{
		states.back()->OnDraw(m_hdc);
	}
	// resume previous state
	else if(!states.empty()) {
		states.back()->OnDraw(m_hdc);
	}
	this->EndDraw();

}

void CGameFrameWork_2D::EndDraw()
{
	HDC hDC = ::GetDC(m_hWnd);

	::BitBlt(hDC, 0, 0, m_nWndClientWidth, m_nWndClientHeight, m_hdc, 0, 0, SRCCOPY);
	::ReleaseDC(m_hWnd, hDC);


}

void CGameFrameWork_2D::OnUpdate()
{	
	//::gotoxy(0, 0, "mouse(%d,%d)", INPUT->GetMousePoint().x, INPUT->GetMousePoint().y);

	TIMEMGR->Tick(20);

	m_fTimeElapsed = TIMEMGR->GetTimeElapsed();

	if (!states.empty())
	{
		states.back()->OnUpdate(m_fTimeElapsed);
	}
	// resume previous state
	else if(!states.empty()) {
		states.back()->OnUpdate(m_fTimeElapsed);
	}


	SOUNDMGR->OnUpdate();

	//if (GetAsyncKeyState(VK_F12) & 0x8000)
	//{
	//	SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
	//}
}

void CGameFrameWork_2D::OnDestory()
{
	// cleanup the current state
	if (!states.empty()) {
		states.back()->exit();
		states.pop_back();
	}
	// resume previous state
	if (!states.empty()) {
		states.back()->exit();
	}
	this->exit();

	cout << "Exit" << endl;
}


//CallBack

void CGameFrameWork_2D::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{

	if (!states.empty())
	{
		states.back()->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
	}

	// resume previous state
	else if(!states.empty()) 
	{
		states.back()->OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
	}

	switch (nMessageID)
	{
	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
		break;

	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
		break;

	case WM_MOUSEMOVE:

		INPUT->SetMousePoint(
			POINT
			{ 
				 LOWORD(lParam)
				,HIWORD(lParam) 
			}
		);
		break;
	}
}

void CGameFrameWork_2D::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	if (nMessageID == WM_KEYUP && wParam == 'q'-32)
	{
		SendMessage(m_hWnd, WM_DESTROY, NULL, NULL);
	}

	if (!states.empty())
	{
		states.back()->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	}

	// resume previous state
	else if (!states.empty()) {
		states.back()->OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
	}
}

void CGameFrameWork_2D::SetWindowsSizeChange(int width, int height)
{
	m_nWndClientWidth = width;
	m_nWndClientHeight = height;

	if (!states.empty())
	{
		states.back()->SetWindowsSizeChange(m_nWndClientWidth, m_nWndClientHeight);
	}
	// resume previous state
	else if (!states.empty()) {
		states.back()->SetWindowsSizeChange(m_nWndClientWidth, m_nWndClientHeight);
	}

}

void CGameFrameWork_2D::CallMenu(WPARAM wParam)
{
	if (!states.empty())
	{
		states.back()->CallMenu(wParam);
	}
	// resume previous state
	else if (!states.empty()) {
		states.back()->CallMenu(wParam);
	}
	//nowState->callMenu(wParam);
}

LRESULT CALLBACK CGameFrameWork_2D::OnProcessingWindowMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	switch (nMessageID)
	{
		/*윈도우의 크기가 변경될 때(현재는 “Alt+Enter“ 전체 화면 모드와 윈도우 모드로 전환될 때) 스왑 체인의 후면버퍼 크기를 조정하고 후면버퍼에 대한 렌더 타겟 뷰를 다시 생성한다. */
	case WM_SIZE:
	{
		m_nWndClientWidth = LOWORD(lParam);
		m_nWndClientHeight = HIWORD(lParam);

		break;
	}

	case WM_LBUTTONDOWN:
	case WM_RBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONUP:
	case WM_MOUSEMOVE:
		OnProcessingMouseMessage(hWnd, nMessageID, wParam, lParam);
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
		OnProcessingKeyboardMessage(hWnd, nMessageID, wParam, lParam);
		break;
	}
	return(0);
}


