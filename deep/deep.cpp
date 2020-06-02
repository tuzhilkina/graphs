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
	static const size_t n{ 12 };
	static const size_t m{ 15 };
	// Ребра
	array<int, 2 * m> IJ{ 0,2,1,4,2,6,1,0,4,3,8,0,7,4,7,10,10,9,7,11,5,9,4,6,11,5,7,8,3,9 };

	// Номер последнего ребра, выходящего из вершины i
	array<int, n> H;
	// Номер первого непросмотренного ребра, выходящего из вершины i
	array<int, n> Hn;
	// Номер следующего с конца ребра, которое выходит из той же вершины, что и ребро по номеру индекса
	array<int, 2 * m> L;
	// Стэк активных вершин
	array<int, n> S;
	// Метки компонент для каждой вершины
	array<int, n> K;
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : K) it = -1;
	ptrdiff_t w{ 0 };
	int x{ -1 };

	for (ptrdiff_t k(0); k < 2* m; ++k) {
		ptrdiff_t i = IJ[k];
		L[k] = H[i];
		H[i] = k;
	}
	Hn = H;
	print();
	cout << "\n\n";

	// Цикл по вершинам
	for (ptrdiff_t i0(0); i0 < n; ++i0) {
		// Если вершина помечена, рассматриваем следующую
		if (K[i0] != -1) continue;
		// Номер текущей компоненты связности
		++x;
		// Текущая вершина
		ptrdiff_t i(i0);
		// Просмотр ребер текущей вершины, начиная с первого непросмотренного
		while (1) {
			K[i] = x;// Текущая вершина принадлежит данной компоненте связности
			// Вершина, следующая после текущей
			ptrdiff_t k(Hn[i]);
			// Вершина на другом конце ребра
			ptrdiff_t j(0);
			for (k = Hn[i]; k != -1; k = L[k]) {
				 j = IJ[2 * m - 1 - k];
				// Ищем первую непомеченную вершину
				if (K[j] == -1) break;
			}

			// Если мы нашли непомеченную вершину
			if (k != -1) {
				// Делаем шаг вперед
				Hn[i] = L[k]; // Запоминаем первую непросмотренное ребро из i
				S[w] = i; // Заносим вершину в стэк
				++w; // Размер стэка увеличился
				i = j; // Текущей вершиной становится следующая вглубь
			}
			else {
				// Делаем шаг назад
				if (w == 0) break; // Стэк пуст и мы обошли всю компоненту
				else {
					--w;
					i = S[w]; // Берем из стэка последнюю вершину
				}
			}
		}
	}
	print();
}

void Graph::print() const {
	cout << "I: ";
	for (const auto& it : IJ)
		cout << setw(2) << it << " ";
	cout << "\nH: ";
	for (const auto& it : H)
		cout << setw(2) << it << " ";
	cout << "\nL: ";
	for (const auto& it : L)
		cout << setw(2) << it << " ";
	cout << "\nK: ";
	for (const auto& it : K)
		cout << setw(2) << it << " ";
}

int main() {
	Graph obj = Graph();
}