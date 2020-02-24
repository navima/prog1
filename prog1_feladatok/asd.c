#include <omp.h>
#include <Windows.h>

int inf()
{
	while (1);
}

int inf2()
{
	while (1);
		//sleep(1);
}

int inf3()
{
#pragma omp parralel
	{
		while (1);
	}
	return 0;
}