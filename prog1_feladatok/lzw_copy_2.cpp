#include <iostream>

template <typename T>
class Node
{
private:
	T value;
	Node *left;
	Node *right;
	int count{ 0 };

	Node(const Node &) = delete;
	Node &operator=(const Node &) = delete;
	Node(Node &&) = delete;
	Node &operator=(Node &&) = delete;
public:
	Node(T value)
	{
		this->value = value;
		this->left = nullptr;
		this->right = nullptr;
	}
	T getValue()
	{
		return value;
	}
	Node *leftChild()
	{
		return left;
	}
	Node *rightChild()
	{
		return right;
	}
	void leftChild(Node *node)
	{
		left = node;
	}
	void rightChild(Node *node)
	{
		right = node;
	}
	int getCount()
	{
		return count;
	}
	void incCount()
	{
		count++;
	}
};

template <typename T>
class BinTree
{
protected:
	Node<T> *root;
	Node<T> *treep;
	int depth{ 0 };



public:
	BinTree(Node<T> *root = nullptr, Node<T> *treep = nullptr)
	{
		this->root = root;
		this->treep = treep;
	}
	~BinTree()
	{
		deltree(root);
	}

	void print() { print(root, std::cout); }
	void print(Node<T> * node, std::ostream & os)
	{
		if (node)
		{
			depth++;
			print(node->leftChild(), os);

			for (int i{ 0 }; i < depth; i++) {
				os << "---";
			}
			os << node->getValue() << " " << depth << " " << node->getCount() << std::endl;
			print(node->rightChild(), os);
			depth--;
		}
	}
	void deltree(Node<T> * node)
	{
		if (node)
		{
			deltree(node->leftChild());  
			deltree(node->rightChild()); 

			delete node;                 
		}

	}

	BinTree(const BinTree& old)
	{
		root = cp(old.root, old.treep);
	}
	Node<T>* cp(Node<T>* node, Node<T>* treep)
	{
		Node<T>* newNode = nullptr;
		
		if (node)
		{
			newNode = new Node<T>(node->getValue());

			newNode->leftChild(cp(node->leftChild(), treep));
			newNode->rightChild(cp(node->rightChild(), treep));

			if (node == treep)
			{
				this->treep = newNode;
			}
		}

		return newNode;
	}
	BinTree &operator=(const BinTree& old)
	{
		BinTree<T> tmp{ old };
		std::swap(*this, tmp);
		return *this;
	}
	BinTree(const BinTree&& old)
	{
		root = nullptr;
		*this = std::move(old);
	}
	BinTree &operator=(BinTree&& old)
	{
		std::swap(old.root, root);
		std::swap(old.treep, treep);
	}

	BinTree<T> & operator<<(T value)
	{
		if (!treep)
		{
			root = treep = new Node<T>(value);
		}
		else if (treep->getValue() == value) 
		{
			treep->incCount();
		}
		else if (treep->getValue() > value)
		{
			if (!treep->leftChild())
			{
				treep->leftChild(new Node<T>(value));
			}
			else
			{
				treep = treep->leftChild();
				*this << value;
			}

		}
		else if (treep->getValue() < value) {
			if (!treep->rightChild())
			{
				treep->rightChild(new Node<T>(value));
			}
			else
			{
				treep = treep->rightChild();
				*this << value;
			}

		}

		treep = root;

		return *this;
	}
};

template <typename T>
class LZWTree : public BinTree<T>
{
public:
	LZWTree() : BinTree<T>(new Node<T>('/'))
	{
		this->treep = this->root;
	}

	LZWTree<T> & operator<<(T value)
	{

		if (value == '0')
		{
			if (!this->treep->leftChild())
			{
				Node<T>* node = new Node<T>(value);
				this->treep->leftChild(node);
				this->treep = this->root;
			}
			else
			{
				this->treep = this->treep->leftChild();
			}

		}
		else
		{
			if (!this->treep->rightChild())
			{
				Node<T>* node = new Node<T>(value);
				this->treep->rightChild(node);
				this->treep = this->root;
			}
			else
			{
				this->treep = this->treep->rightChild();
			}

		}

		return *this;
	}

};
