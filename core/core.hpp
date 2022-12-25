#ifndef CORE_HPP
#define CORE_HPP

#include "board.hpp"

//
// Главная структура программы, обрабатывает различные базовые процессы
//
struct Main
{
public:
	Main() : is_open(true), board(nullptr) {}
	~Main()
	{
		delete board;
	}

	//Инициализация, если прошла удачно должна должна вернуть true
	bool init()
	{
		//Присваиваем различные значения или делаем предварительную подготовку, например:
		//latter = 'd';

		std::cout << "init" << std::endl;
		
		// ■ - белые
		// 0 - Чёрные

		width = 8;
		height = 8;
		board = new Board(width, height);
		board->addChecker(0, 0, Checker::White);
		board->addChecker(2, 0, Checker::White);
		board->addChecker(4, 0, Checker::White);
		board->addChecker(6, 0, Checker::White);
		board->addChecker(1, 1, Checker::White);
		board->addChecker(3, 1, Checker::White);
		board->addChecker(5, 1, Checker::White);
		board->addChecker(7, 1, Checker::White);
		board->addChecker(0, 2, Checker::White);
		board->addChecker(2, 2, Checker::White);
		board->addChecker(4, 2, Checker::White);
		board->addChecker(6, 2, Checker::White);

		board->addChecker(1, 5, Checker::Black);
		board->addChecker(3, 5, Checker::Black);
		board->addChecker(5, 5, Checker::Black);
		board->addChecker(7, 5, Checker::Black);
		board->addChecker(0, 6, Checker::Black);
		board->addChecker(2, 6, Checker::Black);
		board->addChecker(4, 6, Checker::Black);
		board->addChecker(6, 6, Checker::Black);
		board->addChecker(1, 7, Checker::Black);
		board->addChecker(3, 7, Checker::Black);
		board->addChecker(5, 7, Checker::Black);
		board->addChecker(7, 7, Checker::Black);

		//board->getCheckerByPosition(1, 1)->status = Checker::Queen;

		return true;
	}
	//Обновление
	//Вызывается перед отрисовкой (различные расчеты и функции ввода прописываем в данной функции)
	void update()
	{
		std::cout << "update" << std::endl;
		unsigned char command;
		std::cin >> command;
		if (command == 'q')
			close();
		else if (command == 'm')
		{
			unsigned char commandX;
			unsigned char commandY;

			//  -------------------------> X
			// |
			// |
			// |
			// |
			// |
			// |
			// |
			// |
			// v
			// 
			// Y

																					

			int x1;
			int y1;
			int x2;
			int y2;
			
			int l = -1;
			int r = 1;


			if (side == Checker::White) {
				side = Checker::Black;
				std::cout << "---> Black" << std::endl;
			}
			else {
				side = Checker::White;
				std::cout << "---> White" << std::endl;
			}



restart_move:
			std::cout << "Coords:" << std::endl;
			std::cin >> y1 >> x1;
			std::cout << "Left(l) or Right(r)? ";
			std::cin >> commandX;
			if (commandX == 'l')
				x2 =  l;
			else if (commandX == 'r')
				x2 =  r;
			
			Checker* checker = board->getCheckerByPosition(x1, y1);
			switch (side)
			{
			case Checker::White:
				if (checker != 0 && checker->side == Checker::White)
				{
					if (board->moveDeltaChecker(x1, y1, x2, 1) == false)
						goto restart_move;
				}
				else {
					goto restart_move;
				}
				break;
			case Checker::Black:
				if (checker != 0 && checker->side == Checker::Black)
				{
					if (board->moveDeltaChecker(x1, y1, x2, -1) == false)
						goto restart_move;
				}
				else {
					goto restart_move;
				}
				break;
			default:
				break;
			}
		}
		else if (command == 's') {
			int x1;
			int y1;

			int l = -1;
			int r = 1;
		}
	}
	//Отрисовка
	//Вызываетс после обновления (одиночно вызывается перед запускам основного цикла)
	void render()
	{
		//Если надо очистить консоль исспользуйте system("cls")
		system("cls");

		std::cout << "render" << std::endl;
		std::cout << "   ";
		for (int x = 0; x < width; x++)
		{
			std::cout << x << "  ";
		}
		std::cout << std::endl;
		for (int y = 0; y < height; y++)
		{
			std::cout << y << " ";
			for (int x = 0; x < width; x++)
			{
				for (int i = 0; i < 3; i++)
				{
					Checker* checker = board->getCheckerByPosition(x, y);
					if (checker != NULL && i == 1)
					{
						switch (checker->side)
						{
						case Checker::White:
							if (checker->status == Checker::Base)
								std::cout << char(254);
							else
								std::cout << char(2);
							break;
						case Checker::Black:
							if (checker->status == Checker::Base)
								std::cout << char(79);
							else
								std::cout << char(1);
							break;
						}
					}
									}
			}
			std::cout << std::endl;
		}
	}

	//Открыта ли программа
	bool isOpen() const { return is_open; }
	//Закрывает программу
	void close() { is_open = false; }

private:
	Board* board;	//<-- Игровая доска
	bool is_open;	//<-- Определяет открыта ли программа
	
	//Переменные объявляем после этого коментария (если есть необходимость создания переменных доступных по всему коду)
	//char latter;	//<-- Например
	int width;
	int height;
	Checker::Side side = Checker::Side::Black;
};

#endif // !CORE_HPP