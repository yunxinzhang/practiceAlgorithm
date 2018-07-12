#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
#include <set>
#include <xfunctional>
#include "IndexMinHeap.h"
using namespace std;
class edge2 {
public:
	size_t a;
	size_t b;
	double w;
	edge2(size_t a, size_t b, double w) :a(a), b(b), w(w) {}
	edge2(){}
	bool operator<(const edge2 & e) const {
		return w < e.w;
	}
	bool operator>=(const edge2 & e) const {
		return w >= e.w;
	}
	bool operator<=(const edge2 & e) const {
		return w <= e.w;
	}
	bool operator>(const edge2 & e) const {
		return w > e.w;
	}
};
static bool cmp2(edge2 & a, edge2 & b) { return a.w < b.w; };
class ufs {
public:
	size_t n;
	size_t * parent;
	size_t * rank;
	ufs() {
		parent = NULL;
		rank = NULL;
	}
	ufs(size_t n) : n(n){
		parent = new size_t[n];
		rank = new size_t[n];
		for (size_t i = 0; i < n; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}
	void init(size_t n) {
		this->n = n;
		parent = new size_t[n];
		rank = new size_t[n];
		for (size_t i = 0; i < n; ++i) {
			parent[i] = i;
			rank[i] = 1;
		}
	}
	~ufs(){
		//TODO
	}
	size_t getRoot(size_t x) {
		while (parent[x]!=x) {
			// compress path
			x = parent[x] = parent[parent[x]];
		}
		return x;
	}
	bool isConnected(size_t a, size_t b){
		return getRoot(a) == getRoot(b);
	}
	void unionEntry(size_t a, size_t b) {
		size_t ra = getRoot(a);
		size_t rb = getRoot(b);
		if (ra == rb)return;
		if (rank[ra] > rank[rb]) {
			parent[rb] = ra;
		}
		else if (rank[ra] < rank[rb]) {
			parent[ra] = rb;
		}
		else {
			parent[ra] = rb;
			++rank[rb];
		}
	}
};



class graph2 {
public:
	size_t v;
	size_t e;
	vector<set<pair<size_t,double>>> mat;
	ufs type;
	bool *selected;
	vector<edge2> es;
	graph2() { v = 0; e = 0; selected = NULL; type = NULL; }
	~graph2() {
		//TODO
	}
	void readGraph(const string path) {
		ifstream fin(path);
		assert(fin);
		fin >> v >> e;
		mat.reserve(v);
		for (int i = 0; i < v; ++i) {
			set<pair<size_t, double>> s;
			mat.push_back(s);
		}
		type.init(v);
		size_t  a, b;
		double w;
		for (size_t i = 0; i < e; ++i) {
			fin >> a >> b >> w;
			if (a > b) {
				swap(a, b);
			}
			mat[a].insert(pair<size_t,double>(b,w));
			mat[b].insert(pair<size_t, double>(a, w));
			es.push_back(edge2(a, b, w));
		}
		//show();
		selected = new bool[v];
		for (size_t i = 0; i < v; ++i) {
			selected[i] = false;
		}
		fin.close();
	}
	
	// 不考虑数据结构的流程实现
	void krusal(vector<edge2> & res) {
		sort(es.begin(), es.end(), cmp2);
		for (auto it : es) {
			if (type.getRoot(it.a) != type.getRoot(it.b)) {
				res.push_back(it);
				type.unionEntry(it.a, it.b);
			}
		}
	}
	void show() {
		for (size_t i = 0; i < v; ++i) {
			for (auto it : mat[i]) {
				cout << it.first << "->" <<it.second <<"\t";
			}
			cout << endl;
		}
	}
	// 不考虑数据结构的流程实现
	void prim(vector<edge2> &res) {
		priority_queue<edge2, vector<edge2>, greater<edge2>> pq;
		selected[0] = true;
		for(auto it : mat[0]){
			pq.push(edge2(0, it.first, it.second));
		}
		while (!pq.empty()) {
			edge2 e = pq.top();
			pq.pop();
			if (!selected[e.b]) {
				selected[e.b] = true;
				res.push_back(e);
				for (auto it : mat[e.b]) {
					if (!selected[it.first]) {
						pq.push(edge2(e.b, it.first, it.second));
					}
				}
			}
		}
	}
	// 不考虑数据结构的流程实现
	void prim2(vector<edge2> &res) {
		IndexMinHeap<edge2> pq(v);
		
		selected[0] = true;
		for (auto it : mat[0]) {
			pq.add(it.first,edge2(0, it.first, it.second));
		}
		while (pq.size>0) {
			edge2 e = pq.pop();
			if (!selected[e.b]) {
				selected[e.b] = true;
				res.push_back(e);
				for (auto it : mat[e.b]) {
					if (!selected[it.first]&&pq.reves[it.first + 1] != 0) {
						if(it.second < pq.data[pq.inds[pq.reves[it.first+1]]].w)
							pq.change(it.first, edge2(e.b, it.first, it.second));
					}
					else if (!selected[it.first]) {
						pq.add(it.first,edge2(e.b, it.first, it.second));
					}
				}
			}
		}
	}
};