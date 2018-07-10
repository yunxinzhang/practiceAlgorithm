#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

class edge {
public:
	int a;
	int b;
	double w;
	
	edge(int a, int b, double w):a(a),b(b),w(w){}
};
static bool cmp(edge a, edge b) { return a.w < b.w; };
class graph {
public:
	int v;
	int e;
	int ** matrix; 
	int *type;
	vector<edge> es;
	graph() { v = 0; e = 0; matrix = NULL; type = NULL; }
	graph(int v, int e):v(v),e(e){
		matrix = new int *[v];
		for (int i = 0; i < v; ++i) {
			matrix[i] = new int[v];
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
	void readGraph() {
		ifstream fin("map.txt");
		assert(fin);
		fin >> v >> e;
		matrix = new int *[v];
		for (int i = 0; i < v; ++i) {
			matrix[i] = new int[v];
			for (int j = 0; j < v; ++j) {
				matrix[i][j] = 0;
			}
		}
		type = new int[v];
		for (int i = 0; i < v; ++i) {
			type[i] = i;
		}
		int a, b;
		double w;
		for (int i = 0; i < e; ++i) {
			fin >> a >> b >> w;
			matrix[a][b] = w;
			matrix[b][a] = w;
			es.push_back(edge(a, b, w));
		}
		fin.close();
	}
	int getRoot(int ind) {
		while (type[ind] != ind) {
			ind = type[ind];
		}
		return ind;
	}
	void krusal(vector<edge> & res){
		sort(es.begin(), es.end(), cmp);
		
		for (auto it : es) {
			if (getRoot(it.a) != getRoot(it.b)) {
				res.push_back(it);
				if (getRoot(it.a) != it.a) {
					type[it.b] = type[it.a];
				}
				else {
					type[it.a] = type[it.b];
				}
				
			}
		}
		delete[] type;
	}
};

int main() {
	graph g;
	g.readGraph();
	vector<edge> res;
	g.krusal(res);

	for (auto it : res) {
		cout << it.a << ", " << it.b << " " << it.w << endl;
	}
	getchar();
}