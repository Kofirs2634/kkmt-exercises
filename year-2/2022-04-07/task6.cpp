#include <iostream>
#include <deque>
#include <queue>
#include <cstdlib>
#include <time.h>
using namespace std;

void print_queue(queue<int> _q) {
    while (_q.size()) {
        cout << _q.front() << " ";
        _q.pop();
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    queue<int> q;
    deque<int> _b;

    int n;
    cout << "Amount of numbers: ";
    cin >> n;

    for (int i = 0; i < n; i++)
        q.push(rand() % 500 - 250);

    cout << "Queue" << endl;
    print_queue(q);

    while (q.size()) {
        _b.push_front(q.front());
        q.pop();
    }
    while (_b.size()) {
        q.push(_b.front());
        _b.pop_front();
    }

    cout << "Reversed queue" << endl;
    print_queue(q);

    return 0;
}
