#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef VECTOR
#define VECTOR

/*
 * Must initialize vector struct variable by first assigning it the output from the newVec function in a local
 * scope and then calling the init function by itself.
 *
 * Need to use typedef struct vector VectorInt if you want to use that verbiage in local scope
*/
typedef struct{
	int data;
	int size;
	int capacity;
	int front;
	int back;
	int * start;
}VectorInt;

VectorInt * newVec(int size){
	VectorInt * newStruct = (VectorInt*)malloc(sizeof(VectorInt));
	if(size > 0){
		newStruct->size = size;
		newStruct->capacity = size + 5;
		int * newArr = (int*)malloc(newStruct->capacity * sizeof(int *));
		newStruct->start = newArr;
	}
	else{
		newStruct->size = 1;
		newStruct->capacity = 5;
		int * newArr = (int*)malloc(5 * sizeof(int *));
		newStruct->start = newArr;
	}
	return newStruct;
}

int getVec(VectorInt * vec, int index){
	if(index < vec->size && index >= 0)
		return vec->start[index];
	else
		return -1;
}

void insertVec(VectorInt * vec, int index, int data){
	if(index < vec->size)
		vec->start[index] = data;
	else{
		printf("Invalid index value\n");
	}
}

void pushVec(VectorInt * vec, int index, int data){

	if(index < vec->size){
		if(vec->size + 1 <= vec->capacity){
			vec->size+=1;
			int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
			int i = 0;
			for(i = 0; i < index; i++){
				newArr[i] = vec->start[i];
				//printf("Start element #%d is %d\n", i, newArr[i]);
			}
			//printf("Start element #%d is %d\n", i, newArr[i]);
			newArr[i] = data;
			for(int j = i + 1; j < vec->size; j++){
				newArr[j] = vec->start[j - 1];
				//printf("Start element #%d is %d\n", j, newArr[j]);
			}
			free(vec->start);
			vec->start = newArr;
		}
		else if(index < vec->capacity){
			vec->size+=1;
			vec->capacity += 5;
			int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
			int i = 0;
			for(i = 0; i < index; i++){
				newArr[i] = vec->start[i];
				//printf("Start element #%d is %d\n", i, newArr[i]);
			}
			newArr[i] = data;
			//printf("Start element #%d is %d\n", i, newArr[i]);
			for(int j = i + 1; j < vec->size; j++){
				newArr[j] = vec->start[j - 1];
				//printf("Start element #%d is %d\n", j, newArr[j]);
			}
			free(vec->start);
			vec->start = newArr;
		}
		else{
			printf("Invalid push index %d\n", index);
		}
	}
}

void addBackVec(VectorInt * vec, int data){
	if(vec->size+1 <= vec->capacity){
		vec->start[vec->size] = data;
		vec->size += 1;
	}
	else{
		vec->capacity += 5;
		int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
		int i = 0;
		for(i = 0; i < vec->size; i++){
			newArr[i] = vec->start[i];
		}
		newArr[i] = data;
		free(vec->start);
		vec->start = newArr;
		vec->size += 1;
	}
}

void addFrontVec(VectorInt * vec, int data){
	if(vec->size + 1 <= vec->capacity){
		vec->size += 1;
		int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
		int i = 0;
		newArr[0] = data;
		for(i = 1; i < vec->size; i++){
			newArr[i] = vec->start[i - 1];
		}
		free(vec->start);
		vec->start = newArr;
	}
	else{
		vec->capacity += 5;
		vec->size += 1;
		int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
		int i = 0;
		newArr[0] = data;
		for(i = 1; i < vec->size; i++){
			newArr[i] = vec->start[i - 1];
		}
		free(vec->start);
		vec->start = newArr;
	}
}

void deleteElementVec(VectorInt * vec, int index){
	int i = 0;
	int * newArr = (int*)malloc(vec->capacity * sizeof(int *));
	if(index < vec->size){
		for(i = 0; i < index; i++){
			newArr[i] = vec->start[i];
		}
		for(int j = i + 1; j < vec->size; j++){
			newArr[j] = vec->start[j + 1];
		}
		free(vec->start);
		vec->start = newArr;
		vec->size -= 1;
	}
	else{
		printf("Remove index is invalid\n");
	}
}

void deleteValueVec(VectorInt * vec, int item){
	int * newArr = (int*)malloc(vec->capacity * sizeof(VectorInt));
	int size = vec->size;
	int index = 0;
	for(int i = 0; i < vec->size; i++){
		if(vec->start[i] == item){
			//printf("Removed element %d at index %d\n", vec->start[i], i);
			size -= 1;
			continue;
		}
		else{
			//printf("Added element %d to index %d\n", vec->start[i], index);
			newArr[index] = vec->start[i];
			index += 1;
		}
	}
	free(vec->start);
	vec->start = newArr;
	vec->size = size;
}

int findVec(VectorInt * vec, int item){
	for(int i = 0; i < vec->size; i++){
		if(vec->start[i] == item)
			return i;
	}
}

int * findAllVec(VectorInt * vec, int item){
	int * items = (int*)malloc(vec->size * sizeof(int *));
	memset(items, -1, vec->size * sizeof(int *));
	int index = 0;
	for(int i = 0; i < vec->size; i++){
		if(vec->start[i] == item){
			items[index] = i;
			index+=1;
		}
	}
	return items;
}

void printVec(VectorInt * vector){
	printf("[");
	for(int i = 0; i < vector->size; i++){
		if(vector->size == 1){
			printf("%d]", vector->start[i]);
		}
		else if(i + 1 == vector->size){
			printf(", %d]", vector->start[i]);
		}
		else if(i == 0)
			printf("%d", vector->start[i]);
		else{
			printf(", %d", vector->start[i]);
		}
	}
	printf("\n");
}

//void printArray(int * array, int size){
//	//Input negative value for size for an array of undefined size
//	if(size < 0){
//		int i = 0;
//		printf("[");
//		while(array[i] >= 0){
//			if(array[i + 1] < 0){
//				printf("%d]\n", array[i]);
//			}
//			else
//				printf("%d, ", array[i]);
//			i++;
//		}
//		return;
//	}
//
//	printf("[");
//	for(int i = 0; i < size; i++){
//		if(i + 1 == size){
//			printf("%d", array[i]);
//			break;
//		}
//		printf("%d, ", array[i]);
//	}
//	printf("]\n");
//}

int size(VectorInt * vec){
	return vec->size;
}

int capacity(VectorInt * vec){
	return vec->capacity;
}

bool isEmptyVec(VectorInt * vec){
	if(vec->size > 0){
		return true;
	}
	else{
		return false;
	}
}

#endif
