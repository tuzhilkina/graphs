// wide.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include <iomanip>
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
	// Ќачало ребра
	array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	//  онец ребра
	array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Ќомер последнего ребра, выход€щего из вершины i
	array<int, n> H{ 0 };
	// Ќомер следующего с конца ребра, которое выходит из той же вершины, что и ребро по номеру индекса
	array<int, m> L{ 0 };
	// рассто€ние от исходной вершины s до вершины i
	array<int, n> R{ 0 };
	// модифицированный список предков, хранит номер дуги, вход€щей в вершину i
	array<int, n> P{ 0 };
	// вершины дл€ просмотра
	array<int, n> Q{ 0 };
	// корень дерева кратчайших путей
	const int s{ 0 };
};

Tree::Tree() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = 1024; 
	R[s] = 0; 
	for (auto& it : P) it = -2; // ¬се вершины недоступны
	P[s] = -1; // // ” нее нет предка
	for (auto& it : Q) it = -2;

	for (size_t k(0); k < m; ++k) {
		int i = I[k];
		L[k] = H[i];
		H[i] = k;
	}

	int h_Q{ s };
	// пока очередь не пуста
	while (h_Q != -1) {
		// берем вершину из очереди дл€ просмотра
		int min(1024); // текущий минимум
		int j(h_Q); // текуща€ вершина при проходе по списку
		int pj(-1); // предыдуща€ вершина при проходе по списку
		int pi(-1); // вершина, на которой достигаетс€ минимум
		int i(-1);
		for (pj, j; j != -1; pj = j, j = Q[j]) {
			if (R[j] < min) {
				min = R[j];
				pi = pj;
			}
		}
		// если i - не перва€ в списке
		if (pi != -1) {
			i = Q[pi];
			Q[pi] = Q[i]; // удал€ем i из списка
		}
		// если i - перва€ в списке
		else {
			i = h_Q;
			h_Q = Q[i]; // ѕередвигаем начало списка
		}
		// ѕросмотр дуг, выход€щих из вершины i
		for (size_t k(H[i]); k != -1; k = L[k]) {
			j = J[k]; // ѕротивоположна€ вершина
			// ѕроверка основного соотношени€
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