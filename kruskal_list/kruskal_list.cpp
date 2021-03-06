// ������ 4
// ������ ���������� ����������� ������������ ������
// �������� ��������
// ���������� ���������������� ���������

#include <iostream>
#include <array>
#include <string>
#include <iomanip>

class Graph {
public:
    Graph();
    ~Graph() = default;
    Graph(const Graph&) = default;
    Graph& operator=(const Graph&) = default;
    void print() const;

private:
    // ���������� ����� �� ����������� �����
    void sort();
    void surface(int i, int k);
    // ����������� ������������, � �������� ����������� ������� i
    int find(const int& i) const;
    // ����������� �����������
    void unite(const int& mi, const int& mj);

    static const int m{ 13 };
    static const int n{ 7 };
    // ������ �����
    std::array<int, m> I{ 0, 0, 0, 1, 1, 1, 2, 4, 5, 3, 6, 4, 6 };
    // ����� �����
    std::array<int, m> J{ 4, 1, 2, 4, 2, 3, 3, 3, 2, 5, 3, 6, 5 };
    // ����� �����
    std::array<int, m> C{ 9, 6, 9, 4, 8, 6, 7, 3, 5, 2, 4, 3, 4 };
    // ���������� � ����������� ������ �����
    std::array<int, n - 1> K{ 0 };
    // ����� ������������, � ������� ������ ������� [v]
    std::array<int, n> M{ 0 };
    // ����� ������ �������, �������� � ������������ k
    std::array<int, n> H{ 0 };
    // ��������� �������, �������� � �� �� ������������, ��� � ������� [v]
    std::array<int, n> L{ 0 };
    // ����� ������ � k-� ������������
    std::array<int, n> X{ 0 };
};

// ����������� ����� ������������� ������ � ��������������
// ������������� ������ - �������� � ��� ������� �� ������, ��� �������� � �������� ��������
// �������� ������������� ������ - ��������������� ����������� ��� ������ �� ������, �� �� ��� �����
void Graph::surface(int root, int max) {
    // root - ������ ���������
    // max - ������� ������� � ������������ ��������, ������� ����������� ������, �� ���� ����� ������
    int child(-1); // ������� �� ������ ���������
    // ���������� �������� ����� ���������
    int i_r(I[root]), j_r(J[root]), c_r(C[root]);
    // ���� �� ��������� � �������� ���������
    while (2 * root <= max) {
        // ���� ����� ������� ��������� � ������������ ��������� ���������
        if (2 * root == max)
            child = 2 * root; // �� ��� ������ �������
        else
            // �������� ������� �������. ��� ��������� ���������� ������
            (C[2 * root] > C[2 * root + 1]) ? (child = 2 * root) : (child = 2 * root + 1);

        // ���� ������� ������ �����
        if (C[child] > c_r) {
            // ������� ������� ���������� ������
            I[root] = I[child];
            J[root] = J[child];
            C[root] = C[child];
            root = child;
        }
        // � ������� ��������� ������� �������
        else break;
    }
    // ������� ����� ����� ��������� �� �����, ��� ���������� ������� �������
    I[root] = i_r;
    J[root] = j_r;
    C[root] = c_r;
}

void Graph::sort() {
    int last = m - 1; // ����� ���������� �������� � �������
    // ���� �� "�������" - �� ������� � ��������
    // �� ������ ������ ��������� - ������ + 2 �������
    // � ����� ����������� ������� �� 3 �����
    // �� ������� ������� ��� ����������� ������������� ��� �������������� ��������� �������:
    // ������� �������� ������ ������� ������������� � ��������, ��������� �� �����
    // � ���������� �������� ������������� ������
    for (int i(last / 2); i > 0; --i)
        surface(i, last);

    // ������������� ������, ������ �������� - 0
    // � ����� ������ - ��������� ������� ����� ������������� ��������
    for (int i(last); i > 0; --i) {
        // � ���������� ���������� ������������� ������
        // � ������� �������������� ������ ���������� ������� �������
        surface(0, i);
        // ������� ������� ����������� � ����� ������
        // ����� ������ ������ ����������� ������������� �������
        // ������ ���������� �������� �������������
        std::swap(I[i], I[0]);
        std::swap(J[i], J[0]);
        std::swap(C[i], C[0]);
    }
}

int Graph::find(const int& i) const {
    return M[i];
}

void Graph::unite(const int& mi, const int& mj) {
    // less - ����� �������� ������������
    int less(-1);
    // larger - ����� �������� ������������
    int larger(-1);
    // �������� ������� �� ���� �����������
    (X[mi] < X[mj]) ? (less = mi, larger = mj) : (less = mj, larger = mi);

    //����� �������� ������������
    int v(H[less]);
    for (v; L[v] != -1; v = L[v])
        M[v] = larger; //������������� �������
    M[v] = larger; //������������� ��������� �������
    L[v] = H[larger]; //� ������ k ���������� ������ l
    H[larger] = H[less]; //��������� ������ ������
    X[larger] += X[less]; //������ ������ ������������
}

Graph::Graph() {
    sort();
    //������������� ������ � ������ ����������-�����
    for (int v(0); v < n; ++v) {
        H[v] = v;
        L[v] = -1;
        X[v] = 1;
        M[v] = v;
    }
    int w(0); // ��������� �� ������ ��������� ������� � ������� K

    // �������� ����� ����� �� ����������� �����
    // ����������� �������� ����� ���������� ��� �����
    // � ����� ��������� ������������ ������
    for (int e(0); e < m && w < n - 1; ++e) {
        int i(I[e]);
        int j(J[e]);
        int mi = find(i);
        int mj = find(j);
        // ���� i � j ��������� � ������ �������������, �.�. �� ���������� ����
        if (mi != mj) {
            K[w] = e; // ��������� ����� k � ���� K
            ++w;
            unite(mi, mj);
        }
    }
}

void Graph::print() const {
    std::cout << "   ";
    for (int i(0); i < m; ++i)
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

int main() {
    Graph obj{ Graph() };
    obj.print();
};