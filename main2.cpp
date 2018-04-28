//
// Created by Peter Zheng on 2018/04/23.
//

#include "Set.hpp"
#include <set>
#include <cstdio>
#include <deque>

using namespace myAlgorithm;

std::set<int> p;
int current = 134234;
const int mod = 200000000 + 7;

int Random() {
    current = ((current * current * 2) + current * 3) % mod;
    if (current < 0) current = -current;
    return current;
}
bool CheckEqual(const std::set<int>& answerSet, Set<int>& mySet12){
    std::set<int>::iterator ite = answerSet.begin();
    Set<int>::iterator itemy = mySet12.begin();
    int phase = 1;
    for (; ite != answerSet.end(); ite++, itemy++, phase++) {
        if (*ite != *itemy) {
            printf("Phase Equal Checking #%d:   Standard Answer:%d -> Your Answer: %d  RESULT: Wrong Answer\n",
                   phase, *ite, *itemy);
            return false;
        }
    }
    return true;
}

int test1(){
    printf("Test Group #1: Constructor(Default, Copy), Insert, Iterator(Orderly Accessing):\n");
    printf("--------------------------------------------------\n");
    Set<int> mySet;
    Set<int> mySet2 = mySet, mySet3(mySet2);
    for (int i = 0; i < 2000000; i++) {
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

}

int test2(){
    printf("Test Group #2: Insert, Erase, Iterator(Randomly Accessing):\n");
    printf("--------------------------------------------------\n");
    std::set<int> answerSet;
    Set<int> mySet12;
    std::deque<int> KeyData;
    for (int i = 0; i < 200000; i++) {
        int num = Random();
        mySet12.insert(num);
        answerSet.insert(num);
        KeyData.push_back(num);
    }
    for(int i = 0;i < 10000; i++){
        int t = Random() % KeyData.size();
        int ans = KeyData[t];
        mySet12.erase(ans);
        answerSet.erase(ans);
        KeyData.erase(KeyData.begin() + t);
        bool result = CheckEqual(answerSet, mySet12);
        if(result) continue;
        else {
            printf("Phase #2 - %d: Erasing Number:%d  Verdict: Wrong Answer.\n",i,ans);
            return 0;
        }
    }
    printf("Phase #2: Erasing Number  Verdict: Accepted.\n");
    mySet12.clear();
    answerSet.clear();
    if(answerSet.size() != 0 || !answerSet.empty()){
        printf("Phase #3: Clearing  Verdict: Wrong Answer.\n");
        return 0;
    }
    printf("Phase #3: Clearing  Verdict: Accepted.\n");
    KeyData.clear();
    for (int i = 0; i < 500000; i++) {
        int num = Random();
        mySet12.insert(num);
        answerSet.insert(num);
        KeyData.push_back(num);
    }
    for(int i = 0; i < 1000000; i++){
        int choice = Random() % 2;
        if(choice){
            int t = Random() % KeyData.size();
            int ans = KeyData[t];
            unsigned long long myAns = mySet12.count(ans);
            unsigned long long curAns = answerSet.count(ans);
            if(myAns != curAns){
                printf("Phase #4 - %d: Counting Function Number:%d  Verdict: Wrong Answer.\n",i,ans);
                return 0;
            }
        } else {
            int t = Random() % KeyData.size();
            int ans = KeyData[t];
            Set<int>::iterator myAns = mySet12.find(ans);
            std::set<int>::iterator curAns = answerSet.find(ans);
            if(*myAns != *curAns){
                printf("Phase #4 - %d: Finding Function Number:%d  Standard Answer:%d -> Your Answer:%d  Verdict: Wrong Answer.\n",i,ans,
                       *curAns, *myAns);
                return 0;
            }
        }
    }
    printf("Phase #4: Finding  Verdict: Accepted.\n");
    Set<int>::iterator ite = mySet12.begin();
    ite++;
    Set<int>::iterator ite2(ite), ite3 = ite;
    if(ite2 != ite || ite3 != ite){
        printf("Phase #5: Iterator(operator==, !=), Copy Assignment   Verdict: Wrong Answer.\n");
        return 0;
    }
    if(*ite2 != *ite || *ite3 != *ite){
        printf("Phase #5: Iterator(operator==, !=), Copy Assignment   Verdict: Wrong Answer.\n");
        return 0;
    }
    printf("Phase #5: Iterator(operator==, !=), Copy Assignment  Verdict: Accepted.\n");
}
int main() {
    test1();
    test2();
}