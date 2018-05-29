/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS
//#define _NO_DEBUG
//#define _LINUX_MODE
#define MAXNN 10000
#include "BPlusTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
using namespace std;
using namespace myAlgorithm;

struct BigSize {
    int k = 0;
    int a[100];

    BigSize(int n = 0) : k(n) {}

    BigSize &operator =(const BigSize &b) {
        k = b.k;
        return *this;
    }

    bool operator <(const BigSize &b) const {
        return k < b.k;
    }
};

BPlusTree<int, int> bpt(true);

int main() {
    clock_t start, end;
    cout << "START" << endl;
    start = clock();
    for (int i = MAXNN; i >= 1; --i) {
        int s = rand() % MAXNN;
        bpt.insert(s, i);
    }
    /*printf("After Insertion.\n");
    for (int i = MAXNN; i >= 1; --i) {
        auto p = bpt.search(i);
        if (p.first.k != i || !p.second) {
            cout << i << endl;
        }
        bpt.erase(i);
        p = bpt.search(i);
        if (p.second) {
            cout << i << endl;
        }
    }*/
#ifdef _NO_DEBUG
    bpt.closeFile();
#endif
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    system("PAUSE");
    return 0;
}
