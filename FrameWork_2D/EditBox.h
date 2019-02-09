#pragma once

#include "stdafx.h"


class CEditBox : public CSingleTonBase<CEditBox>
{
private:
	struct EditBoxStruct
{
	BoundingBox_2D boundingbox;
	std::wstring	msg = L"";
	int			   color;
	int			  penColor;
	int				alpha = 255;
	int				round = 0;

	
};


private:
	//EditBox 정보
	std::vector<EditBoxStruct>	m_vEditBox;

	//Msg 위치
	int							m_nMsgPivot;

	HWND						m_hWnd;

public:
	CEditBox();
	
	~CEditBox();

	void Load(HWND hwnd);

	void PushEditBoxCenterPosition(int cx, int cy, int width, int backColor = Color_2D::WHITE,int penColor = Color_2D::BLACK, int alpha = 255, int round = 0);

	void PushEditBoxCenteLTRD(int l, int t, int r, int backColor = Color_2D::WHITE, int penColor = Color_2D::BLACK, int alpha = 255, int round = 0);
	
	void OnDraw(HDC hdc);

	void Input(WPARAM wParam);

	std::string GetText(int nReadboxNumber = -1) const
	{ 
		if (nReadboxNumber == -1) nReadboxNumber = m_nMsgPivot;
		std::string str;
		str.assign(m_vEditBox[nReadboxNumber].msg.begin(), m_vEditBox[nReadboxNumber].msg.end());
		return str;
	}



};


