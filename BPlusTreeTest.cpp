/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS
//#define _NO_DEBUG
//#define _LINUX_MODE
#define MAXNN 100000
#include "BPlusTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
using namespace std;
using namespace myAlgorithm;

BPlusTree<int, pair<long long, long long>> bpt(true);

int main() {
    for (int i = MAXNN; i >= 1; --i) {
        bpt.insert(i, make_pair(i, i));
       // printf("Insertion %d Accepted.\n", i);
    }
    printf("After Insertion.\n");
    for (int i = 1; i <= MAXNN; ++i) {
#ifndef _LINUX_MODE
        if (i == 21690)
            system("PAUSE");
#endif // !_LINUX_MODE

        auto p = bpt.search(i);
        if (p.first.first != i || !p.second) {
            cout << i << endl;
#ifndef _LINUX_MODE
            system("PAUSE");
#endif
        }
        bpt.erase(i);
        p = bpt.search(i);
        if (p.second) {
            cout << i << endl;
#ifndef _LINUX_MODE
            system("PAUSE");
#endif
        }
    }
#ifdef _NO_DEBUG
    bpt.closeFile();
#endif
    return 0;
}
