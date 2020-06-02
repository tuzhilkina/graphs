// wide.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include<iomanip>
using namespace std;

class Tree {
public:
	Tree();
	Tree(const int& s_) : s(s_) { Tree(); };
	~Tree() = default;
	Tree(const Tree&) = default;
	Tree& operator=(const Tree&) = default;
	void print();

private:
	static const size_t m{ 13 };
	static const size_t n{ 7 };
	// Начало ребра
	array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// Конец ребра
	array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Номер последнего ребра, выходящего из вершины i
	array<int, n> H{ 0 };
	// Номер следующего с конца ребра, которое выходит из той же вершины, что и ребро по номеру индекса
	array<int, m> L{ 0 };
	// расстояние от исходной вершины s до вершины i
	array<int, n> R{ 0 };
	// модифицированный список предков, хранит номер дуги, входящей в вершину i
	array<int, n> P{ 0 };
	// очередь вершин для просмотра
	array<int, n> Q{ 0 };
	// корень дерева кратчайших путей
	const int s{ 0 };
};

Tree::Tree() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = -1;
	R[s] = 1024;
	for (auto& it : P) it = -2;
	P[s] = -1;
	for (auto& it : Q) it = -1;

	for (size_t k(0); k < m; ++k) {
		int i = I[k];
		L[k] = H[i];
		H[i] = k;
	}

	int h_Q{ s };
	// пока очередь не пуста
	while (h_Q != -1) {
		// берем вершину из очереди для просмотра
		int min(1024); // текущий минимум
		int j(h_Q); // текущая вершина при проходе по списку
		int pj(-1); // предыдущая
		int pi(-1); // вершина, на которой достигается минимум
		int i(-1);
		for (pj, j; j != -1; pj = j, j = Q[j]) {
			if (R[j] < min) {
				min = R[j];
				pi = pj;
			}
		}
		// если i - не первая в списке
		if (pi != -1) {
			i = Q[pi];
			Q[pi] = Q[i]; // удаляем i из списка
		}
		// если i - первая в списке
		else {
			i = h_Q;
			h_Q = Q[i]; // Передвигаем начало списка
		}
		// Просмотр дуг, выходящих из вершины i
		for (size_t k(H[i]); k != -1; k = L[k]) {
			j = J[k]; // Противоположная вершина
			// Проверка основного соотношения
			int rj(R[j]);
			if (R[i] + C[k]; )
		}
		

	}

	print();
}

void Tree::print() {
	cout << "   ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(2) << i << " ";
	cout << "\nI: ";
	for (const auto& it : I)
		cout << setw(2) << it << " ";
	cout << "\nJ: ";
	for (const auto& it : J)
		cout << setw(2) << it << " ";
	cout << "\nP: ";
	for (const auto& it : P)
		cout << setw(2) << it << " ";
	cout << "\nR: ";
	for (const auto& it : R)
		cout << setw(2) << it << " ";
	cout << "\n";
}



int main() {
	Tree obj{ Tree() };
}