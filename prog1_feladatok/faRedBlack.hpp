#pragma once

#include "fa.hpp"

enum Colour
{
	red, black
};

// A struct containing the value and colour of a node
template <typename T>
struct RBValue
{
	T value{};
	Colour colour = red;
	
	bool operator==(const RBValue& other) { return value == other.value; }
	bool operator>(const RBValue& other) { return value > other.value; }
};


template <typename T>
class RedBlackTree : public Node<RBValue<T>>
{
	typedef Node<RBValue<T>> node;

	// returns with reference of inserted node
	//node& insertRedBlack(const T& toInsert)
	//{
	//	RedBlackTree* current = this;
	//	while (true)
	//	{
	//		// Find insert 
	//		auto currVal = current->data.value;
	//		if (toInsert > currVal)
	//		{
	//			if (current->right)
	//				current = current->right;
	//			else
	//			{
	//				return current->makeRight(new node(RBValue<T>{ currVal, red }));
	//			}
	//		}
	//		else// if (toInsert < currVal)
	//		{
	//			if (current->left)
	//				current = current->left;
	//			else
	//			{
	//				return current->makeLeft(new node(RBValue<T>{ currVal, red }));
	//			}
	//		}
	//	}
	//}

	void balanceOkasaki(node& inserted)
	{
		while (inserted.parent->data.colour = red)
		{
			if (inserted.parent == inserted.parent->parent->left)
			{
				if (&inserted == inserted.parent->right)
				{
					inserted = *inserted.parent;
				}
			}
		}
	}

public:
	virtual node& insert(const RBValue<T>& toInsert) override
	{
		node& inserted = node::insert(toInsert);
		balanceOkasaki(inserted);
		return inserted;
	}

	bool insert(const T& toInsert) 
	{
		insert(RBValue<T>{ toInsert, red });
		return false;
	}

	virtual bool remove(const RBValue<T>& toRemove) override
	{
		return false;
	}
};