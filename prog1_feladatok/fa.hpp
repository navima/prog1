#pragma once

#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <string>


template <typename T> 
class Node
{

public:

	T data{};
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
	
	/* Rule of three */
	Node() {}

	Node(const T& data) : data(data) {}

	~Node() 
	{
		delete left;
		delete right;
	}

	Node(const Node<T>& old)
	{
		data = old.data;
		if (old.left)
			left = new Node<T>(*old.left);
		if (old.right)
			right = new Node<T>(*old.right);
	}

	Node(Node<T>&& old) noexcept
	{
		data = old.data;
		std::swap(left, old.left);
		std::swap(right, old.right);
	}

	virtual Node<T>* makeLeft(Node<T>& newLeft = *(new Node<T>()))
	{
		if (left)
			return nullptr;
		else
			left = &newLeft;
			left->parent = this;
			return left;
	}

	virtual Node<T>* makeRight(Node<T>& newRight = *(new Node<T>()))
	{
		if (right)
			return nullptr;
		else
			right = &newRight;
			right->parent = this;
			return right;
	}

	template <typename Pred>
	void preorder(Pred f = {})
	{
		f(this);
		if (left)
			left->preorder(f);
		if (right)
			right->preorder(f);
	}

	template <typename Pred>
	void inorder(Pred f = {})
	{
		if (left)
			left->inorder(f);
		f(this);
		if (right)
			right->inorder(f);
	}

	template <typename Pred>
	void postorder(Pred f = {})
	{
		if (left)
			left->postorder(f);
		if (right)
			right->postorder(f);
		f(this);
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

	// Method to delete from tree
	virtual bool remove(const T& toRemove) { return false; }

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

		size_t width = (size_t) std::pow(2, _height)*2; //2^height -times- 2(number of characters) 


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
					printernal(out, maxdepth, FaCurr->left, width,"/", depth + 1);
				else
					printernal(out, maxdepth, nullptr, width,"/", depth + 1);


				if (FaCurr->right)
					printernal(out, maxdepth, FaCurr->right, width,"\\", depth + 1);
				else
					printernal(out, maxdepth, nullptr, width,"\\", depth + 1);
			}
			else
			{
				printernal(out, maxdepth, nullptr, width,"/", depth + 1);
				printernal(out, maxdepth, nullptr, width,"\\", depth + 1);
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