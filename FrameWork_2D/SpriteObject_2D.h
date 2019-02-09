#pragma once

#include "GraphicObject_2D.h"

class CSpriteObject_2D :public CGraphicObject_2D
{
protected:
	//처음
	float						m_frameFPS;

	//처음
	int							m_frameCount;

	//처음
	float						m_frameWidth;

public: 
	//상시
	float						m_frameCountHeight;

protected:
	//상시
	float						m_frameLeft;

	//상시
	float						m_frameTop;

public:

	CSpriteObject_2D();

	CSpriteObject_2D(std::string name);

	CSpriteObject_2D(std::string name, float cx, float cy);

	virtual ~CSpriteObject_2D();

	virtual void Init();

	virtual void Init(std::string name);

	virtual void Init(std::string name,float cx, float cy);

	virtual void OnCreate(std::string name);

	virtual void OnCreate(float cx, float cy, float width, float height);

	virtual void OnCreate(float cx, float cy, float frameFPS, int frameCount, int frameCountHeight);

	virtual void OnCreate(float cx, float cy, float width, float height, float frameFPS, int frameCount, int frameCountHeight);

	virtual void OnDraw(HDC hdc);

	virtual void OnDraw(std::string name, HDC hdc);

	virtual void OnUpdate(float fTimeElapsed = 0.0f);

	virtual void OnDrawAlpha(HDC hdc, int alpha);

	virtual void OnSpriteUpdate();

	virtual void SetSpriteHeight(int n);

	virtual void SetSprite(float frameFPS, int frameCount, int frameCountHeight);

	virtual void SetName(std::string name);


};