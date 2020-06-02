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
	// ������ �����
	array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// ����� �����
	array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// ����� ���������� �����, ���������� �� ������� i
	array<int, n> H{ 0 };
	// ����� ���������� � ����� �����, ������� ������� �� ��� �� �������, ��� � ����� �� ������ �������
	array<int, m> L{ 0 };
	// ���������� �� �������� ������� s �� ������� i
	array<int, n> R{ 0 };
	// ���������������� ������ �������, ������ ����� ����, �������� � ������� i
	array<int, n> P{ 0 };
	// ������� ��� ���������
	array<int, n> Q{ 0 };
	// ������ ������ ���������� �����
	const int s{ 0 };
};

Tree::Tree() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = 1024; 
	R[s] = 0; 
	for (auto& it : P) it = -2; // ��� ������� ����������
	P[s] = -1; // // � ��� ��� ������
	for (auto& it : Q) it = -2;

	for (size_t k(0); k < m; ++k) {
		int i = I[k];
		L[k] = H[i];
		H[i] = k;
	}

	int h_Q{ s };
	// ���� ������� �� �����
	while (h_Q != -1) {
		// ����� ������� �� ������� ��� ���������
		int min(1024); // ������� �������
		int j(h_Q); // ������� ������� ��� ������� �� ������
		int pj(-1); // ���������� ������� ��� ������� �� ������
		int pi(-1); // �������, �� ������� ����������� �������
		int i(-1);
		for (pj, j; j != -1; pj = j, j = Q[j]) {
			if (R[j] < min) {
				min = R[j];
				pi = pj;
			}
		}
		// ���� i - �� ������ � ������
		if (pi != -1) {
			i = Q[pi];
			Q[pi] = Q[i]; // ������� i �� ������
		}
		// ���� i - ������ � ������
		else {
			i = h_Q;
			h_Q = Q[i]; // ����������� ������ ������
		}
		// �������� ���, ��������� �� ������� i
		for (size_t k(H[i]); k != -1; k = L[k]) {
			j = J[k]; // ��������������� �������
			// �������� ��������� �����������
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