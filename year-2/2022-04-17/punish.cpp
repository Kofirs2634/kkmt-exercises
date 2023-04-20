#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

typedef struct Point {
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
} Point;

void print_point(Point _p) {
    cout << "(" << _p.x << "; " << _p.y << ") ";
}
void print_vector(vector<Point> _v) {
    for (Point _p: _v) print_point(_p);
    cout << endl;
}

int main() {
    srand(time(nullptr));
    double peny;
    cout << "Enter size of penalty: ";
    cin >> peny;

    int n;
    cout << "Enter amount of turns: ";
    cin >> n;
    n += 2;

    vector<Point> path;
    for (int i = 0; i < n; i++)
        path.push_back(Point(rand() % 20 - 10, rand() % 20 - 10));

    cout << "Car path" << endl;
    print_vector(path);

    int viol = 0;
    for (int i = 1; i < path.size() - 1; i++) {
        int prod = (path[i].x - path[i - 1].x) * (path[i + 1].y - path[i].y) -
            (path[i].y - path[i - 1].y) * (path[i + 1].x - path[i].x);
        if (prod > 0) viol++;
    }
    cout << "Violations: " << viol << endl;
    cout << "Sum of penalty: " << (double)(viol * peny) << endl;

    return 0;
}
