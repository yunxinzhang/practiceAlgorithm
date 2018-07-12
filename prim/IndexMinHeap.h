#pragma once
#include <iostream>
#include <cassert>
using namespace std;

// 速度从2446-->24是因为减少了复制类的开销？
// 思路简单，具体的细节实现略繁琐
template<typename T>
class IndexMinHeap {
public:
	size_t capacity;
	size_t size;
	size_t* inds;
	size_t* reves;
	T* data;
	IndexMinHeap(size_t capacity):capacity(capacity+1){
		size = 0;
		inds = new size_t[capacity+1];
		for (size_t i = 0; i < capacity + 1; ++i) {
			inds[i] = INT_MAX;
		}
		data = new T[capacity+1];
		reves = new size_t[capacity + 1];
		for (size_t i = 0; i <= capacity; ++i) {
			reves[i] = 0;
		}
	}
	void shiftUp(size_t p) {
		while (p>1 && data[inds[p/2]] > data[inds[p]]) {
			swap(inds[p], inds[p/2]);
			reves[inds[p]] = p;
			reves[inds[p / 2]] = p / 2;
			p /= 2;
		}
	}
	void add(size_t i ,const T & t) {
		data[++i] = t;
		inds[size+1] = i;
		reves[i] = size + 1;
		++size;
		shiftUp(size);
	}
	void shiftDown(size_t p) {
		while (2 * p <= size) {
			size_t j = 2 * p;
			if (j + 1 <= size && data[inds[j]] > data[inds[j + 1]]) {
				j += 1;
			}
			if (data[inds[j]] >= data[inds[p]])
				break;
			swap(inds[p], inds[j]);
			reves[inds[p]] = p;
			reves[inds[j]] = j;
			p = j;
		}
	}
	void change(int i, T t) {
		
		i += 1;
		assert(i >= 1 && i <= capacity && reves[i] !=0);
		data[i] = t;
		size_t j = reves[i];
		shiftUp(j);
		shiftDown(j);
	}
	const T& pop() {
		T &t = data[inds[1]];
		swap(inds[1], inds[size]);
		reves[inds[1]] = 1;
		reves[inds[size]] = 0;
		--size;
		shiftDown(1);
		
		return t;
	}
	size_t popInd() {
		size_t res = inds[1]-1;
		swap(inds[1], inds[size]);
		reves[inds[1]] = 1;
		reves[inds[size]] = 0;
		--size;
		shiftDown(1);

		return res;
	}
	T * getData(int i) {
		return &data[i+1];
	}
	~IndexMinHeap() {
		//TODO
	}
};