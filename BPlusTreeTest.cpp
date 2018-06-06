/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS

#define MAXNN 500000
#include "BPlusTree.hpp"
#include "Vector.h"
#include "CoreData.h"
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
	
	bool operator ==(const BigSize &b) const {
        return k == b.k;
    }
};

const int N = 1e5;
int a[N + 10];
clock_t start_, end_;

void Test1()
{
	BPlusTree<int, BigSize> bpt(true, "tmp/cache.dat");
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
	BPlusTree<int, BigSize> bpt(true, "tmp/cache.dat");
	srand(time(0));
	printf("Test2:");
	start_ = clock();
	for(int i = 1; i <= N; i++)
		a[i] = i;
	random_shuffle(a + 1, a + 1 + N);
	for(int i = 1; i <= N / 10; i++)
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
	for(int i = N / 10 + 1; i <= N; i++)
	{
		int nowx = rand() % N + 1;
		auto p = bpt.search(nowx);
		if(p.second)
		{
			bpt.erase(nowx);
			p = bpt.search(nowx);
			if(p.second)
			{
				puts("find value after erase it!");
				return;
			}
		}
		else
		{
			bpt.insert(nowx, i);
			p = bpt.search(nowx);
			if(!p.second)
			{
				puts("can't find value after insert it!");
				return;
			}
		}
	}
	printf("passed! ");
    end_ = clock();
    cout << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
}

void Test3()
{
	BPlusTree<int, BigSize> bpt(true, "tmp/cache.dat");
	srand(time(0));
    start_ = clock();
	printf("Test3:");
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
	bpt.clear();
	for(int i = 1; i <= N; i++)
	{
		auto p = bpt.search(i);
		if(p.second)
		{
			puts("find value after clear tree!");
			return;
		}
	}
	printf("passed! ");
    end_ = clock();
    cout << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
}

const int N_ = 500;
const int M = 250;

void Test4()
{
	static int flag[N_ + 10][N_ + 10];
	static int bo[N_ + 10];
	BPlusTree<Pair<int, BigSize>, int> bpt(true, "tmp/cache.dat");
	srand(time(0));
    start_ = clock();
	printf("Test4:");
	int n = N_, m = M;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
			a[j] = j;
		random_shuffle(a + 1, a + 1 + n);
		for(int j = 1; j <= m; j++)
		{
			bpt.insert(Pair<int, BigSize>(i, j), a[j]);
			flag[i][a[j]] = 1;
		}
	}
	for(int i = 1; i <= n; i++)
	{
		Vector<int> v = bpt.searchFirst(Pair<int, BigSize>(i, 0));
		if(v.size() != m)
		{
			puts("the number of value went wrong!");
			return;
		}
		memset(bo, 0, sizeof(bo));
		for(int j = 0; j < m; j++)
		{
			if(!flag[i][v[j]])
			{
				puts("extra elements appear!");
				return;
			}
			if(bo[v[j]])
			{
				puts("an element appear twice!");
				return;
			}
			bo[v[j]] = 1;
		}
	}
	printf("passed! ");
    end_ = clock();
    cout << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
}

const int N__ = 50;
const int M_ = 20;

void Test5()
{
	static int flag[N__ + 10][N__ + 10][N__ + 10];
	static int bo[N__ + 10];
	BPlusTree<TriplePair<int, int, BigSize>, int> bpt(true, "tmp/cache.dat");
	srand(time(0));
    start_ = clock();
	printf("Test5:");
	int n = N__, m = M_;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			for(int k = 1; k <= n; k++)
				a[k] = k;
			random_shuffle(a + 1, a + 1 + n);
			for(int k = 1; k <= m; k++)
			{
				bpt.insert(TriplePair<int, int, BigSize>(i, j, k), a[k]);
				flag[i][j][a[k]] = 1;
			}
		}
	}
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			Vector<int> v = bpt.searchFirstAndSecond(TriplePair<int, int, BigSize>(i, j, 0));
			printf("%d\n", v.size());
			if(v.size() != m)
			{
				puts("the number of value went wrong!");
				return;
			}
			memset(bo, 0, sizeof(bo));
			for(int k = 0; k < m; k++)
			{
				if(!flag[i][j][v[k]])
				{
					puts("extra elements appear!");
					return;
				}
				if(bo[v[k]])
				{
					puts("an element appear twice!");
					return;
				}
				bo[v[k]] = 1;
			}
		}
	}
	printf("passed! ");
    end_ = clock();
    cout << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
}

void Test6()
{
}

int main() {
    cout << "START" << endl;
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	Test6();
    return 0;
}
