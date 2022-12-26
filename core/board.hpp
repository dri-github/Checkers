#ifndef BOARD_HPP
#define BOARD_HPP

#include <math.h>

//
// Шашка - хранит в себе координаты, сторону за которую играет и является ли она королевой или нет
//
struct Checker
{
	enum Side
	{
		White = 0,
		Black = 1
	};
	enum Status
	{
		Base = 0,
		Queen = 1
	};

	Checker(Side side = Side::White) : x(0), y(0), side(side), status(Status::Base) {}

	int x;			//<-- Координата по x
	int y;			//<-- Координата по y
	Side side;		//<-- Сторона за которую играет шашка (белые или черные)
	Status status;	//<-- Статус (королева или нет)
};

//
// Доска - хранит в себе размер, количество шашек и сами шашки
//
struct Board
{
public:
	Board(int width, int height) : width(width), height(height), checkers(new Checker* [width * height]), count(0) {}
	~Board()
	{
		delete[] checkers;
	}
	
	//Добавить шашку на доску, добавление шашки на занятую координату вернёт false
	bool addChecker(int x, int y, Checker::Side side)
	{
		if (getCheckerByPosition(x, y) != NULL)
			return false;

		Checker* checker = new Checker();
		checker->x = x;
		checker->y = y;
		checker->side = side;
		checker->status = Checker::Status::Base;

		if (count < 0)
			return false;

		checkers[count] = checker;
		count++;

		return true;
	}
	//Удалить шашку с доски, удаление несуществующей шашки вернёт false
	bool deleteChecker(int x, int y)
	{
		for (int i = 0; i < count; i++)
		{
			Checker* checker = checkers[i];
			if (checker->x == x && checker->y == y)
			{
				count--;
				for (int j = i; j < count; j++)
					*(checkers + j) = *(checkers + j + 1);
				return true;
			}
		}

		return false;
	}
	//Перемещает шашку, перемещение несуществующей шашки или действие нерушающее правилам шашек вернёт false
	bool moveChecker(int start_x, int start_y, int end_x, int end_y)
	{
		Checker* checker = getCheckerByPosition(start_x, start_y);
		if (checker == nullptr)
			return false;
		if (getCheckerByPosition(end_x, end_y) != nullptr ||
			end_x < 0 || end_x > width - 1 || end_y < 0 || end_y > height - 1 || start_x == end_x || start_y == end_y ||
			checker->status == Checker::Base && (abs(start_x - end_x) > 1 || abs(start_y - end_y) > 1) || (start_x == end_x && start_y == end_y) ||
			abs(end_x - start_x) != abs(end_y - start_y))
			return false;

		if (checker->status == Checker::Base)
		{
			bool isOne = false;
			for (int i = 0; i < abs(end_x - start_x); i++)
			{
				Checker* check_checker = getCheckerByPosition(start_x + i, start_y + i);
				if (check_checker != NULL)
				{
					if (check_checker->side != checker->side)
					{
						if (isOne == false)
						{
							isOne = true;
						}
						else {
							return false;
						}
					}
					else return false;
				}
			}
		}

		checker->x = end_x;
		checker->y = end_y;

		return true;
	}
	//Перемещвет шашку на относительное значение, перемещение несуществующей шашки или действие нерушающее правилам шашек вернёт false
	bool moveDeltaChecker(int start_x, int start_y, int dx, int dy)
	{
		Checker* checker = getCheckerByPosition(start_x, start_y);
		if (checker == nullptr)
			return false;
		if (getCheckerByPosition(start_x + dx, start_y + dy) != NULL || dx == 0 || dy == 0 ||
			checker->status == Checker::Base && (abs(dx) > 1 || abs(dy) > 1) ||
			start_x + dx > width - 1 || start_x + dx < 0 || start_y + dy > height - 1 || start_y + dy < 0 || abs(dx) != abs(dy))
			return false;

		if (checker->status == Checker::Base)
		{
			bool isOne = false;
			for (int i = 0; i < abs(dx); i++)
			{
				Checker* check_checker = getCheckerByPosition(start_x + i, start_y + i);
				if (check_checker != NULL)
				{
					if (check_checker->side != checker->side)
					{
						if (isOne == false)
						{
							isOne = true;
						}
						else {
							return false;
						}
					}
					else return false;
				}
			}
		}

		checker->x = start_x + dx;
		checker->y = start_y + dy;

		return true;
	}

	//Возвращает количество шашек заданного цвета
	int getCountCheckers(Checker::Side side)
	{
		int count = 0;
		for (int i = 0; i < this->count; i++)
		{
			if (checkers[i]->side == side)
				count++;
		}

		return count;
	}

	//Возвращает шашку по заданным координатам
	Checker* getCheckerByPosition(int x, int y)
	{
		for (int i = 0; i < count; i++)
		{
			Checker* checker = checkers[i];
			if (checker->x == x && checker->y == y)
				return checker;
		}

		return nullptr;
	}
	//Возвращает массив шашек заданного цвета
	Checker** getCheckers(Checker::Side side)
	{
		int count = getCountCheckers(side);
		Checker** side_checkers = new Checker * [count];
		int number = 0;
		for (int i = 0; i < count; i++)
		{
			Checker* checker = checkers[i];
			if (checker->side == side)
			{
				side_checkers[number] = checker;
				number++;
			}
		}

		return side_checkers;
	}

private:
	Checker** checkers;	//<-- Массив шашек
	int count;			//<-- Количество шашек
	int width;			//<-- Размер доски по ширине
	int height;			//<-- Размер доски по высоте
};

#endif // !BOARD_HPP
