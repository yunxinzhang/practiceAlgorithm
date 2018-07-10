#pragma once
#include <iostream>
#include <ctime>
#include <random>
using namespace std;

namespace sortMethods {

	template<typename T>
	void bubbleSort(T *arr, int n) {
		for (size_t i = n-1; i >0 ; --i) {
			for (size_t j = 0; j < i; ++j) {
				if (arr[j] > arr[j+1]) {
					swap(arr[j], arr[j + 1]);//std::swap
				}
			}
		}
	}
	
	template<typename T>
	void selectSort(T *arr, int n) {
		int index;
		for (size_t i = 0; i <n ; ++i) {
			index = i;
			for (size_t j = i; j < n; ++j) {
				if (arr[j] < arr[index]) {
					index = j;
				}
			}
			swap(arr[i], arr[index]);
		}
	}

	template<typename T>
	void insertSort(T *arr, int n) {//数学归纳法
		T temp;
		int j;						//size_t 不要随便用 ************
		for (size_t i = 0; i < n-1; ++i) {
			temp = arr[i+1];
			for (j = i; j >= 0 && arr[j] > temp; --j) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}

	template<typename T>
	static void merge(T *&arr, int start, int mid, int end) {
		int size = end - start + 1;
		T * temp = new T[size];
		for (size_t i = 0; i < size; ++i) {
			temp[i] = arr[i + start];
		}
		int ml = 0, mr = (mid - start + 1), mmid = mid - start;
		for (size_t i = 0; i < end - start + 1; ++i) {
			if (ml > mmid) {
				arr[start+i] = temp[mr++];	// 复制的索引要分清
			}
			else if (mr >= size) {
				arr[start + i] = temp[ml++];
			}
			else {
				if (temp[ml] > temp[mr]) {
					arr[start + i] = temp[mr++];
				}
				else {
					arr[start + i] = temp[ml++];
				}
			}
		}
		delete[] temp;
	}


	template<typename T>
	void __mergeSort(T *& arr, int start, int end) {
		if (start >= end) return;
		int mid = start + (end - start) / 2;
		__mergeSort(arr, start, mid);
		__mergeSort(arr, mid + 1, end);
		if (arr[mid] > arr[mid + 1]) {	// 差不多有序的情况
			merge(arr, start, mid, end);
		}
		
	}

	template<typename T>
	void __mergeSort2(T *& arr, int start, int end) {
		if (start >= end) return;
		if (end - start <= 15) {
			insertSort(arr + start, end - start + 1);
			return;
		}
		int mid = start + (end - start) / 2;
		__mergeSort(arr, start, mid);
		__mergeSort(arr, mid + 1, end);
		merge(arr, start, mid, end);
	}

	template<typename T>
	void mergeSort(T * arr, int n) {
		__mergeSort(arr, 0, n - 1);
	}
	template<typename T>
	void mergeSort2(T * arr, int n) {
		__mergeSort2(arr, 0, n - 1);
	}

	template<typename T>
	void __quickSort(T *& arr, int start, int end) {
		if (start >= end) return;
		if (end - start <= 15) {
			insertSort(arr + start, end - start + 1);
			return;
		}
		int index = rand() % (end - start) + start;
		swap(arr[start], arr[index]);
		// (start, ml] 为 <, (mr,end] 为>
		int ml = start;
		int mr = end;
		int mv = start + 1;
		while (ml < mr) {
			//cout << ml << " " << mr << endl;
			if (arr[mv] > arr[start]) {
				swap(arr[mv], arr[mr--]);
			}
			else {
				swap(arr[mv++], arr[++ml]);
			}
		}
		swap(arr[start], arr[ml]);			//
		__quickSort(arr, start, ml-1);		// 数量减一，必能出递归到底。
		__quickSort(arr, ml + 1, end);
	}

	template<typename T>
	void __quickSort2(T *& arr, size_t start, size_t end) {
		if (start >= end) return;
		if (end - start <= 15) {
			insertSort(arr + start, end - start + 1);
			return;
		}
		swap(arr[start], arr[rand() % (end - start) + start]);
		// (start, ml] 为 <, (mr,end] 为>
		size_t ml = start+1;
		size_t mr = end;
		//int mv = start + 1;
		//while (ml < mr && mv < mr+1) {	// 不同的方式循环条件不一样
		//	//cout << ml << " " << mr << endl;
		//	if (arr[mv] > arr[start]) {
		//		swap(arr[mv], arr[mr--]);
		//	}
		//	else if(arr[mv] < arr[start]) {
		//		swap(arr[mv++], arr[++ml]);
		//	}
		//	else {
		//		++mv;
		//	}
		//}
		while (true) {// 减少不必要的判断
			while (ml <= mr&&arr[ml] < arr[start]) {
				++ml;
			}
			while (mr >= ml && arr[mr] > arr[start]) {
				--mr;
			}
			if(ml<mr)// 减少不必要的交换
				swap(arr[ml++], arr[mr--]);
			else{
				break;
			}
		}
		swap(arr[start], arr[ml-1]);			//
		__quickSort2(arr, start, ml - 2);		// 数量减一，必能出递归到底。
		__quickSort2(arr, ml, end);
	}

	template<typename T>
	void quickSort(T * arr, int n) {
		srand(time(NULL));
		__quickSort(arr, 0, n - 1);
	}
	template<typename T>
	void quickSort2(T * arr, size_t n) {
		srand(time(NULL));
		__quickSort2(arr, 0, n - 1);
	}
}