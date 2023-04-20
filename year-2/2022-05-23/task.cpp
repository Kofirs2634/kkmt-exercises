#include <iostream>
#include <deque>
using namespace std;

class Matrix {
    private:
        deque< deque<int> > _content;
    public:
        int m;
        int n;

        Matrix(int _m, int _n) {
            this->m = _m;
            this->n = _n;
            for (int i = 0; i < m; i++) {
                deque<int> _row(n);
                _content.push_back(_row);
            }
        }
        void init() {
            cout << "Expected size: " << m << "x" << n << endl;
            for (int i = 0; i < m; i++) {
                string _t;
                int pos = 0;

                cin >> ws; // cin конфликтует с getline
                getline(cin, _t);
                for (int j = 0; j < n; j++) {
                    pos = _t.find(' ');
                    put(i, j, stoi(_t.substr(0, pos)));
                    _t.erase(0, pos + 1);
                }
            }
        }
        void print() {
            for (deque<int> row: _content) {
                for (int num: row) cout << num << "\t";
                cout << endl;
            }
        }
        int at(int _i, int _j) {
            return _content[_i][_j];
        }
        void put(int _i, int _j, int _what) {
            _content[_i][_j] = _what;
        }
};

Matrix operator * (Matrix _a, Matrix _b) {
    if (_a.n != _b.m) throw runtime_error("Number of columns in the first matrix is not equal to number of rows in the second one");
    Matrix _t = Matrix(_a.m, _b.n);
    for (int i = 0; i < _t.m; i++) { // обходим строку
        for (int j = 0; j < _t.n; j++) { // обходим столбцы
            int sum = 0;
            for (int n = 0; n < _a.n; n++) // перебираем элементы
                sum += _a.at(i, n) * _b.at(n, j);
            _t.put(i, j, sum);
        }
    }
    return _t;
}

Matrix operator + (Matrix _a, Matrix _b) {
    if (_a.m != _b.m || _a.n != _b.n) throw runtime_error("Matrix sizes are not equal");
    Matrix _t = Matrix(_a.m, _a.n);
    for (int i = 0; i < _a.m; i++) {
        for (int j = 0; j < _a.n; j++)
            _t.put(i, j, _a.at(i, j) + _b.at(i, j));
    }
    return _t;
}

Matrix operator - (Matrix _a, Matrix _b) {
    if (_a.m != _b.m || _a.n != _b.n) throw runtime_error("Matrix sizes are not equal");
    Matrix _t = Matrix(_a.m, _a.n);
    for (int i = 0; i < _a.m; i++) {
        for (int j = 0; j < _a.n; j++)
            _t.put(i, j, _a.at(i, j) - _b.at(i, j));
    }
    return _t;
}

int main() {
    int ma, na;
    int mb, nb;
    cout << "Matrix A size: ";
    cin >> ma >> na;
    cout << "Matrix B size: ";
    cin >> mb >> nb;

    Matrix a = Matrix(ma, na);
    Matrix b = Matrix(mb, nb);

    cout << "Init matrix A" << endl;
    a.init();
    cout << endl << "Init matrix B" << endl;
    b.init();

    try {
        cout << endl << "Multiplication product" << endl;
        (a * b).print();
    } catch (const exception &e) {
        cerr << "Impossible to multiply matrixes: " << e.what() << endl;
    }

    try {
        cout << endl << "Addition product" << endl;
        (a + b).print();
    } catch (const exception &e) {
        cerr << "Impossible to add matrixes: " << e.what() << endl;
    }

    try {
        cout << endl << "Subtraction product" << endl;
        (a - b).print();
    } catch (const exception &e) {
        cerr << "Impossible to subtract matrixes: " << e.what() << endl;
    }

    return 0;
}