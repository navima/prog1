#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int it(fs::path p)
{
	int classCounter = 0;

	for (const auto& x : fs::recursive_directory_iterator(p))
	{
		if (fs::path(x.path()).extension() == ".java" && fs::is_regular_file(x.path()))
		{
			classCounter++;
			std::cout << "    " << x.path() << '\n';
		}

	}
	return classCounter;
}

int test(std::string path)
{

	fs::path p(path);

	try
	{
		int classCounter = it(p);
		std::cout << "Java fajlok szama: " << classCounter << std::endl;
	}
	catch (const fs::filesystem_error& e)
	{
		std::cout << e.what() << '\n';
	}

	return 0;
}