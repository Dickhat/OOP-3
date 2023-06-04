#include "classes 3.h"

//������ ��� ����������� ���� ������� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

static HWND GetConcolWindow()
{
	char str[128];
	// char title[128]="xxxxxxxxxxxxxxxxxx";
	LPWSTR title = (LPWSTR)"xxxxxxxxxxxxxxxxxx";	//����� ������ Windows
	GetConsoleTitle((LPWSTR)str, sizeof((LPWSTR)str)); // �������� ��������� ����
	SetConsoleTitle(title);						// ���������� ����� ��������� ����
	Sleep(100);									// ���� ����� ��������� ���� (100 ��);

	HWND hwnd = FindWindow(NULL, (LPWSTR)title);// ���������� ���������� ����
	SetConsoleTitle((LPWSTR)str);				//���������� ������� ���������

	return hwnd;//������� ���������� ����
}//end GetConcolWindow()

//������� ����� �� ������� ������
static void PressKey(int VkCode)
{
	while (1)
		if (KEY_DOWN(VkCode))
			break;
}

//�������� ������������
static void check(int i, Point*& current, std::vector <ball*>& BALL, Tower* collisions[4][2])
{

	for (int j = 0; j < BALL.size(); ++j)
	{
		//if ��������, ��� ������� �����������
		if (current->get().end_X < BALL[j]->get().start_X
			|| current->get().start_X > BALL[j]->get().end_X
			|| current->get().end_Y > BALL[j]->get().start_Y
			|| current->get().start_Y < BALL[j]->get().end_Y)
		{
			//��� ������������
		}
		else
		{
			//Point temp = collisions[i][j];
			current->set_invisible();					//������ ������ ������

			//if ���� ������ ����������
			if (i == -1)
				break;

			//��������� ����� ������ �� ����� ������
			collisions[i][j]->Move_To(current->Get_X(), current->Get_Y());

			current = collisions[i][j];				//����� ������ �� ������� ��������
			current->set_visible(current->pen_color());	//���������� ����� ������

			BALL[0]->set_visible(BALL[0]->pen_color());	//��������� ��������� ����
			BALL[1]->set_visible(BALL[1]->pen_color());	//��������� ��������� ����
		}
	}

	BALL[0]->set_visible(BALL[0]->pen_color());			//��������� ��������� ����
	BALL[1]->set_visible(BALL[1]->pen_color());			//��������� ��������� ����
};

//���������� ������ current
static void Drag(int i, Point*& current, std::vector <Tower*>& Tow, std::vector <ball*>& BALL, Tower* collisions[4][2])
{
	//while 7 - �����
	while (!KEY_DOWN(55))
	{
		// A - �����
		if (KEY_DOWN(65))
		{
			current->Move_To(current->Get_X() - 20, current->Get_Y());

			//if ��������, ��� ������ �� �������
			if (current == Tow[0] || current == Tow[1] || current == Tow[2] || current == Tow[3])
				check(i, current, BALL, collisions);
			//else if �� ������� ������ ������
			else if (current == collisions[0][1])
				break;
		}
		// W - �����
		else if (KEY_DOWN(87))
		{
			current->Move_To(current->Get_X(), current->Get_Y() - 20);

			//if ��������, ��� ������ �� �������
			if (current == Tow[0] || current == Tow[1] || current == Tow[2] || current == Tow[3])
				check(i, current, BALL, collisions);
			//else if �� ������� ������ ������
			else if (current == collisions[0][1])
				break;
		}
		// D - ������
		else if (KEY_DOWN(68))
		{
			current->Move_To(current->Get_X() + 20, current->Get_Y());

			//if ��������, ��� ������ �� �������
			if (current == Tow[0] || current == Tow[1] || current == Tow[2] || current == Tow[3])
				check(i, current, BALL, collisions);
			//else if �� ������� ������ ������
			else if (current == collisions[0][1])
				break;
		}
		// S - ����
		else if (KEY_DOWN(83))
		{
			current->Move_To(current->Get_X(), current->Get_Y() + 20);

			//if ��������, ��� ������ �� �������
			if (current == Tow[0] || current == Tow[1] || current == Tow[2] || current == Tow[3])
				check(i, current, BALL, collisions);
			//else if �� ������� ������ ������
			else if (current == collisions[0][1])
				break;
		}
		Sleep(1);
	}
}
