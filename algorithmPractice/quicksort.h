#ifndef INC_07_QUICK_SORT_THREE_WAYS_QUICKSORT_H
#define INC_07_QUICK_SORT_THREE_WAYS_QUICKSORT_H

#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;
namespace liusort {
	template<typename T>
	void insertionSort(T arr[], int n) {

		for (int i = 1; i < n; i++) {

			T e = arr[i];
			int j;
			for (j = i; j > 0 && arr[j - 1] > e; j--)
				arr[j] = arr[j - 1];
			arr[j] = e;
		}

		return;
	}

	// ��arr[l...r]��Χ��������в�������
	template<typename T>
	void insertionSort(T arr[], int l, int r) {

		for (int i = l + 1; i <= r; i++) {

			T e = arr[i];
			int j;
			for (j = i; j > l && arr[j - 1] > e; j--)
				arr[j] = arr[j - 1];
			arr[j] = e;
		}

		return;
	}


	// ��arr[l...r]���ֽ���partition����
	// ����p, ʹ��arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
	template <typename T>
	int _partition(T arr[], int l, int r) {

		// �����arr[l...r]�ķ�Χ��, ѡ��һ����ֵ��Ϊ�궨��pivot
		swap(arr[l], arr[rand() % (r - l + 1) + l]);

		T v = arr[l];
		int j = l;
		for (int i = l + 1; i <= r; i++)
			if (arr[i] < v) {
				j++;
				swap(arr[j], arr[i]);
			}

		swap(arr[l], arr[j]);

		return j;
	}

	// ˫·���������partition
	// ����p, ʹ��arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
	template <typename T>
	int _partition2(T arr[], int l, int r) {

		// �����arr[l...r]�ķ�Χ��, ѡ��һ����ֵ��Ϊ�궨��pivot
		swap(arr[l], arr[rand() % (r - l + 1) + l]);
		T v = arr[l];

		// arr[l+1...i) <= v; arr(j...r] >= v
		int i = l + 1, j = r;
		while (true) {
			// ע������ı߽�, arr[i] < v, ������arr[i] <= v
			// ˼��һ��Ϊʲô?
			while (i <= r && arr[i] < v)
				i++;

			// ע������ı߽�, arr[j] > v, ������arr[j] >= v
			// ˼��һ��Ϊʲô?
			while (j >= l + 1 && arr[j] > v)
				j--;

			// ��������������߽���趨, �е�ͬѧ�ڿγ̵��ʴ����кܺõĻش�:)
			// ��ҿ��Բο�: http://coding.imooc.com/learn/questiondetail/4920.html

			if (i > j)
				break;

			swap(arr[i], arr[j]);
			i++;
			j--;
		}

		swap(arr[l], arr[j]);

		return j;
	}

	// ��arr[l...r]���ֽ��п�������
	template <typename T>
	void _quickSort(T arr[], int l, int r) {

		// ����С��ģ����, ʹ�ò�����������Ż�
		if (r - l <= 15) {
			insertionSort(arr, l, r);
			return;
		}

		// ����˫·���������partition
		int p = _partition2(arr, l, r);
		_quickSort(arr, l, p - 1);
		_quickSort(arr, p + 1, r);
	}

	template <typename T>
	void quickSort(T arr[], int n) {

		srand(time(NULL));
		_quickSort(arr, 0, n - 1);
	}

}

#endif //INC_07_QUICK_SORT_THREE_WAYS_QUICKSORT_H
