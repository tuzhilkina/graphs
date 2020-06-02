// Лекция 3
// АЛГОРИТМ НАХОЖДЕНИЯ КОМПОНЕНТ СВЯЗНОСТИ ГРАФА


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
	// Количество вершин
	static const int n{ 12 };
	// Количество ребер
	static const int m{ 15 };
	// Ребра: [e] - одна вершина; [2 * m - 1 - e] - другая вершина
	array<int, 2 * m> IJ{ 0,2,1,4,2,6,1,0,4,3,8,0,7,4,7,10,10,9,7,11,5,9,4,6,11,5,7,8,3,9 };

	// Номер первого ребра, выходящего из вершины [v]
	array<int, n> H{ 0 };
	// Номер первого непросмотренного ребра, выходящего из вершины [v]
	array<int, n> Hn{ 0 };
	// Номер следующего ребра, которое выходит из той же вершины, что и [v]
	array<int, 2 * m> L{ 0 };
	// Стэк активных вершин
	array<int, n> S{ 0 };
	// Метки компонент для каждой вершины
	array<int, n> K{ 0 };
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : K) it = -1;
	int s_head{ 0 }; // указатель на голову стэка
	int x{ -1 }; // номер компоненты связности

	for (int e(0); e < 2* m; ++e) {
		int v = IJ[e];
		L[e] = H[v];
		H[v] = e;
	}
	Hn = H;
	print();
	cout << "\n\n";

	// Цикл по вершинам
	for (int v(0); v < n; ++v) {
		// Если вершина помечена, рассматриваем следующую
		if (K[v] != -1) continue;
		// Номер текущей компоненты связности
		++x;
		// Текущая вершина
		int curr_v(v);
		// Просмотр ребер текущей вершины, начиная с первого непросмотренного
		while (true) {
			K[curr_v] = x; // Текущая вершина принадлежит данной компоненте связности
			int e(-1); // Первое непросмотренное ребро из текущей вершины
			int next_v(-1); // Вершина на другом конце ребра

			// Продвигаемся вглубь из текущей вершины
			for (e = Hn[curr_v]; e != -1; e = L[e]) {
				 next_v = IJ[2 * m - 1 - e];
				// Ищем первую непомеченную вершину
				if (K[next_v] == -1) break;
			}

			// Если мы нашли непомеченную вершину
			if (e != -1) {
				// Делаем шаг вперед
				Hn[curr_v] = L[e]; // Обновляем первое непросмотренное ребро из текущей вершины
				S[s_head] = curr_v; // Заносим вершину в стэк
				++s_head; // Размер стэка увеличился
				curr_v = next_v; // Текущей вершиной становится следующая вглубь
			}
			else {
				// Делаем шаг назад
				if (s_head == 0) break; // Стэк пуст и мы обошли всю компоненту
				else {
					--s_head; // удаляем помеченную и просмотренную вершину из стэка
					curr_v = S[s_head]; // переходим к следующей в стэке вершине
				}
			}
		}
	}
}

void Graph::print() const {
	cout << "IJ:";
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
	obj.print();
}