// Лекция 8
// ЗАДАЧА ПОСТРОЕНИЯ КРАТЧАЙШИХ ПУТЕЙ
// АЛГОРИТМ ДЕЙКСТРЫ
// конкретизация общего алгоритма построения дерева кратчайших путей.
// выбираем некоторую перспективную вершину и обрабатываем все выходящие из нее дуги

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

class Graph {
public:
	Graph();
	Graph(const int& i_v_) : i_v(i_v_) { Graph(); };
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

	// список вершин для просмотра в виде списка
	// если вершина [v] вне списка, то Q[v] = -2
	// если вершина [v] в списке, то Q[v] = номер следующей после v вершины
	// если вершина [v] - последняя, то Q[v] = -1
	array<int, n> Q{ 0 };
	for (auto& it : Q) it = -2; // все вершины вне списка
	int h_Q = i_v; // начало списка
	Q[i_v] = -1; // после начальной вершины в списке никого нет 

	// пока список не пуст
	while (h_Q != -1) {
		int min_r = numeric_limits<int>::max(); // текущее минимальное расстояние
		int curr_v(h_Q); //текущая вершина при проходе по списку
		int prev_v(-1); // предыдущая вершина списка
		int min_v(-1); // оптимальная вершина с минимальным текущим расстоянием
		int pmin_v(-1); // вершина, предшествующая в списке оптимальной

		// выбираем из списка вершин самую перспективную - т.е. вершину с минимальным расстоянием
		for (curr_v, prev_v; curr_v != -1; prev_v = curr_v, curr_v = Q[curr_v]) 
			if (R[curr_v] < min_r) {
				min_r = R[curr_v];
				pmin_v = prev_v; // минимум достигается в вершине, следующей за pmin_v
			}

		// Вершину Q[min_v] выбираем для просмотра и удаляем из списка
		if (pmin_v != -1) { // если оптимальная вершина - не первая в списке
			min_v = Q[pmin_v];
			Q[pmin_v] = Q[min_v]; // Удаляем оптимальную вершину из списка
		}
		else { // если оптимальная вершина - первая в списке
			min_v = h_Q; // то она является началом списка
			h_Q = Q[min_v]; // теперь начало списка - следующая вершина
		}

		// просмотриваем дуги, исходящие из оптимальной вершины
		for (int e(H[min_v]); e != -1; e = L[e]) {
			int next_v(J[e]); // противоположная, т.е. следующая вершина
			int r_n(R[next_v]); // сохраняем значение текущего пути, чтобы выяснить, помечена ли вершина
			// если текущий путь до следующей вершины длиннее пути через оптимальную вершину
			if (R[min_v] + C[e] < R[next_v]) {
				R[next_v] = R[min_v] + C[e]; // путь до следующей вершины теперь проходит через оптимальную
				P[next_v] = e; // в следующую вершину входит текущее ребро

				if (r_n == numeric_limits<int>::max()) { // если вершина не помечена
					Q[next_v] = h_Q; // следующая вершина является первой в списке на просмотр
					h_Q = next_v;
				}
			}
		}		
	}
}

void Graph::print() const {
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