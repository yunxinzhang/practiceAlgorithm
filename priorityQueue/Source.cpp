#include <queue>
#include <vector>
#include <algorithm>
#include <xfunctional>
#include <iostream>

using namespace std;
class vertex {
public:
	int x;
	int y;
	vertex(int a, int b):x(a),y(b){}
	bool operator<(const vertex & v) const {
		if (x < v.x)return true;
		else if (x == v.x) return y < v.y ? true : false;
		return false;
	}
};

//_Pred --> cmp		小于的否定	&&	大于的否定

//return (!_Pred(_Left, _Right)
//	? false
//	: _Pred(_Right, _Left)
//	? (_DEBUG_ERROR2("invalid comparator", _File, _Line), true)
//	: true);

struct cmp {
	bool operator()(const vertex &v1, const vertex & v2) {
		if (v1.x < v2.x)return false;
		else if (v1.x == v2.x) return v1.y <= v2.y ? false : true;
		return true;
	}
};

void test1() {
	priority_queue<int> pq;
	pq.push(10);
	pq.push(33);
	pq.push(4);
	while (!pq.empty()) {
		cout << pq.top() << endl;
		pq.pop();
	}
	priority_queue<int, vector<int>, greater<int> > pq2;
	pq2.push(10);
	pq2.push(33);
	pq2.push(4);
	while (!pq2.empty()) {
		cout << pq2.top() << endl;
		pq2.pop();
	}
}
void test2() {
	priority_queue<vertex> pq;
	pq.push(vertex(1, 2));
	pq.push(vertex(2, 3));
	pq.push(vertex(0, 2));
	pq.push(vertex(1, 1));
	pq.push(vertex(1, 2));
	while (!pq.empty()) {
		cout << pq.top().x <<","<<pq.top().y << endl;
		pq.pop();
	}

	priority_queue<vertex, vector<vertex>, cmp> pq2;
	pq2.push(vertex(1, 2));
	pq2.push(vertex(2, 3));
	pq2.push(vertex(0, 2));
	pq2.push(vertex(1, 1));
	pq2.push(vertex(1, 2));
	while (!pq2.empty()) {
		cout << pq2.top().x << "," << pq2.top().y << endl;
		pq2.pop();
	}
}
int main() {
	test2();
}