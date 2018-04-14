#include <iostream>
#include <cstring>
#include <cstddef>
#include <cwchar>
#include <stdexcept>
#include <string>
#include "WString.hpp"

using namespace std;

myAlgorithm::WString target;
wstring source;

template<class T1, class T2>
class myException{
private:
    string what;
    T1 q1;
    T2 q2;
public:
    void output() const {
        cout << what << "  Expected " << q1 << "   Current " << q2 << endl;
    }

    myException(string _what, T1 p, T2 p2) {
        what = _what;
        q1 = p;
        q2 = p2;
    }

    myException(string _what) {
        what = _what;
    }
};

bool test1() {
    cin >> target;
    wcin >> source;
    int length = source.length();
    int lengthTarget = target.length();
    if(length != lengthTarget){
        myException<int, int> e("Phase #1 - 1:Length Error", length, lengthTarget);
        e.output();
        return false;
    }
    myException<int, int> e("Phase #1 - 1:Accepted.");
    e.output();
    for(int i = 0; i< length;i++){
        if(target[i] != source[i]){
            myException<wchar_t, wchar_t> e2("Phase #1 - 2:Words Error", target[i], source[i]);
            e2.output();
            return false;
        } else {
            myException<wchar_t, wchar_t> e2("Phase #1 - 2:Words Accepted", target[i], source[i]);
            e2.output();
        }
    }
    myException<int, int> e2("Phase #1 - 2:Accepted.");
    e2.output();

    target = target + target;
    source = source + source;
    length = source.length();
    lengthTarget = target.length();
    if(length != lengthTarget){
        myException<int, int> e("Phase #1 - 3:Length Error", length, lengthTarget);
        e.output();
        return false;
    }
    myException<int, int> e5("Phase #1 - 3:Accepted.");
    e5.output();
    for(int i = 0; i< length;i++){
        if(target[i] != source[i]){
            myException<wchar_t, wchar_t> e2("Phase #1 - 4:Words Error", target[i], source[i]);
            e2.output();
            return false;
        }
    }
    myException<int, int> e3("Phase #1 - 4:Accepted.");
    e3.output();
    return true;
}




int main() {
    bool flag = test1();
    if(flag){
        printf("\nTest 1 Accepted. \n");
    } else {
        printf("\nTest 1 Not Accepted. \n");
        return 0;
    }

}
