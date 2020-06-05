// Лекция 8
// ЗАДАЧА ПОСТРОЕНИЯ КРАТЧАЙШИХ ПУТЕЙ
// АЛГОРИТМ ДЕЙКСТРЫ
// с использованием АТД черпаки

#include <iostream>
#include <vector>
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
	void insert(const int& v, const int& pos);
	int get(const int& b_n);
	void remove(const int& v, const int& pos);
	// количество рёбер
	int m{ 13 };
	// количество вершин
	int n{ 7 };
	// Начало ребра
	vector<int> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
	// Конец ребра
	vector<int> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
	// Длина ребра
	vector<int> C{ 9, 6, 9, 4, 8, 6, 7, 3, 5, 2, 4, 3, 4 };
	// Номер первого ребра, выходящего из вершины [v]
	vector<int> H;
	// Номер следующего ребра, которое выходит из той же вершины, что и [e]
	vector<int> L;
	// расстояние от исходной вершины i_v до вершины [v]
	vector<int> R;
	// модифицированный список предков, хранит номер дуги, входящей в вершину [v]
	vector<int> P;
	// черпак B[r] хранит все помеченные и непросмотренные вершины, текущее расстояние до которых сейчас равно r
	vector<int> B;
	// ссылка вперед, Fw[v] - номер следующей после v вершины в том же черпаке
	vector<int> Fw;
	// ссылка назад, Bk[v] - номер предыдущей после v вершины в том же черпаке
	vector<int> Bk;
	// корень дерева кратчайших путей
	int i_v{ 0 };
};

// взять вершину из черпака
int Graph::get(const int& b_n) {
	int i(B[b_n]);; // первая вершина в черпаке или -1, если черпак пуст
	if (i != -1) B[b_n] = Fw[i]; // удалили вершину из черпака
	return i;
}
// добавление вершины в начало черпака
void Graph::insert(const int& v, const int& pos) {
	int first(B[pos]); // первая вершина в черпаке или -1, если черпак пуст
	// вставка элемента в начало двустороннего списка
	Fw[v] = first;
	if (first != -1) Bk[first] = v;
	B[pos] = v;
}
// удаление вершины v из черпака pos
void Graph::remove(const int& v, const int& pos) {
	int fv(Fw[v]); // следуюшая в черпаке
	int bv(Bk[v]); // предыдущая в черпаке
	if (v == B[pos])
		B[pos] = fv; // v была первой в черпаке
	else {
		Fw[bv] = fv; // удаляем вершину из списка
		if (fv != -1) // если v не последняя
			Bk[fv] = bv;
	}
}

Graph::Graph() {
	for (int i(0); i < n; ++i) H.push_back(-1);
	for (int i(0); i < m; ++i) L.push_back(-1);
	for (int e(0); e < m; ++e) {
		int v(I[e]);
		L[e] = H[v];
		H[v] = e;
	}
	for (int i(0); i < n; ++i) R.push_back(numeric_limits<int>::max());
	for (int i(0); i < n; ++i) P.push_back(-2); // все вершины недоступны
	R[i_v] = 0; // расстояние от начальной вершины до самой себя
	P[i_v] = -1; // у начальной вершины нет предка


	int max_e(0); // максимальная длина дуги
	for (const auto& it : C)
		if (it > max_e) max_e = it;
	// максимальное число черпаков 
	for (int i(0); i <= n * max_e; ++i) {
		B.push_back(-1);
		Fw.push_back(-1);
		Bk.push_back(-1);
	}
	insert(i_v, 0); // исходная вершина находится в нулевом черпаке

	//просматриваем черпаки
	for (int b(0); b <= n * max_e; ++b) {
		// выбираем вершины с минимальным расстоянием из текущего черпака пока он не станет пустым
		int v(get(b));
		while (v != -1) {
			// просмотриваем дуги, исходящие из оптимальной вершины
			for (int e(H[v]); e != -1; e = L[e]) {
				int next_v(J[e]); // противоположная, т.е. следующая вершина
				int r_n(R[next_v]); // сохраняем значение текущего пути, чтобы выяснить, помечена ли вершина
				// если текущий путь до следующей вершины длиннее пути через оптимальную вершину
				if (R[v] + C[e] < R[next_v]) {
					R[next_v] = R[v] + C[e]; // путь до следующей вершины теперь проходит через оптимальную
					P[next_v] = e; // в следующую вершину входит текущее ребро

					if (r_n != numeric_limits<int>::max()) // если вершина помечена и находится в черпаке r_n
						remove(next_v, r_n);
					insert(next_v, R[next_v]);
				}
			}
			v = get(b); // выбираем новую вершину из черпака
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