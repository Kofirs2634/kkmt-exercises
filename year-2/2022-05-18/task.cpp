#include <iostream>
#include <fstream>
#include <cmath>
#include <queue>
#include <deque>
using namespace std;

class Triangle {
    protected:
        string type;
        Triangle(int _a, int _b, int _c, string _type = "Undefined") {
            this->a = _a; this->b = _b; this->c = _c;
            this->type = _type;
        }
    public:
        int a; int b; int c;
        int get_perimeter() { return a + b + c; }
        double get_area() {
            double p = get_perimeter() / 2.0;
            return sqrt(p * (p - a) * (p - b) * (p - c));
        }
        string stringify() {
            return type + " triangle: sides are " + to_string(a) + ", " + to_string(b) + ", " + to_string(c) + " units; " + 
                "perimeter " + to_string(get_perimeter()) + " units; area " + to_string(get_area()) + " sq. units";
        }
};
class InvalidTriangle: public Triangle { // треугольник не существует
    public:
        InvalidTriangle(int _a, int _b, int _c): Triangle(_a, _b, _c, "Invalid") {}
        int get_perimeter() { return -1; }
        double get_area() { return -1.0; }
};
class RightTriangle: public Triangle { // прямоугольный треугольник
    public:
        RightTriangle(int _a, int _b, int _c): Triangle(_a, _b, _c, "Right") {}
};
class AcuteTriangle: public Triangle { // остроугольный треугольник
    public:
        AcuteTriangle(int _a, int _b, int _c): Triangle(_a, _b, _c, "Acute") {}
};
class ObtuseTriangle: public Triangle { // тупоугольный треугольник
    public:
        ObtuseTriangle(int _a, int _b, int _c): Triangle(_a, _b, _c, "Obtuse") {}
};
class EquilateralTriangle: public Triangle { // равносторонний треугольник
    public:
        EquilateralTriangle(int _a, int _b, int _c): Triangle(_a, _b, _c, "Equilateral") {}
};

int pq_at(priority_queue< int, deque<int>, greater<int> > _q, int _at) {
    for (int i = 0; i < _at; i++) _q.pop();
    return _q.top();
}

int main() {
    ifstream f("./input.txt");

    deque<InvalidTriangle> invalids;
    deque<EquilateralTriangle> equils;
    deque<RightTriangle> rights;
    deque<AcuteTriangle> acutes;
    deque<ObtuseTriangle> obtuses;

    while (!f.eof()) {
        int a, b, c;
        if (!(f >> a >> b >> c)) continue;

        priority_queue< int, deque<int>, greater<int> > _s;
        _s.push(a); _s.push(b); _s.push(c);

        int _cat = pow(pq_at(_s, 0), 2) + pow(pq_at(_s, 1), 2);
        int _hyp = pow(pq_at(_s, 2), 2);

        if (!((a + b > c) && (a + c > b) && (b + c > a)))
            invalids.push_back(InvalidTriangle(a, b, c));
        else if (a == b && b == c && c == a)
            equils.push_back(EquilateralTriangle(a, b, c));
        else if (_cat == _hyp)
            rights.push_back(RightTriangle(a, b, c));
        else if (_cat < _hyp)
            acutes.push_back(AcuteTriangle(a, b, c));
        else if (_cat > _hyp)
            obtuses.push_back(ObtuseTriangle(a, b, c));
        else
            cout << "Failed to resolve triangle " + to_string(a) + ", " + to_string(b) + ", " + to_string(c) << endl;
    }
    f.close();

    ofstream o;
    o.open("./output.txt");
    o << "== INVALID TRIANGLES ==" << endl;
    for (Triangle _t: invalids) o << _t.stringify() << endl;

    o << endl << "== EQUILATERAL TRIANGLES ==" << endl;
    for (Triangle _t: equils) o << _t.stringify() << endl;

    o << endl << "== RIGHT TRIANGLES ==" << endl;
    for (Triangle _t: rights) o << _t.stringify() << endl;

    o << endl << "== ACUTE TRIANGLES ==" << endl;
    for (Triangle _t: acutes) o << _t.stringify() << endl;

    o << endl << "== OBTUSE TRIANGLES ==" << endl;
    for (Triangle _t: obtuses) o << _t.stringify() << endl;
    o.close();

    return 0;
}
