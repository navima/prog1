#include "lzw_copy.cpp"

class myMove
{
public:
	int asd = 1;
	myMove(const myMove&& other)
	{
		*this = std::move(other);
	}
	myMove& operator=(const myMove&& other)
	{
		//other.modify();
		return *this;
	}
	void modify()
	{
		asd = -1;
	}
};

int main()
{
	BinTree<int> binTree;
	binTree << 8 << 9 << 5 << 2 << 7<<8<<8<<7<<2;
	binTree.print();
	std::cout << std::endl;
	ZLWTree<char> zlwTree;
	//zlwTree << '0' << '1' << '1' << '1' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '0' << '1' << '1' << '1';
	zlwTree << '0' << '1' ;
	auto& binzlw = static_cast<BinTree<char>&>(zlwTree);
	binzlw << '0' << '0' << '0' << '0';
	zlwTree.print();
}