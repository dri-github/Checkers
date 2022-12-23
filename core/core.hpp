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

		board = new Board(8, 8);
		board->addChecker(0, 0, Checker::White);
		board->addChecker(0, 0, Checker::White);
		std::cout << "init" << std::endl;
		
		return true;
	}
	//Обновление
	//Вызывается перед отрисовкой (различные расчеты и функции ввода прописываем в донной функции)
	void update()
	{
		std::cout << "update" << std::endl;
		unsigned char command;
		std::cin >> command;
	}
	//Отрисовка
	//Вызываетс после обновления (одиночно вызывается перед запускам основного цикла)
	void render()
	{
		//Если надо очистить консоль исспользуйте system("cls")
		std::cout << "render" << std::endl;
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
};

#endif // !CORE_HPP
