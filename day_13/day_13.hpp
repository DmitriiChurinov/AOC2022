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

int compareLines(string line1, string line2) {
    bool normalize = true;
    int position = -1;
    while (normalize) {
        position++;

        if (position >= line1.size() || position >= line2.size()) {
            normalize = false;
            position = -1;
        }
        else if (line1[position] == '[' && line2[position] == ']') {
            normalize = false;
            position = -2;
        }
        else if (line2[position] == '[' && line1[position] == ']') {
            normalize = false;
            position = -3;
        }
        else if (line1[position] != line2[position]) {
            if (line1[position] == '[') {
                line2.insert(position, 1, '[');
                if (line2[position + 1] >= '0' && line2[position + 1] <= '9') {
                    if (position + 2 < line2.size() && line2[position + 2] >= '0' && line2[position + 2] <= '9') {
                        line2.insert(position + 3, 1, ']');
                    }
                    else {
                        line2.insert(position + 2, 1, ']');
                    }
                }
                else {
                    normalize = false;
                    position = -2;
                }
            }
            else if (line2[position] == '[') {
                line1.insert(position, 1, '[');
                if (line1[position + 1] >= '0' && line1[position + 1] <= '9') {
                    if (position + 2 < line1.size() && line1[position + 2] >= '0' && line1[position + 2] <= '9') {
                        line1.insert(position + 3, 1, ']');
                    }
                    else {
                        line1.insert(position + 2, 1, ']');
                    }
                }
                else {
                    normalize = false;
                    position = -3;
                }
            }
            else {
                normalize = false;
            }
        }
    }
    int result = 0;
    if (position == -1) {
        result = 0;
    }
    else if (position == -2) {
        result = 1;
    }
    else if (position == -3) {
        result = -1;
    }
    else if (line1[position] >= '0' && line1[position] <= '9' && line2[position] >= '0' && line2[position] <= '9') {
        int num1 = line1[position] - (int)'0';
        int num2 = line2[position] - (int)'0';
        if (line1[position + 1] >= '0' && line1[position + 1] <= '9') {
            num1 *= 10;
            num1 += line1[position + 1] - (int)'0';
        }
        if (line2[position + 1] >= '0' && line2[position + 1] <= '9') {
            num2 *= 10;
            num2 += line2[position + 1] - (int)'0';
        }
        if (num1 < num2) {
            result = -1;
        }
        else if (num2 < num1){
            result =  1;
        }
    }
    else if (line1[position] == ']' && line2[position] == '\0') {
        result = 1;
    }
    else if (line2[position] == ']' && line1[position] == '\0') {
        result = -1;
    }
    else if (line2[position] == ']' && (line1[position] == ',' || line1[position] >= '0' && line1[position] <= '9')) {
        result = 1;
    }
    else if (line1[position] == ']' && (line2[position] == ',' || line2[position] >= '0' && line2[position] <= '9')) {
        result = -1;
    }
    return result;
}

void sortLines(vector<string> *lines) {
    vector<string> copyLines = (*lines);
    for (int i = 0; i < copyLines.size(); i++) {
        string line = copyLines[i];
        int ind = i;
        for (int j = i + 1; j < copyLines.size(); j++) {
            string line2 = copyLines[j];
            int res = compareLines(line2, line);
            if (res == -1) {
                line = line2;
                ind = j;
            }
        }
        string tmp = copyLines[i];
        copyLines[i] = line;
        copyLines[ind] = tmp;
    }
    (*lines) = copyLines;
}

void day13_start(string filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cout << "Файл потерялся оО" << endl;
        return;
    }

    //todo: переписать этот говнокод
    int part1{ 0 }, part2{ -1 };
    int index = 1;
    vector<string> lines;
    while (!inputFile.eof()) {
        string line1;
        getline(inputFile, line1);

        if (!line1.empty()) {
            string line2;
            getline(inputFile, line2);
            int res = compareLines(line1, line2);
            if (res <= 0) {
                part1 += index;
            }
            index++;
            lines.push_back(line1);
            lines.push_back(line2);
        }
    }
    lines.push_back("[[2]]");
    lines.push_back("[[6]]");
    sortLines(&lines);
    int pack2 = 0, pack6 = 0;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i] == "[[2]]") {
            pack2 = i + 1;
        }
        if (lines[i] == "[[6]]") {
            pack6 = i + 1;
        }
    }
    part2 = pack2 * pack6;
    cout << endl << "Day 13" << endl;
    cout << "part 1: " << part1 << endl;
    cout << "part 2: " << part2 << endl;
    inputFile.close();
}
