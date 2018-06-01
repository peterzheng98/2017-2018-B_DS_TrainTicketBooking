/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS
//#define _NO_DEBUG
//#define _LINUX_MODE
#include "BPlusTree.hpp"
#include <algorithm>
#include <iostream>
#include <map>
#include <ctime>
using namespace std;
using namespace myAlgorithm;

const int MAXN = 500000;

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

int a[MAXN + 10];
BPlusTree<int, BigSize> bpt(true);

int main() {
	srand(time(0));
    clock_t start, end;
    cout << "START" << endl;
    start = clock();
    for(int i = 1; i <= MAXN; i++)
    	a[i] = i;
    random_shuffle(a + 1, a + 1 + MAXN);
    for(int i = 1; i <= MAXN; i++) {
        auto p = bpt.search(a[i]);
        if (p.second)
            cout << i << "!!!" << endl;
        bpt.insert(a[i], i);
        p = bpt.search(a[i]);
        if (!p.second)
            cout << i << "!!" << endl;
    }
    for(int i = 1; i <= MAXN; i++)
    {
    	auto p = bpt.search(i);
    	if(!p.second)
    	{
    		cout << i << "!" << endl;
    	}
    	else
    	{
    		bpt.erase(i);
    		p = bpt.search(i);
    		if(p.second)
    		{
    			cout << i << "?" << endl;
    		}
    	}
    }
#ifdef _NO_DEBUG
    bpt.closeFile();
#endif
    end = clock();
    cout << (double)(end - start) / CLOCKS_PER_SEC << endl;
    system("PAUSE");
    return 0;
}
