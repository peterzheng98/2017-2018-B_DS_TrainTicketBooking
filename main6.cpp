//
// Created by Peter Zheng on 2018/06/07.
//

#include "Vector.h"
#include "String.h"
using namespace myAlgorithm;
int main(){
    Vector<String> str;
    for(int i = 0;i < 100000;i++) str.push_back("213");

    printf("%p", &str[9]);
}