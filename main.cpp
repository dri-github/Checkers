#include <iostream>

#include "core/core.hpp"

int main()
{
	start_loger("result.log");
	Main* _main = new Main();

	if (_main->init())
	{
		_main->render();
		while (_main->isOpen())
		{
			_main->update();
			_main->render();
		}
	}

	delete _main;
	end_loger();

	return 0;
}
