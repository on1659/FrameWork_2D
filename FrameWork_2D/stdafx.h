#pragma once

#ifdef _DEBUG
	#ifdef UNICODE
		#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
	#else 
		#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
	#endif
#endif

using namespace std;

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include <string>
#include <map>
#include <vector>
#include <string>
#include <atlimage.h>
#include <memory>
#include <iostream>
#include <fstream>

#include "GameState_2D.h"
#include "SingleTon.h"
#include "GameTimer.h"
#include "Sound.h"

#include "GraphicObject_2D.h"
#include "SpriteObject_2D.h"

#include "RenderManager_2D.h"
#include "InputManager.h"
#include "MyFunction.h"
#include "Utill.h"


//
#include "Draw_2D.h"
#include "Lusian_Scrool.h"
#include "Object_2D.h"
#include "EditBox.h"

#define _OPTIMIZATION

#define WIDTH 1280
#define HEIGHT 720

#define WIDTH_POSITION	50
#define HEIGHT_POSITION 0

#define OBSTACLE_COUNT	8
#define PI				3.141592
#define RADIAN			(3.141592 / 180)

//싱글톤
#define FRAMEWORK_2D	 CGameFrameWork_2D::GetInstance()
#define RENDERMGR_2D	 CRenderManager_2D::GetInstance()
#define SOUNDMGR		 SoundManager::GetInstance()
#define TIMEMGR			 CGameTimer::GetInstance()
#define INPUT			 CInputManager::GetInstance()

static HINSTANCE g_hInstance;
static HWND g_Hwnd;

static void gotoxy(const int x,const int y, const char *msg, ...)
{
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	va_list arg;
	va_start(arg, msg);
	vprintf(msg, arg);
	va_end(arg);
	printf("\n");
}

//#define SAVE
static ofstream m_fStreamOut;//("../replay.txt");
static ifstream m_fStreamIn;//("../replay.txt");

static int gframeCount = 0;

//#define PI								3.14159
#define RADAIN(X)						(PI / 180) * X
