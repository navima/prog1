#include "stdio.h"
#include "string.h"
#include "ctype.h"

int xor_encrypt(char* source, size_t size, char* destination, char key)
{
	size_t actual_size = size-1;

	if (strlen(destination) < size)
		actual_size = strlen(destination);

	for (size_t i = 0; i < actual_size; i++)
	{
		destination[i] = (char) ((unsigned char) source[i] ^ (unsigned char) key);
	}

	return 1;
}

int xor_decrypt(char* source, size_t size, char* destination, char key) { return xor_encrypt(source, size, destination, key); }

unsigned int count_ciphertext[128];
float distribution_ciphertext[128];
int xor_crack(char* source, size_t size, char* destination)
{
	//Count occurences of characters in the ciphertext
	size_t i = size;
	while (i-->0)
		count_ciphertext[(unsigned char)source[i]]++;


	i = 128;
	while (i-->0)
	{
		if (count_ciphertext[i] > 0)
		{
			distribution_ciphertext[i] = (float) count_ciphertext[i] / (float) size;
		}
	}


	//Associating max frequency with space
	int max_cipher_index = 0;
	int max_english_index = 4;
	unsigned char key = 0;

	for (int k = 0; k < 128; k++)
	{
		if (distribution_ciphertext[k] > distribution_ciphertext[max_cipher_index])
			max_cipher_index = k;
	}

	key = 32^max_cipher_index;

	i = size;
	while (i-- > 0)
		destination[i] = source[i]^key;


	return 0;
}

int xor_test()
{

	char plaintext[] = "This book is meant to help the reader learn how to program in C. It contains a tutorial introduction to get new users started as soon as possible, separate chapters on each major feature, and a reference manual. Most of the treatment is based on reading, writing and revising examples, rather than on mere statements of rules. For the most part, the examples are complete, real programs rather than isolated fragments. All examples have been tested directly from the text, which is in machine-readable form. Besides showing how to make effective use of the language, we have also tried where possible to illustrate useful algorithms and principles of good style and sound design.";
	size_t size = strlen(plaintext);
	_strlwr_s(plaintext,size+1);

	char ciphertext[681];
	char decodetext[681];
	char cracktext[681];
	memset(ciphertext, ' ', sizeof ciphertext);
	memset(decodetext, ' ', sizeof decodetext);
	memset(cracktext, ' ', sizeof cracktext);
	ciphertext[680] = 0;
	decodetext[680] = 0;
	cracktext[680] = 0;

	unsigned char key = 1;


	xor_encrypt(plaintext, size, ciphertext, key);

	xor_decrypt(ciphertext, size, decodetext, key);
 
	xor_crack(ciphertext, size, cracktext);

	printf("%s\n\n", plaintext);
	printf("%s\n\n", ciphertext);
	printf("%s\n\n", decodetext);
	printf("%s\n\n", cracktext);

	return 0;
}