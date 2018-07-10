#include "sort.h"
#include "sortHelper.h"
#include "quicksort.h"

int main() {
	int* arr = NULL;//指针必须初始化
	int* arr2 = arr;
	int* arr3 = arr;
	int* arr4 = arr;
	int n = 800000;
	int range = 800000;
	sortHelper::getRandomNumbers(arr, n,range); // 指针传引用。开辟空间真正的指针指向开辟空间的地址。
	sortHelper::copyArray(arr, arr2, n);
	sortHelper::copyArray(arr, arr3, n);
	sortHelper::copyArray(arr, arr4, n);
	//sortHelper::testSort(sortMethods::bubbleSort, arr, n);	// 太慢
	sortHelper::testSort(sortMethods::mergeSort, arr, n);
	sortHelper::testSort(sortMethods::mergeSort2, arr2, n);
	//sortHelper::testSort(sortMethods::selectSort, arr2, n);

	//sortHelper::testSort(sortMethods::insertSort, arr3, n);
	//sortHelper::testSort(sortMethods::quickSort, arr4, n);
	sortHelper::testSort(liusort::quickSort, arr4, n);
	//sortHelper::print(arr3, n);
	sortHelper::testSort(sortMethods::quickSort2, arr3, n);
	//sortHelper::print(arr4, n);
	
	//sortHelper::print(arr3, n);
	getchar();
}