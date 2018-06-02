//
// Created by Peter Zheng on 2018/06/01.
//

#include "String.h"
#include <algorithm>
using namespace myAlgorithm;
using namespace std;
const int maxn = int(1e5 + 7);
myAlgorithm::String result[maxn];

int main(){
    freopen("internal.loxy", "r", stdin);
    freopen("out.loxy2", "w", stdout);
    myAlgorithm::String str;
    int i = 0;
    cin >> str;
    while(str != "END"){
        result[i] = str;
        i++;
        cin >> str;
    }


    sort(result, result + i);
//    cout << "//Auto Generator v0.1\n";
//    cout << "//Total Count : " << i << "\n";
//    cout << "myAlgorithm::String InternalStation[] = {";
    for(int j = 0; j < i - 1;j++) cout /*< "\"" */<< result[j] /*<< "\",\n"*/ << "\n";
    cout /*<< "\""*/ << result[i - 1] << /*"\"}\n"*/ "\n";
    fclose(stdin);
    fclose(stdout);
}