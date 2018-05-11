//
// Created by Peter Zheng on 2018/05/07.
//
#include "String.h"
//#include <fstream>
#include <unistd.h>
using namespace myAlgorithm;
int main(){
    String s1("abcde", 1), s2("abcd", 1), s3("bcde", 1);

    bool flag1 = (s1 >= s2);
    bool flag2 = (s1 >= s3);
    bool flag3 = (s2 >= s3);
    bool flag4 = (s1 == s2);
    bool flag5 = (s1 == s3);
    bool flag6 = (s1 >= s3);
    bool flag7 = (s1 < s3);
    int p;
    std::cin >> p;
}
