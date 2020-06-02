#include <iostream>
#include <array>
#include <string>
#include <iomanip>

class Tree {
public:
    Tree();
    ~Tree() = default;
    Tree(const Tree&) = default;
    Tree& operator=(const Tree&) = default;
    void print();
    void temp(const ptrdiff_t& k);

private:
    // Сортировка ребер по возрастанию длины
    void sort();
    void surface(ptrdiff_t i, ptrdiff_t k);
    // Определение подмножества, к которому принаджедит вершина i
    int find(const ptrdiff_t& i);
    // Объединение подмножеств
    void unite(const ptrdiff_t& mi, const ptrdiff_t& mj);

    static const int m{ 13 };
    static const int n{ 7 };
    // Начало ребра
    std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
    // Конец ребра
    std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
    // Длина ребра
    std::array<int, m> C{ 9, 6, 9, 4, 8, 6, 7, 3, 5, 2, 4, 3, 4 };
    // Включенные в связывающее дерево ребра
    std::array<int, n - 1> K{ 0 };
    // Номер подмножества, в которое входит вершина i
    std::array<int, n> M{ 0 };
    // Номер первой вершины, входящей в подмножество k
    std::array<int, n> H{ 0 };
    // Следующая вершина, входящая в то же подмножество, что и вершина i
    std::array<int, n> L{ 0 };
    // Число вершин в k-м подмножестве
    std::array<int, n> X{ 0 };
};

void Tree::surface(ptrdiff_t i, ptrdiff_t k) {
    ptrdiff_t j(0), m(2 * i);
    std::array<int, 3> copy{ I[i], J[i], C[i] };
    while (m <= k) {
        if (m == k) j = m;
        else
            if (C[m] > C[m + 1]) j = m;
            else j = m + 1;
        if (C[j] > copy[2]) {
            I[i] = I[j];
            J[i] = J[j];
            C[i] = C[j];
            i = j;
            m = 2 * i;
        }
        else break;
    }
    I[i] = copy[0];
    J[i] = copy[1];
    C[i] = copy[2];
}

void Tree::sort() {
    ptrdiff_t s = m - 1;
    for (ptrdiff_t i(s / 2); i >= 1; --i)
        surface(i, s);
    for (ptrdiff_t i(s); i >= 1; --i) {
        surface(0, i);
        std::swap(I[i], I[0]);
        std::swap(J[i], J[0]);
        std::swap(C[i], C[0]);
    }
}

int Tree::find(const ptrdiff_t& i) {
    return M[i];
}

void Tree::unite(const ptrdiff_t& mi, const ptrdiff_t& mj) {
    // k - номер меньшего подмножества
    ptrdiff_t k(-1);
    // l - номер большего подмножества
    ptrdiff_t l(-1);
    // выбираем меньшее из двух подмножеств
    if (X[mi] < X[mj]) { k = mi; l = mj; }
    else { k = mj; l = mi; }

    //обход меньшего подмножества
    ptrdiff_t i(H[k]);
    for (i; L[i] != -1; i = L[i])
        M[i] = l; //перекрашиваем вершины
    M[i] = l; //перекрашиваем последнюю вершину

    L[i] = H[l]; //к списку k прицепляем список l
    H[l] = H[k]; //переносим начало списка
    X[l] += X[k]; //размер нового подмножества
}

Tree::Tree() {
    sort();
    //Инициализация данных в задаче Объединить-Найти
    for (ptrdiff_t it(0); it < n; ++it) {
        H[it] = it;
        L[it] = -1;
        X[it] = 1;
        M[it] = it;
    }

    // Указатель на первую свободную позицию в массиве K
    ptrdiff_t w(0);

    // Просмотр ребер графа по возрастанию длины
    // Заканчиваем просмотр после исчерпания дуг графа
    // или когда полностью сформируется дерево
    for (ptrdiff_t k(0); k < m && w < n - 1; ++k) {
        ptrdiff_t i(I[k]);
        ptrdiff_t j(J[k]);
        int mi = find(i);
        int mj = find(j);
        // Если i и j находятся в разных подмножествах, т.е. не образуется цикл
        if (mi != mj) {
            K[w] = k; // Добавляем ребро k в граф K
            ++w;
            unite(mi, mj);
        }
        temp(k);
    }
    print();
}

void Tree::print() {
    std::cout << "\n\n\n   ";
    for (ptrdiff_t i(0); i < m; ++i)
        std::cout << std::setw(2) << i << " ";
    std::cout << "\nI: ";
    for (const auto& it : I)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nJ: ";
    for (const auto& it : J)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nC: ";
    for (const auto& it : C)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nK: ";
    for (const auto& it : K)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\n";
}

void Tree::temp(const ptrdiff_t& k) {
    std::cout << "k = " << k;
    std::cout << "\nH: ";
    for (const auto& it : H)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nL: ";
    for (const auto& it : L)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nX: ";
    for (const auto& it : X)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\nM: ";
    for (const auto& it : M)
        std::cout << std::setw(2) << it << " ";
    std::cout << "\n\n";
}


int main() {
    Tree obj{ Tree() };
};