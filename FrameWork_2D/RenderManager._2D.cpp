
#include "stdafx.h"
#include "RenderManager_2D.h"

Image::Image()
{

}

Image::Image(TCHAR* filePath)
{
	this->LoadCImage(filePath);
}

Image::~Image()
{
	//delete m_image;
}


void Image::Init(TCHAR* filePath)
{
	this->LoadCImage(filePath);
}

void Image::LoadCImage(TCHAR* filePath)
{
	m_image = new CImage();
	HRESULT result = m_image->Load(filePath);
	if (result == S_OK)
	{
		m_Width = m_image->GetWidth();
		m_Height = m_image->GetHeight();
	}
	else
	{
		MessageBox(NULL, filePath, L"경로가 잘못되었습니다.", NULL);
		//GlobalVar::GetInstance()->ErrorMessage(filePath, "경로가 잘못되었습니다");
	}
}

CRenderManager_2D::CRenderManager_2D()
{

}

CRenderManager_2D::~CRenderManager_2D()
{
	this->Release();
}

void CRenderManager_2D::AddImage(TCHAR* filePath, std::string name)
 {
	auto pFindImg = this->InsertFindImage(name);

	if (pFindImg != NULL)return;

	else
	{
		std::vector<Image> vecImage;
		Image img;
		img.LoadCImage(filePath);
		vecImage.push_back(img);
		m_ImageMap.insert(std::make_pair(name, vecImage));

	}

}

std::vector<Image>* CRenderManager_2D::FindImage(std::string name)
{
	std::map<std::string, std::vector<Image>>::iterator iter = m_ImageMap.find(name);

	if (iter == m_ImageMap.end())
		return FindImage("default");
	else
		return &iter->second;
}

std::vector<Image>* CRenderManager_2D::InsertFindImage(std::string name)
{
	std::map<std::string, std::vector<Image>>::iterator iter = m_ImageMap.find(name);

	if (iter == m_ImageMap.end())
		return nullptr;
	else
		return &iter->second; 
}

void CRenderManager_2D::LoadCImage()
{
	AddImage(L"../Resource/default.png", "Default");


	AddImage(L"../Resource/WarpLogo.png", "로고");
	AddImage(L"../Resource/BtnSave.png",  "Start");
	AddImage(L"../Resource/BtnPlay.png",  "Load");
	AddImage(L"../Resource/BtnHelp.png",  "Help");
	AddImage(L"../Resource/BtnExit.png", "Exit");
	AddImage(L"../Resource/help.png",    "HelpImg");
	AddImage(L"../Resource/waterfall.png","폭포");
}


void CRenderManager_2D::DrawImageSpriteAlphaBackground(HDC hdc, std::string name, float left, float top, float width, float height, float s_left, float s_top, float s_width, float s_height, COLORREF removeColor, int alpha)
{
	HDC LayDC;
	HBITMAP Lay;
	BLENDFUNCTION bf;

	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = alpha;

	Lay = CreateCompatibleBitmap(hdc, (int)width, (int)height);
	LayDC = CreateCompatibleDC(hdc);
	SelectObject(LayDC, Lay);
	TransparentBlt(LayDC, 0, 0, (int)width, (int)height, hdc, s_left, s_top, s_width, s_left, removeColor);

	std::vector<Image>* image = FindImage(name);

	if (image)
		image->begin()->GetCimage()->TransparentBlt(hdc, left, top, width, height,
		s_left, s_top, s_width, s_height, removeColor);

	AlphaBlend(hdc, (int)left, (int)top, (int)width, (int)height, LayDC, 0, 0, (int)width, (int)height, bf);

	//Rectangle(hdc, (int)rect.left, (int)rect.top, (int)rect.left + (int)rect.width, (int)rect.top + (int)rect.height);

	DeleteDC(LayDC);
	DeleteObject(Lay);
}

void CRenderManager_2D::Render(HDC hdc, std::string name, float left, float top, float width, float height, float s_left, float s_top, float s_width, float s_height, COLORREF removeColor)
{
	std::vector<Image>* image = FindImage(name);

	if (image)
		image->begin()->GetCimage()->TransparentBlt(hdc, (int)left, (int)top, (int)width, (int)height, (int)s_left, (int)s_top, (int)s_width, (int)s_height, removeColor);	
}

Image* CRenderManager_2D::GetImage(std::string name)
{
	return FindImage(name)->begin()->GetImage();
}

void CRenderManager_2D::Release()
{
	m_ImageMap.clear();
}


