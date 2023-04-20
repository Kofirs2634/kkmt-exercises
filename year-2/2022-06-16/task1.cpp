#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool has_consonant(string _s) {
    const vector<string> _c{"b", "c", "d", "f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t", "v", "x", "z"};
    bool flag = false;
    for (string con: _c) {
        if (!flag && _s.find(con) != -1) flag = true;
    }
    return flag;
}

int main() {
    cout << "Opening input file..." << endl;
    fstream f("./input1.txt");

    if (!f) {
        cout << "File not found!" << endl;
        return 0;
    }

    cout << "Reading words..." << endl;
    int total = 0;
    int cons = 0;
    while (!f.eof()) {
        string word;
        if (!(f >> word)) continue;
        total++;
        if (has_consonant(word)) cons++;
    }

    cout << "Total words: " << total << endl;
    cout << "Words with consonants: " << cons << endl;

    f.close();
    return 0;
}