#include "stdafx.h"
#include <iostream>

class ArrFunctions {
public:
	static void copyArr(int *arr1, int *arr2, int n) {
		for (int i = 0; i < n; i++)
			arr1[i] = arr2[i];
	}

	static void printArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << ", ";
	}

	static void clearArr(int *arr, int n) {
		for (int i = 0; i < n; i++)
			arr[i] = 0;
	}
};