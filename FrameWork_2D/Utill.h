#pragma once

#include "stdafx.h"

#include <windows.h>
#include <math.h>

class Vector2
{

public:
	float x;
	float y;

	Vector2()
	{
		x = 0;
		y = 0;
	}

	~Vector2()
	{

	}

	Vector2(float x, float y)
	{
		Vector2::x = x;
		Vector2::y = y;
	}

	void set(float x, float y)
	{
		Vector2::x = x;
		Vector2::y = y;
	}

	Vector2 operator+(Vector2 A)
	{
		Vector2 tmp;
		tmp.x = x + A.x;
		tmp.y = y + A.y;
		return tmp;
	}

	Vector2 operator-(Vector2 A)
	{
		Vector2 tmp;
		tmp.x = x - A.x;
		tmp.y = y - A.y;
		return tmp;
	}

	Vector2 operator*(Vector2 A)
	{
		Vector2 tmp;
		tmp.x = x * A.x;
		tmp.y = y * A.y;
		return tmp;
	}

	Vector2 operator*(int a)
	{
		Vector2 tmp;
		tmp.x = x * a;
		tmp.y = y * a;
		return tmp;
	}

	Vector2 operator*(float a)
	{
		Vector2 tmp;
		tmp.x = x * a;
		tmp.y = y * a;
		return tmp;
	}

	Vector2 operator/(int a)
	{
		Vector2 tmp;
		tmp.x = x / a;
		tmp.y = y / a;
		return tmp;
	}

};

class BoundingBox_2D
{

public:
	float			left;
	float			right;
	float			top;
	float			bot;

	float			cx;
	float			cy;
	float			w;
	float			h;

public:

	void SetBoxLTRD(float _left, float _top, float _right, float _bot)
	{
		left = _left;
		right = _right;
		top = _top;
		bot = _bot;

		w = right - left;
		h = bot - top;
		cx = left + w / 2;
		cy = top + h / 2;

	}
	void SetBoxCenter(float cx, float cy, float _w, float _h)
	{
		w = _w;
		h = _h;
		BoundingBox_2D::cx = cx;
		BoundingBox_2D::cy = cy;
		left = cx - w / 2;
		right = cx + w / 2;
		top = cy - h / 2;
		bot = cy + h / 2;
	}

	bool Collision(BoundingBox_2D col)
	{
		if (left > col.right)return false;
		if (right < col.left)return false;
		if (top > col.bot)return false;
		if (bot < col.top)return false;
		return true;
	}

	bool Contains(float x, float y)
	{
		return left < right && top < bot
			&& x >= left && x < right && y >= top && y < bot;
	}


	WindowsFrameCollision WidownsBoxCollision(int WidndowsWidth, int WindowsHeight)
	{
		if (left < 0.0f || right > WidndowsWidth)
			return COLLISION_X;
		if (top < 0.0f || bot > WindowsHeight)
			return COLLISION_Y;

		return COLLISION_NON;
	}

	void Update(float cx, float cy)
	{
		left = cx - w / 2;
		right = cx + w / 2;
		top = cy - h / 2;
		bot = cy + h / 2;
		BoundingBox_2D::cx = cx;
		BoundingBox_2D::cy = cy;
	}

};

class MathCalu
{

public:
	MathCalu() {};
	~MathCalu() {};

	static float Scale(Vector2 A) {
		return sqrt((A.x * A.x) + (A.y * A.y));
	}

	static float Length(Vector2 A, Vector2 B)
	{
		return sqrt(pow(A.x - B.x, 2) + pow(A.y - B.y, 2));
	}

	static Vector2 Normalize(Vector2 A)
	{
		Vector2 tmp;
		tmp.x = A.x / Scale(A);
		tmp.y = A.y / Scale(A);
		return tmp;
	}

	static float InnerProduct(float x, float y, float x2, float y2)
	{
		return (x * x2) + (y * y2);
	}

	static float VectorScale(float x, float y, float x2, float y2)
	{
		return sqrt(pow(x, 2.0f) + pow(y, 2.0f)) + sqrt(pow(x2, 2.0f) + pow(y2, 2.0f));
	}

	static float getACOS(float x, float y, float x2, float y2)
	{
		float dot = InnerProduct(x, y, x2, y2);
		float length = VectorScale(x, y, x2, y2);
		float radian = acos(dot / length);
		float degree = radian * 180.0f / (float)PI;
		return degree;
	}

	static float getCos(float x, float y, float x2, float y2)
	{
		float a, b;
		a = -y;
		b = x;
		float tmp_dot = InnerProduct(a, b, x2, y2);
		float tmp_length = VectorScale(a, b, x2, y2);
		float tmp_radian = acos(tmp_dot / tmp_length);
		float tmp_degree = tmp_radian * 180.0f / (float)PI;

		if (tmp_degree < 90)
			return getACOS(x, y, x2, y2);
		else
			return 360.0f - getACOS(x, y, x2, y2);

	}

	static float InnerProduct(Vector2 A, Vector2 B)
	{
		return (A.x * B.x) + (A.y * B.y);
	}

	static float VectorScale(Vector2 A, Vector2 B)
	{
		return sqrt(pow(A.x, 2.0f) + pow(A.y, 2.0f)) + sqrt(pow(B.x, 2.0f) + pow(B.y, 2.0f));
	}

	static float getACOS(Vector2 A, Vector2 B)
	{
		float dot = InnerProduct(A.x, A.y, B.x, B.y);
		float length = VectorScale(A.x, A.y, B.x, B.y);
		float radian = acos(dot / length);
		float degree = radian * 180.0f / (float)PI;
		return degree;
	}

	static float getCos(Vector2 A, Vector2 B)
	{
		float a, b;
		a = -A.y;
		b = B.x;
		float tmp_dot = InnerProduct(a, b, B.x, B.y);
		float tmp_length = VectorScale(a, b, B.x, B.y);
		float tmp_radian = acos(tmp_dot / tmp_length);
		float tmp_degree = tmp_radian * 180.0f / (float)PI;

		if (tmp_degree < 90)
			return getACOS(A.x, A.y, B.x, B.y);
		else
			return 360.0f - getACOS(A.x, A.y, B.x, B.y);

	}
};