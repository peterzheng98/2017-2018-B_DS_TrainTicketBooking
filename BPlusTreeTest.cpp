/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS
//#define _NO_DEBUG

#include "BPlusTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
using namespace std;
using namespace myAlgorithm;

BPlusTree<int, int> bpt(true);

int main(){
    for (int i = 100000; i >= 1; --i){
        bpt.insert(i, i);
    }
    for (int i = 100000; i >= 1; --i) {
        auto p = bpt.search(i);
        if (p.first != i || !p.second) {
            cout << i << endl;
            system("PAUSE");
        }
        bpt.erase(i);
        p = bpt.search(i);
        if (p.second) {
            cout << i << endl;
            system("PAUSE");
        }
    }
#ifdef _NO_DEBUG
    bpt.closeFile();
#endif
    return 0;
}