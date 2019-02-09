#include "stdafx.h"
#include "EditBox.h"

CEditBox::CEditBox()
{
	m_vEditBox.clear();
	m_nMsgPivot = 0;
}


CEditBox::~CEditBox()
{
	HideCaret(m_hWnd);
	DestroyCaret();
}

void CEditBox::Load(HWND hwnd)
{
	m_hWnd = hwnd;
	CreateCaret(m_hWnd, NULL, 5, 15);
	ShowCaret(m_hWnd);
}

void CEditBox::PushEditBoxCenterPosition(int cx, int cy, int width, int color, int penColor, int alpha, int round)
{
	EditBoxStruct editbox;

	int height = 20;
	editbox.boundingbox.SetBoxCenter(cx, cy, width, height);
	editbox.color = color;
	editbox.msg = L"";
	editbox.penColor = penColor;
	editbox.alpha = alpha;
	editbox.round = round;

	m_vEditBox.push_back(editbox);
	if (m_vEditBox.size() == 1) SetCaretPos(cx - width, cy - height / 2 + 3);
}

void CEditBox::PushEditBoxCenteLTRD(int l, int t, int r, int color, int penColor, int alpha, int round)
{
	
	EditBoxStruct editbox;

	int b = t + 20;
	editbox.boundingbox.SetBoxLTRD(l ,t, r, b);
	editbox.msg = L"";
	editbox.color = color;
	editbox.penColor = penColor;
	editbox.alpha = alpha;
	editbox.round = round;

	m_vEditBox.push_back(editbox);
	if (m_vEditBox.size() == 1) SetCaretPos(l, t +3);
}

void CEditBox::OnDraw(HDC hdc)
{
	int iCaretPosLeft = 5 + m_vEditBox[m_nMsgPivot].boundingbox.left + 6 * m_vEditBox[m_nMsgPivot].msg.size();
	int iCaretPosY = m_vEditBox[m_nMsgPivot].boundingbox.cy- 8;
	SetCaretPos(iCaretPosLeft, iCaretPosY);

	for (auto &editbox : m_vEditBox)
	{
		Draw_2D::drawRectRoundAlpha(hdc, editbox.boundingbox.left, editbox.boundingbox.top, editbox.boundingbox.w, editbox.boundingbox.h,
										 editbox.color, editbox.penColor, editbox.alpha, editbox.round);
		TextOut(hdc, 3 + editbox.boundingbox.left, editbox.boundingbox.top, editbox.msg.c_str(), editbox.msg.size());
	}
}

void CEditBox::Input(WPARAM wParam)
{
	if (m_vEditBox.size() <= 0)return;


	if (wParam == VK_BACK)
	{
		Loop:
		if(false == m_vEditBox[m_nMsgPivot].msg.empty())
			m_vEditBox[m_nMsgPivot].msg.pop_back();

		else if (m_nMsgPivot-- > 0)
			goto Loop;

		if (m_nMsgPivot < 0) m_nMsgPivot = 0;
	}

	else if (wParam == VK_RETURN)
	{
		m_nMsgPivot++;
		if ((size_t)m_nMsgPivot >= m_vEditBox.size())
			m_nMsgPivot--;
	}

	else
		m_vEditBox[m_nMsgPivot].msg += wParam;

	//if ('a' <= wParam && wParam <= 'z' )
	//	m_vEditBox[m_nMsgPivot].msg += wParam;
	//
	//else if('A'<=wParam && wParam <= 'Z') 
	//	m_vEditBox[m_nMsgPivot].msg += wParam;
	//
	//else if(48 <= wParam && wParam <= 57)
	//	m_vEditBox[m_nMsgPivot].msg += wParam;

	if (6 * m_vEditBox[m_nMsgPivot].msg.size() > m_vEditBox[m_nMsgPivot].boundingbox.w)
		m_vEditBox[m_nMsgPivot].msg.pop_back();


}

