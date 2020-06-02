// Лекция 6
// ЗАДАЧА ПОСТРОЕНИЯ КРАТЧАЙШИХ ПУТЕЙ
// Реализация алгоритма поиска в ширину



#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

class Tree {
public:
	Tree();
	Tree(const size_t& i_v_) : i_v(i_v_) { Tree();	};
	~Tree() = default;
	Tree(const Tree&) = default;
	Tree& operator=(const Tree&) = default;
	void print();

private:
	// количество рёбер
	static const size_t m{ 13 };
	// количество вершин
	static const size_t n{ 7 };
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
	const ptrdiff_t i_v{ 0 };
};

Tree::Tree() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = n;
	R[i_v] = 0;
	for (auto& it : P) it = -2;
	P[i_v] = -1;
	Q[0] = i_v;
	ptrdiff_t r(0), w(1);

	for (ptrdiff_t k(0); k < m; ++k) {
		ptrdiff_t i = I[k];
		L[k] = H[i];
		H[i] = k;
	}

	// пока очередь не пуста
	while (r < w) {
		// берем вершину из очереди для просмотра
		ptrdiff_t i(Q[r]);
		++r;

		// Просмотр дуг, выходящих из вершины i
		for (ptrdiff_t k(H[i]); k != -1; k = L[k]) {
			ptrdiff_t j = J[k]; // Противоположная вершина
			// Если вершина j не помечена
			if (R[j] == n) {
				R[j] = R[i] + 1; //Расстояние до j на 1 больше, чем до i
				P[j] = k; //Последняя дуга на пути из i_v в j - это k
				Q[w] = j; //Помещаем вершину j в очередь на просмотр
				++w; //Передвигаем указатель записи
			}
		}
	}

	print();
}

void Tree::print() {
	std::cout << "   ";
	for (ptrdiff_t i(0); i < m; ++i)
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
	Tree obj{ Tree() };
}