#include "map-sorter.hpp"

void valueSort(std::map<int, int>& map)
{
	std::map<int, int> map2 = std::map<int, int>();

	for (auto i : map)
		map2.insert(std::pair<int, int>(i.second, i.first));
	   
	map = map2;
}

template <typename First, typename Second>
std::vector<std::pair<First, Second>> sort_map(const std::map<First, Second>& rank)
{
	std::vector<std::pair<First, Second>> ordered;

	for (const auto& i : rank) 
		ordered.push_back(i);

	std::sort(
		std::begin(ordered),
		std::end(ordered),
		[](const auto& p1, const auto& p2) 
		{
			return p1.second < p2.second;
		}
	);

	return ordered;
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

	auto temp = sort_map(map);

	for (const auto& elem : temp)
		std::cout << elem.first << "\t" << elem.second << "\n";
	
	std::cout << "\n";

	//print(map);
}