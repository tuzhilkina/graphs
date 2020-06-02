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
	// �����
	array<int, 2 * m> IJ{ 0,2,1,4,2,6,1,0,4,3,8,0,7,4,7,10,10,9,7,11,5,9,4,6,11,5,7,8,3,9 };

	// ����� ���������� �����, ���������� �� ������� i
	array<int, n> H;
	// ����� ������� ���������������� �����, ���������� �� ������� i
	array<int, n> Hn;
	// ����� ���������� � ����� �����, ������� ������� �� ��� �� �������, ��� � ����� �� ������ �������
	array<int, 2 * m> L;
	// ���� �������� ������
	array<int, n> S;
	// ����� ��������� ��� ������ �������
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

	// ���� �� ��������
	for (ptrdiff_t i0(0); i0 < n; ++i0) {
		// ���� ������� ��������, ������������� ���������
		if (K[i0] != -1) continue;
		// ����� ������� ���������� ���������
		++x;
		// ������� �������
		ptrdiff_t i(i0);
		// �������� ����� ������� �������, ������� � ������� ����������������
		while (1) {
			K[i] = x;// ������� ������� ����������� ������ ���������� ���������
			// �������, ��������� ����� �������
			ptrdiff_t k(Hn[i]);
			// ������� �� ������ ����� �����
			ptrdiff_t j(0);
			for (k = Hn[i]; k != -1; k = L[k]) {
				 j = IJ[2 * m - 1 - k];
				// ���� ������ ������������ �������
				if (K[j] == -1) break;
			}

			// ���� �� ����� ������������ �������
			if (k != -1) {
				// ������ ��� ������
				Hn[i] = L[k]; // ���������� ������ ��������������� ����� �� i
				S[w] = i; // ������� ������� � ����
				++w; // ������ ����� ����������
				i = j; // ������� �������� ���������� ��������� ������
			}
			else {
				// ������ ��� �����
				if (w == 0) break; // ���� ���� � �� ������ ��� ����������
				else {
					--w;
					i = S[w]; // ����� �� ����� ��������� �������
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