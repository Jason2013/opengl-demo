#include "globjs.h"
#include <iostream>
#include <conio.h>

void err_hander(const std::string& err_message)
{
	std::cerr << err_message << std::endl;
	_getch();


}
