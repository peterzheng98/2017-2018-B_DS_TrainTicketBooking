//
// Created by Peter Zheng on 2018/05/07.
//
//#include "String.h"
//#include <fstream>
#include <unistd.h>
#include "BPlusTree.hpp"

using namespace myAlgorithm;

int A = 774;
int B = 51702;
int C = 21910;

int randomR() {
    int d = random() % 10000;
    return A * d * d + B * d + C * d;
}

int main() {
    BPlusTree<int, int> bpt;
    srand(time(NULL));

//    for(int i = 0; )
}
