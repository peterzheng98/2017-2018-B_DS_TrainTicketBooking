#include <iostream>
//#include <cstdio>
#include "ParserForCommand.h"
#include "Kernel.hpp"
#include "String.h"
using namespace std;
using namespace myAlgorithm;
using namespace Kernel;

int main(){
    ifstream ifs("all.in");
    ParserForCommand parserForCommand = ParserForCommand();
    while(parserForCommand.Parser(ifs)){
//        int t;
//        cout << "Press 1 and Enter To Next";
//        cin >> t;
    }
//    cout << "Here!";
//    myAlgorithm::String string1;
//    cin >> string1;
//    if(string1 == "测试数据") cout << "Here!";
}