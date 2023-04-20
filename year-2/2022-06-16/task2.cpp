#include <iostream>
#include <deque>
#include <cstdlib>
#include <ctime>
using namespace std;

void create_matrix(deque< deque<int> > &_cont, int _rows, int _cols) {
    for (int i = 0; i < _rows; i++) {
        deque<int> row;
        for (int j = 0; j < _cols; j++)
            row.push_back(rand() % 101 - 50);
        _cont.push_back(row);
    }
}
void print_matrix(deque< deque<int> > _cont) {
    for (deque<int> row: _cont) {
        for (int e: row) cout << e << "\t";
        cout << endl;
    }
}

int main() {
    srand(time(nullptr));

    deque< deque<int> > m;
    deque<int> nums;
    create_matrix(m, 10, 5);

    cout << "Base matrix: " << endl;
    print_matrix(m);

    for (deque<int> row: m)
        for (int e: row)
            if (e < 0 && e % 10 == -4) nums.push_back(e);

    cout << endl << "Matched numbers: " << nums.size() << endl;
    cout << "---> ";
    for (int n: nums) cout << n << " ";
    cout << endl;

    return 0;
}