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

    string start = "";
    while (q.size() && start != q.front()) {
        if (q.front()[0] == 'a') q.pop_front();
        else {
            string _t = q.front();
            if (start.empty()) start = _t;
            q.pop_front();
            q.push_back(_t);
        }
    }

    cout << "Modified deque" << endl;
    print_deque(q);

    cout << endl << "Length: " << q.size() << endl;
    cout << "First element: " << q.front() << endl;
    cout << "Last element: " << q.back() << endl;

    return 0;
}
