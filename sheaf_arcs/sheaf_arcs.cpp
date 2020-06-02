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
	static const size_t n{ 5 };
	static const size_t m{ 8 };
	array<int, m> I{ 1, 2, 4, 3, 0, 2, 4, 3 };  
	array<int, m> J{ 3, 3, 0, 0, 1, 1, 6, 4 };
	array<int, n> H{ -1, -1, -1, -1, -1 };
	array<int, m> L{ -1, -1, -1, -1, -1, -1, -1, -1 };
};

Graph::Graph() {
	for (ptrdiff_t k(0); k < m; ++k) {
		ptrdiff_t i = I[k];
		L[k] = H[i];
		H[i] = k;
	}
	print();
}

void Graph::print() const {
	cout << "I: ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(2) << I[i] << " ";
	cout << "\nJ: ";
	for (ptrdiff_t i(0); i < m; ++i)
		cout << setw(2) << J[i] << " ";
	cout << "\nH: ";
	for (ptrdiff_t i(0); i < n; ++i)
		cout << setw(2) << H[i] << " ";
	cout << "\nL: ";
	for (ptrdiff_t i(0); i < m; ++i) 
		cout << setw(2) << L[i] << " ";
}



int main() {
	//Graph obj = Graph();
	double r = (4330 - 4252.5) / (5 * sqrt(505) * 1.1);
	cout << r;
}