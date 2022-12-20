#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

const int TIME_MAX = 32;
const int ORE_ROBOTS_MAX_COUNT = 10;
const int CLAY_ROBOTS_MAX_COUNT = 30;
const int OBSIDIAN_ROBOTS_MAX_COUNT = 40;
const int GEODE_ROBOTS_MAX_COUNT = 32;

struct State {
    int ore, clay, obsidian, geode;
    bool operator<(const State& o) const {
        return tie(ore, clay, obsidian) < tie(o.ore, o.clay, o.obsidian);
    }
};
map<State, int> cache[TIME_MAX + 1][ORE_ROBOTS_MAX_COUNT + 1][CLAY_ROBOTS_MAX_COUNT + 1][OBSIDIAN_ROBOTS_MAX_COUNT + 1][GEODE_ROBOTS_MAX_COUNT + 1];

class NotEnoughMinerals {
public:
    NotEnoughMinerals(string filename) {
        getPlansFromFiles(filename);
    }
    int getSumQuality(int time) {
        int sumQuality = 0;
        for (auto plan : plans) {
            clearCache();
            sumQuality += dfs(plan.id - 1, time, 1, 0, 0, 0, 0, 0, 0, 0) * plan.id;;
        }
        return sumQuality;
    }
    int getSumQuality2(int time) {
        int sumQuality2 = 1;
        for (auto plan : plans) {
            if (plan.id <= 3) {
                clearCache();
                sumQuality2 *= dfs(plan.id - 1, time, 1, 0, 0, 0, 0, 0, 0, 0);
            };
        }
        return sumQuality2;
    }
private:
    struct Plan {
        int id, oreRobotCostOre, clayRobotCostOre, obsidianRobotCostOre, obsidianRobotCostClay, geodeRobotCostOre, geodeRobotCostObsidian;
    };

    vector<Plan> plans;

    void getPlansFromFiles(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            string str;
            Plan plan;
            iss >> str >> plan.id >> str;
            iss >> str >> str >> str >> str >> plan.oreRobotCostOre >> str;
            iss >> str >> str >> str >> str >> plan.clayRobotCostOre >> str;
            iss >> str >> str >> str >> str >> plan.obsidianRobotCostOre >> str >> str >> plan.obsidianRobotCostClay >> str;
            iss >> str >> str >> str >> str >> plan.geodeRobotCostOre >> str >> str >> plan.geodeRobotCostObsidian >> str;
            plans.push_back(plan);
        }
        inputFile.close();
    }

    void clearCache() {
        for (int i = 0; i <= TIME_MAX; ++i)
        {
            for (int j = 0; j <= ORE_ROBOTS_MAX_COUNT; ++j)
            {
                for (int k = 0; k <= CLAY_ROBOTS_MAX_COUNT; ++k)
                {
                    for (int l = 0; l <= OBSIDIAN_ROBOTS_MAX_COUNT; ++l)
                    {
                        for (int m = 0; m <= GEODE_ROBOTS_MAX_COUNT; ++m)
                        {
                            cache[i][j][k][l][m].clear();
                        }
                    }
                }
            }
        }
    }
    int dfs(int id, int time, int oreRobotCount, int clayRobotCount, int obsidianRobotCount, int geodeRobotCount, int ore, int clay, int obsidian, int geode) {
        if (ore >= 30) {
            ore = 30;
        }
        if (clay >= 40) {
            clay = 40;
        }
        if (oreRobotCount > ORE_ROBOTS_MAX_COUNT || clayRobotCount > CLAY_ROBOTS_MAX_COUNT || obsidianRobotCount > OBSIDIAN_ROBOTS_MAX_COUNT || geodeRobotCount > GEODE_ROBOTS_MAX_COUNT) {
            return 0;
        }
        if (time == 0) {
            return geode;
        }
        State state = { ore, clay, obsidian };
        if (cache[time][oreRobotCount][clayRobotCount][obsidianRobotCount][geodeRobotCount].count(state)) {
            return cache[time][oreRobotCount][clayRobotCount][obsidianRobotCount][geodeRobotCount][state];
        }
        int& cur = cache[time][oreRobotCount][clayRobotCount][obsidianRobotCount][geodeRobotCount][state];

        if (plans[id].oreRobotCostOre <= ore) {
            cur = max(cur, dfs(id, time - 1, oreRobotCount + 1, clayRobotCount, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount - plans[id].oreRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
        }

        if (plans[id].clayRobotCostOre <= ore) {
            cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount + 1, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount - plans[id].clayRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
        }

        if (plans[id].obsidianRobotCostOre <= ore && plans[id].obsidianRobotCostClay <= clay) {
            cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount + 1, geodeRobotCount, ore + oreRobotCount - plans[id].obsidianRobotCostOre, clay + clayRobotCount - plans[id].obsidianRobotCostClay, obsidian + obsidianRobotCount, geode + geodeRobotCount));
        }

        if (plans[id].geodeRobotCostOre <= ore && plans[id].geodeRobotCostObsidian <= obsidian) {
            cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount, geodeRobotCount + 1, ore + oreRobotCount - plans[id].geodeRobotCostOre, clay + clayRobotCount, obsidian + obsidianRobotCount - plans[id].geodeRobotCostObsidian, geode + geodeRobotCount));
        }

        cur = max(cur, dfs(id, time - 1, oreRobotCount, clayRobotCount, obsidianRobotCount, geodeRobotCount, ore + oreRobotCount, clay + clayRobotCount, obsidian + obsidianRobotCount, geode + geodeRobotCount));
        return cur;
    }
};

void day19_start(string filename) {
    cout << endl << "Day 19" << endl;
    NotEnoughMinerals notEnoughMinerals(filename);
    // todo: подумать как оптимизировать
    cout << "part 1: " << notEnoughMinerals.getSumQuality(24) << endl;
    cout << "part 2: " << notEnoughMinerals.getSumQuality2(32) << endl;
}