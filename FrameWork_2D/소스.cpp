#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MaxStage 10 //�������� ���ϱ� 

HINSTANCE g_hlnstl;
LPCTSTR lpszClass = "�������� ���� ����";

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM IParam);

int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hlnstl = hlnstance;

	//������ Ŭ���� ����ü �� ����
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hlnstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//������ Ŭ���� ���
	RegisterClassEx(&WndClass);

	//������ ����
	hWnd = CreateWindow(lpszClass, "�������� �������� ", WS_OVERLAPPEDWINDOW, 0, 0, 1020, 640, NULL, (HMENU)NULL, hlnstance, NULL);

	//������ ���
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//�̺�Ʈ ���� ó��
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
//��
int Damage = 1;
struct Place
{


	void init(float G, float S, int hp);

	int left;
	int top;
	int right;               //����:40  ��:100
	int bottom;
	int Hp;
	void move();
	BOOL colision();
};


void Place::init(float G, float S, int hp)               //G ȭ���� ���� S����
{
	top = S;
	bottom = S + 40;
	left = G;
	right = G + 100;
	Hp = hp;
}
BOOL Place::colision()
{
	return 1;
}
void Place::move()
{
	top += 40;
	bottom += 40;
}
//�� ����
struct Item1
{

	void init(float G, float S);
	float left;
	float top;
	float right;               //��    ������:15
	float bottom;
	float x;    //�߽� ��ǥ x
	float y;    //�߽� ��ǥ y
	void move();
};


void Item1::move()
{
	bottom += 40;
	top += 40;
	y += 40;
}
void Item1::init(float G, float S)
{
	left = G + 35;
	right = G + 65;
	top = S + 5;
	bottom = S + 35;
	x = left + 15;
	y = top + 15;
}
//�����ٲ�
struct Item2
{

	void move();

	void init(float G, float S);
	float left;
	float top;
	float right;               //���̴�.    ������:15
	float bottom;
	float x;    //�߽� ��ǥ x
	float y;    //�߽� ��ǥ y
};


void Item2::move()
{
	bottom += 40;
	top += 40;
	y += 40;
}
void Item2::init(float G, float S)
{
	left = G + 35;
	right = G + 65;
	top = S + 5;
	bottom = S + 35;
	x = left + 15;
	y = top + 15;
}
//���������� ����
struct Item3
{

	void init(float G, float S);
	float left;
	float top;
	float right;               //��    ������:15
	float bottom;
	float x;    //�߽� ��ǥ x
	float y;    //�߽� ��ǥ y
	void move();
};


void Item3::move()
{
	bottom += 40;
	top += 40;
	y += 40;
}
void Item3::init(float G, float S)
{
	left = G + 35;
	right = G + 65;
	top = S + 5;
	bottom = S + 35;
	x = left + 15;
	y = top + 15;
}
//��
struct MyBall
{

	void move(float X, float Y);
	float left;
	float top;
	float right;               //���̴�.    ������:15
	float bottom;
	float x;    //�߽� ��ǥ x
	float y;    //�߽� ��ǥ y
	int ATK;   //������
	int ch;     //���� ���� ��Ҵ� �� üũ
	int direct;    //�� ������ ���� 1:���� 2:���ϴ�,3:�»��,4:���ϴ�
	void init();// ó������ �� �ʱ�ȭ
	void init1(float nLeft, float nTop, float nRight, float nBottom);//�� �� ���� �� �ʱ�ȭ

};
void MyBall::init()
{
	left = 400;
	top = 572;
	right = 430;
	bottom = 602;
	x = left + 15;
	y = top + 15;
	ATK = Damage;
	direct = 1;
	ch = 0;
}
void MyBall::init1(float nLeft, float nTop, float nRight, float nBottom)
{
	left = nLeft;
	top = 572;
	right = nRight;
	bottom = 602;
	x = left + 15;
	y = top + 15;
	ATK = Damage;
	direct = 1;
	ch = 0;
}

void MyBall::move(float X, float Y)
{
	left += X;
	top += Y;
	right += X;
	bottom += Y;
	x = left + 15;
	y = top + 15;
}
//���� �� �浹

BOOL IsPointInCircle(float cx, float cy, float cr, float px, float py)
{
	//x��ȭ��
	float deltaX = cx - px;
	//y��ȭ��
	float deltaY = cy - py;
	//���� �߽ɰ� ������ �Ÿ�
	float length = sqrt(deltaX*deltaX + deltaY*deltaY);
	//���� �߽ɺ��� ������ �Ÿ��� ���� ���������� ũ�ٸ� �浹����
	if (length > cr)
		return FALSE;
	return TRUE;
}

//�簢�� �浹
int Collision_R_C(float cx, float cy, float cr, const Place* lprect)
{
	int nCenterX = static_cast<int>(cx);
	int nCenterY = static_cast<int>(cy);
	int nRadius = static_cast<int>(cr);

	if ((lprect->left < nCenterX&&nCenterX <= lprect->right) || (lprect->top <= nCenterY&&nCenterY <= lprect->bottom))
	{

		RECT rcEx = {
			lprect->left - nRadius,      //left
			lprect->top - nRadius,       //top
			lprect->right + nRadius,     //right
			lprect->bottom + nRadius     //bottom
		};
		//�簢�� �ȿ� ���� �߽��� ����ִ��� Ȯ��
		if ((rcEx.left < nCenterX&&nCenterX < rcEx.right) && (rcEx.top < nCenterY&&nCenterY < rcEx.bottom))
		{
			return 1;
		}
	}
	else
	{
		//������ ������
		if (IsPointInCircle(cx, cy, cr, (float)lprect->left, (float)lprect->top))return 2;
		//���ʾƷ� ������
		if (IsPointInCircle(cx, cy, cr, (float)lprect->left, (float)lprect->bottom))return 3;
		//������ ������
		if (IsPointInCircle(cx, cy, cr, (float)lprect->right, (float)lprect->top)) return 4;
		//�����Ʒ� ������
		if (IsPointInCircle(cx, cy, cr, (float)lprect->right, (float)lprect->bottom))return 5;
	}
	return 0;
}

//������
BOOL Collisin_C_C(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
	float deltaX = c1x - c2x;
	float deltaY = c1y - c2y;


	float length = sqrt(deltaX = deltaX*deltaX + deltaY*deltaY);

	if (length > (c1r + c2r))
		return FALSE;
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int i, j, k, n;
	static Place block[MaxStage][10];   //��
	static Item1 Item1[MaxStage][10];   //������
	static Item2 Item2[MaxStage][10];   //������ȯ
	static Item3 Item3[MaxStage][10];//��������������
	static int P_Check[MaxStage][10];  //0:�� 1:������1  2:������2  3:������3 ������:����
	static RECT winSize;  //������
	static int Garo = 1, Sero = -1;   //���� ������ ������ ����
	static int nStage = 1;  //��������
	static int score = 0;  //����
	static MyBall Ball[MaxStage * 10]; //��
	static int maxB = 1;  //��� ���� ��� �ð� ���� ���� ������ ���� ��� ��
	static int Ball_start = 1;//����� ������
	static int Ball_end = 1;// ����� �������ٵ� ������
	static int nlast = 0; //����ġ
	static int stack = 0; //��ó����°�
	char str[50];  //�ؽ�Ʈ
	static float resultX; //����  x
	static float resultY; //����  y
	static double radian; //���� ��


	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;
	HBRUSH Old;
	RECT r;
	static BOOL flag = FALSE; //���콺 Ŭ�� ����
	static BOOL EndFlag = FALSE;//���� �� ��ư �÷���
	static int nBlock = 0;
	static float x, y; //���콺Ʈ ������ ��ġ



	srand((int)time(NULL));
	// �޽��� ó���ϱ�
	switch (uMsg) {
	case WM_TIMER:

		switch (wParam)
		{
		case 1:

			for (n = 0; n < maxB; n++)
			{
				if (Ball[n].ch == 1)
				{
					if (Ball[n].direct == 1)
					{
						Garo = 1;
						Sero = -1;
					}
					else if (Ball[n].direct == 2)
					{
						Garo = 1;
						Sero = 1;
					}
					else if (Ball[n].direct == 3)
					{
						Garo = -1;
						Sero = -1;
					}
					else if (Ball[n].direct == 4)
					{
						Garo = -1;
						Sero = 1;
					}

					Ball[n].move(15 * Garo*cos(radian), 15 * Sero*sin(radian));   //�� �̵�

					for (i = 0; i < nStage; i++)
					{
						for (j = 0; j < 10; j++)            //�浹
						{
							if (P_Check[i][j] == 0)
							{
								if (Collision_R_C(Ball[n].x, Ball[n].y, 15, &block[i][j]) == 1)
								{
									if (Ball[n].x < block[i][j].left)
									{
										if (Ball[n].direct == 1)
											Ball[n].direct = 3;
										else if (Ball[n].direct == 2)
											Ball[n].direct = 4;
									}
									else if (Ball[n].x>block[i][j].right)
									{
										if (Ball[n].direct == 4)
											Ball[n].direct = 2;
										else if (Ball[n].direct == 3)
											Ball[n].direct = 1;
									}
									else if (Ball[n].y < block[i][j].top)
									{
										if (Ball[n].direct == 2)
											Ball[n].direct = 1;
										else if (Ball[n].direct == 4)
											Ball[n].direct = 3;
									}
									else if (Ball[n].y > block[i][j].bottom)
									{
										if (Ball[n].direct == 1)
											Ball[n].direct = 2;
										else if (Ball[n].direct == 3)
											Ball[n].direct = 4;
									}
									block[i][j].Hp -= Ball[n].ATK;
									if (block[i][j].Hp <= 0)
									{
										P_Check[i][j] = 4;
										score++;
										nBlock--;
									}
								}
								else if (Collision_R_C(Ball[n].x, Ball[n].y, 15, &block[i][j]) == 2)
								{
									Ball[n].direct = 3;
									block[i][j].Hp -= Ball[n].ATK;
									if (block[i][j].Hp <= 0)
									{
										P_Check[i][j] = 4;
										score++;
										nBlock--;
									}

								}
								else if (Collision_R_C(Ball[n].x, Ball[n].y, 15, &block[i][j]) == 3)
								{
									Ball[n].direct = 4;
									block[i][j].Hp -= Ball[n].ATK;
									if (block[i][j].Hp <= 0)
									{
										P_Check[i][j] = 4;
										score++;
										nBlock--;
									}
								}
								else if (Collision_R_C(Ball[n].x, Ball[n].y, 15, &block[i][j]) == 4)
								{
									Ball[n].direct = 1;
									block[i][j].Hp -= Ball[n].ATK;
									if (block[i][j].Hp <= 0)
									{
										score++;
										P_Check[i][j] = 4;
										nBlock--;
									}
								}
								else if (Collision_R_C(Ball[n].x, Ball[n].y, 15, &block[i][j]) == 5)
								{
									Ball[n].direct = 2;
									block[i][j].Hp -= Ball[n].ATK;
									if (block[i][j].Hp <= 0)
									{
										score++;
										P_Check[i][j] = 4;
										nBlock--;
									}
								}

							}
							else if (P_Check[i][j] == 1)//����
							{
								if (Collisin_C_C(Ball[n].x, Ball[n].y, 15, Item1[i][j].x, Item1[i][j].y, 15))
								{
									P_Check[i][j] = 4;
									Ball_end++;
									Ball[Ball_end - 1].left = Item1[i][j].left;
									Ball[Ball_end - 1].right = Item1[i][j].right;
									Ball[Ball_end - 1].x = Item1[i][j].x;
									Ball[Ball_end - 1].y = Ball[Ball_end].bottom - 15;


								}
							}
							else if (P_Check[i][j] == 2)    //����
							{
								if (Collisin_C_C(Ball[n].x, Ball[n].y, 15, Item2[i][j].x, Item2[i][j].y, 15))
								{
									P_Check[i][j] = 4;
									k = rand() % 4;
									if (k == 0)
										Ball[n].direct = 1;
									else if (k == 1)
										Ball[n].direct = 2;
									else if (k == 2)
										Ball[n].direct = 3;
									else
										Ball[n].direct = 4;

								}
							}
							else if (P_Check[i][j] == 3)//����������
							{
								if (Collisin_C_C(Ball[n].x, Ball[n].y, 15, Item3[i][j].x, Item3[i][j].y, 15))
								{
									P_Check[i][j] = 4;
									Damage = 2;


								}
							}

						}
					}
					//�ʵ� �浹 �� ����ٲ�

					if (Ball[n].right >= winSize.right)
					{
						if (Ball[n].direct == 1)
							Ball[n].direct = 3;
						else if (Ball[n].direct == 2)
							Ball[n].direct = 4;
					}
					else if (Ball[n].left <= winSize.left)
					{
						if (Ball[n].direct == 3)
							Ball[n].direct = 1;
						else if (Ball[n].direct == 4)
							Ball[n].direct = 2;
					}
					else if (Ball[n].top <= winSize.top)
					{
						if (Ball[n].direct == 1)
							Ball[n].direct = 2;
						else if (Ball[n].direct == 3)
							Ball[n].direct = 4;
					}
					else if (Ball[n].bottom >= winSize.bottom)
					{
						Ball[n].ch = 0;
						if (stack == 0)
							nlast = n;
						stack++;


					}
				}
			}
			for (i = 0; i < Ball_start; i++)
			{
				if (Ball[i].ch != 0)
				{
					break;
				}
				if (i == Ball_start - 1)
				{
					for (j = 0; j < Ball_start; j++)
						Ball[j].init1(Ball[nlast].left, Ball[nlast].top, Ball[nlast].right, Ball[nlast].bottom);  //ó����������ġ��
					for (n = 0; n < nStage; n++)
					{
						for (k = 0; k < 10; k++)
						{
							if (P_Check[n][k] == 0)
								block[n][k].move();
							else if (P_Check[n][k] == 1)
								Item1[n][k].move();
							else if (P_Check[n][k] == 2)
								Item2[n][k].move();
							else if (P_Check[n][k] == 3)
								Item3[n][k].move();
						}
					}
					if (nStage != MaxStage)
						nStage++;
					flag = FALSE;
					KillTimer(hWnd, 1);
				}
			}
			//------------------------------------------------------------
			break;
		}
		if (maxB < Ball_start)
		{
			maxB++;
		}
		Ball_start = Ball_end;


		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (EndFlag)
		{
			if (wParam == 'Y' || wParam == 'y')
			{
				Ball_start = 1;
				Ball_end = 1;
				stack = 0;
				Damage = 1;
				maxB = 1;
				nStage = 1;
				nBlock = 0;
				score = 0;
				for (i = 0; i < 100; i++)
				{
					Ball[i].init();
				}
				for (i = 0; i < MaxStage; i++)
				{

					for (j = 0; j < 10; j++)
					{
						P_Check[i][j] = rand() % 5;

						if (P_Check[i][j] == 1)
							Item1[i][j].init(100 * j, 0);
						else if (P_Check[i][j] == 2)
						{

							Item2[i][j].init(100 * j, 0);



						}
						else if (P_Check[i][j] == 0)
						{
							nBlock++;
							block[i][j].init(100 * j, 0, i + 1);
						}
						else if (P_Check[i][j] == 3)
						{

							Item3[i][j].init(100 * j, 0);



						}
					}
				}
				EndFlag = FALSE;
				flag = FALSE;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else if (wParam == 'N' || wParam == 'n')
				PostQuitMessage(0);
		}
		break;

	case WM_CREATE:
		for (i = 0; i < MaxStage * 10; i++)
		{
			Ball[i].init();
		}
		for (i = 0; i < MaxStage; i++)
		{

			for (j = 0; j < 10; j++)
			{
				P_Check[i][j] = rand() % 5;

				if (P_Check[i][j] == 1)
					Item1[i][j].init(100 * j, 0);
				else if (P_Check[i][j] == 2)
				{

					Item2[i][j].init(100 * j, 0);


				}
				else if (P_Check[i][j] == 0)
				{
					block[i][j].init(100 * j, 0, i + 1);
					nBlock++;
				}
				else if (P_Check[i][j] == 3)
				{

					Item3[i][j].init(100 * j, 0);


				}
			}
		}
		GetClientRect(hWnd, &winSize);

		break;
	case WM_LBUTTONDOWN:
		if (flag == FALSE)
		{
			stack = 0;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			resultX = x - Ball[0].x;
			resultY = Ball[0].y - y;
			if (resultX < 0)
				resultX *= -1;
			if (resultY < 0)
				resultY *= -1;

			radian = atan(resultY / resultX);
			maxB = 1;

			for (i = 0; i < Ball_start; i++)
			{
				Ball[i].ch = 1;
				if (Ball[0].x>x)
					Ball[i].direct = 3;
				else
					Ball[i].direct = 1;
			}
			if (sin(15 * 3.14 / 180) <= sin(radian))   //���� 15�� �̻�
			{
				flag = TRUE;
				SetTimer(hWnd, 1, 20, NULL);
			}
			Damage = 1;

		}
		break;
	case WM_PAINT:
		hdc = (HDC)BeginPaint(hWnd, &ps);
		hBrush = CreateSolidBrush(RGB(244, 164, 96));
		Old = (HBRUSH)SelectObject(hdc, hBrush);
		for (i = 0; i < nStage; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (P_Check[i][j] == 0)
				{
					Rectangle(hdc, block[i][j].left, block[i][j].top, block[i][j].right, block[i][j].bottom);
					wsprintf(str, "%d", block[i][j].Hp);
					TextOut(hdc, block[i][j].left + 45, block[i][j].top + 10, str, strlen(str));
				}
			}
		}
		SelectObject(hdc, Old);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(124, 252, 0));
		Old = (HBRUSH)SelectObject(hdc, hBrush);
		for (i = 0; i < nStage; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (P_Check[i][j] == 1)
				{
					Ellipse(hdc, Item1[i][j].left, Item1[i][j].top, Item1[i][j].right, Item1[i][j].bottom);
				}
			}
		}
		SelectObject(hdc, Old);
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(188, 145, 143));
		Old = (HBRUSH)SelectObject(hdc, hBrush);
		for (i = 0; i < nStage; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (P_Check[i][j] == 2)
				{
					Ellipse(hdc, Item2[i][j].left, Item2[i][j].top, Item2[i][j].right, Item2[i][j].bottom);
				}
			}
		}
		SelectObject(hdc, Old);
		DeleteObject(hBrush);

		hBrush = CreateSolidBrush(RGB(255, 105, 65));
		Old = (HBRUSH)SelectObject(hdc, hBrush);

		for (i = 0; i < nStage; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (P_Check[i][j] == 3)
				{
					Ellipse(hdc, Item3[i][j].left, Item3[i][j].top, Item3[i][j].right, Item3[i][j].bottom);
				}
			}
		}
		SelectObject(hdc, Old);
		DeleteObject(hBrush);
		if (Damage == 1)
		{
			hBrush = CreateSolidBrush(RGB(65, 105, 255));
			Old = (HBRUSH)SelectObject(hdc, hBrush);
		}
		else if (Damage == 2)
		{
			hBrush = CreateSolidBrush(RGB(255, 105, 65));
			Old = (HBRUSH)SelectObject(hdc, hBrush);
		}
		for (i = 0; i < Ball_start; i++)
		{
			Ellipse(hdc, Ball[i].left, Ball[i].top, Ball[i].right, Ball[i].bottom);
		}

		SelectObject(hdc, Old);
		DeleteObject(hBrush);
		wsprintf(str, "���� ��������:%d", nStage);//��������,����,��
		TextOut(hdc, 0, 280, str, strlen(str));
		wsprintf(str, "���� ������ ���� ��:%d", score);
		TextOut(hdc, 0, 300, str, strlen(str));
		wsprintf(str, "�������ִ� ���� ����:%d", Ball_start);
		TextOut(hdc, 0, 320, str, strlen(str));
		for (i = 0; i < nStage; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (P_Check[i][j] == 0)
				{
					if ((block[i][j].bottom>winSize.bottom)) //�й�
					{
						KillTimer(hWnd, 1);
						wsprintf(str, "  �й�");
						TextOut(hdc, 400, 250, str, strlen(str));
						wsprintf(str, "���� �� ��:%d", score);
						TextOut(hdc, 400, 300, str, strlen(str));
						wsprintf(str, "�ٽý��� �ϰڽ��ϱ�? Y/N");
						TextOut(hdc, 400, 350, str, strlen(str));
						EndFlag = TRUE;

					}
				}
			}
		}
		if (nBlock == 0)   //�¸�
		{
			KillTimer(hWnd, 1);
			wsprintf(str, "   �¸�");
			TextOut(hdc, 400, 250, str, strlen(str));
			wsprintf(str, "���� �� ��:%d", score);
			TextOut(hdc, 400, 300, str, strlen(str));
			wsprintf(str, "�ٽý��� �ϰڽ��ϱ�? Y/N");
			TextOut(hdc, 400, 350, str, strlen(str));
			EndFlag = TRUE;
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}