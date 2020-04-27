#pragma once

#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <string>

//Templateljük, hogy ne csak egy típusú Node legyen, hanem egy Node "gyár", amiből
//tettszőleges típusú fát csinálhatunk (ha a típus implementálja a '>' '<' '==' operátorokat)
//ennek szintaxisa Node<Típus> lesz
//a Node kódján belül a típusára T-ként referálhatunk
//Itt a Node típusa azt határozza meg hogy milyen adat van benne (data változó)

template <typename T> 
class Node
{

//minden member funkcióját és változóját amit ez után írunk publikussá tesszük
public:

	T data = false;			//Az adat amit tárol a Node
	Node<T>* left = nullptr;		//a bal részfára mutató mutató (lol)
	Node<T>* right = nullptr;		//a jobb részfára mutató mutató
	int depth = 0;		//a Node mélysége = hanyadik szinten van a Node a hierarchiában -majd csak a bináris fában fogjuk használni a beszúrásnál, de itt is hasznos lehet
	
	int _leaves = 0;
	bool outdated = true;


	int count() { return elemszam(); }  //A főbb funkciókra angol álnevek (mert magyarul sosem programozunk)
	bool insert(T t) { return beszur(t); }
	auto find(T t) { return keres_iter(t); }
	auto remove(T t) { return torol(t); }
	auto height() { return magassag(); };

	Node() {};

	Node(T data)
	{
		this->data = data;
	}

	Node(const Node<T>& other)
	{
		data = other.data;
		if(other.left)
			left = new Node<T>(*other.left);
		if(other.right)
			right = new Node<T>(*other.right);
	}

	Node(Node<T>&& old)
	{
		if (old.left)
		{
			left = old.left;
			old.left = nullptr;
		}
		if (old.right)
		{
			right = old.right;
			old.right = nullptr;
		}
		data = old.data;
	}

	~Node()
	{
		delete left;
		delete right;
	}

	int getLeaves()
	{
		if (outdated)
			refresh();
		return _leaves;
	}

	void refresh()
	{
		_leaves = levelelemszam();
	}

	//Külön funkciók left és right részfák létrehozására -ez azért kell hogy le legyen kezelve a mélység
	
	bool makeLeft()
	{
		//Megvizsgáljuk hogy mutat-e már részfára a left
		if (left)                   //(ez azért műküdik mert a mutató impliciten "átkonvertálódik" (cast-olódik) booleanra és csak a nullptr cast-ol false-ra)
			return false;
		else
			outdated = true;

			left = new Node<T>();
			left->depth = depth + 1;
			return true;
	}

	bool makeRight()
	{
		if (right)
			return false;
		else
			outdated = true;

			right = new Node<T>();
			right->depth = depth + 1;
			return true;
	}

	int elemszam()
	{
		int rightc = 0;
		int leftc = 0;
		if (left)
			leftc = left->elemszam();
		if (right)
			rightc = right->elemszam();
		return rightc + leftc + 1;
	}

	int levelelemszam()
	{
		if (!left && !right)
			return 1;

		int rightc = 0;
		int leftc = 0;

		if (left)
			leftc = left->levelelemszam();
		if (right)
			rightc = right->levelelemszam();

		return leftc + rightc;
	}

	int magassag()
	{
		int lefth = 0;
		int righth = 0;

		if (left)
			lefth = left->magassag();
		if (right)
			righth = right->magassag();

		return 1 + std::max(lefth, righth);
	}

	bool kiegy()
	{
		if (!left && !right)
			return true;

		if (left && right)
			return left->kiegy() && right->kiegy() && (abs(left->magassag() - right->magassag()) <= 1);
		else
			return false;
	}

	bool tok_kiegy()
	{
		if (!left && !right)
			return true;

		if (left && right)
			return left->tok_kiegy() && right->tok_kiegy() && (abs(left->elemszam() - right->elemszam()) <= 1);
		else
			return false;
	}


	//Itt csak zavart hogy a pseudokódban annyi volt a funkcióhívás helyett hogy [adatok feldolgozása],
	//ezért itt ezek az eljárások egy funkciót kérnek paraméterként, amit az [adatok feldolgozása] résznél meghívnak
	//az éppen vizsgált fára mutató pointerrel (= this) paraméterezve (hogy a funkció tudja milyen kontextusban lett meghívva).
	//mivel std::function a paraméter típusa ezért capturing lambdák-kal is meghívhatjuk

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

	
	//Itt szintén csak zavart hogy a pseudokódban a keresés függvények csak egy booleant adnak vissza,
	//ami távol áll a használhatótól (inkább 'Tartalmaz'-nak kéne őket hívni),
	//ezért a függvény értéke egy Node pointer lesz ami arra a fára mutat amiben megtalálható a 'toFind'.
	//Ha az érték nem található a fában akkor nullptr-t fog visszaadni
	
	Node<T>* keres_iter(const T& toFind)
	{
		Node<T>* x = this;
		while (x)
		{
			if (x->data == toFind)
				return x;
			if (x->data > toFind && x->left)
				x = x->left;
			else if (x->right)
				x = x->right;
			else
				x = nullptr;
		}
		return nullptr;
	}

	Node<T>* keres(const T& toFind)
	{
		if (data == toFind)
			return this;
		if (left && data > toFind)
			return left->keres_iter(toFind);
		if (right && data < toFind)
			return right->keres_iter(toFind);
		else
			return nullptr;
	}

	//Ezek a függvények eredetileg csak eljárások voltak, de azok nem valami beszédesek,
	//úgyhogy itt egy boolean-al térnek vissza ami azt adja meg sikerült-e beilleszteni/törölni 'toInsert'-et
	
	bool beszur(const T& toInsert)
	{
		if (data == toInsert)
			//Item already exists
			return false;

		outdated = true;

		if (data > toInsert)
			if (left)
				return left->beszur(toInsert);
			else
			{

				makeLeft();
				left->data = toInsert;
				return true;
			}


		if (right)
			return right->beszur(toInsert);
		else
		{
			makeRight();
			right->data = toInsert;
			return true;
		}
	}

	//Lusta voltam megcsinálni mégegy bejárást úgyhogy a preordert hívom meg egy lambdával ami akkor adja hozzá a depthet a vektorhoz ha levélelemen van meghívva
	
	std::vector<int> branchLengths()
	{
		std::vector<int> lengths;

		preorder([&lengths](Node<T>* Node) {
			if (!(Node->left || Node->right))
				lengths.push_back((Node->depth));
		});


		return lengths;
	}

	//prints the tree to standard out ROTATED
	void print(std::string pre = "")
	{
		if (right)
			right->print("/");
		else
			std::cout << "\n";


		for (auto i = 0; i < depth; i++)
		{
			std::cout << "      ";
		}
		std::cout << pre << data << "\n";


		if (left)
			left->print("\\");
		else
			std::cout << "\n";
	}

	//prints the tree to standard out PROPERLY
	void print2()
	{
		const int _height = magassag();

		auto width = std::pow(2, _height)*2; //2^height -times- 2(number of characters) 

		std::vector<std::string> out;
		out.resize(_height+1);

		print2r(out, _height, this, (int)width);

		for (auto elem : out)
		{
			std::cout << elem << std::endl;
		}
	}

	void print2r(std::vector<std::string>& out, int maxdepth, Node<T>* FaCurr,int width ,std::string pre = "",int depth = 0)
	{
		if (depth < maxdepth) {
			if (FaCurr)
			{
				if (FaCurr->left)
					print2r(out, maxdepth, FaCurr->left, width,"/", depth + 1);
				else
					print2r(out, maxdepth, nullptr, width,"/", depth + 1);


				if (FaCurr->right)
					print2r(out, maxdepth, FaCurr->right, width,"\\", depth + 1);
				else
					print2r(out, maxdepth, nullptr, width,"\\", depth + 1);
			}
			else
			{
				print2r(out, maxdepth, nullptr, width,"/", depth + 1);
				print2r(out, maxdepth, nullptr, width,"\\", depth + 1);
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