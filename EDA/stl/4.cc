#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() {
    string word;
    map<string, int> vec;
    
    while (cin >> word) {
        if (word == "minimum?") {
            if (!vec.empty()) {
                map<string, int>::const_iterator it = vec.begin();
                cout << "minimum: " << it->first << ", " << it->second <<" time(s)" << endl;
            }
            else cout << "indefinite minimum" << endl;
        }
        else if (word == "maximum?") {
            if (!vec.empty()) {
                map<string, int>::const_iterator it = vec.end();
                --it;
                cout << "maximum: " << it->first << ", " << it->second <<" time(s)" << endl;
            }
            else cout << "indefinite maximum" << endl;
        }
        else if (word == "store") {
            cin >> word;
            map<string, int>::const_iterator it = vec.find(word);
            if (it != vec.end()) {
                ++vec[word];
            }
            else vec.insert(make_pair(word, 1));
        }
        else if (word == "delete") {
            cin >> word;
            map<string, int>::const_iterator it = vec.find(word);
            if (it != vec.end() and it->second > 0) {
                if (it->second > 1) {
                --vec[word];
                }
                else {
                    vec.erase(word);
                }
            }
        }
    }
}
