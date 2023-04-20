#include <iostream>
#include <deque>
#include <cstdlib>
#include <cstring>
#include <time.h>
using namespace std;

string make_surname() {
    string _s;
    const string vow = "aueoi";
    const string con = "stvbnmrplz";
    deque<string> parts;
    for (int i = 0; i < vow.length(); i++) {
        for (int j = 0; j < con.length(); j++) {
            string _t = "";
            parts.push_back(_t + con[i] + vow[i]);
        }
    }
    for (int i = 0; i < rand() % 3 + 3; i++) _s.append(parts[rand() % parts.size()]);
    _s[0] = toupper(_s[0]);
    return _s;
}

void print_deque(deque<string> _q) {
    for (int i = 0; i < _q.size(); i++)
        cout << _q[i] << " ";
    cout << endl;
}

int main() {
    srand(time(nullptr));
    deque<string> q1, q2, r;
    int n;
    cout << "Amount of clients: ";
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        q1.push_back(make_surname());
        q2.push_back(make_surname());
    }

    cout << "Deques" << endl;
    print_deque(q1);
    print_deque(q2);

    for (int i = 0; i < n; i++) {
        r.push_back(q1.back());
        r.push_back(q2.back());
        q1.pop_back(); q2.pop_back();
    }

    cout << endl << "Result" << endl;
    print_deque(r);

    return 0;
}
