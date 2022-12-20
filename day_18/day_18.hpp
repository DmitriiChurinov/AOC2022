#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class BoilingBoulders
{
public:
    BoilingBoulders(string filename) {
        getDropsOfLavaFromFile(filename);
    }

    int getDropsOfLavaSquare() {
        for (auto item : dropsOfLava) {
            if (!dropsOfLava.count({ item.x - 1, item.y, item.z }))
            {
                lavaSquare.insert({ item.x - 1, item.y, item.z });
            }
            if (!dropsOfLava.count({ item.x + 1, item.y, item.z })) {
                lavaSquare.insert({ item.x + 1, item.y, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y - 1, item.z })) {
                lavaSquare.insert({ item.x, item.y - 1, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y + 1, item.z })) {
                lavaSquare.insert({ item.x, item.y + 1, item.z });
            }
            if (!dropsOfLava.count({ item.x, item.y, item.z - 1 })) {
                lavaSquare.insert({ item.x, item.y, item.z - 1 });
            }
            if (!dropsOfLava.count({ item.x, item.y, item.z + 1 })) {
                lavaSquare.insert({ item.x, item.y, item.z + 1 });
            }
        }
        return lavaSquare.size();
    }
private:
    struct point {
        int x, y, z;
        bool operator<(const point& other) const {
            return tie(x, y, z) < tie(other.x, other.y, other.z);
        }
    };
    set<point> dropsOfLava;
    multiset<point> lavaSquare;

    void getDropsOfLavaFromFile(string filename) {
        ifstream inputFile(filename);
        char ch;
        int x, y, z;
        while (inputFile >> x >> ch >> y >> ch >> z) {
            dropsOfLava.insert({ x, y, z });
        }
        inputFile.close();
    }
};

void day18_start(string filename) {
    cout << endl << "Day 18" << endl;
    BoilingBoulders boilingBoulders(filename);
    cout << "part 1: " << boilingBoulders.getDropsOfLavaSquare() << endl;
    cout << "part 2: " << endl;
}
