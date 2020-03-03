#include <stdio.h>
#include <stdlib.h>

typedef struct fa fa;

struct fa
{
	fa* left;
	fa* right;
	int value;
};

int fa_insert(fa* target, char* toInsert,int length)
{
	fa* curr = target;
	int strIndex = 0;
	int success = 0;

	while (!success && strIndex < length)
	{
		if (toInsert[strIndex] = '0')
			if (curr->left)
				curr = curr->left, strIndex++;
			else
				curr->left = (fa*) malloc(sizeof(fa)), curr->left->value = 0,curr->left->left = 0, curr->left->right = 0, strIndex++, success = 1;
		else
			if (curr->right)
				curr = curr->right, strIndex++;
			else
				curr->right = (fa*)malloc(sizeof(fa)), curr->left->value = 1, curr->left->left = 0, curr->left->right = 0, strIndex++, success = 1;
	}
	return 0;
}

int preorder(fa* target)
{
	//do stuff
	if (target->left)
		preorder(target->left);
	if(target->right)
		preorder(target->right);
	return 0;
}

int postorder(fa* target)
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

	char asd[4] = { '0','1','0','0' };

	fa_insert(&myFa, asd, 3);

	return 0;
}