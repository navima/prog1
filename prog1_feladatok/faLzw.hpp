#pragma once

#include "fa.hpp"
#include <iostream>
#include <fstream>

class Tree
{
public:

	Node<char>* tree = new Node<char>;


	Tree() {};

	~Tree() { delete tree; }

	Tree(const Tree& old)
	{
		tree = new Node<char>(*old.tree);
	}

	Tree& operator=(Tree& old)
	{
		Tree temp(old);
		std::swap(*this, temp);
		return *this;
	}

	Tree& operator=(Tree&& old)
	{
		std::swap(old.tree, tree);
		return *this;
	}

	Tree(Tree&& old)
	{
		tree = new Node<char>(std::move(*old.tree));
	}


	int insert(std::string const& toInsert, unsigned int index = 0, Node<char>* Node = nullptr)
	{
		if ((unsigned int)toInsert.length() > index)		//Ha bárki megmondja nekem hogy miért nem képes a c++ normálisan összehasonlítani két nem pontosan ugyanolyan típusú integert akkor boldogan halok meg
		{
			char relevantBit = toInsert[index];    //Lemásoljuk a stringből az "első" (csak számunkra első) karaktert mert majd sokszor fogunk referálni rá

			if (relevantBit == '0')
			{
				if (!(Node->left))
				{
					Node->makeLeft();
					Node->left->data = relevantBit;
					return Node->left->depth;							//Mivel új részfát kellett létrehozni ezért visszatérünk a Node mélységével (=mennyire volt hosszú a beillesztett karakterlánc)
				}
				else
					return insert(toInsert, index + 1, Node->left);	//index + 1  -el hívjuk meg a függvényt mivel a string vizsgált része már benne van a fában
			}
			else
			{
				if (!(Node->right))
				{
					Node->makeRight();
					Node->right->data = relevantBit;
					return Node->right->depth;
				}
				else
					return insert(toInsert, index + 1, Node->right);
			}
		}
		else
		{
			return toInsert.length() + 1;
		}
	}


	//Egy egyszerű függvény ami egy megadott stringgel feltölti a fát az 'insert' segítségével
	void fill(const std::string& toFillWith)
	{
		int strIndex = 0;		//Hol tartunk éppen a stringünkben

		while (toFillWith.length() > strIndex)
		{
			strIndex += insert(toFillWith, strIndex, tree);		//Az insert azzal tér vissza hogy hány karaktert tudott feldolgozni
																//Ezt a számot hozzáadjuk az indexünkhöz, mivel annyi karaktert dolgoztunk fel
		}
	}



	//Ez egy nemrekurzív megoldás istream-ekkel (azok annyit tudnak hogy a következő karaktert beolvassák, ilyen pl. a "cin")
	int insert(std::istream & insertStream, Node<char>* Node = nullptr)
	{
		int length = 0;
		while (insertStream && !insertStream.eof()) //Ez addig fog futni amíg a stream 'jó'  -ÉS-  a mostani karakter nem EndOfFile
		{
			char relevantBit;

			//insertStream >> relevantBit;
			insertStream.get(relevantBit);	//itt ugyanazt csinálja a 'get' meg a '>>', de általában '>>' a formázott inputra jó, a 'get' pedig a nyers adatra
			length++;


			if (relevantBit == '0')
			{
				if (!(Node->left))
				{
					Node->makeLeft();
					Node->left->data = relevantBit;
					return length;				//Itt megtörjük a loopot mivel egy új részfát kellett generálnunk (értsd: a feldolgozott bit-lánc még nem volt benne a fában)
				}
				else { Node = Node->left; }	//Continue loop      ==kiválasztottuk hogy melyik ágon szeretnénk továbbhaladni és az tesszük meg az új gyökérelemnek
			}
			else if(relevantBit == '1')
			{
				if (!(Node->right))
				{
					Node->makeRight();
					Node->right->data = relevantBit;
					return length;
				}
				else { Node = Node->right; }  //Cont
			}
		}
		return length; //Ha a stream hamarabb végetér minthogy a másik kettő 'return'-höz érne, akkor is visszatérünk
	}


	void fill(std::istream& fillStream) {
		auto done = 0;
		while (fillStream)
		{
			done += insert(fillStream, tree);
		}
	}
};