#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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


bool isIn(int num, int * array, int length){
	for(int i = 0; i < length; i++){
		if(num == array[i]){
			printf("\n\n%d\n", num);
			printf("v\n");
			printArray(array, length);
			return true;
		}
	}
	return false;
}
// *************************** end Hash table data structure *************************** 


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


#endif
