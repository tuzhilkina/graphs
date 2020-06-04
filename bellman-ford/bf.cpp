// Лекция 7
// ЗАДАЧА ПОСТРОЕНИЯ КРАТЧАЙШИХ ПУТЕЙ
// АЛГОРИТМ БЕЛЛМАНА - ФОРДА
// построение дерева кратчайших путей на сети
// с произвольными(в т.ч. c	отрицательными) длинами дуг.
// отрицательных циклов в сети нет.

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
	// Начало ребра
	std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// Конец ребра
	std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Длина ребра
	std::array<int, m> C{ 9, 6, 9, 4, 8, 6, 7, 3, 5, 2, 4, 3, 4 };
 	// Номер первого ребра, выходящего из вершины [v]
	array<int, n> H{ 0 };
	// Номер следующего ребра, которое выходит из той же вершины, что и [e]
	array<int, m> L{ 0 };
	// расстояние от исходной вершины i_v до вершины [v]
	array<int, n> R{ 0 };
	// модифицированный список предков, хранит номер дуги, входящей в вершину [v]
	array<int, n> P{ 0 };
	// корень дерева кратчайших путей
	const int i_v{ 0 };
}; 

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (int e(0); e < m; ++e) {
		int v(I[e]);
		L[e] = H[v];
		H[v] = e;
	}
	for (auto& it : R) it = numeric_limits<int>::max();
	for (auto& it : P) it = -2; // все вершины недоступны
	R[i_v] = 0; // расстояние от начальной вершины до самой себя
	P[i_v] = -1; // у начальной вершины нет предка

	// очередь вершин для просмотра в виде списка
	// если вершина [v] вне очереди, то Q[v] = -2
	// если вершина [v] в очереди, то Q[v] = номер следующей после v вершины
	// если вершина [v] - последняя, то Q[v] = -1
	array<int, n> Q{ 0 };
	for (auto& it : Q) it = -2; // все вершины вне очереди
	int h_Q = i_v; // начало очереди
	int t_Q = i_v; // конец очереди
	Q[i_v] = -1;
 
	// пока очередь не пуста
	while (h_Q != -1) {
		int curr_v(h_Q); //текущая вершина для просмотра
		h_Q = Q[h_Q]; // новое начало очереди - вершина, следующая после предыдущего начала
		Q[curr_v] = -2; // текущая вершина теперь вне очереди

		// просмотр ребер e, выходящих из текущей вершины
		for (int e(H[curr_v]); e != -1; e = L[e]) {
			int next_v(J[e]); // вершина на другом конце ребра
			int r_n(R[next_v]);
			// если  путь, проходящий через текущую вершину, короче
			// чем текущий путь до следующей вершины			
			if (R[curr_v] + C[e] < r_n) {
				R[next_v] = R[curr_v] + C[e]; // новое расстояние до следующей вершины
				P[next_v] = e; // ребро, входящее в следующую вершину, - текущее

				// если следующая вершина вне очереди
				if (Q[next_v] == -2) {
					// добавляем ее в конец очереди
					(h_Q != -1) ? 
						(Q[t_Q] = next_v) : 
						(h_Q = next_v);
					t_Q = next_v; // теперь конец очереди - следующая вершина
					Q[next_v] = -1; // после следующей вершины, т.е. конца очереди, никого нет		
				}
			}
		}
	}
}

void Graph::print() const{
	std::cout << "   ";
	for (int i(0); i < m; ++i)
		std::cout << setw(3) << i << " ";
	std::cout << "\nI: ";
	for (const auto& it : I)
		std::cout << setw(3) << it << " ";
	std::cout << "\nJ: ";
	for (const auto& it : J)
		std::cout << setw(3) << it << " ";
	cout << "\nH: ";
	for (ptrdiff_t i(0); i < n; ++i)
		cout << setw(3) << H[i] << " ";
	cout << "\nL: ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(3) << L[i] << " ";
	std::cout << "\n\nP: ";
	for (const auto& it : P)
		std::cout << setw(3) << it << " ";
	std::cout << "\nR: ";
	for (const auto& it : R)
		std::cout << setw(3) << it << " ";
	std::cout << "\n";
}

int main() {
	const clock_t begin_time = clock();
	Graph obj{ Graph() };
	obj.print();
	cout << "\n\nTime: " << float(clock() - begin_time) / CLOCKS_PER_SEC << "\n\n";
}