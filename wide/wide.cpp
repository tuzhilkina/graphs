// wide.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array>
#include<iomanip>
using namespace std;

class Tree {
public:
	Tree();
	Tree(const ptrdiff_t& s_) : s(s_) { Tree();	};
	~Tree() = default;
	Tree(const Tree&) = default;
	Tree& operator=(const Tree&) = default;
	void print();

private:
	static const size_t m{ 13 };
	static const size_t n{ 7 };
	// Ќачало ребра
	std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	//  онец ребра
	std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Ќомер последнего ребра, выход€щего из вершины i
	array<int, n> H{ 0 };
	// Ќомер следующего с конца ребра, которое выходит из той же вершины, что и ребро по номеру индекса
	array<int, m> L{ 0 };
	// рассто€ние от исходной вершины s до вершины i
	array<int, n> R{ 0 };
	// модифицированный список предков, хранит номер дуги, вход€щей в вершину i
	array<int, n> P{ 0 };
	// очередь вершин дл€ просмотра
	array<int, n> Q{ 0 };
	// корень дерева кратчайших путей
	const ptrdiff_t s{ 0 };
};

Tree::Tree() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = n;
	R[s] = 0;
	for (auto& it : P) it = -2;
	P[s] = -1;
	Q[0] = s;
	ptrdiff_t r(0), w(1);

	for (ptrdiff_t k(0); k < m; ++k) {
		ptrdiff_t i = I[k];
		L[k] = H[i];
		H[i] = k;
	}

	// пока очередь не пуста
	while (r < w) {
		// берем вершину из очереди дл€ просмотра
		ptrdiff_t i(Q[r]);
		++r;

		// ѕросмотр дуг, выход€щих из вершины i
		for (ptrdiff_t k(H[i]); k != -1; k = L[k]) {
			ptrdiff_t j = J[k]; // ѕротивоположна€ вершина
			// ≈сли вершина j не помечена
			if (R[j] == n) {
				R[j] = R[i] + 1; //–ассто€ние до j на 1 больше, чем до i
				P[j] = k; //ѕоследн€€ дуга на пути из s в j - это k
				Q[w] = j; //ѕомещаем вершину j в очередь на просмотр
				++w; //ѕередвигаем указатель записи
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