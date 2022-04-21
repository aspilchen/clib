#include <stdio.h>

#include "dynarrExperiment.h"

#ifndef DYNAR__int__
#define DYNAR__int__
dynarr_declareValueArray(int);
#endif


#ifndef DYNAR__char__
#define DYNAR__char__
dynarr_declareValueArray(char);
#endif

struct testStruct {
	int a;
	int b;
}typedef strct;

typedef strct *asdf;

#ifndef DYNAR__testStruct__PTRS__
#define DYNAR__testStruct__PTRS__
dynarr_declareValueArray(strct);
dynarr_declareValueArray(asdf);
#endif


int main() {
	Dynarr(int) intArr;
	dynarr_init(&intArr);

	Dynarr(char) charArr;
	dynarr_init(&charArr);

	Dynarr(asdf) test;
	dynarr_init(&test);

	strct a = {0, 1};
	strct b = {2, 3};
	strct c = {4, 5};

	dynarr_pushBack(&test, &a);
	dynarr_pushBack(&test, &b);
	dynarr_pushBack(&test, &c);


	strct *ptr;
	for(int i = 0; i < 3; i++) {
		ptr = dynarr_get(&test, i);
		printf("%d %d\n", ptr->a, ptr->b);
	}

	for(char c = 'a'; c <= 'z'; c++) {
		dynarr_pushBack(&charArr, c);
		dynarr_pushBack(&intArr, c);
	}

	printf("printing from char array\n");
	for(int i = 0; i < arrsize(&charArr); i++) {
		printf("%c\n", dynarr_get(&charArr, i));
	}

	printf("printing from int array\n");
	for(int i = 0; i < arrsize(&intArr); i++) {
		printf("%d\n", dynarr_get(&intArr, i));
	}
}