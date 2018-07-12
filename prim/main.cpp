#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <queue>
#include <ctime>
#include <string>
#include "graphAdjTable.h"
#include "IndexMinHeap.h"
using namespace std;

class edge {
public:
	int a;
	int b;
	double w;
	
	edge(int a, int b, double w):a(a),b(b),w(w){}
	bool operator < (const edge & e) const {
		return w > e.w;
	}
	bool operator >= (const edge & e) const {
		return w <= e.w;
	}
};

static bool cmp(edge a, edge b) { return a.w < b.w; };
struct cmp2
{
	bool operator()(edge &a, edge &b) const
	{
		//因为优先出列判定为!cmp，所以反向定义实现最小值优先
		return a.w > b.w;
	}
};
class graph {
public:
	int v;
	int e;
	double ** matrix; 
	int *type;
	int *rank;
	bool *selected;
	vector<edge> es;
	graph() { v = 0; e = 0; matrix = NULL; type = NULL; }
	graph(int v, int e):v(v),e(e){
		selected = new bool[v];
		for (int i = 0; i < v; ++i) {
			selected[i] = false;
		}
		matrix = new double *[v];
		for (int i = 0; i < v; ++i) {
			matrix[i] = new double[v];
			for (int j = 0; j < v; ++j) {
				matrix[i][j] = 0;
			}
		}
		type = new int[v];
		for (int i = 0; i < v; ++i) {
			type[i] = i;
		}
	}
	~graph() {
		//TODO
	}
	size_t getRoot(size_t x) {
		while (type[x] != x) {
			// compress path
			x = type[x] = type[type[x]];
		}
		return x;
	}
	bool isConnected(size_t a, size_t b) {
		return getRoot(a) == getRoot(b);
	}
	void unionEntry(size_t a, size_t b) {
		size_t ra = getRoot(a);
		size_t rb = getRoot(b);
		if (ra == rb)return;
		if (rank[ra] > rank[rb]) {
			type[rb] = ra;
		}
		else if (rank[ra] < rank[rb]) {
			type[ra] = rb;
		}
		else {
			type[ra] = rb;
			++rank[rb];
		}
	}
	void readGraph(const string path) {
		ifstream fin(path);
		assert(fin);
		fin >> v >> e;
		matrix = new double *[v];
		for (int i = 0; i < v; ++i) {
			matrix[i] = new double[v];
			for (int j = 0; j < v; ++j) {
				matrix[i][j] = 0;
			}
		}
		type = new int[v];
		rank = new int[v];
		for (int i = 0; i < v; ++i) {
			type[i] = i;
			rank[i] = 1;
		}
		int a, b;
		double w;
		for (int i = 0; i < e; ++i) {
			fin >> a >> b >> w;
			matrix[a][b] = w;
			matrix[b][a] = w;
			es.push_back(edge(a, b, w));
		}
		//show();
		selected = new bool[v];
		for (int i = 0; i < v; ++i) {
			selected[i] = false;
		}
		fin.close();
	}
	
	// 不考虑数据结构的流程实现
	void krusal(vector<edge> & res){
		sort(es.begin(), es.end(), cmp);
		
		for (auto it : es) {
			if (getRoot(it.a) != getRoot(it.b)) {
				res.push_back(it);
				unionEntry(it.a, it.b);
				
			}
		}
		delete[] type;
	}
	void show() {
		for (int i = 0; i < v; ++i) {
			for (int j = 0; j < v; ++j) {
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
	// 不考虑数据结构的流程实现
	void prim(vector<edge> &res) {
		double min;
		int ind;
		priority_queue<edge> pq;
		selected[0] = true;
		for (int i = 0; i < v; ++i) {
			if (matrix[0][i] > 0) {
				pq.push(edge(0, i, matrix[0][i]));
			}
		}
		while (pq.size() > 0) {
			edge e = pq.top();
			pq.pop();
			if (!selected[e.b]) {
				selected[e.b] = true;
				res.push_back(e);
				for (int j = 0; j < v; ++j) {
					if (matrix[e.b][j] != 0 && !selected[j]) {
						pq.push(edge(e.b, j, matrix[e.b][j]));
					}
				}
			}
			else {
				continue;
			}
		}
	}
};

void test() {
	//priority_queue<int> pq;
	//pq.push(1);


	graph g;
	g.readGraph("1.txt");
	//g.show();
	vector<edge> res;
	
	clock_t t1, t2, t3;
	t1 = clock();
	g.krusal(res);
	//t2 = clock();
	//g.prim(res);
	t2 = clock();
	double ss = 0;
	int ccc = 0;
	for (auto it : res) {
		//cout << it.a << ", " << it.b << " " << it.w << endl;
		++ccc;
		ss += it.w;
	}
	cout <<"time >>"<< t2 - t1 << endl;
	cout <<ccc <<" "<< ss << endl;
}
void test2() {
	graph2 g;
	g.readGraph("1.txt");
	//g.show();
	vector<edge2> res;

	clock_t t1, t2;
	t1 = clock();
	g.krusal(res);
	//g.prim2(res);
	t2 = clock();
	double ss = 0;
	int ccc = 0;
	for (auto it : res) {
		//cout << it.a << ", " << it.b << " " << it.w << endl;
		++ccc;
		ss += it.w;
	}
	cout << "time >> "<<t2 - t1 << endl;
	cout << ccc << " " << ss << endl;
}

void test3() {
	IndexMinHeap<size_t> imh(10);
	imh.add(1, 9);
	imh.add(2, 7);
	imh.add(6, 3);
	size_t t;
	while (imh.size > 0) {
		t = imh.pop();
		cout << t << endl;
	}
	for (int i = 0; i <= imh.capacity; ++i) {
		cout << imh.data[i] << endl;
	}
}
int main() {
	test();
	/*edge2 e1(3, 4, 0.5);
	edge2 e2(4, 2, 0.3);
	cout << (e1 < e2) << endl;
	cout << (e1>= e2) << endl;*/
}