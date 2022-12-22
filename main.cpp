#include <iostream>

#include "core/core.hpp"

int main()
{
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
	return 0;
}
