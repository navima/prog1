#pragma once

#include "fa.hpp"
#include <iostream>
#include <fstream>

class Tree
{
public:

	Node<char> tree;

	int insert(std::istream & insertStream, std::ostream & asd, Node<char>* Node = nullptr)
	{
		int length = 0;
		while (insertStream && !insertStream.eof())
		{
			char relevantBit;

			insertStream.get(relevantBit);
			length++;
			asd<<(relevantBit);


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
		std::ofstream b("asd");
		auto done = 0;
		while (fillStream)
		{
			done += insert(fillStream, b, &tree);
		}
		b.close();
		std::ifstream a("asd");
		char c = '0';
		if (done < 1002)
			while (a >> c) std::cout << c;
		std::cout << "\n";
	}
};