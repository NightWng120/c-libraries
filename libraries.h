#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#ifndef LIBRARY
#define LIBRARY

char * fileRead(char * name){
	char* output;
	FILE*fp = fopen(name, "r");
	int length;
	char c;
	int i = 0;

	if(fp == NULL) return NULL;

	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	output = (char *)malloc(sizeof(char) * (length + 1));
	// Need + 1 to length to account for string null terminator, '\0'

	while((c = fgetc(fp)) != EOF){
		output[i] = c;
		i++;
	}

	output[i] = '\0';
	fclose(fp);

	return output;
}


void printArray(int * array, int length){
	printf("[");
	for(int i = 0; i < length; i++){
		if(i + 1 == length){
			printf("%d", array[i]);
			break;
		}
		printf("%d, ", array[i]);
	}
	printf("]\n");
}


// *************************** Hash table data structure ***************************
typedef struct{
	int key;
	int data;
}DataItem;

int hashCode(int key, int size){
	return key % size;
}

void init(int size, DataItem * table[size]){
	for(int i = 0; i < size; i++){
		table[i] = NULL;
	}
}
void insert(int key, int data, int size, DataItem * table[size]){
	DataItem * item = (DataItem *) malloc(sizeof(DataItem));
	item->key = key;
	item->data = data;
	int hashIndex = hashCode(key, size);
	if(table[hashIndex] != NULL){
		return;
	}

	table[hashIndex] = item;
}
bool search(int key, int size,  DataItem * table[size]){
	int hashIndex = hashCode(key, size);
	if(table[hashIndex] != NULL && table[hashIndex]->key == key){
		return true;;
	}

	return false;
}

// *************************** end Hash table data structure *************************** 

bool isIn(int num, int * array, int length){
	for(int i = 0; i < length; i++){
		if(num == array[i]){
			return true;
		}
	}
	return false;
}


int * copyInt(int * input, int length){
	int * copy = (int*)malloc(length * sizeof(int));
	int * start = copy;


	*copy = *input;
	copy++, input++;

	while(length > 1){
		//printf("Length: %d", length);
		*copy = *input;
		copy++, input++, length--;
	}

	return start;
}


int * mergeSort(int * array, int n){
	int * temp = array;
	int * A;
	int * B;
	int * startA;
	int * startB;
	int lenB = 0;
	int lenA = 0;
	int i = 0;
	int j = 0;
	//printf("\n\n-----------------------\nFirst element of current array: %d\nLength: %d\n-----------------------\n\n", *array, n);

	if(n < 2){
		//printf("\nReturned array\n");
		return array;
	}

	else if(n%2 == 1){
		//printf("\n\n-----------------------\nFirst element of current array: %d\nLength: %d\n-----------------------\n\n", *array, n);
		lenA = (n - 1)/2;
		lenB = (n - 1)/2 + 1;
		A = mergeSort(copyInt(array, lenA), lenA);
		startA = A;
		B = mergeSort(copyInt(array + lenA, lenB), lenB);
		startB = B;
	}

	else{
		//printf("\n\n-----------------------\nFirst element of current array: %d\nLength: %d\n-----------------------\n\n", *array, n);
		lenA = n/2;
		lenB = n/2;
		A = mergeSort(copyInt(array, lenA), lenA);
		startA = A;
		B = mergeSort(copyInt(array + lenB, lenB), lenB);
		startB = B;
	}

	for(int k = 0; k < n; k++){
		if(A == NULL){

			*temp = *B;
			if(j + 1 == lenB) B = NULL;
			else j++, B++;
		}

		else if(B == NULL){

			*temp = *A;
			if(i + 1 == lenA) A = NULL;
			else i++, A++;
		}

		else if(A != NULL && *A < *B){
			*temp = *A;
			if(i + 1 == lenA) A = NULL;
			else i++, A++;

		}

		else if(B != NULL && *B < *A){
			*temp = *B;
			if(j + 1 == lenB) B = NULL;
			else j++, B++;

		}

		else if(*B == *A){
			*temp = *B;
			if(j + 1 == lenB) B = NULL;
			else j++, B++;
		}

		temp++;
	}

	free(startA);
	free(startB);
	return array;
}

char * copyChar(char * input, int length){
	char * copy = (char*)malloc(length * sizeof(char));
	char * start = copy;


	*copy = *input;
	copy++, input++;

	while(length > 1){
		//printf("Length: %d", length);
		*copy = *input;
		copy++, input++, length--;
	}

	return start;
}

int stringLength(char * string){
	char * output;
	int length = 0;
	while(*string != '\0'){
		length++;
		string++;
	}

	return length;
}
char ** splitString(char * string, int num){
	int len = stringLength(string);
	if(num >= len)
		return NULL;
	printf("meme\n");
	char ** split = (char**)malloc(2 * sizeof(char *));
	int size = 0;
	split[0] = (char*)malloc(len * sizeof(char));
	split[1] = (char*)malloc(len * sizeof(char));
	for(int i = 0; i < num; i++){
		split[0][i] = string[i];
		//printf("%c\n", split[0][i]);
		size++;
	}
	split[0][size] = '\0';
	for(int i = 0; i < len - num; i++){
		split[1][i] = string[size + i];
		//printf("%c\n", split[1][i]);
	}
	split[1][len - num] = '\0';
	return split;
}

char * toString(int num){
	int temp = num;
	int size;
	while(temp != 0){
		temp/=10;
		size++;
	}
	size++;
	char * string = (char*)malloc(size*sizeof(char));
	string[size - 1] = '\0';
	size--;
	for(int i = 0; i < size; i++){
		string[size-i-1] = '0' + num%10;
		num -= num%10;
		num/=10;
	}
	return string;
}
char * toStringDouble(double num){
	double temp = num;
	int size;
	while(temp != 0.0){
		temp -= fmod(temp, 10.0); 
		temp/=10.0;
		size++;
	}
	size++;
	char * string = (char*)malloc(size*sizeof(char));
	string[size - 1] = '\0';
	size--;
	for(int i = 0; i < size; i++){
		string[size-i-1] = '0' + fmod(num, 10.0); 
		num -= fmod(num, 10.0); 
		num/=10.0;
	}
	return string;
}


#endif
