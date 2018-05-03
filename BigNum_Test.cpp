#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <ctime>
#include <queue>
#include <vector>
#include "BigNum.hpp"

using namespace std;
using namespace myAlgorithm;

typedef BigNum<int> Big;

void T1()
{
    Big A(2),B(10);
    A *= B;
    B *= A;
    A = A + B;
    B = A - B;
    A += B;
    B *= Big(2);
    A -= B;
    if(A == Big(200))
        puts("Test1 Correct");
    else puts("Test1 Fail");
}

void T2()
{
    for(int i=1;i<=4;i++)
    {
        int c = 2, d = rand()%10+20, num1 = 1;
        Big num2(1);
        while(d)
        {
            if(d % 2 == 1)
            {
                num1 *= c;
                num2 *= Big(c);
            }
            c= c*c;
            d>>=1;
        }
        if(Big(num1) != num2)
        {
            puts("Test2 Fail");
            return;
        }
    }
    puts("Test2 Correct");
}

int main()
{
    srand((int)time(NULL));
    T1();
    T2();
    return 0;
}
