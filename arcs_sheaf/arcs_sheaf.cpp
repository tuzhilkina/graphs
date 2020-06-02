// Лекция 2
// ПРЕДСТАВЛЕНИЕ СЕТЕЙ В КОМПЬЮТЕРЕ
// Списки пучков дуг

#include <iostream>
#include <array>
#include <iomanip>

using namespace std;

class Graph {
public:
	Graph();
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	void print() const;

private:
	// количество вершин v
	static const int n{ 5 };
	// количество ребер e
	static const int m{ 8 };
	// начала рёбер
	array<int, m> I{ 1, 2, 4, 3, 0, 2, 4, 3 };
	// концы рёбер
	array<int, m> J{ 3, 3, 0, 0, 1, 1, 6, 4 };
	// первое ребро, выходящее из вершины [v]
	array<int, n> H{ 0 };
	// следующее ребро, выходящее из той же вершины, откуда выходит ребро [e]
	array<int, m> L{ 0 };
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	// для каждого ребра k
	for (int e(0); e < m; ++e) {
		int v = I[e]; // вершина начала
		L[e] = H[v]; // добавить следующее ребро после e, которое так же выходит из v
		H[v] = e; // добавить первое ребро, выходящее из вершины v
	}
	print();
}

void Graph::print() const {
	cout << "I: ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(2) << I[i] << " ";
	cout << "\nJ: ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(2) << J[i] << " ";
	cout << "\nH: ";
	for (ptrdiff_t i(0); i < n; ++i)
		cout << setw(2) << H[i] << " ";
	cout << "\nL: ";
	for (ptrdiff_t i(0); i < m; ++i) 
		cout << setw(2) << L[i] << " ";
}



int main() {
	Graph obj = Graph();
}