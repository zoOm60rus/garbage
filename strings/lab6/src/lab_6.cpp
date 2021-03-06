#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include "bohr.h"


int main()
{
	size_t num_of_strs = 0;
	std::string base_string;
	std::vector<pos_str> vec;
	std::vector<std::string> pattern;
	std::getline(std::cin, base_string);
	std::cin >> num_of_strs;
	std::cin.ignore();
	bohr_ini();
	for (size_t i = 0; i < num_of_strs; i++)
	{
		std::string temp;
		std::getline(std::cin, temp);
		add_string(temp, pattern);
	}
	find_all_pos_stand(base_string, pattern, vec);
	for (auto el : vec)
	{
		std::cout << el.pos << " " << el.num_str << std::endl;
	}
	system("pause");
    return 0;
}