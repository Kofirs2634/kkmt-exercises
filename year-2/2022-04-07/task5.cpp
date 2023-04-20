#include <iostream>
#include <deque>
#include <queue>
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

typedef struct Student {
    string surname;
    int group;
    int birth_year;
    Student() {
        this->surname = make_surname();
        this->group = rand() % 100 + 1000;
        this->birth_year = rand() % 25 + 1980;
    }
} Student;

int main() {
    srand(time(nullptr));
    deque<Student> q;
    int n;
    cout << "Amount of students: ";
    cin >> n;
    for (int i = 0; i < n; i++)
        q.push_back(Student());
    
    cout << endl << "Student List" << endl;
    for (int i = 0; i < n; i++) {
        Student _s = q[i];
        cout << _s.surname << " born in " << _s.birth_year << " and studying in group " << _s.group << endl;
    }

    queue<Student> fq;
    int year;
    cout << endl << "Filter by year: ";
    cin >> year;

    cout << "Born in " << year << ": " << endl;
    for (int i = 0; i < n; i++) {
        Student _s = q[i];
        if (_s.birth_year == year) {
            fq.push(_s);
            cout << _s.surname << " from group " << _s.group << endl;
        }
    }

    return 0;
}
