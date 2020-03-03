#pragma warning(disable:4996)

#include "stdio.h"
#include "string.h"
#include "ctype.h"

int xor_encrypt(char* source, size_t size, char* destination, char* key, size_t sizeKey)
{
	size_t actual_size = size-1;

	if (strlen(destination) < size)
		actual_size = strlen(destination);


	for (size_t i = 0; i < actual_size; i++)
	{
		unsigned char sourceChar = (unsigned char)source[i];
		unsigned char keyChar = (unsigned char)key[i%sizeKey];
		destination[i] = (char)(sourceChar^keyChar);
	}

	return 1;
}

int xor_decrypt(char* source, size_t size, char* destination, char* key, size_t sizeKey) { return xor_encrypt(source, size, destination, key, sizeKey); }

unsigned int count_ciphertext[128];
float distribution_ciphertext[128];
int xor_crack_1byte(char* source, size_t size, char* destination)
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

	char plaintext[] = "uve been bamboozled look at you. -navima ";
	size_t size = strlen(plaintext);
	_strlwr(plaintext);

	char ciphertext[681];
	char decodetext[681];
	char cracktext[681];
	memset(ciphertext, ' ', sizeof ciphertext);
	memset(decodetext, ' ', sizeof decodetext);
	memset(cracktext, ' ', sizeof cracktext);
	ciphertext[680] = 0;
	decodetext[680] = 0;
	cracktext[680] = 0;

	char key[] = "laci";
	size_t sizeKey = strlen(key);

	xor_encrypt(plaintext, size, ciphertext, key, sizeKey);

	xor_decrypt(ciphertext, size, decodetext, key, sizeKey);
 
	xor_crack_1byte(ciphertext, size, cracktext);

	printf("%s\n\n", plaintext);
	printf("%s\n\n", ciphertext);
	printf("%s\n\n", decodetext);
	printf("%s\n\n", cracktext);

	FILE *f = fopen("ciphertext", "w");
	fprintf(f, ciphertext);
	fclose(f);

	return 0;
}