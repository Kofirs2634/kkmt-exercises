#include <iostream>
#include <cstdlib>
#include <ctime>
#include <deque>
using namespace std;

void print_matrix(deque< deque<int> > _m) {
    for (deque<int> row: _m) {
        for (int e: row) cout << e << "\t";
        cout << endl;
    }
}

int main() {
    srand(time(nullptr));

    int n, m;
    cout << "Enter matrix size (NxM): ";
    cin >> n >> m;

    deque< deque<int> > matrix;
    for (int i = 0; i < n; i++) {
        deque<int> row;
        for (int j = 0; j < m; j++)
            row.push_back(rand() % 101 - 50);
        matrix.push_back(row);
    }
    cout << "Matrix:" << endl;
    print_matrix(matrix);

    return 0;
}