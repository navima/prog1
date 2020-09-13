#pragma once

#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <string>
#include <iostream>


template <typename T>
class Node
{
public:

	T data{};
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;


	//A sztenderd konstruktor
	Node() {}

	//Quality of life
	Node(const T& data) : data(data) {}

	//A sztenderd destruktor
	~Node()
	{
		delete left;
		delete right;
	}

	//A másoló konstruktor
	//	Ez egy konstans Node<T> referenciát fog kapni,
	//	amibol mi kell leprogramozzuk, hogy hogy készít másolatot
	//	Természetesen konstans a referencia, hiszen az eredetit is meg szeretnénk hagyni.
	//	Ez gyakorlatilag egy deep copyt készít a paraméterérol
	Node(const Node<T>& old)
	{

		// Eloször lemásoljuk a templatelt classú memberünket (annak másoló konstruktorával)
		//data = old.data;
		data = T(old.data);

		// Majd a pointerek által mutatott objektumokat is lemásoljuk
		if (old.left)
			left = new Node<T>(*old.left);
		if (old.right)
			right = new Node<T>(*old.right);
	}

	//A mozgató konstruktor
	//	Ez egy rvalue referenciát fog kapni, aminek az eroforrásait el kell "lopnia"
	//	Ez pl. a = b + c eseteknél fordul elo, ahol a "b + c" egy olyan objektumot csinál,
	//	ami csak arra kell, hogy az a-nak értéket adjunk vele, utána pedig nem tudunk hozzáférni.
	//	Emiatt megtehetjük azt, hogy nem lemásoljuk az objekumot, hanem mozgatjuk
	//	Ezért is nem konstans a paraméter, mert elvárt, hogy annak eroforrásait ellopjuk
	//	Egy fontos ajánlás/sztenderd az, hogy a paraméterként kapott objektum még valid legyen
	//	a mozgatés után is.
	Node(Node<T>&& old) noexcept
	{
		// Eloszor a datát mozgatjuk át. A mozgató konstruktort expliciten is meghívhatjuk az std::move(old)-al
		data = std::move(old.data);

		// Az std::swap három mozgatást végez: egyik->temp, másik->egyik, temp->egyik
		std::swap(left, old.left);
		std::swap(right, old.right);
	}

	//A másoló értékadás 
	//	(igazából csak Quality of life; a nehezét a másoló/mozgató konstruktor csinálja, 
	//	itt csak azokat használjuk)
	Node<T>& operator=(const Node<T>& other)
	{
		// A másoló konstruktort használva csinálunk egy temp-et a másolandó másolatából
		Node<T> temp(other);

		// A mozgató konstruktort használva kicseréljük magunkat a temp-el
		std::swap(*this, temp);

		// Visszatérünk magunkkal
		return *this;
	}

	//A mozgató értékadás (-||-)
	Node<T>& operator=(Node<T>&& old) noexcept
	{
		// Csak simán kicseréli a kettot a mozgató konstruktorral
		std::swap(old.data, data);
		std::swap(old.left, left);
		std::swap(old.right, right);

		// Visszatérünk magunkkal
		return *this;
	}

	virtual Node<T>* makeLeft(Node<T>& newLeft = *(new Node<T>()))
	{
		if (left)
			return nullptr;
		else
			left = &newLeft;
		return left;
	}

	virtual Node<T>* makeRight(Node<T>& newRight = *(new Node<T>()))
	{
		if (right)
			return nullptr;
		else
			right = &newRight;
		return right;
	}

	// Method to insert into tree
	virtual Node<T>& insert(const T& toInsert)
	{
		if (data == toInsert)
			//Item already exists
			return *(new Node<T>());

		if (data > toInsert)
			if (left)
				return left->insert(toInsert);
			else
			{
				return *makeLeft(*(new Node<T>(toInsert)));
			}

		if (right)
			return right->insert(toInsert);
		else
		{
			return *makeRight(*(new Node<T>(toInsert)));
		}
	}

	size_t height()
	{
		size_t lefth = 0;
		size_t righth = 0;
		if (left)
			lefth = left->height();
		if (right)
			righth = right->height();
		return std::max(lefth, righth) + 1;
	}

	void print(std::ostream& outStream = std::cout)
	{
		const size_t _height = height();

		size_t width = (size_t)std::pow(2, _height) * 2; //2^height -times- 2(number of characters) 


		std::vector<std::string> out;
		out.resize(_height + 1);

		printernal(out, _height, this, width);

		for (auto elem : out)
		{
			outStream << elem << std::endl;
		}
	}

private:
	void printernal(std::vector<std::string>& out,
		size_t maxdepth,
		Node<T>* FaCurr,
		size_t width,
		std::string pre = "",
		size_t depth = 0)
	{
		if (depth < maxdepth) {
			if (FaCurr)
			{
				if (FaCurr->left)
					printernal(out, maxdepth, FaCurr->left, width, "/", depth + 1);
				else
					printernal(out, maxdepth, nullptr, width, "/", depth + 1);


				if (FaCurr->right)
					printernal(out, maxdepth, FaCurr->right, width, "\\", depth + 1);
				else
					printernal(out, maxdepth, nullptr, width, "\\", depth + 1);
			}
			else
			{
				printernal(out, maxdepth, nullptr, width, "/", depth + 1);
				printernal(out, maxdepth, nullptr, width, "\\", depth + 1);
			}




			if (out.at(depth).empty())
			{
				for (auto i = 0; i < std::pow(2, maxdepth - depth); i++)
				{
					out.at(depth) += " ";
				}
			}
			else
			{
				for (auto i = 0; i < std::pow(2, maxdepth - depth + 1) - 2; i++)
				{
					out.at(depth) += " ";
				}
			}

			if (FaCurr)
			{
				out.at(depth) += pre + std::to_string(FaCurr->data);
				//out.at(depth - 1) += pre;
			}
			else
			{
				out.at(depth) += "  ";
			}


		}
	}
};

void NodeTest()
{
	Node<int> node;
	node.insert(2);

	Node<int> node_copy(node);
	node_copy.insert(3);

	Node<int> node_move = std::move(node);
	node_move.insert(1);

	std::cout << "original:---------------------------------\n";
	node.print();
	std::cout << "copy:-------------------------------------\n";
	node_copy.print();
	std::cout << "move:-------------------------------------\n";
	node_move.print();
}