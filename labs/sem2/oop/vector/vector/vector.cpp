// vector.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <vector>
#include "my_vector.h"
#include "iostream"


int main()
{
	std::initializer_list<int> two = { 1,2 };
	//stepik::vector<size_t>&& three = { 3,4,5 };
	stepik::vector<size_t> one(2);
	stepik::vector<int> new_one(two);
	int vec_size = one.size();
	//std::cout << vec_size << std::endl;
	//std::cout << new_one[0] << std::endl;
	//std::cout << new_one[1] << std::endl;
	//stepik::vector<size_t> new_one_2(three);
	//for (size_t i = 0; i < three.size(); i++)
	//{
	//	std::cout << new_one_2[i] << std::endl;
	//}
	//stepik::vector<size_t> temp(three.size());
	//temp = three;
	stepik::vector <size_t> temp2(3);
	//temp2.assign(&three[0], &three[3]);
	/*for (size_t i = 0; i < three.size(); i++)
	{
		std::cout << "[" << temp[i] << "]" << std::endl;
		std::cout << "{" << temp2[i] << "}" << std::endl;
	}
	stepik::vector<size_t>& lol = three;
	for (size_t i = 0; i < lol.size(); i++)
	{
		std::cout << "[" << lol[i] << "]" << std::endl;
		//std::cout << "{" << temp2[i] << "}" << std::endl;
	}*/
	stepik::vector<int> a={ 1,2,3,4,5,6,7,8 };
	stepik::vector<int> b = a;
	//stepik::vector<int> c(std::move(b));
	b.push_back(1);
	b.push_back(3);
	b.push_back(4);
	b.print();
	//b.insert(b.begin(), 888);
	b.print();
	b.insert(b.begin() + 5, a.begin(), a.end());
	b.print();
	//b.insert(b.begin() + 2, a, a + 3);
	//b.print();
	//b.erase(b.begin()+1, b.begin()+1);
	//b.print();
	/*b.print();
	b.resize(10);
	b.print();
	b.resize(2 * 10);
	b.print();
	b.resize(5);
	b.print();*/
	//c.assign(99, 100);
	//c.erase(c.begin(), c.end());
	//c.print();
	system("pause");
    return 0;
}

