/* Test for BPlusTree */
#include "BPlusTree.hpp"
#include <algorithm>
#include <map>
using namespace std;
using namespace myAlgorithm;

BPlusTree<int, int> bpt;

int main(){
    for (int i = 1; i <= 10; ++i){
        bpt.insert(i, i);
    }
    return 0;
}