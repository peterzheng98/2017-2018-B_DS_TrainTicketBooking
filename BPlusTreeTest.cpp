/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS

#define MAXNN 500000
#include "BPlusTree.hpp"
#include "Vector.h"
#include <bits/stdc++.h>

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

BPlusTree<int, BigSize> bpt(true, "tmp/cache.dat");

const int N = 1e5;
int a[N + 10];
clock_t start_, end_;

void Test1()
{
	srand(time(0));
    start_ = clock();
	printf("Test1:");
	for(int i = 1; i <= N; i++)
		a[i] = i;
	random_shuffle(a + 1, a + 1 + N);
	for(int i = 1; i <= N; i++)
	{
		auto p = bpt.search(a[i]);
		if(p.second)
		{
			puts("find value that doesn't exist!");
			return;
		}
		bpt.insert(a[i], i);
		p = bpt.search(a[i]);
		if(!p.second)
		{
			puts("can't find value after insert it!");
			return;
		}
	}
	for(int i = 1; i <= N; i++)
	{
		auto p = bpt.search(i);
		if(!p.second)
		{
			puts("can't find value in tree!");
			return;
		}
		else
		{
			bpt.erase(i);
			p = bpt.search(i);
			if(p.second)
			{
				puts("find value after erase it!");
				return;
			}
		}
	}
	printf("passed! ");
    end_ = clock();
    cout << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
}

void Test2()
{
	printf("Test2:");
}

void Test3()
{
}

void Test4()
{
}

void Test5()
{
}

void Test6()
{
}

int main() {
    cout << "START" << endl;
#ifdef _NO_DEBUG
    bpt.closeFile();
    //dkt.closeFile();
#endif
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
    return 0;
}
