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

void drawPixel(vector<char>* image, int x, int cycleNumber) {
    int pixelPosition = (cycleNumber - 1) % 40;

    if (pixelPosition >= x && pixelPosition <= x + 2 || pixelPosition == 0 && x >= 38) {
        image->push_back('#');
    }
    else {
        image->push_back('.');
    }
}
void day10_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "‘айл не найден ќо" << endl;
        return;
    }

    int part1{ -1 };
    int cycleNum = 1;
    vector<int> cycles;
    vector<char> cyclesImage;
    cycles.push_back(cycleNum);
    cyclesImage.push_back('.');
    while (!inputFile.eof()) {
        comandLine line;
        string s;
        int num = 0;
        inputFile >> s;
        if (!s.empty()) {
            int np = cycleNum + num;

            if (s == "noop") {
                cycles.push_back(cycleNum);
                drawPixel(&cyclesImage, cycleNum, cycles.size());
            }
            if (s == "addx") {
                inputFile >> num;
                cycles.push_back(cycleNum);
                drawPixel(&cyclesImage, cycleNum, cycles.size());
                cycles.push_back(cycleNum);
                drawPixel(&cyclesImage, cycleNum, cycles.size());

                cycleNum += num;
            }
        }
        else {
            break;
        }
    }

    part1 = 0;
    for (int i = 20; i < cycles.size(); i += 40) {
        part1 += i * cycles[i];
    }



    cout << endl << "Day 10" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << endl;
    for (int i = 1; i < cyclesImage.size(); i++) {
        cout << cyclesImage[i];
        if (i % 40 == 0) {
            cout << endl;
        }
    }
    inputFile.close();
}
