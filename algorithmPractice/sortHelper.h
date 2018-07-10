#pragma once
#include <random>
#include <ctime>
#include <cassert>
using namespace std;

namespace sortHelper {
	template<typename T>
	bool isSorted(T *arr, int n) {
		for (size_t i = 0; i < n - 1; ++i) {
			if (arr[i] > arr[i + 1])return false;
		}
		return true;
	}
	void getRandomNumbers(int *& arr, int n, int range) {
		arr = new int[n];
		srand(time(NULL));
		for (size_t i = 0; i < n; ++i) {
			arr[i] = rand() % range;
		}
	}
	template<typename T>
	void print(T * arr, int n) {
		for (size_t i = 0; i < n; ++i) {
			cout << arr[i] << " ";
		}
		cout << endl;
	}

	template<typename T>
	void testSort(void(*sort)(T *ar, int n), T * arr, int n) {
		
		clock_t t1, t2;
		t1 = clock();
		//print(arr, n);
		sort(arr, n);
		t2 = clock();
		// 默认宏
		//cout << (double)(t2 - t1)/CLOCKS_PER_SEC << endl;
		//print(arr, n);
		assert(isSorted(arr, n));
		cout << (t2 - t1)  << endl;
	}
	template<typename T>
	void testSort(void(*sort)(T *ar, size_t n), T * arr, size_t n) {

		clock_t t1, t2;
		t1 = clock();
		//print(arr, n);
		sort(arr, n);
		t2 = clock();
		// 默认宏
		//cout << (double)(t2 - t1)/CLOCKS_PER_SEC << endl;
		//print(arr, n);
		assert(isSorted(arr, n));
		cout << (t2 - t1) << endl;
	}
	void copyArray(int *& from, int *& to, int n) {
		to = new int[n];	// 必须用指针引用，并且开辟新的空间
		//copy(from, from+n, to);
		for (int i = 0; i < n; ++i) {
			to[i] = from[i];
		}
	}

	
}