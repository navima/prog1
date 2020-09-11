#include "map-sorter.hpp"

void valueSort(std::map<int, int>& map)
{
	std::map<int, int> map2 = std::map<int, int>();

	for (auto i : map)
	{
		map2.insert(std::pair<int, int>(i.second, i.first));
	}

	map = map2;
}

void print(std::map<int, int>& map)
{
	for (auto elem : map)
		std::cout << elem.first << "\t" << elem.second <<"\n";
	std::cout << "\n";
}

void test()
{
	//declare map
	std::map<int, int> map = std::map<int, int>();
	
	//fill map
	for (int i = 0; i < 5; i++)
		map.insert(std::pair<int, int>(i, 5-i));

	for (int i = 5; i < 10; i++)
		map.insert(std::pair<int, int>(i+5, 10+5-i));

	print(map);

	valueSort(map);

	print(map);
}