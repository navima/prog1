#pragma warning(disable:4996)

#include "stdio.h"
#include "string.h"
#include "ctype.h"
#include "stdlib.h"

//https://stackoverflow.com/a/23618467/9281022
char* strlwr_(char *str)
{
	unsigned char *p = (unsigned char *)str;

	while (*p) {
		*p = tolower((unsigned char)*p);
		p++;
	}

	return str;
}

int xor_encrypt(char* source, size_t size, char* destination, char* key, size_t sizeKey)
{
	size_t actual_size = size-1;

	for (size_t i = 0; i < actual_size; i++)
	{
		unsigned char sourceChar = (unsigned char)source[i];
		unsigned char keyChar = (unsigned char)key[i%sizeKey];
		destination[i] = (char)(sourceChar^keyChar);
	}

	destination[actual_size] = 0;

	return 1;
}

int xor_decrypt(char* source, size_t size, char* destination, char* key, size_t sizeKey) { return xor_encrypt(source, size, destination, key, sizeKey); }

unsigned int count_ciphertext[256];
float distribution_ciphertext[256];
int xor_crack_1byte(char* source, size_t size, char* destination)
{
	//Count occurences of characters in the ciphertext
	size_t i = size;
	while (i-->0)
		count_ciphertext[(unsigned char)source[i]]++;


	//Count distribution
	i = 256;
	while (i-->0)
	{
		if (count_ciphertext[i] > 0)
		{
			distribution_ciphertext[i] = (float) count_ciphertext[i] / (float) size;
		}
	}


	//Associating max frequency with space
	int max_cipher_index = 0;

	for (int k = 0; k < 256; k++)
	{
		if (distribution_ciphertext[k] > distribution_ciphertext[max_cipher_index])
			max_cipher_index = k;
	}

	unsigned char key = (unsigned char)' ' ^ (unsigned char)max_cipher_index;


	i = size;
	while (i-- > 0)
		destination[i] = (char)((unsigned char)(source[i])^key);


	return 0;
}

int xor_crack_variable(char* source, size_t size, char* destination, int keyLength)
{
	char **asd = (char**)malloc(sizeof(char*)*keyLength);

	for (int i = 0; i < keyLength; i++)
	{
		asd[i] = (char*)malloc(sizeof(char)*(size / keyLength) + 1 + 1);
	}

	for (int i = 0; i < size; i += keyLength)
	{
		for (int j = 0; j < keyLength; j++)
		{
			asd[j][i / keyLength] = source[i + j];
		}
		
	}

	for (int i = 0; i < keyLength; i++)
	{
		//printf(asd[i]);
		xor_crack_1byte(asd[i], (size / keyLength) + 2, asd[i]);
	}



	for (int i = 0; i < size; i += keyLength)
	{
		for (int j = 0; j < keyLength; j++)
		{
			destination[i+j] = asd[j][i / keyLength];
		}

	}



	return 0;
}

int xor_test()
{

	char plaintext[] = "Why would you want to program? Our civilization runs on software. Without understanding software you are reduced to believing in “magic” and will be locked out of many of the most interesting, profitable, and socially useful technical fields of work. When I talk about programming, I think of the whole spectrum of computer programs from personal computer applications with GUIs (graphical user interfaces), through engineering calculations and embedded systems control applications (such as digital cameras, cars, and cell phones), to text manipulation applications as found in many humanities and business applications.";
	size_t size = strlen(plaintext);
	strlwr_(plaintext);

	char ciphertext[681];
	char decodetext[681];
	char cracktext[681];
	memset(ciphertext, ' ', sizeof ciphertext);
	memset(decodetext, ' ', sizeof decodetext);
	memset(cracktext, ' ', sizeof cracktext);
	ciphertext[680] = 0;
	decodetext[680] = 0;
	cracktext[680] = 0;

	char key[] = {1,2};
	size_t sizeKey = strlen(key);

	xor_encrypt(plaintext, size, ciphertext, key, sizeKey);

	xor_decrypt(ciphertext, size, decodetext, key, sizeKey);
 
	//xor_crack_1byte(ciphertext, size, cracktext);

	xor_crack_variable(ciphertext, size, cracktext, 2);

	printf("%s\n\n", plaintext);
	printf("%s\n\n", ciphertext);
	printf("%s\n\n", decodetext);
	printf("%s\n\n", cracktext);

	FILE *f = fopen("ciphertext", "w");
	fprintf(f, ciphertext);
	fclose(f);

	FILE *g = fopen("plaintext", "w");
	fprintf(g, plaintext);
	fclose(g);


	return 0;
}