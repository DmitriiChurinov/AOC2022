#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class PyroclasticFlow {
public:
    PyroclasticFlow(string filename) {
        readPattern(filename);
    }
    long long simulate(long year) {
        int patternIndex = 0;
        int currentHeight = 0;
        for (int currentYear = 0; currentYear < year; ++currentYear) {
            set<pair<int, int>> currentShape = getShape(currentYear, currentHeight);
            while (true) {
                set<pair<int, int>> tmp;
                int shiftDif = 1;
                if (pattern[patternIndex++ % pattern.size()] == '<') {
                    shiftDif = -1;
                }
                tmp = shift(currentShape, shiftDif, 0);
                if (!tmp.empty()) {
                    currentShape = tmp;
                }
                tmp = shift(currentShape, 0, -1);
                if (tmp.empty()) {
                    for (auto p : currentShape) {
                        insert(p, currentHeight, currentYear);
                    }
                    break;
                }
                else {
                    currentShape = tmp;
                }
            }
        }
        return currentHeight;
    }
    void displaySimulate(int height) {
        for (int i = height + 10; i >= 0; --i) {
            cout << "|";
            for (int x = 0; x < 7; ++x) {
                if (seen.count({ x, i })) {
                    cout << '#';
                }
                else {
                    cout << '.';
                }
            }
            cout << "| " << i << " " << latest[i] << endl;
        }
    }
private:
    string pattern;
    vector<set<pair<int, int>>> peculiarShapes =
    {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{1, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 1}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}
    };
    set<pair<int, int>> seen;
    map<int, int> latest;
    void readPattern(string filename) {
        ifstream inputFile(filename);
        inputFile >> pattern;
        inputFile.close();
    }
    void insert(pair<int, int> x, int& height, int currentYear) {
        seen.insert(x);
        height = max(height, x.second + 1);
        latest[x.second] = currentYear;
    }

    bool checkInsert(pair<int, int> p) {
        return p.first >= 0 && p.first < 7 && !seen.count(p) && p.second >= 0;
    }

    set<pair<int, int>> shift(set<pair<int, int>> shape, int dx, int dy) {
        set<pair<int, int>> nxt;
        for (auto p : shape) {
            pair<int, int> pp = { p.first + dx, p.second + dy };
            if (!checkInsert(pp)) {
                return {};
            }
            nxt.insert(pp);
        }
        return nxt;
    }

    set<pair<int, int>> getShape(int year, int height) {
        set<pair<int, int>> currentShape;
        int offsetX = 2, offsetY = height + 3;
        for (pair<int, int> shape : peculiarShapes[year % peculiarShapes.size()]) {
            currentShape.insert({ shape.first + offsetX, shape.second + offsetY });
        }

        return currentShape;
    }

};

void day17_start(string filename) {
    cout << endl << "Day 17" << endl;
    ifstream inputFile(filename);
    PyroclasticFlow pyroclasticFlow(filename);

    int part1 = pyroclasticFlow.simulate(2022);
    pyroclasticFlow.displaySimulate(2022);
    cout << "part 1: " << part1 << endl;
    // TODO: нужно найти начала и период
    cout << "part 2: " << endl;
}
