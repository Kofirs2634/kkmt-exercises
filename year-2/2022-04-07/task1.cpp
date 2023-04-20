#include <iostream>
#include <deque>
using namespace std;

void print_deque(deque<string> _q) {
    while (!_q.empty()) {
        cout << _q.front() << " ";
        _q.pop_front();
    }
    cout << endl;
}

int main() {
    deque<string> q;
    cout << "Awaiting items... (full-stop terminates sequence)" << endl;
    while (true) {
        string _t;
        cin >> _t;
        if (_t == ".") break;
        q.push_back(_t);
    }
    cout << "Sequence ended" << endl << endl;
    cout << "Initial deque" << endl;
    print_deque(q);

    deque<string> r;
    while (!q.empty()) {
        r.push_back(q.back());
        q.pop_back();
    }

    cout << "Reversed deque" << endl;
    print_deque(r);

    return 0;
}
