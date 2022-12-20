#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <map>

using namespace std;

class GrovePositioningSystem {
public:
    GrovePositioningSystem(string filename) {
        getEncryptedFile(filename);
    }
    long long getGroveSum(int encuredCountCycle = 1, bool useDecryptionKey = false) {
        for (int i = 0; i < encuredCountCycle; i++) {
            clearEncreptedInfo();
            encrepted(useDecryptionKey);
        }
        long long sum = 0;
        sum = getValueAfterZero(1000) + getValueAfterZero(2000) + getValueAfterZero(3000);
        //displayEncryptedFile();
        return sum;
    }
private:
    struct element {
        int value = 0;
        bool needEncrepted = true;
    };
    list<element> encreptedFile;
    long long decryptionKey = 811589153ll;
    long long getValueAfterZero(int offset) {
        auto iter = encreptedFile.cbegin();
        int pos = 0;
        while ((*iter).value != 0) {
            iter++;
            pos++;
        }
        int newPos = (encreptedFile.size() + pos + offset) % encreptedFile.size();
        iter = encreptedFile.cbegin();
        while (newPos)
        {
            iter++;
            newPos--;
        }
        long long value = (*iter).value;
        return value;
    }
    void clearEncreptedInfo() {
        for (auto element : encreptedFile) {
            element.needEncrepted = true;
        }
    }
    void getEncryptedFile(string filename) {
        ifstream inputFile(filename);
        string line;
        while (getline(inputFile, line)) {
            istringstream iss(line);
            int number;
            iss >> number;
            element el;
            el.value = number;
            encreptedFile.push_back(el);
        }
        inputFile.close();
        //displayEncryptedFile();
    }

    void encrepted(bool useDecryptionKey = false) {
        int count = 0;
        while (count != encreptedFile.size()) {
            auto iter = encreptedFile.cbegin();
            long long pos = 0;
            while (!(*iter).needEncrepted) {
                iter++;
                pos++;
            }
            element cur = *iter;
            cur.needEncrepted = false;
            count++;
            long long size = encreptedFile.size();

            encreptedFile.erase(iter);
            iter = encreptedFile.cbegin();
            long long newPos = cur.value;
            if (useDecryptionKey) {
                newPos *= decryptionKey;
            }
            newPos += pos;
            while (newPos < 0) {
                newPos += encreptedFile.size();
            }
            newPos %= encreptedFile.size();
            if (newPos == 0) {
                newPos = encreptedFile.size();
            }
            while (newPos)
            {
                iter++;
                newPos--;
            }
            encreptedFile.insert(iter, cur);

            //cout << "step: " << count << endl;
            //displayEncryptedFile();
        }
    }
    void displayEncryptedFile() {
        for (auto element : encreptedFile) {
            cout << element.value << " ";
        }
        cout << endl;
    }
};

void day20_start(string filename) {
    cout << endl << "Day 20" << endl;
    GrovePositioningSystem grovePositioningSystem(filename);
    cout << "part 1: "  << grovePositioningSystem.getGroveSum() << endl;
    cout << "part 2: "  << grovePositioningSystem.getGroveSum(10, true) << endl;
}