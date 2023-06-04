#pragma once
#include "includes.h"

using namespace std;

//Класс местоположение
class Location
{
protected:
	int X;//Координата X
	int Y;//Координата Y

public:
	//Конструктор
	Location(int ind_X, int ind_Y)
	{
		X = ind_X;
		Y = ind_Y;
	}

	//Возвращает X
	int Get_X()
	{
		return X;
	};

	//Возвращает Y
	int Get_Y()
	{
		return Y;
	}

	//Устанавливает X
	void Set_X(int ind_X)
	{
		X = ind_X;
	};

	//Устанавливает Y
	void Set_Y(int ind_Y)
	{
		Y = ind_Y;
	};
};

//Класс точка
class Point :public Location
{
protected:
	bool Visible;//Видимость точки
	HPEN pen;
	struct heat_box
	{
		int start_X, end_X, start_Y, end_Y;	//Координаты фигуры(В форме квадрата)
	} boxheat;

public:
	//КОНСТРУКТОР
	Point(int X, int Y, HPEN& color) :Location(X, Y)
	{
		Visible = false;
		pen = color;
		boxheat.start_X = X;
		boxheat.end_X = X + 1;
		boxheat.start_Y = Y;
		boxheat.end_Y = Y + 1;
	};

	//Возвращает хитбоксы
	const heat_box& get()
	{
		return boxheat;
	}

	HPEN& pen_color() 
	{ 
		return pen;
	}

	//Делает видимой точку
	virtual void set_visible(HPEN color);

	//Делает невидимой точку
	virtual void set_invisible();

	//Текущая область фигуры
	virtual void current_region(int X, int Y);

	//Перемещает точку
	void Move_To(int X, int Y);
};

//Класс ядро
class ball :public Point
{
protected:
	int radius;
public:
	//Конструктор
	ball(int X, int Y, HPEN color, int Rad) :Point(X, Y, color) { radius = Rad; };

	void Paint_ball();

	void set_rad(int Rad) { radius = Rad; };
	int get_rad() { return radius; };

	//Запоминает местоположение фигуры
	void current_region(int X, int Y);

	void set_visible(HPEN color);

	void set_invisible();
};

//Класс фигура (Башня)
class Tower :public Point
{
public:
	Tower(int X, int Y, HPEN& color) :Point(X, Y, color) {

	};
	void virtual Paint();

	void current_region(int X, int Y);

	//Делает видимой точку
	void set_visible(HPEN color);

	//Делает невидимой точку
	void set_invisible();
};

//Вертикальная иерархия 1
class vertical_Tower_1 :public Tower
{
public:
	//Конструктор
	vertical_Tower_1(int X, int Y, HPEN& color) :Tower(X, Y, color) {};

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Вертикальная иерархия 2
class vertical_Tower_2 :public vertical_Tower_1
{
public:
	//Конструктор
	vertical_Tower_2(int X, int Y, HPEN& color) :vertical_Tower_1(X, Y, color) {};

	void print_construction();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 1
class left_construction_Tower : public Tower
{
public:
	//Конструктор
	left_construction_Tower(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	//Левая конструкция
	void left_print();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};

//Веерная иерархия 2
class right_construction_Tower : public Tower
{
public:
	//Конструктор
	right_construction_Tower(int X, int Y, HPEN color) :Tower(X, Y, color) {};

	//Правая конструкция
	void right_print();

	void current_region(int X, int Y);

	//Делает видимой башню
	void set_visible(HPEN color);

	//Делает невидимой башню
	void set_invisible();
};