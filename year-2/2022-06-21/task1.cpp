#include <iostream>
#include <fstream>
#include <deque>
using namespace std;

// посчитать слова, начинающиеся с заглавной буквы

bool starts_with_caps(string _word) {
    return _word[0] >= 'A' && _word[0] <= 'Z';
}

int main() {
    ifstream f("./files/input1.txt");
    ofstream o("./files/output1.txt", fstream::out);

    if (!f) {
        cout << "File not found" << endl;
        return 0;
    }

    deque<string> found;
    while (!f.eof()) {
        string _w;
        if (!(f >> _w)) continue;
        if (starts_with_caps(_w)) found.push_back(_w);
    }
    cout << "Found " << found.size() << " words" << endl;
    cout << "See ./files/output1.txt for full list" << endl;

    for (string _w: found) o << _w << endl;

    f.close();
    o.close();

    return 0;
}