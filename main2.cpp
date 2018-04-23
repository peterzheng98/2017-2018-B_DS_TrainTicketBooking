//
// Created by Peter Zheng on 2018/04/23.
//

#include "Set.hpp"
#include <set>
#include <cstdio>
using namespace myAlgorithm;

std::set<std::pair<int, int>> p;
int current = 134234;
const int mod = 200000000 + 7;
int Random(){
    current = ((current * current * 2) + current * 3) % mod;
    if(current < 0) current = - current;
    return current;
}

int main(){
    printf("Test Group #1: Constructor(Default, Copy), Insert, Iterator(Orderly Accessing):\n");
    printf("--------------------------------------------------\n");
    Set<std::pair<int, int> > mySet;
    Set<std::pair<int, int> > mySet2 = mySet, mySet3(mySet2);
    for(int i = 0;i < 200000; i++){
        int num = Random();
        int num2 = Random();
        std::pair<int, int> ii;
        ii.first = num;
        ii.second = num2;
        mySet.insert(ii);
        mySet2.insert(ii);
        mySet3.insert(ii);
        p.insert(ii);
    }
    if(mySet.size() == mySet2.size() && mySet2.size() == mySet3.size() && mySet.size() == p.size()){
        printf("Phase #1: Size Test  RESULT: Accepted\n");
    }
    else {
        printf("Phase #1: Size Test  Standard Answer:%d -> Your Set: %d/%d/%d RESULT: Wrong Answer\n",p.size(),mySet.size(),mySet2.size(),mySet3.size());
        return 0;
    }
    std::set<std::pair<int, int> >::iterator set_iter = p.begin();
    Set<std::pair<int, int> >::iterator my_iter = mySet.begin();
    int phase = 1;
    for(;set_iter != p.end(); set_iter++, my_iter++, phase++){
        if(*set_iter != *my_iter){
            printf("Phase #2 - %d: Iterator Accessing  Standard Answer:%d -> Your Answer: %d  RESULT: Wrong Answer\n", phase, *my_iter, *set_iter);
            return 0;
        }
    }
    printf("Phase #2: Iterator Accessing & Insertion RESULT: Accepted\n");

}