#pragma once

#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>

template <typename T>
struct Reporter
{
	T data{};

	Reporter()
	{
		std::cout << "Constructed " << data << "\n";
	}

	Reporter(T in) : data(in)
	{
		std::cout << "Constructed " << data << "\n";
	}


	~Reporter()
	{
		std::cout << "Destructed " << data << "\n";
	}
};

template <class T>
struct CAlloc
{
	typedef T value_type;

	CAlloc() = default;
	template <class U> constexpr CAlloc(const CAlloc <U>&) noexcept {}

	T* allocate(std::size_t n) {
		if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
			throw std::bad_alloc();

		if (auto p = static_cast<T*>(std::malloc(n * sizeof(T)))) {
			report(p, n);
			return p;
		}

		throw std::bad_alloc();
	}

	void deallocate(T* p, std::size_t n) noexcept {
		report(p, n, 0);
		std::free(p);
	}

	static void test()
	{
		std::vector<Reporter<int>, CAlloc<Reporter<int>>> asd = {};
		std::cout << "declared vector\n";

		for (int i = 0; i < 4; i++)
		{
			asd.push_back(Reporter<int>(i));
			std::cout << "added " << i << "\n";
		}

		asd.clear();
		std::cout << "cleared\n";

		for (int i = 4; i < 8; i++)
		{
			asd.push_back(Reporter<int>(i));
			std::cout << "added " << i << "\n";
		}

	}

private:
	void report(T* p, std::size_t n, bool alloc = true) const {
		std::cout << (alloc ? "Alloc: " : "Dealloc: ") << sizeof(T)*n
			<< " bytes at " << std::hex << std::showbase
			<< reinterpret_cast<void*>(p) << std::dec << '\n';
	}
};

template <class T, class U>
bool operator==(const CAlloc <T>&, const CAlloc <U>&) { return true; }
template <class T, class U>
bool operator!=(const CAlloc <T>&, const CAlloc <U>&) { return false; }

