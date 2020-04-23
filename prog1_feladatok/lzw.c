#include <stdio.h>
#include <stdlib.h>

//Hogy tudja saját magát tartalmazni a fa, itt deklarájuk, hogy létezik
typedef struct fa fa;

//A fa struktúránk
struct fa
{
	fa *left;
	fa *right;
	int value;
};

//Standard LZW beillesztés
int fa_insert(fa *target, char *toInsert, int length)
{
	fa *curr = target;
	int strIndex = 0; //Hol tartunk a beillesztendő sztingben
	int success = 0;  //sikerült-e beilleszteni

	while (strIndex < length)	//addig megyünk amí van a stringünkből
	{
		success = 0;
		curr = target;
		while (!success && strIndex < length) //addig megyünk amíg nem lett sikeres egy beillesztés vagy a stringünk végére nem értünk
		{
			if (toInsert[strIndex] = '0') //balra szúrunk be
				if (curr->left)
					curr = curr->left, strIndex++; //már volt ott érték, tehát folytatjuk a beszúrást azon a részfán
				else
					curr->left = (fa *)malloc(sizeof(fa)), curr->left->value = 0, curr->left->left = 0, curr->left->right = 0, strIndex++, success = 1; //új részfát illesztünk be, majd jelezzük, hogy sikerült a beszúrás.
			else if (curr->right)	//ugyanez jobbra
				curr = curr->right, strIndex++;
			else
				curr->right = (fa *)malloc(sizeof(fa)), curr->left->value = 1, curr->left->left = 0, curr->left->right = 0, strIndex++, success = 1;
		}
	}
	return 0;
}

int preorder(fa *target)
{
	//do stuff
	if (target->left)
		preorder(target->left);
	if (target->right)
		preorder(target->right);
	return 0;
}

int postorder(fa *target)
{
	if (target->left)
		postorder(target->left);
	if (target->right)
		postorder(target->right);
	//do stuff
	return 0;
}

int lzw()
{
	fa myFa = {0, 0, -1};

	char asd[7] = {'0', '1', '0', '0', '0', '1', 0};

	fa_insert(&myFa, asd, 5);

	return 0;
}