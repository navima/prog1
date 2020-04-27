#include <stdio.h>
#include <stdlib.h>

//Hogy tudja saját magát tartalmazni a fa, itt deklarájuk, hogy létezik
typedef struct fa fa;

//egy funkció ami majd a pre, in és posztorder által lesz meghívva a megfelelő helyen
typedef void(*faActor)(fa*);

//A fa struktúránk
struct fa
{
	fa* left;
	fa* right;
	int value;
};

//Standard LZW beillesztés
int fa_insert(fa* target, char* toInsert, int length)
{
	fa* curr = target;
	int strIndex = 0; //Hol tartunk a beillesztendő sztingben
	int success = 0;  //sikerült-e beilleszteni

	while (strIndex < length)	//addig megyünk amí van a stringünkből
	{
		success = 0;
		curr = target;
		while (!success && strIndex < length) //addig megyünk amíg nem lett sikeres egy beillesztés vagy a stringünk végére nem értünk
		{
			if (toInsert[strIndex] == '0') //balra szúrunk be
				if (curr->left)
					curr = curr->left, strIndex++; //már volt ott érték, tehát folytatjuk a beszúrást azon a részfán
				else
					curr->left = (fa *)malloc(sizeof(fa)), curr->left->value = 0, curr->left->left = 0, curr->left->right = 0, strIndex++, success = 1; //új részfát illesztünk be, majd jelezzük, hogy sikerült a beszúrás.
			else if (curr->right)	//ugyanez jobbra
				curr = curr->right, strIndex++;
			else
				curr->right = (fa *)malloc(sizeof(fa)), curr->right->value = 1, curr->right->left = 0, curr->right->right = 0, strIndex++, success = 1;
		}
	}
	return 0;
}

void fa_preorder(fa* target, faActor f)
{
	//do stuff
	f(target);
	if (target->left)
		fa_preorder(target->left, f);
	if (target->right)
		fa_preorder(target->right, f);
}

void fa_postorder(fa* target, faActor f)
{
	if (target->left)
		fa_postorder(target->left, f);
	if (target->right)
		fa_postorder(target->right, f);
	//do stuff
	f(target);
}

void fa_inorder(fa* target, faActor f)
{
	if (target->left)
		fa_inorder(target->left, f);
	//do stuff
	f(target);
	if (target->right)
		fa_inorder(target->right, f);
}


void fa_print(fa* target)
{
	printf("%d ", target->value);
}

void fa_free(fa* target)
{
	free(target);
}


int test()
{
	fa* myFa = (fa*)malloc(sizeof(fa));
	myFa->left = 0;
	myFa->right = 0;
	myFa->value = -1;

	char asd[7] = {'0', '1', '0', '0', '0', '1', 0};

	fa_insert(myFa, asd, 6);

	fa_inorder(myFa, &fa_print);

	fa_postorder(myFa, &fa_free);
	myFa = 0;

	return 0;
}