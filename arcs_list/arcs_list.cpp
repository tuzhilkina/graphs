// Лекция 2
// ПРЕДСТАВЛЕНИЕ СЕТЕЙ В КОМПЬЮТЕРЕ
// Упорядоченный список дуг
// дуги упорядочены по исходящей вершине

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class Graph {
public:
	Graph();
	Graph(const int& N, vector<int> i, vector<int> j) : n(N), I(i), J(j) { };
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	void print() const;

private:
	// количество вершин v
    int n{ 6 };
	// начала рёбер
	vector<int> I{ 1, 2, 4, 5, 0, 1, 3, 0, 3 };
	// концы рёбер
	vector<int> J{ 2, 4, 5, 0, 1, 3, 2, 4, 5 };
	// указатель на позицию первого ребра, выходящего из вершины [v]
	vector<int> S;
};

Graph::Graph() {
	for (int i(0); i < n; ++i)
		S.push_back(0);
	// для каждой вершины, кроме последней, 
	// вычислить количество исходящих дуг
	for (const auto& v : I) {
		if (v != n - 1)
			++S[v + 1];
	}
	// для 0 вершины первое ребро находится по индексу 0
	// для остальных вершин индекс находится суммированием количества ребер предыдущих вершин
	for (int i(1); i < n; ++i)
		S[i] += S[i - 1];

	// доступная позиция для вставки ребра из [v]
	vector<int> P(S);

	for (int v(0); v < n - 1; ++v)
		// Начиная от позиции, куда можно поставить дугу из вершины v
		// до конца области, где располагаются ребра из вершины v
		for (int e(P[v]); e < S[v + 1]; ) {
			// если ребро выходит из вершины, область которой мы рассматриваем,
			// то есть ребро стоит на месте, переходим к следующему
			if (I[e] == v) ++e;
			else {
				// выясняем вершину ребра, которое стоит не на своем месте
				int e_v = I[e];
				// ищем позицию, куда надо поставить это ребро
				int e_p = P[e_v];
				// меняем местами
				swap(I[e], I[e_p]);
				swap(J[e], J[e_p]);
				// вычисляем новую позицию для следующего ребра из данной вершины
				++P[e_v];
			}
		}
}

void Graph::print() const {
	std::cout << "I: ";
	for (const auto& it : I)
		std::cout << std::setw(2) << it << " ";
	std::cout << "\nJ: ";
	for (const auto& it : J)
		std::cout << std::setw(2) << it << " ";
}

int main() {
	Graph obj = Graph();
	obj.print();
}