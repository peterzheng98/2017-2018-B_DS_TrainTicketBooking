/* Test for BPlusTree */
#define _CRT_SECURE_NO_WARNINGS

#include "BPlusTree.hpp"
#include <algorithm>
#include <map>
#include <ctime>
using namespace std;
using namespace myAlgorithm;

BPlusTree<int, int> bpt(true);

int main(){
    for (int i = 1; i <= 10; ++i){
        bpt.insert(i, i);
    }
    for (int i = 1; i <= 10; ++i) {
        auto p = bpt.search(i);
        if (!p.second || p.first != i)
            system("PAUSE");
    }
    return 0;
}