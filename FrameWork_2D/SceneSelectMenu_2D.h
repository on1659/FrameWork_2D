#pragma once


class CSceneSelectMenu_2D : public CGameState_2D
{
private:
	float m_x, m_y;
	int m_r;
	float m_s;

public:

	CSceneSelectMenu_2D(std::string name);

	~CSceneSelectMenu_2D();

	//Sate Change
	virtual void enter(HWND hWnd, HINSTANCE m_hInstance, int nWndClientWidth, int nWndClientHeight);

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

