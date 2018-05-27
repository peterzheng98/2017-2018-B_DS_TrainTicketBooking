//
// Created by Peter Zheng on 2018/05/21.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
#define INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
#define DEBUGMODE_PARSER

#include <iostream>
#include "String.h"

using namespace std;
using namespace myAlgorithm;

class ParserForCommand {
public:

    int Parser(ifstream &is) {
        myAlgorithm::String firstWord;
        is >> firstWord;
        if(firstWord == "register"){
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
        }
        if(firstWord == "buy_ticket"){
            String arg[4];
            for (int i = 0; i < 7; ++i) is >> arg[i];
        }
        if(firstWord == "add_train"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "add_train\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "login"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "login\n";
//#endif
            String arg[2];
            for (int i = 0; i < 2; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 2; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "query_profile"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_profile\n";
//#endif
            String arg[4];
            for (int i = 0; i < 1; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 1; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "query_ticket"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_ticket\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "query_transfer"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_transfer\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "query_order"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_order\n";
//#endif
            String arg[4];
            for (int i = 0; i < 3; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 3; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "query_train"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_train\n";
//#endif
            String arg[1];
            for (int i = 0; i < 1; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 1; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "modify_profile"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "modify_profile\n";
//#endif
            String arg[4];
            for (int i = 0; i < 5; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 5; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "modify_privilege"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "modify_privilege\n";
//#endif
            String arg[4];
            for (int i = 0; i < 3; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 3; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "sale_train"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "sale_train\n";
//#endif
            String arg[4];
            for (int i = 0; i < 1; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 1; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "modify_train"){
#ifdef DEBUGMODE_PARSER
            cout << __LINE__;
#endif
        }
        if(firstWord == "refund_ticket"){
#ifdef DEBUGMODE_PARSER
            cout << __LINE__;
#endif
        }
        if(firstWord == "delete_train"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "delete_train\n";
//#endif
            String arg[4];
            for (int i = 0; i < 1; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for(int i = 0; i < 1; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
            cout << "\n";
#endif
        }
        if(firstWord == "exit"){
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "exit\n";
            return false;
//#endif
//            String arg[4];
//            for (int i = 0; i < 1; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
//            cout << "Args: ";
//            for(int i = 0; i < 1; ++i)
//                cout << "[" << i + 1 << "] : [" << arg[i] << "]   "; 
//            cout << "\n";
#endif
        }
        return true;
    }
};


#endif //INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
