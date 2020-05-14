#include <iostream>

#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <string>


#define NIL nullptr

enum Color { red, black };

class tree
{
public:
	tree* left = nullptr;
	tree* right = nullptr;
	tree* parent = nullptr;
	int val{};
	Color color = red;


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
		tree* FaCurr,
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
				out.at(depth) += pre + std::to_string(FaCurr->val);
				//out.at(depth - 1) += pre;
			}
			else
			{
				out.at(depth) += "  ";
			}


		}
	}

};

// gymut-ot x körül forgat
void bal_forgat(tree*& gymut, tree*& x)
{
	/*
	tree* y;

	y = x->right;
	x->right = y->left;
	y->left->parent = x;
	y->parent = x->parent;
	if (x->parent == NIL)
		gymut = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;
	y->left = x;
	x->parent = y;
	*/

	if (x->left)
	{
		gymut->right = x->left;
		x->left->parent = gymut;

		x->left = gymut;
	}
	else
	{
		x->left = gymut;
		gymut->right = nullptr;
	}

	if (gymut->parent)
	{
		if (gymut->parent->left = gymut)
			gymut->parent->left = x;
		else
			gymut->parent->right = x;

		x->parent = gymut->parent;
	}
	else
		x->parent = nullptr;

	gymut->parent = x;

	std::swap(gymut, x);
}


void jobb_forgat(tree* gymut, tree* x)
{
	tree* y;

	y = x->left;
	x->left = y->right;
	y->right->parent = x;
	y->parent = x->parent;
	if (x->parent == NIL)
		gymut = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	y->right = x;
	x->parent = y;

}


tree* PIROS_FEKETE_BESZUR(tree*& gymut, int érték)
{
	tree* y = nullptr;
	tree* x = gymut;
	while (!(x==nullptr))
	{
		y = x;
		if (érték == x->val)
		{
			return nullptr;
		}
		else if(érték<x->val)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	tree* z = new tree{ nullptr, nullptr, y, érték, red };

	z->left = nullptr;
	z->right = nullptr;
	z->color = red;


	if (y == nullptr)
	{
		gymut = z;
	}
	else if(z->val<y->val)
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}

	return z;
}

void javítOkasaki(tree* gymut, tree*& z)
{
	if (z->parent) {
		while (z->parent->color == red)
		{
			if (z->parent->parent)
			{
				if (z->parent == z->parent->parent->left)
				{
					if (z == z->parent->right)
					{
						z = z->parent;
						bal_forgat(gymut, z);
					}
					z->color = black;
					z->parent->color = red;
					z = z->parent->parent;
					jobb_forgat(gymut, z);
				}
				else
				{
					if (z == z->parent->left)
					{
						z = z->parent;
						jobb_forgat(gymut, z);
					}
					z->color = black;
					z->parent->color = red;
					//z = z->parent->parent;
					bal_forgat(gymut, z->parent);
				}
			}
			else
				break;
		}
		gymut->color = black;
	}

}

void PIROS_FEKETE_TÖRÖL_JAVÍT(tree* gymut, tree* x) {
	tree* w;

	while (!(x == gymut) || x->color == black) {
		if (x == x->parent->left) {
			w = x->parent->right;
			if (w->color == red) {
				w->color = black;
				x->parent->color = red;
				bal_forgat(gymut, x->parent);
				w = x->parent->right;
			}
			if (w->left->color == black || w->right->color == black) {
				w->color = red;
				x = x->parent;
			}
			else if (w->right->color == black) {
				w->left->color = black;
				w->color = red;
				jobb_forgat(gymut, w);
				w = x->parent->right;
			}
			else {
				w->color = w->parent->color;
				x->parent->color = black;
				w->right->color = black;
				bal_forgat(gymut, x->parent);
				x = gymut;
			}
		}
		else {
			w = x->parent->left;
			if (w->color == red) {
				w->color = black;
				x->parent->color = red;
				jobb_forgat(gymut, x->parent);
				w = x->parent->left;
			}
			if (w->right->color == black || w->left->color == black) {
				w->color = red;
				x = x->parent;
			}
			else if (w->left->color == black) {
				w->right->color = black;
				w->color = red;
				bal_forgat(gymut, w);
				w = x->parent->left;
			}
			else {
				w->color = w->parent->color;
				x->parent->color = black;
				w->left->color = black;
				jobb_forgat(gymut, x->parent);
				x = gymut;
			}
		}
	}
	x->color = black;
}

void töröl(tree* gymut, tree*  z)
{
	tree* y;
	tree* x;

	if (z->left == NIL || z->right == NIL) {
		y = z;
	}
	else {
		y = z->right;
		while (!(y->left == NIL)) {
			y = y->left;
		}
	}
	if (!(y->left == NIL)) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	if (!(x == NIL)) {
		x->parent = y->parent;
	}
	if (y->parent == NIL) {
		gymut = x;
	}
	else if (y == y->parent->left) {
		y->parent->left = x;
	}
	else {
		y->parent->right = x;
	}
	if (!(y == z)) {
		z->val = y->val;
	}
	if (y->color == black) {
		PIROS_FEKETE_TÖRÖL_JAVÍT(gymut, x);
	}
}

void insert(tree*& gymut, int érték)
{
	tree* z = PIROS_FEKETE_BESZUR(gymut, érték);
	javítOkasaki(gymut, z);
}


int main()
{
	tree* myTree = new tree;
	myTree->val = 7;
	//insert(myTree, 7);
	insert(myTree, 15);
	insert(myTree, 37);
	myTree->print();
}