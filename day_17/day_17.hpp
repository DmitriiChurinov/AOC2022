﻿#include <vector>
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
    long long simulate(long long year) {
        long long patternIndex = 0;
        long long currentHeight = 0;
        seen.clear();
        latest.clear();

        for (long long currentYear = 0; currentYear < year; ++currentYear) {
            set<pair<long long, long long>> currentShape = getShape(currentYear, currentHeight);
            while (true) {
                set<pair<long long, long long>> tmp;
                long long shiftDif = 1;
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
            if (currentYear % 10000 == 5100) {
                cout << "current year: " << currentYear << endl;
                cout << "check year: " << currentYear - 100 << endl;
                long long period = checkPeriod(currentYear - 100);
                cout << "period height: " << period << endl;
            }
        }
        return currentHeight;
    }
    long long checkPeriod(long long height) {
        long long period = -1;
        int save[50][7];
        for (long long i = height; i > height - 50; i--) {
            for (long long x = 0; x < 7; x++) {
                save[height - i][x] = seen.count({ x, i });
            }
        }
        for (long long i = height - 50; i >= 50; i --) {
            bool check = true;
            for (long long j = 0; j < 50 && check; j++) {
                for (long long x = 0; x < 7 && check; x++) {
                    if (save[j][x] != seen.count({ x, i - j })) {
                        check = false;
                    }
                }
            }
            if (check) {
                period = height - i;
                cout << "|";
                for (long long x = 0; x < 7; x++) {
                    if (seen.count({ x, height })) {
                        cout << '#';
                    }
                    else {
                        cout << '.';
                    }
                }
                cout << "| " << height << " " << latest[height] << endl;
                cout << "|";
                for (long long x = 0; x < 7; x++) {
                    if (seen.count({ x, i })) {
                        cout << '#';
                    }
                    else {
                        cout << '.';
                    }
                }
                cout << "| " << i << " " << latest[i] << endl;
                cout << "period year: " << latest[height] - latest[i] << endl;
                long double answer = ((long double)(1000000000000LL - latest[i])) / ((long double)(latest[height] - latest[i])) * period - i;
                cout << "answer 1000000000000: " << (long long) answer << endl;
                break;
            }
        }
        return period;
    }
    void displaySimulate(long long height) {
        for (long long i = height + 10; i >= 0; i--) {
            cout << "|";
            for (long long x = 0; x < 7; x++) {
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
    vector<set<pair<long long, long long>>> peculiarShapes =
    {
        {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
        {{1, 0}, {0, 1}, {1, 1}, {1, 2}, {2, 1}},
        {{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}},
        {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}}
    };
    set<pair<long long, long long>> seen;
    map<long long, long long> latest;
    void readPattern(string filename) {
        ifstream inputFile(filename);
        inputFile >> pattern;
        inputFile.close();
    }
    void insert(pair<long long, long long> x, long long& height, long long currentYear) {
        seen.insert(x);
        height = max(height, x.second + 1);
        latest[x.second] = currentYear;
    }

    bool checkInsert(pair<long long, long long> p) {
        return p.first >= 0 && p.first < 7 && !seen.count(p) && p.second >= 0;
    }

    set<pair<long long, long long>> shift(set<pair<long long, long long>> shape, long long dx, long long dy) {
        set<pair<long long, long long>> nxt;
        for (auto p : shape) {
            pair<long long, long long> pp = { p.first + dx, p.second + dy };
            if (!checkInsert(pp)) {
                return {};
            }
            nxt.insert(pp);
        }
        return nxt;
    }

    set<pair<long long, long long>> getShape(long long year, long long height) {
        set<pair<long long, long long>> currentShape;
        long long offsetX = 2, offsetY = height + 3;
        for (pair<long long, long long> shape : peculiarShapes[year % peculiarShapes.size()]) {
            currentShape.insert({ shape.first + offsetX, shape.second + offsetY });
        }

        return currentShape;
    }

};

void day17_start(string filename) {
    cout << endl << "Day 17" << endl;
    ifstream inputFile(filename);
    PyroclasticFlow pyroclasticFlow(filename);

    long long part1 = pyroclasticFlow.simulate(2022);
    //pyroclasticFlow.displaySimulate(2022);
    cout << "part 1: " << part1 << endl;
    long long part2 = pyroclasticFlow.simulate(1000000000000);

    // TODO: Найти период и начала периода
    cout << "part 2: " << part2 << endl;
}