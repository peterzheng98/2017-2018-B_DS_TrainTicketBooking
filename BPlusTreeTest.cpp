/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS
//#define _NO_DEBUG
//#define _LINUX_MODE
#define MAXNN 500000
#include "BPlusTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
#include "Vector.h"
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

struct DoubleKey {
    int p = 0, q = 0;

    DoubleKey(int pp = 0, int qq = 0) : p(pp), q(qq) {}
    bool operator <(const DoubleKey &dk) const {
        return p < dk.p || (p == dk.p && q < dk.q);
    }
    int first() const {
        return p;
    }
};

BPlusTree<int, int> bpt(true);
//BPlusTree<DoubleKey, int> dkt(true);

int main() {
    clock_t start, end;
    cout << "START" << endl;
    start = clock();
    /*for (int i = MAXNN; i >= 1; --i) {
        for (int j = 1; j <= MAXNN; ++j) {
            dkt.insert(DoubleKey(j, i), i);
        }
    }
    for (int i = 1; i <= 10; ++i) {
        auto ans = dkt.searchFirst(DoubleKey(i));
        for (int j = 0; j < ans.size(); ++j)
            cout << ans[j] << ' ';
        cout << endl;
    }*/
    for (int i = MAXNN; i >= 1; --i) {
        //if (i == 281)
            //cout << i << endl;
        bpt.insert(i, i);
        auto p = bpt.search(i);
        if (!p.second) {
            cout << i << endl;
        }
    }
    printf("After Insertion.\n");
    for (int i = MAXNN; i >= 1; --i) {
        auto p = bpt.search(i);
        if (p.first != i || !p.second) {
            cout << i << endl;
        }
        bpt.erase(i);
        p = bpt.search(i);
        if (p.second) {
            cout << i << endl;
        }
    }
#ifdef _NO_DEBUG
    bpt.closeFile();
    //dkt.closeFile();
#endif
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    system("PAUSE");
    return 0;
}
