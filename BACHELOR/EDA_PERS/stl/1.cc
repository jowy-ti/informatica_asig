#include<iostream>
#include<list>
using namespace std;

void save(list<int>& vec, int num) {
    list<int>::const_iterator it = vec.begin();
    if (!vec.empty()) {
        while (it != vec.end() and num < *it) {
            ++it;
        }
    }
    vec.insert(it,num);
}

int main() {
    int num;
    char inst;
    list<int> vec;
    while (cin >> inst) {
        list<int>::iterator it = vec.begin();
        if (inst == 'S') {
            cin >> num;
            save(vec, num);
        }
        else if (inst == 'A') {
            if (vec.empty()) cout << "error!" << endl;
            else cout << *it << endl;
        }
        else if (inst == 'R') {
            if (vec.empty()) cout << "error!" << endl;
            else vec.pop_front();
        }
        else if (inst == 'I') {
            cin >> num;
            if (vec.empty()) cout << "error!" << endl;
            else {
                int result = *it + num;
                vec.erase(it);
                vec.push_front(result);
            }
        }
        else if (inst == 'D') {
            cin >> num;
            if (vec.empty()) cout << "error!" << endl;
            else {
                int result = *it - num;
                vec.erase(it);
                it = vec.begin();
                while (it != vec.end() and result < *it) {
                    ++it;
                }
                vec.insert(it,result);
            }
        }
    }
}
