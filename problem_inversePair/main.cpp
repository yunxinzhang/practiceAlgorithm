#include <iostream>
#include <ctime>
#include <random>
using namespace std;
template <typename T>

// Ö±½ÓÊý
size_t countInversePair(T *arr, size_t n) {
	size_t cnt = 0;
	for (size_t i = 0; i < n-1; ++i) {
		for (size_t j = i + 1; j < n; ++j) {
			if (arr[i] > arr[j])++cnt;
		}
	}
	return cnt;
}
size_t mcnt = 0;
template <typename T>
void merge(T *& arr, size_t l, size_t mid, size_t r) {
	T * narr = new T[r - l + 1];
	for (size_t i = 0; i < r - l + 1; ++i) {
		narr[i] = arr[l+i];
	}
	size_t ml  = 0, mr = mid+1-l;
	for (size_t i = 0; i < r - l + 1; ++i) {
		if (ml<=mid && mr <=r) {
			if (narr[ml] > narr[mr]) {
				mcnt += (mid - l - ml + 1);
				arr[i] = narr[mr++];
			}
			else {
				arr[i] = narr[ml++];
			}
			
		}
		else if(ml<=mid){
			arr[i] = narr[ml++];
		}
		else {
			arr[i] = narr[mr++];
		}
	}
	delete narr;
}
template <typename T>
void mergeCount(T *& arr, size_t l, size_t r) {
	if (l == r) return;
	size_t mid = (l + r) / 2;
	mergeCount(arr, l, mid);
	mergeCount(arr, mid + 1, r);
	merge(arr, l, mid, r);
}

void getRandomArray(int *&arr, size_t n, size_t upperLimit) {
	arr = new int[n];
	srand(time(NULL));
	for (size_t i = 0; i < n; ++i) {
		arr[i] = rand() % upperLimit;
	}
	//delete[] arr;
}



void print(int *arr, int n) {
	for(size_t i = 0; i < n; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
int main() {
	int *arr;
	size_t num = 4;
	getRandomArray(arr, num, num);
	print(arr, num);
	cout << countInversePair(arr, num) << endl;
	mergeCount(arr, 0, num - 1);
	cout << mcnt << endl;
	getchar();
}