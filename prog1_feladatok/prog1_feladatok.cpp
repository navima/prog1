#include "lzw_copy.cpp"

int main()
{
	BinTree<int> binTree;
	//binTree << 8 << 9 << 5 << 2 << 7;
	binTree << 8 << 2 << 7 << 8<<2;
	binTree.print();
	std::cout << std::endl;
	ZLWTree<char> zlwTree;
	zlwTree << '0' << '1' << '1' << '1' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '1' << '0' << '0' << '0' << '1' << '1' << '1';
	zlwTree.print();
}