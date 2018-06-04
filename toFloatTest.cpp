#include <bits/stdc++.h>
#include "String.h"

using namespace std;
using namespace myAlgorithm;

int main()
{
	freopen("all.in", "r", stdin);
	freopen("tmp.out", "w", stdout);
	String tmp = "гд"; 
	String s;
	cin >> s;
	while(s != "END")
	{ 
		if(s[0] == -17 && s[1] == -65)printf("%.6f\n", s.toFloat());
		cin >> s;
	}
}
