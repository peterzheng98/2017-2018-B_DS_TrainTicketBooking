//
// Created by Peter Zheng on 2018/05/07.
//
#include "String.h"
//#include <fstream>
#include <unistd.h>
using namespace myAlgorithm;
int main(){
    std::ifstream fin("register.in");
//    freopen("addtrain.in","r",stdin);
    for(int i = 1; i <= 1000000; ++i){
        std::cout << "\nPhase # " << i << " Started" << std::endl;
//        String st("Test", 1);
//    std::cout << st;
        for(int i = 0; i < 5; i++){
//            std::ofstream fout("Result3.log", std::ofstream::app);
            std::cout << "Waiting to Input...";
            String st;
            fin >> st;
            String st2(st);
            String st3('0');
            st3 = st;
            std::cout <<"Raw:[" << st << "] Copy:[" << st2 << "] Assign:[" << st3 << "]\n";
//            fout <<"Raw:[" << st << "] Copy:[" << st2 << "] Assign:[" << st3 << "]\n";
//            fout.close();
            std::cout << "operator Result : " << (st == st2) << " " << (st <= st3) << "\n";
            std::cout << "operator Result 2 :" << (st == "register") << "\n";
            std::cout << "operator [] Result : [" << st[0] << "]  [" << st[1] << "]\n";

        }}
//        int t;
//        std::cin >> t;
//        std::cout << "Phase # " << i << " Ended" << std::endl;
//        sleep(1);


}
