#include <iostream>

template <typename T>
class BinTree {

protected:
	class Node {

	private:
		T value;
		Node *left;
		Node *right;
		int count{ 0 };

		// TODO rule of five
		Node(const Node &);
		Node & operator=(const Node &);
		Node(Node &&);
		Node & operator=(Node &&);

	public:
		Node(T value) : value(value), left(nullptr), right(nullptr) {}
		T getValue() { return value; }
		Node * leftChild() { return left; }
		Node * rightChild() { return right; }
		void leftChild(Node * node) { left = node; }
		void rightChild(Node * node) { right = node; }
		int getCount() { return count; }
		void incCount() { ++count; }
	};

	Node *root;
	Node *treep;
	int depth{ 0 };

private:
	// TODO rule of five
	//BinTree(const BinTree &);
	//BinTree & operator=(const BinTree &);
	//BinTree(const BinTree &&);
	//BinTree & operator=(const BinTree &&);

public:
	BinTree(Node *root = nullptr, Node *treep = nullptr) : root(root), treep(treep) {}
	~BinTree() {
		deltree(root);
	}
	BinTree & operator<<(T value);
	void print() { print(root, std::cout); }
	void print(Node *node, std::ostream & os)
	{
		if (node)
		{
			++depth;
			print(node->leftChild(), os);

			for (int i{ 0 }; i < depth; ++i)
				os << "---";
			os << node->getValue() << " " << depth << " " << node->getCount() << std::endl;

			print(node->rightChild(), os);
			--depth;
		}

	}
	void deltree(Node *node)
	{
		if (node)
		{
			deltree(node->leftChild());
			deltree(node->rightChild());

			delete node;
		}

	}

};

template <typename T>
class ZLWTree : public BinTree<T> {

public:
	ZLWTree() : BinTree<T>(new typename BinTree<T>::Node('/')) {
		this->treep = this->root;
	}
	ZLWTree & operator<<(T value);


};

template <typename T>
BinTree<T> & BinTree<T>::operator<<(T value)
{
	if (!treep) {

		root = treep = new Node(value);

	}
	else if (treep->getValue() == value) {

		treep->incCount();

	}
	else if (treep->getValue() > value) {

		if (!treep->leftChild()) {

			treep->leftChild(new Node(value));

		}
		else {

			treep = treep->leftChild();
			*this << value;
		}

	}
	else if (treep->getValue() < value) {

		if (!treep->rightChild()) {

			treep->rightChild(new Node(value));

		}
		else {

			treep = treep->rightChild();
			*this << value;
		}

	}

	treep = root;

	return *this;
}


template <typename T>
ZLWTree<T> & ZLWTree<T>::operator<<(T value)
{

	if (value == '0') {

		if (!this->treep->leftChild()) {

			typename BinTree<T>::Node * node = new typename BinTree<T>::Node(value);
			this->treep->leftChild(node);
			this->treep = this->root;

		}
		else {

			this->treep = this->treep->leftChild();
		}

	}
	else {

		if (!this->treep->rightChild()) {

			typename BinTree<T>::Node * node = new typename BinTree<T>::Node(value);
			this->treep->rightChild(node);
			this->treep = this->root;

		}
		else {

			this->treep = this->treep->rightChild();
		}

	}

	return *this;
}

int test(int argc, char** argv, char ** env)
{
	BinTree<int> bt;

	bt << 8 << 9 << 5 << 2 << 7;

	bt.print();

	std::cout << std::endl;

	ZLWTree<char> zt;

	zt << '0' << '1' << '1' << '1' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '0' << '1' << '1' << '1';

	zt.print();

	return 0;
}
