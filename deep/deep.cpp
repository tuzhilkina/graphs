// ������ 3
// �������� ���������� ��������� ��������� �����


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
	// ���������� ������
	static const int n{ 12 };
	// ���������� �����
	static const int m{ 15 };
	// �����: [e] - ���� �������; [2 * m - 1 - e] - ������ �������
	array<int, 2 * m> IJ{ 0,2,1,4,2,6,1,0,4,3,8,0,7,4,7,10,10,9,7,11,5,9,4,6,11,5,7,8,3,9 };

	// ����� ������� �����, ���������� �� ������� [v]
	array<int, n> H{ 0 };
	// ����� ������� ���������������� �����, ���������� �� ������� [v]
	array<int, n> Hn{ 0 };
	// ����� ���������� �����, ������� ������� �� ��� �� �������, ��� � [v]
	array<int, 2 * m> L{ 0 };
	// ���� �������� ������
	array<int, n> S{ 0 };
	// ����� ��������� ��� ������ �������
	array<int, n> K{ 0 };
};

Graph::Graph() {
	for (auto& it : H) it = -1;
	for (auto& it : L) it = -1;
	for (auto& it : K) it = -1;
	int s_head{ 0 }; // ��������� �� ������ �����
	int x{ -1 }; // ����� ���������� ���������

	for (int e(0); e < 2* m; ++e) {
		int v = IJ[e];
		L[e] = H[v];
		H[v] = e;
	}
	Hn = H;
	print();
	cout << "\n\n";

	// ���� �� ��������
	for (int v(0); v < n; ++v) {
		// ���� ������� ��������, ������������� ���������
		if (K[v] != -1) continue;
		// ����� ������� ���������� ���������
		++x;
		// ������� �������
		int curr_v(v);
		// �������� ����� ������� �������, ������� � ������� ����������������
		while (true) {
			K[curr_v] = x; // ������� ������� ����������� ������ ���������� ���������
			int e(-1); // ������ ��������������� ����� �� ������� �������
			int next_v(-1); // ������� �� ������ ����� �����

			// ������������ ������ �� ������� �������
			for (e = Hn[curr_v]; e != -1; e = L[e]) {
				 next_v = IJ[2 * m - 1 - e];
				// ���� ������ ������������ �������
				if (K[next_v] == -1) break;
			}

			// ���� �� ����� ������������ �������
			if (e != -1) {
				// ������ ��� ������
				Hn[curr_v] = L[e]; // ��������� ������ ��������������� ����� �� ������� �������
				S[s_head] = curr_v; // ������� ������� � ����
				++s_head; // ������ ����� ����������
				curr_v = next_v; // ������� �������� ���������� ��������� ������
			}
			else {
				// ������ ��� �����
				if (s_head == 0) break; // ���� ���� � �� ������ ��� ����������
				else {
					--s_head; // ������� ���������� � ������������� ������� �� �����
					curr_v = S[s_head]; // ��������� � ��������� � ����� �������
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