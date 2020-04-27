#include <iostream>
#include "fa.hpp"
#include "faLzw.hpp"

int main()
{
	//Node<int> myNode;
	//
	//myNode.beszur(3);
	//myNode.beszur(5);

	//Node<int> myNode2(std::move(myNode));

	//myNode.beszur(4);
	//myNode.beszur(2);

	//myNode2.beszur(1);

	//myNode.print2();
	//myNode2.print2();

	Tree myTree;

	myTree.fill("010001");

	Tree myTree2;
	myTree2 = myTree;

	myTree.fill("11111");

	myTree.tree->print2();
	myTree2.tree->print2();
}