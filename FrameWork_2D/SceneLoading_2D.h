#pragma once


class CSceneLoading_2D: public CGameState_2D
{

private:
	CSpriteObject_2D							m_logo;
	int											m_alpha;

public:
	
	CSceneLoading_2D(std::string name);
	
	~CSceneLoading_2D();


	//Sate Change
	virtual void enter(HWND hWnd, HINSTANCE hInstance, int nWndClientWidth, int nWndClientHeight);

	virtual void exit();

	virtual void pause();

	virtual void resume();

	//Render & Logic
	virtual void OnDraw(HDC hdc);

	virtual void OnUpdate(float fTimeElapsed);


	//Call
	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	virtual void SetWindowsSizeChange(int width, int height);

	virtual void CallMenu(WPARAM wParam);

};

