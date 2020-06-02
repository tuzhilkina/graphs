// ������ 6
// ������ ���������� ���������� �����
// ���������� ��������� ������ � ������



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
	// ���������� ����
	static const size_t m{ 13 };
	// ���������� ������
	static const size_t n{ 7 };
	// ������ ����� e
	std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// ����� ����� 
	std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// ����� ������� �����, ���������� �� ������� [v]
	array<int, n> H{ 0 };
	// ����� ���������� �����, ������� ������� �� ��� �� �������, ��� � [e]
	array<int, m> L{ 0 };
	// ���������� �� �������� ������� i_v �� ������� i
	array<int, n> R{ 0 };
	// ���������������� ������ �������, ������ ����� ����, �������� � ������� i
	array<int, n> P{ 0 };
	// ������� ������ ��� ���������
	array<int, n> Q{ 0 };
	// ������ ������ ���������� �����
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

	// ���� ������� �� �����
	while (r < w) {
		// ����� ������� �� ������� ��� ���������
		ptrdiff_t i(Q[r]);
		++r;

		// �������� ���, ��������� �� ������� i
		for (ptrdiff_t k(H[i]); k != -1; k = L[k]) {
			ptrdiff_t j = J[k]; // ��������������� �������
			// ���� ������� j �� ��������
			if (R[j] == n) {
				R[j] = R[i] + 1; //���������� �� j �� 1 ������, ��� �� i
				P[j] = k; //��������� ���� �� ���� �� i_v � j - ��� k
				Q[w] = j; //�������� ������� j � ������� �� ��������
				++w; //����������� ��������� ������
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