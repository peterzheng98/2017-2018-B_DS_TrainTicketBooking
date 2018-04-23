//
// Created by Peter Zheng on 2018/04/23.
//

#include "Set.hpp"
#include <set>
#include <cstdio>

using namespace myAlgorithm;

std::set<int> p;
int current = 134234;
const int mod = 200000000 + 7;

int Random() {
    current = ((current * current * 2) + current * 3) % mod;
    if (current < 0) current = -current;
    return current;
}

int main() {
    printf("Test Group #1: Constructor(Default, Copy), Insert, Iterator(Orderly Accessing):\n");
    printf("--------------------------------------------------\n");
    Set<int> mySet;
    Set<int> mySet2 = mySet, mySet3(mySet2);
    for (int i = 0; i < 200000; i++) {
        int num = Random();
        mySet.insert(num);
        mySet2.insert(num);
        mySet3.insert(num);
        p.insert(num);
    }
    if (mySet.size() == mySet2.size() && mySet2.size() == mySet3.size() && mySet.size() == p.size()) {
        printf("Phase #1: Size Test  RESULT: Accepted\n");
    } else {
        printf("Phase #1: Size Test  Standard Answer:%d -> Your Set: %d/%d/%d RESULT: Wrong Answer\n", p.size(),
               mySet.size(), mySet2.size(), mySet3.size());
        return 0;
    }
    std::set<int>::iterator set_iter = p.begin();
    Set<int>::iterator my_iter = mySet.begin();
    int phase = 1;
    for (; set_iter != p.end(); set_iter++, my_iter++, phase++) {
        if (*set_iter != *my_iter) {
            printf("Phase #2 - %d: Iterator Accessing  Standard Answer:%d -> Your Answer: %d  RESULT: Wrong Answer\n",
                   phase, *my_iter, *set_iter);
            return 0;
        }
    }
    printf("Phase #2: Iterator Accessing & Insertion RESULT: Accepted\n");
    printf("--------------------------------------------------\n");
    printf("Group #1 RESULT: CORRECT\n\n");

    printf("Test Group #2: Insert, Erase, Iterator(Randomly Accessing):\n");
    printf("--------------------------------------------------\n");
    std::set<int> answerSet;
    Set<int> mySet12;
    for (int i = 0; i < 200000; i++) {
        int num = Random();
        mySet12.insert(num);
        answerSet.insert(num);
    }
    for (int i = 0; i < 100000; i++) {
        int tmp;
        switch (Random() % 2) {
            case 0: {
                tmp = Random();
                Set<int>::iterator ite = mySet12.end();
                std::set<int>::iterator ite2 = answerSet.end();
                for (int i = 0; i < tmp % mySet12.size(); i++) ite--, ite2--;
                bool caught = false;
                try {
                    mySet12.erase(ite);
                } catch(...){
                    caught = true;
                }
                try {
                    answerSet.erase(ite2);
                } catch(...){
                    if(!caught) printf("Runtime Error Occurred.\n");
                }

                break;
            }
            case 1: {
                tmp = Random();
                Set<int>::iterator ite3 = mySet12.begin();
                std::set<int>::iterator ite4 = answerSet.begin();
                for (int i = 0; i < tmp % mySet12.size(); i++) ite3++, ite4++;
                bool caught = false;
                try {
                    mySet12.erase(ite3);
                } catch(...){
                    caught = true;
                }
                try {
                    answerSet.erase(ite4);
                } catch(...){
                    if(!caught) printf("Runtime Error Occurred.\n");
                }
                break;
            }
            default:
                break;
                //Nothing to do
        }
    }
    set_iter = answerSet.begin();
    my_iter = mySet12.begin();
    phase = 1;
    for (; set_iter != p.end(); set_iter++, my_iter++, phase++) {
        if (*set_iter != *my_iter) {
            printf("Phase #1 - %d: Iterator Accessing  Standard Answer:%d -> Your Answer: %d  RESULT: Wrong Answer\n",
                   phase, *my_iter, *set_iter);
            return 0;
        } else {
            printf("Phase #1 - %d: Iterator Accessing  Standard Answer:%d -> Your Answer: %d  RESULT: Accepted\n",
                   phase, *my_iter, *set_iter);
        }
    }
    printf("Phase #2: Iterator Accessing & Insertion RESULT: Accepted\n");
}