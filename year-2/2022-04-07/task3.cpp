#include <iostream>
#include <deque>
using namespace std;

void print_deque(deque<int> _q) {
    while (!_q.empty()) {
        cout << _q.front() << " ";
        _q.pop_front();
    }
    cout << endl;
}

int main() {
    deque<int> q;
    cout << "Awaiting items... (0 terminates sequence)" << endl;
    while (true) {
        int _t;
        cin >> _t;
        if (!_t) break;
        q.push_back(_t);
    }
    cout << "Sequence ended" << endl << endl;

    cout << "Deque" << endl;
    print_deque(q);

    deque<int> a = q;
    bool flag = true;
    while (!q.empty() && flag) {
        if (q.front() != a.back()) flag = false;
        q.pop_front();
        a.pop_back();
    }
    cout << (flag ? "Symmetric" : "Asymmetric") << endl;

    return 0;
}
