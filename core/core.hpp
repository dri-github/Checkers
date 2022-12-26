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
		// board->addChecker(0, 0, Checker::White);
		// board->addChecker(2, 0, Checker::White);
		// board->addChecker(4, 0, Checker::White);
		// board->addChecker(6, 0, Checker::White);
		// board->addChecker(1, 1, Checker::White);
		// board->addChecker(3, 1, Checker::White);
		// board->addChecker(5, 1, Checker::White);
		// board->addChecker(7, 1, Checker::White);
		// board->addChecker(0, 2, Checker::White);
		// board->addChecker(2, 2, Checker::White);
		// board->addChecker(4, 2, Checker::White);
		// board->addChecker(6, 2, Checker::White);
		// 
		// board->addChecker(1, 5, Checker::Black);
		// board->addChecker(3, 5, Checker::Black);
		// board->addChecker(5, 5, Checker::Black);
		// board->addChecker(7, 5, Checker::Black);
		// board->addChecker(0, 6, Checker::Black);
		// board->addChecker(2, 6, Checker::Black);
		// board->addChecker(4, 6, Checker::Black);
		// board->addChecker(6, 6, Checker::Black);
		// board->addChecker(1, 7, Checker::Black);
		// board->addChecker(3, 7, Checker::Black);
		// board->addChecker(5, 7, Checker::Black);
		// board->addChecker(7, 7, Checker::Black);

		board->addChecker(2, 2, Checker::Black);
		board->addChecker(3, 3, Checker::White);

		//board->getCheckerByPosition(1, 1)->status = Checker::Queen;

		while (true)
		{
			system("cls");
			std::cout << "======================- Checkers -======================" << std::endl;
			std::cout << "======================-   Menu   -======================" << std::endl;
			std::cout << "|  s - Start game                                      |" << std::endl;
			std::cout << "|  q - Quite program                                   |" << std::endl;
			std::cout << "========================================================" << std::endl;

			unsigned char command;
			std::cin >> command;
			switch (command)
			{
			case 's':
				return true;
			case 'q':
				return false;
			default:
				std::cout << "Not have message" << std::endl;
				alert("Pressed eny key");
				break;
			}
		}

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



			char x1;
			char y1;
			int x2;
			int y2;

			int l = -1;
			int r = 1;


			if (side == Checker::White) {
				side = Checker::Black;
				std::cout << " ---> black " << std::endl;
			}
			else {
				side = Checker::White;
				std::cout << "---> White" << std::endl;
			}



		restart_move:
			//Ввод координат шашки и проверка на корректность введённых данных
			std::cout << "Coords:" << std::endl;
			std::cin >> y1 >> x1;
			y1 = y1 - '0';
			x1 = x1 - '0';
			if (!(x1 >= 0 && x1 <= 7 && y1 >= 0 && y1 <= 7))
				goto restart_move;
			//Куда ходить шашке, налево или направо?
			std::cout << "Left(l) or Right(r)?" << std::endl;
			std::cin >> commandX;
			if (commandX == 'l')
				x2 = l;
			else if (commandX == 'r')
				x2 = r;

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
					else
					{
						if ((x + y) % 2 != 0)
							std::cout << char(0xDB);
						else
							std::cout << char(32);//0XB0
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

	void alert(const char* text)
	{
		std::cout << text << std::endl;
		unsigned char command;
		std::cin >> command;
		std::cout << "\r";
	}
	char* prompt(const char* text, int size)
	{
		std::cout << text << std::endl;
		std::cout << "Yes(y) or Not(n)" << std::endl;
		char* command = new char[size];
		std::cin >> command;

		return command;
	}
	bool confirm(const char* text)
	{
		std::cout << text << std::endl;
		std::cout << "Yes(y) or Not(n)" << std::endl;
		unsigned char command;
		std::cin >> command;

		return command == 'y';
	}

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