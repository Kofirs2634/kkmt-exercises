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
    cout << "Sequence ended" << endl;
    int n;
    cout << "Enter N: ";
    cin >> n;

    cout << endl << "Initial deque" << endl;
    print_deque(q);

    int start = 0;
    while (q.size() && start != q.front()) {
        if (q.front() > n) q.pop_front();
        else {
            int _t = q.front();
            if (!start) start = _t;
            q.pop_front();
            q.push_back(_t);
        }
    }
    cout << "Modified deque" << endl;
    print_deque(q);

    return 0;
}
