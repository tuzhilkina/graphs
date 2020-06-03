// Лекция 6
// ЗАДАЧА ПОСТРОЕНИЯ КРАТЧАЙШИХ ПУТЕЙ
// Реализация алгоритма поиска в ширину

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

class Graph {
public:
	Graph();
	Graph(const int& i_v_) : i_v(i_v_) { Graph();	};
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	void print() const;

private:
	// количество рёбер
	static const int m{ 13 };
	// количество вершин
	static const int n{ 7 };
	// Начало ребра e
	std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// Конец ребра 
	std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Номер первого ребра, выходящего из вершины [v]
	array<int, n> H{ 0 };
	// Номер следующего ребра, которое выходит из той же вершины, что и [e]
	array<int, m> L{ 0 };
	// расстояние от исходной вершины i_v до вершины i
	array<int, n> R{ 0 };
	// модифицированный список предков, хранит номер дуги, входящей в вершину i
	array<int, n> P{ 0 };
	// очередь вершин для просмотра
	array<int, n> Q{ 0 };
	// корень дерева кратчайших путей
	const int i_v{ 0 };
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = n;
	R[i_v] = 0;
	for (auto& it : P) it = -2;
	P[i_v] = -1;
	Q[0] = i_v; // начальная вершина - первая в очереди на просмотр
	int read(0); // откуда читать
	int	write(1); // куда писать

	for (int e(0); e < m; ++e) {
		int v = I[e]; // вершина, из которой выходит ребро e
		L[e] = H[v]; // добавляется следующее ребро из данной вершины
		H[v] = e; // данной ребро становится первым выходящим из данной вершины
	}

	// пока очередь не пуста
	while (read < write) {
		// берем вершину из очереди для просмотра
		int curr_v(Q[read]);
		++read;

		// Просмотр дуг, выходящих из текущей вершины
		for (int e(H[curr_v]); e != -1; e = L[e]) {
			int next_v = J[e]; // Противоположная вершина
			// Если следующая вершина не помечена
			if (R[next_v] == n) {
				R[next_v] = R[curr_v] + 1; //Расстояние до следующей на 1 больше, чем до текущей
				P[next_v] = e; //Последняя дуга на пути из начальной вершины в следующую после текущей
				Q[write] = next_v; //Помещаем следующую вершину в очередь на просмотр
				++write;
			}
		}
	}
}

void Graph::print() const{
	std::cout << "   ";
	for (int i(0); i < m; ++i)
		std::cout << setw(2) << i << " ";
	std::cout << "\nI: ";
	for (const auto& it : I)
		std::cout << setw(2) << it << " ";
	std::cout << "\nJ: ";
	for (const auto& it : J)
		std::cout << setw(2) << it << " ";
	std::cout << "\nP: ";
	for (const auto& it : P)
		std::cout << setw(2) << it << " ";
	std::cout << "\nR: ";
	for (const auto& it : R)
		std::cout << setw(2) << it << " ";
	std::cout << "\n";
}

int main() {
	Graph obj{ Graph() };
	obj.print();
}