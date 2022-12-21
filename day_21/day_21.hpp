#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class MonkeyMath {
public:
    MonkeyMath(string filename) {
        getMonkeyJobFromFile(filename);
    }
    long long getCompliteOperationValue(string monkeyName) {
        MonkeyJob monkeyJob = monkeyDictionary[monkeyName];
        if (!monkeyJob.operationComplite) {
            long long monkeyJobValue1 = getCompliteOperationValue(monkeyJob.monkey1);
            long long monkeyJobValue2 = getCompliteOperationValue(monkeyJob.monkey2);
            long long jobValue = monkeyJobValue1;
            switch (monkeyJob.operation) {
            case '+':
                jobValue += monkeyJobValue2;
                break;
            case '-':
                jobValue -= monkeyJobValue2;
                break;
            case '/':
                jobValue /= monkeyJobValue2;
                break;
            case '*':
                jobValue *= monkeyJobValue2;
                break;
            }
            monkeyJob.jobValue = jobValue;
            monkeyJob.operationComplite = true;
        }
        return monkeyJob.jobValue;
    }
private:
    struct MonkeyJob {
        long long jobValue;
        char operation;
        string monkey1;
        string monkey2;
        bool operationComplite = false;
    };
    map<string, MonkeyJob> monkeyDictionary;
    void getMonkeyJobFromFile(string filename) {
        ifstream inputFile(filename);
        string line;

        while (getline(inputFile, line)) {
            if (line.empty()) {
                break;
            }
            istringstream iss(line);
            string monkeyName;
            iss >> monkeyName;
            monkeyName = monkeyName.substr(0, 4);
            MonkeyJob monkeyJob;
            if (line[6] >= '0' && line[6] <= '9') {
                iss >> monkeyJob.jobValue;
                monkeyJob.operationComplite = true;
            }
            else {
                iss >> monkeyJob.monkey1 >> monkeyJob.operation >> monkeyJob.monkey2;
            }
            monkeyDictionary[monkeyName] = monkeyJob;
        }
        inputFile.close();
    }
};
void day21_start(string filename) {
    cout << endl << "Day 21" << endl;
    MonkeyMath monkeyMath(filename);
    cout << "part 1: " << monkeyMath.getCompliteOperationValue("root") << endl;
    // todo: подумать над оптимизацией
    cout << "part 2: " << endl;
}