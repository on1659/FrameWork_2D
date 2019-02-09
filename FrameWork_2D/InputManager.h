#pragma once

//KYT '12.02.17
/*
Input Manager

KeyDown, KeyUp, MouseWheel, MouseClick

����
1. Define YT_KEY���� ����� Ű���� �߰��Ѵ�.
- ������Ű�°� �߿��ϴ�.
- ����ȭ�� ���� ���ͷ� �Ͽ��� �����̴�.

2. Load�� ��� ����� key���� Add�Ѵ�.
- AddKey(���� Ű��, ������ų VK_KEY��)
- HashTable���� string�� ��� ��Ų��.

�Լ� ����
1. Load : ����� Ű�� ����Ѵ�.
2. KeyDown( YT_KEY(enum) )���� �־ �Ǵ�.
- True : KeyDown
- KeyDown�� Up�� ���� ����ؾ� �Ѵ�.

3. KeyUp (YT_KEY(enum))���� �־ �Ǵ�.
- KeyDown�ϰ� ���� ����� �ʿ�� ����.

4. OnlyKeyDown�� KeyUp�� ������� �������� ����Ѵ�.
cuz. ���ÿ� ������ ����ִ°� ������ �׷�.

5. GetWheel()�� � ��ҿ����� �����͸� ���Ϲ޾Ƽ�
- GetWheel() < 0 �� �Ʒ���
- GetWheel() = 0 �� �ȿ�����
- GetWheel() > 0 �� ����

6. GetInputQueue() = input Data�� Queue�������̴�.

*/

#include <deque>
#include <queue>

typedef struct tagKeyState
{
	YT_KEY  ytkey;
	bool	bUpCheck;
	bool	bDownCheck;
	BYTE	BKey;

	tagKeyState::tagKeyState()
	{
		ytkey = YK_END;
		bUpCheck = false;
		bDownCheck = false;
		BKey = NULL;
	}

}KEYSTATE;

struct KeyStateCheck
{
	YT_KEY key;
	bool   bDown;

	KeyStateCheck() {};

	KeyStateCheck(YT_KEY inKey, bool inDown)
	{
		key = inKey;
		bDown = inDown;
	}
};


class CInputManager : public CSingleTonBase<CInputManager>
{
	//Ű����
private:
	//Key Data
	std::vector<KEYSTATE>				m_vKeyState;

	//KeyState
	bool								m_bKeyState[256];

	std::vector<std::string>		    m_stHashTable;

	int									m_sWheel;
	POINT								pt;

public:
	CInputManager(const CInputManager& rhs) = delete;


public:
	CInputManager();

	~CInputManager();

public:
	void Load();

	// bKeyBoard_Container
	void AddKey(YT_KEY key, BYTE input);
	bool KeyDown(YT_KEY input);
	bool KeyUp(YT_KEY input);

	//KeyUp�� ������� �ʰ� KeyDown�� ����ϴ� Ű���� ���
	bool OnlyKeyDown(YT_KEY input);

	//Mouse
	/*  Wheel Down < WheelNon < Wheel Up  */
	void SetWheel(int wheel);
	int GetWheel() { return m_sWheel; }
	void MouseWheel();
	void SetMousePoint(int qx, int y);
	void SetMousePoint(POINT _pt);
	POINT GetMousePoint() { return pt; }

};

