// ������ 6
// ������ ���������� ���������� �����
// ���������� ��������� ������ � ������

#include <iostream>
#include <array>
#include <iomanip>
using namespace std;

class Graph {
public:
	Graph();
	Graph(const int& i_v_) : i_v(i_v_) { Graph();	};
	~Graph() = default;
	Graph(const Graph&) = default;
	Graph& operator=(const Graph&) = default;
	void print() const;

private:
	// ���������� ����
	static const int m{ 13 };
	// ���������� ������
	static const int n{ 7 };
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
	const int i_v{ 0 };
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : R) it = n;
	R[i_v] = 0;
	for (auto& it : P) it = -2;
	P[i_v] = -1;
	Q[0] = i_v; // ��������� ������� - ������ � ������� �� ��������
	int read(0); // ������ ������
	int	write(1); // ���� ������

	for (int e(0); e < m; ++e) {
		int v = I[e]; // �������, �� ������� ������� ����� e
		L[e] = H[v]; // ����������� ��������� ����� �� ������ �������
		H[v] = e; // ������ ����� ���������� ������ ��������� �� ������ �������
	}

	// ���� ������� �� �����
	while (read < write) {
		// ����� ������� �� ������� ��� ���������
		int curr_v(Q[read]);
		++read;

		// �������� ���, ��������� �� ������� �������
		for (int e(H[curr_v]); e != -1; e = L[e]) {
			int next_v = J[e]; // ��������������� �������
			// ���� ��������� ������� �� ��������
			if (R[next_v] == n) {
				R[next_v] = R[curr_v] + 1; //���������� �� ��������� �� 1 ������, ��� �� �������
				P[next_v] = e; //��������� ���� �� ���� �� ��������� ������� � ��������� ����� �������
				Q[write] = next_v; //�������� ��������� ������� � ������� �� ��������
				++write;
			}
		}
	}
}

void Graph::print() const{
	std::cout << "   ";
	for (int i(0); i < m; ++i)
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
	Graph obj{ Graph() };
	obj.print();
}