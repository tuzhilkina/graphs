// ������ 8
// ������ ���������� ���������� �����
// (�������� ��������)
// ������������� ������ ��������� ���������� ������ ���������� �����.
// �������� ��������� ������������� ������� � ������������ ��� ��������� �� ��� ����

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
	// ���������� ����
	static const int m{ 13 };
	// ���������� ������
	static const int n{ 7 };
	// ������ �����
	std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// ����� �����
	std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// ����� �����
	std::array<int, m> C{ 9, 6, 9, 4, 8, 6, 7, 3, 5, 2, 4, 3, 4 };
	// ����� ������� �����, ���������� �� ������� [v]
	array<int, n> H{ 0 };
	// ����� ���������� �����, ������� ������� �� ��� �� �������, ��� � [e]
	array<int, m> L{ 0 };
	// ���������� �� �������� ������� i_v �� ������� [v]
	array<int, n> R{ 0 };
	// ���������������� ������ �������, ������ ����� ����, �������� � ������� [v]
	array<int, n> P{ 0 };
	// ������ ������ ���������� �����
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
	for (auto& it : P) it = -2; // ��� ������� ����������
	R[i_v] = 0; // ���������� �� ��������� ������� �� ����� ����
	P[i_v] = -1; // � ��������� ������� ��� ������

	// ������ ������ ��� ��������� � ���� ������
	// ���� ������� [v] ��� ������, �� Q[v] = -2
	// ���� ������� [v] � ������, �� Q[v] = ����� ��������� ����� v �������
	// ���� ������� [v] - ���������, �� Q[v] = -1
	array<int, n> Q{ 0 };
	for (auto& it : Q) it = -2; // ��� ������� ��� ������
	int h_Q = i_v; // ������ ������
	Q[i_v] = -1; // ����� ��������� ������� � ������ ������ ��� 

	// ���� ������ �� ����
	while (h_Q != -1) {
		int min_r = numeric_limits<int>::max(); // ������� ����������� ����������
		int curr_v(h_Q); //������� ������� ��� ������� �� ������
		int prev_v(-1); // ���������� ������� ������
		int min_v(-1); // ����������� ������� � ����������� ������� �����������
		int pmin_v(-1); // �������, �������������� � ������ �����������

		// �������� �� ������ ������ ����� ������������� - �.�. ������� � ����������� �����������
		for (curr_v, prev_v; curr_v != -1; prev_v = curr_v, curr_v = Q[curr_v]) 
			if (R[curr_v] < min_r) {
				min_r = R[curr_v];
				pmin_v = prev_v; // ������� ����������� � �������, ��������� �� pmin_v
			}
		// ������� Q[min_v] �������� ��� ��������� � ������� �� ������
		if (pmin_v != -1) { // ���� ����������� ������� - �� ������ � ������
			min_v = Q[pmin_v];
			Q[pmin_v] = Q[min_v]; // ������� ����������� ������� �� ������
		}
		else { // ���� ����������� ������� - ������ � ������
			min_v = h_Q; // �� ��� �������� ������� ������
			h_Q = Q[min_v]; // ������ ������ ������ - ��������� �������
		}

		// ������������� ����, ��������� �� ����������� �������
		for (int e(H[min_v]); e != -1; e = L[e]) {
			int next_v(J[e]); // ���������������, �.�. ��������� �������
			int r_n(R[next_v]); // ��������� �������� �������� ����, ����� ��������, �������� �� �������
			// ���� ������� ���� �� ��������� ������� ������� ���� ����� ����������� �������
			if (R[min_v] + C[e] < R[next_v]) {
				R[next_v] = R[min_v] + C[e]; // ���� �� ��������� ������� ������ �������� ����� �����������
				P[next_v] = e; // � ��������� ������� ������ ������� �����

				if (r_n == numeric_limits<int>::max()) { // ���� ������� �� ��������
					Q[next_v] = h_Q; // ��������� ������� �������� ������ � ������ �� ��������
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