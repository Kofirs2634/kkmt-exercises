#include <iostream>
#include <fstream>
using namespace std;

class Auto {
    public:
        string name;
        int max_speed;

        Auto(string _n, int _ms) {
            this->name = _n;
            this->max_speed = _ms;
        }
        virtual int get_cost() {
            return max_speed * 100;
        }
        void upgrade() {
            max_speed += 10;
        }
        string get_info() {
            return name + ": max " + to_string(max_speed) + " km/h; costs " + to_string(get_cost()) + " a. u.";
        }
};
class DeputyAuto: public Auto {
    public:
        DeputyAuto(string _n, int _ms): Auto(_n, _ms) {};
        int get_cost() override {
            return max_speed * 250;
        }
};

int main() {
    ofstream f("./output3.txt", ofstream::out);

    Auto _a = Auto("Lada Priora", 140);
    DeputyAuto _da = DeputyAuto("Lada Granta", 200);

    cout << _a.get_info() << endl;
    cout << _da.get_info() << endl;

    f << _a.get_info() << endl;
    f << _da.get_info() << endl;
    cout << "File was written" << endl;

    f.close();

    return 0;
}