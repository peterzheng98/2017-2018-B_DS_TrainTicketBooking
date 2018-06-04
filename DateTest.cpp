#include "DateAndTime.h"
#include <bits/stdc++.h>

using namespace std;
using namespace myAlgorithm;

int main()
{
	freopen("DateTest.out", "w", stdout);
	for(int i = 1000; i <= 9999; i++)
		for(int j = 1; j <= 12; j++)
			for(int k = 1; k <= 31; k++)
				cout << Date(i, j, k) << endl;
	cerr << clock() / 1000.0 << endl;
}
