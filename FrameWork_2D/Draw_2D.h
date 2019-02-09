#pragma once


#include <windows.h>

enum Color_2D
{
		RED			= RGB(255,0,0)				//0
	,	BLUE		= RGB(0, 0, 255)				//1
	,	GREEN		= RGB(0, 255, 0)				//2	
	,	BLACK		= RGB(0, 0, 0)				//3
	,	ORANGE		= RGB(230, 130, 5)				//4
	,	CYAN		= RGB(0, 255, 255)				//5
	,	MAGENTA		= RGB(255, 255, 0)			//6
	,	YELLOW		= RGB(255, 0, 255)			//7
	
	,BRIGHT_RED_1		= RGB(238, 20, 45)		//2382045
	,BRIGHT_RED_2		= RGB(229, 52, 165)		//229 52 165
	,BRIGHT_RED_3		= RGB(231, 15, 62)		//231 15 62
	,BRIGHT_RED_4		= RGB(246, 122, 218)		//246 122 218
	,BRIGHT_RED_5		= RGB(238, 5, 33)		//238 5 33
	,BRIGHT_RED_6		= RGB(243, 58, 60)		//243 58 60

	,BRIGHT_YELLOW_1		= RGB( 235, 249,81	 )
	,BRIGHT_YELLOW_2		= RGB( 244,229,109	 )
	,BRIGHT_YELLOW_3		= RGB( 244,213, 28	 )
	,BRIGHT_YELLOW_4		= RGB( 253,218, 76	 )
	,BRIGHT_YELLOW_5		= RGB( 228, 234, 92	 )
	,BRIGHT_YELLOW_6		= RGB( 234, 228, 106 )

	,BRIGHT_ORANGE_1		= RGB(241, 132, 18	)
	,BRIGHT_ORANGE_2		= RGB(244, 129, 83	)

	,BRIGHT_GREEN_1		= RGB( 15, 225, 121	)
	,BRIGHT_GREEN_2		= RGB( 02, 250, 82	)
	,BRIGHT_GREEN_3		= RGB( 7,244,83		)
	,BRIGHT_GREEN_4		= RGB( 117, 226, 153)
	,BRIGHT_GREEN_5		= RGB( 7, 226, 129	)
	,BRIGHT_GREEN_6		= RGB( 111,226,120	)
	,BRIGHT_GREEN_7		= RGB(90,254,108	)
	,BRIGHT_GREEN_8		= RGB(111, 226, 120	)
	,BRIGHT_GREEN_9		= RGB(163, 255, 118	)

	,BRIGHT_BLUE_1		= RGB(33, 201, 216 )
	,BRIGHT_BLUE_2		= RGB(77,94,209	   )
	,BRIGHT_BLUE_4		= RGB(84, 216, 177 )
	,BRIGHT_BLUE_3		= RGB(301,68,194   )
	
					
	,BROWN_GROUND		= RGB(202, 97, 37)
	, BRUSH				= RGB(248, 248, 248)
	, BRUSH2			= RGB(240, 240, 240)
	//보라색이문제가있네

	, WHITE			= RGB(255,255,255)
	, REMOVE_COLOR  = RGB(255,0,255)
	, END_COLOR
};

class Draw_2D
{

public:

	void static drawText(HDC hdc, const int& x, const int& y, const COLORREF& color, const int& size, TCHAR _font[], TCHAR *_message, ...)
	{
		HFONT hFont, OldFont;
		SetTextColor(hdc,color);
		hFont = CreateFont(size, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, (_font));
		OldFont = (HFONT)SelectObject(hdc, hFont);
		SetBkMode(hdc, TRANSPARENT);

		va_list arg;
		va_start(arg, _message);
		TCHAR buf[500] = { NULL };
		//vswprintf(buf, _message, arg);
		vswprintf_s(buf, _message, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		TextOut(hdc, x, y, buf, count);

		DeleteObject(hFont);
		DeleteObject(OldFont);
		va_end(arg);

	}

	void static drawText(HDC hdc, const int& x, const int& y, const COLORREF& color, TCHAR *_message, ...)
	{
		SetTextColor(hdc, color);
		SetBkMode(hdc, TRANSPARENT);

		va_list arg;
		va_start(arg, _message);
		TCHAR buf[500] = { NULL };
		//vswprintf(buf, _message, arg);
		vswprintf_s(buf, _message, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		TextOut(hdc, x, y, buf, count);

		va_end(arg);

	}

	void static drawText(HDC hdc, const int& x, const int& y, TCHAR *_message, ...)
	{
		va_list arg;
		va_start(arg, _message);
		TCHAR buf[500] = { NULL };
		//vswprintf(buf, _message, arg);
		vswprintf_s(buf, _message, arg);
		int count = 0;
		for (int i = 0; buf[i] != NULL; ++i)
			count++;
		TextOut(hdc, x, y, buf, count);

		va_end(arg);

	}
	
	void static drawLine(HDC hdc, const int& start_x, const int& start_y, const int& end_x, const int& end_y, const COLORREF& color)
	{
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

	}
	
	void static drawLine(HDC hdc, const int& start_x, const int& start_y, const int& end_x, const int& end_y){
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

	}
	
	void static drawLine(HDC hdc, const int& start_x, const int& start_y, const int& end_x, const int& end_y, const int& Linesize, const COLORREF& color){
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, Linesize,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, start_x, start_y, NULL);
		LineTo(hdc, end_x, end_y);
		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
	}


	///DrawRect
	void static drawRect(HDC hdc, const float& left, const float& top, const float& width, const float& height, const COLORREF& color, const COLORREF& pen_color, const int& penSize, const bool& isFill)
	{
		const int l = (int)left;
		const int t = (int)top;
		const int w = (int)width;
		const int h = (int)height;
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, penSize,  pen_color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (isFill == false)
		{
			MoveToEx(hdc, l, t, NULL);
			LineTo(hdc, l + w, t);

			MoveToEx(hdc, l + w, t, NULL);
			LineTo(hdc, l + w, t + h);


			MoveToEx(hdc, l + w, t + h, NULL);
			LineTo(hdc, l, t + h);


			MoveToEx(hdc, l, t + h, NULL);
			LineTo(hdc, l, t);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, l, t, l + w, t + h);

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, const int& x, const int& y, const int& size, const COLORREF& color)
	{
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + size, y);

		MoveToEx(hdc, x + size, y, NULL);
		LineTo(hdc, x + size, y + size);


		MoveToEx(hdc, x + size, y + size, NULL);
		LineTo(hdc, x, y + size);


		MoveToEx(hdc, x, y + size, NULL);
		LineTo(hdc, x, y);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, x, y, x + size, y + size);
	}

	void static drawRect(HDC hdc, const int& x, const int& y, const int& sizeX, const int& sizeY, const COLORREF& color){
		 
		 
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, x + sizeX, y);

		MoveToEx(hdc, x + sizeX, y, NULL);
		LineTo(hdc, x + sizeX, y + sizeY);

		MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
		LineTo(hdc, x, y + sizeY);

		MoveToEx(hdc, x, y + sizeY, NULL);
		LineTo(hdc, x, y);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, const int& x, const int& y, const int& sizeX, const int& sizeY, const COLORREF& color, const bool& type){
		 
		 
		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 3,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (type == false){
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x + sizeX, y);

			MoveToEx(hdc, x + sizeX, y, NULL);
			LineTo(hdc, x + sizeX, y + sizeY);

			MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
			LineTo(hdc, x, y + sizeY);

			MoveToEx(hdc, x, y + sizeY, NULL);
			LineTo(hdc, x, y);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x, y, x + sizeX, y + sizeY);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, const int& x, const int& y, const int& sizeX, int sizeY, const COLORREF& color, const COLORREF& pen_color, const bool& isFill)	{

		HPEN MyPen, OldPen;
	
		MyPen = CreatePen(PS_SOLID, 1,  pen_color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (isFill == false)
		{
			MoveToEx(hdc, x, y, NULL);
			LineTo(hdc, x + sizeX, y);

			MoveToEx(hdc, x + sizeX, y, NULL);
			LineTo(hdc, x + sizeX, y + sizeY);

			MoveToEx(hdc, x + sizeX, y + sizeY, NULL);
			LineTo(hdc, x, y + sizeY);

			MoveToEx(hdc, x, y + sizeY, NULL);
			LineTo(hdc, x, y);
		}
		else
		{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, x, y, x + sizeX, y + sizeY);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);

		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	void static drawRect(HDC hdc, const float& l, const float& t, const float& w, const float& h, const COLORREF& color, const COLORREF& pen_color, const bool& isFill = false)
	{
		

		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1,  pen_color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		if (isFill == false)
		{

			MoveToEx(hdc, (int)l, (int)t, NULL);
			LineTo(hdc, (int)(l + w), (int)t);

			MoveToEx(hdc, (int)(l + w), (int)t, NULL);
			LineTo(hdc, (int)(l + w), (int)(t + h));


			MoveToEx(hdc, (int)(l + w), (int)(t + h), NULL);
			LineTo(hdc, (int)l, (int)(t + h));


			MoveToEx(hdc, (int)l, (int)(t + h), NULL);
			LineTo(hdc, (int)l, (int)t);
		}
		else{
			HBRUSH hBrush, oldBrush;
			hBrush = CreateSolidBrush(color);
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			Rectangle(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h));

			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			DeleteObject(oldBrush);
		}

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}


	void static drawProgrees(HDC hdc, const int& persent, float _l, float _t, float _w, float _h, const COLORREF& color, const COLORREF& pen_color)
	{
		float per = _w * persent * 0.01f;
		if (per > _w)per = _w;
		Draw_2D::drawRect(hdc, _l, _t, _w, _h, WHITE, pen_color, true);
		Draw_2D::drawRect(hdc, _l, _t, per, _h, color, pen_color, true);
	}

	void static drawRectRound(HDC hdc, const float& l, const float& t, const float& w, const float& h, const COLORREF& color, const COLORREF& pen_color, int round){

		HPEN MyPen, OldPen;
		MyPen = CreatePen(PS_SOLID, 1,  pen_color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		RoundRect(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h), round, round);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
	}

	void static drawRectRoundAlpha(HDC hdc, const float& l, const float& t, const float& w, const float& h, const COLORREF& color, const COLORREF& pen_color, int alpha, int round)
	{
	
		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		HPEN MyPen, OldPen;
		HBRUSH hBrush, oldBrush;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha;

		Lay = CreateCompatibleBitmap(hdc, (int)w, (int)h);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		BitBlt(LayDC, 0, 0, (int)w, (int)h, hdc, (int)l, (int)t, SRCCOPY);

		MyPen = CreatePen(PS_SOLID, 1,  pen_color);
		OldPen = (HPEN)SelectObject(LayDC, MyPen);

		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(LayDC, hBrush);

		RoundRect(LayDC, 0, 0, (int)w, (int)h, round, round);
		SelectObject(LayDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(LayDC, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

		AlphaBlend(hdc, (int)l, (int)t, (int)w, (int)h, LayDC, 0, 0, (int)w, (int)h, bf);


		DeleteDC(LayDC);
		DeleteObject(Lay);


		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}


	void static drawCicle(HDC hdc,const int& cx, const int& cy, const int& size, const COLORREF& color, const COLORREF& pen_color, const int& Linesize)
	{
		HBRUSH hBrush, oldBrush;
		HPEN hPen, oldPen;
		
		hPen = CreatePen(PS_DOT, Linesize,  pen_color);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, cx - size / 2, cy - size / 2, cx + size / 2, cy + size / 2);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		DeleteObject(hPen);
		DeleteObject(oldPen);
	}

	void static drawCicle(HDC hdc,const int& start_x, const int& start_y, const int& end_x, const int& end_y, const COLORREF& color)
	{
		HBRUSH hBrush, oldBrush;
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, start_x, start_y, end_x, end_y);
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
	}

	void static drawCicle(HDC hdc, const float& l, const float& t, const float& w, const float& h, const COLORREF& color, const COLORREF& pen_color, int Linesize)
	{
		HBRUSH hBrush, oldBrush;
		HPEN hPen, oldPen;

		hPen = CreatePen(PS_DOT, Linesize,  pen_color);
		oldPen = (HPEN)SelectObject(hdc, hPen);
		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Ellipse(hdc, (int)l, (int)t, (int)(l + w), (int)(t + h));
		SelectObject(hdc, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);
		DeleteObject(hPen);
		DeleteObject(oldPen);
	}

	void static drawCircleAlpha(HDC hdc, const float& l, const float& t, const float& w,const float& h, const COLORREF& color, const COLORREF& pen_color, int alpha)
	{
		HDC LayDC;
		HBITMAP Lay;
		BLENDFUNCTION bf;

		HPEN MyPen, OldPen;
		HBRUSH hBrush, oldBrush;

		bf.BlendOp = AC_SRC_OVER;
		bf.BlendFlags = 0;
		bf.AlphaFormat = 0;
		bf.SourceConstantAlpha = alpha;

		Lay = CreateCompatibleBitmap(hdc, (int)w, (int)h);
		LayDC = CreateCompatibleDC(hdc);
		SelectObject(LayDC, Lay);
		BitBlt(LayDC, 0, 0, (int)w, (int)h, hdc, (int)l, (int)t, SRCCOPY);

		MyPen = CreatePen(PS_SOLID, 1,  pen_color);
		OldPen = (HPEN)SelectObject(LayDC, MyPen);

		hBrush = CreateSolidBrush(color);
		oldBrush = (HBRUSH)SelectObject(LayDC, hBrush);

		Ellipse(LayDC, 0, 0, (int)w, (int)h);
		SelectObject(LayDC, oldBrush);
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		SelectObject(LayDC, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);

		AlphaBlend(hdc, (int)l, (int)t, (int)w, (int)h, LayDC, 0, 0, (int)w, (int)h, bf);


		DeleteDC(LayDC);
		DeleteObject(Lay);


		//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);
	}

	//DrawTrangle

	void static drawPentagon(HDC hdc, const int& cx, const int& cy, const int& w, const int& h, const COLORREF& color){
		HPEN MyPen, OldPen;
		 
		 

		MyPen = CreatePen(PS_SOLID, 3,color);
		OldPen = (HPEN)SelectObject(hdc, MyPen);

		MoveToEx(hdc, cx, cy - h, NULL);
		LineTo(hdc, cx + w, cy);

		MoveToEx(hdc, cx + w, cy, NULL);
		LineTo(hdc, cx + w, cy + h);

		MoveToEx(hdc, cx + w, cy + h, NULL);
		LineTo(hdc, cx - w, cy + h);

		MoveToEx(hdc, cx - w, cy + h, NULL);
		LineTo(hdc, cx - w, cy);

		MoveToEx(hdc, cx - w, cy, NULL);
		LineTo(hdc, cx, cy - h);

		SelectObject(hdc, OldPen);
		DeleteObject(MyPen);
		DeleteObject(OldPen);
	}




	int static random(const int&  start, const int&  end){
		if (end <= start) {
			return (rand() % (start - end) + start);
		}
		return (rand() % (end - start) + start);
	}


	int  static randomDir(const int& start, const int& end)
	{
		int dir;
		if (rand() % 2 == 0)
			dir = 1;
		else dir = -1;

		if (end <= start) {
			return (rand() % (start - end) + start) * dir;
		}
		return (rand() % (end - start) + start) * dir;
	}
	

};