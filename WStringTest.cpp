//
// Created by Peter Zheng on 2018/04/28.
//

#include <cwchar>
#include <iostream>
#include "WString.hpp"
using namespace std;

wstring answer, answer2;
myAlgorithm::WString myAnswer, myAnswer2;

int main(){
    wcin >> answer;
    wcin >> myAnswer;
    wcout << "Size Test:" << answer.size() << "  " << myAnswer.size() << "\n";
    wcin >> answer2;
    wcin >> myAnswer2;
    wcout << "Compare: 1st[" << answer << "]\n";
    wcout << "2nd[" << myAnswer << "]\n";
    answer = answer2;
    myAnswer = myAnswer2;
    wcout << "Size Test:" << answer.size() << "  " << myAnswer.size();
    wcout << "Compare: 1st[" << answer << "]\n";
    wcout << "2nd[" << myAnswer << "]\n";
    for(int i = 0;i < answer.size(); i++){
        wcout << "operator[] Test: Phase #" << i + 1 << " :[" << answer[i] << "]";
        wcout << "[" << myAnswer[i] << "]\n";
    }
}