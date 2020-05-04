#pragma once

#include "fa.hpp"
#include <iostream>
#include <fstream>

class Tree
{

protected:
	Node<char>* tree = new Node<char>;

public:

	/* Rule of three */
	Tree(){}

	~Tree() { delete tree; }

	Tree(const Tree& other) : tree(new Node<char>(*other.tree))
	{
	}

	Tree(Tree&& old) : tree(new Node<char>(std::move(*old.tree)))
	{
	}

	Tree& operator=(Tree&& old) noexcept
	{
		std::swap(old.tree, tree);
		return *this;
	}

	Tree& operator=(const Tree& other)
	{
		Tree temp(other);
		std::swap(*this, temp);
		return *this;
	}


	/* Insertion functions ----------------------------------------------------------------*/

	size_t insert(std::string const& toInsert, size_t index = 0, Node<char>* Node = nullptr)
	{
		if (toInsert.length() > index)
		{
			char relevantBit = toInsert[index];

			if (relevantBit == '0')
			{
				if (!(Node->left))
				{
					Node->makeLeft();
					Node->left->data = relevantBit;
					return index + 1;
				}
				else
					return insert(toInsert, index + 1, Node->left);
			}
			else
			{
				if (!(Node->right))
				{
					Node->makeRight();
					Node->right->data = relevantBit;
					return index + 1;
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

	Tree& operator<<(const std::string& in) { fill(in); return *this; }
	void fill(const std::string& toFillWith)
	{
		size_t strIndex = 0;

		while (toFillWith.length() > strIndex)
		{
			strIndex += insert(toFillWith, strIndex, tree);
		}
	}

	size_t insert(std::istream& insertStream, Node<char>* Node = nullptr)
	{
		size_t length = 0;
		while (insertStream && !insertStream.eof())
		{
			char relevantBit;

			insertStream.get(relevantBit);
			length++;


			if (relevantBit == '0')
			{
				if (!(Node->left))
				{
					Node->makeLeft();
					Node->left->data = relevantBit;
					return length;
				}
				else { Node = Node->left; }
			}
			else if(relevantBit == '1')
			{
				if (!(Node->right))
				{
					Node->makeRight();
					Node->right->data = relevantBit;
					return length;
				}
				else { Node = Node->right; }
			}
		}
		return length;
	}

	void fill(std::istream& fillStream) {
		size_t done = 0;
		while (fillStream)
		{
			done += insert(fillStream, tree);
		}
	}

	/* Misc functions ----------------------------------------------------------------------*/

	void print() { tree->print(); }
};

void TreeTest()
{
	Tree tree;
	tree << "01";

	Tree tree_copy = tree;
	tree_copy << "00";

	Tree tree_move = std::move(tree);
	tree_move << "11";

	tree << "0000000000";

	std::cout << "original:---------------------------------\n";
	tree.print();
	std::cout << "copy:-------------------------------------\n";
	tree_copy.print();
	std::cout << "move:-------------------------------------\n";
	tree_move.print();
}