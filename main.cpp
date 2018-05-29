#include <iostream>
#include <cstdio>
#include "ParserForCommand.h"
using namespace std;

int main(){
    ParserForCommand parserForCommand = ParserForCommand();
    ifstream fs("data.in");
    while(parserForCommand.Parser(fs)){
        int t;
        cout << "Press 1 and Enter To Next";
        cin >> t;
    };
    cout << "Here!";
}