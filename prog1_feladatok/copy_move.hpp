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

	//A m�sol� konstruktor
	//	Ez egy konstans Node<T> referenci�t fog kapni,
	//	amibol mi kell leprogramozzuk, hogy hogy k�sz�t m�solatot
	//	Term�szetesen konstans a referencia, hiszen az eredetit is meg szeretn�nk hagyni.
	//	Ez gyakorlatilag egy deep copyt k�sz�t a param�ter�rol
	Node(const Node<T>& old)
	{

		// Elosz�r lem�soljuk a templatelt class� member�nket (annak m�sol� konstruktor�val)
		//data = old.data;
		data = T(old.data);

		// Majd a pointerek �ltal mutatott objektumokat is lem�soljuk
		if (old.left)
			left = new Node<T>(*old.left);
		if (old.right)
			right = new Node<T>(*old.right);
	}

	//A mozgat� konstruktor
	//	Ez egy rvalue referenci�t fog kapni, aminek az eroforr�sait el kell "lopnia"
	//	Ez pl. a = b + c esetekn�l fordul elo, ahol a "b + c" egy olyan objektumot csin�l,
	//	ami csak arra kell, hogy az a-nak �rt�ket adjunk vele, ut�na pedig nem tudunk hozz�f�rni.
	//	Emiatt megtehetj�k azt, hogy nem lem�soljuk az objekumot, hanem mozgatjuk
	//	Ez�rt is nem konstans a param�ter, mert elv�rt, hogy annak eroforr�sait ellopjuk
	//	Egy fontos aj�nl�s/sztenderd az, hogy a param�terk�nt kapott objektum m�g valid legyen
	//	a mozgat�s ut�n is.
	Node(Node<T>&& old) noexcept
	{
		// Eloszor a dat�t mozgatjuk �t. A mozgat� konstruktort expliciten is megh�vhatjuk az std::move(old)-al
		data = std::move(old.data);

		// Az std::swap h�rom mozgat�st v�gez: egyik->temp, m�sik->egyik, temp->egyik
		std::swap(left, old.left);
		std::swap(right, old.right);
	}

	//A m�sol� �rt�kad�s 
	//	(igaz�b�l csak Quality of life; a nehez�t a m�sol�/mozgat� konstruktor csin�lja, 
	//	itt csak azokat haszn�ljuk)
	Node<T>& operator=(const Node<T>& other)
	{
		// A m�sol� konstruktort haszn�lva csin�lunk egy temp-et a m�soland� m�solat�b�l
		Node<T> temp(other);

		// A mozgat� konstruktort haszn�lva kicser�lj�k magunkat a temp-el
		std::swap(*this, temp);

		// Visszat�r�nk magunkkal
		return *this;
	}

	//A mozgat� �rt�kad�s (-||-)
	Node<T>& operator=(Node<T>&& old) noexcept
	{
		// Csak sim�n kicser�li a kettot a mozgat� konstruktorral
		std::swap(old.data, data);
		std::swap(old.left, left);
		std::swap(old.right, right);

		// Visszat�r�nk magunkkal
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