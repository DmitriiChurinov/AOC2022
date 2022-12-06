#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

using namespace std;

int checkUnigue(string code, int position, int length) {
    string copy = code;
    sort(copy.begin() + position, copy.begin() + position + length);
    bool unique = true;
    for (int j = 0; j < length - 1; j++) {
        if (copy[j + position] == copy[j + position + 1]) {
            unique = false;
            break;
        }
    }
    if (unique) {
        return position + length;
    }
    return -1;
}
void day6_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "���� �� ������ ��" << endl;
        return;
    }

    int part1{ -1 }, part2{ -1 };
    string line;
    getline(inputFile, line);

    for (int i = 0; i + 13 < line.size(); i++) {
        string copy = line;
        sort(copy.begin() + i, copy.begin() + i + 14);
        if (part1 < 0) {
            part1 = checkUnigue(line, i, 4);
        }
        if (part2 < 0) {
            part2 = checkUnigue(line, i, 14);
        }
    }

    cout << endl << "Day 6" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;

    inputFile.close();
}
