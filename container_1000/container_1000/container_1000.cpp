// container_1000.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "additional_func.h"
#include "my_shared_ptr.h"
#include "my_vector.h"
#include "shape.h"


int main()
{
	vector<shared_ptr<Shape>> array = create_arr(1000);
	vector<neighbours> pairs = neigh_search(array);
	vector<dual_un> sort_arr = dual_diap_union(rand() % 20, rand() % 20 + 40, rand() % 100 + 540, rand() % 50 + 700, array);
	for (int i = 0; i< sort_arr.size(); i++)
	{
		std::cout << "First: " << sort_arr[i].num << " Second: " << sort_arr[i].val << std::endl;
	}
	std::cout << sort_arr.size() << std::endl;
	system("pause");
    return 0;
}

