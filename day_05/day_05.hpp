#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iterator>
#include <functional>
#include <fstream>

using namespace std;

void day4_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
    }

    int part1{ 0 }, part2{ 0 };

    while (!inputFile.eof()) {
        string line;
        getline(inputFile, line);
    }

    cout << endl << "Day 5" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
