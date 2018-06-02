//
// Created by Peter Zheng on 2018/05/21.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
#define INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
#define DEBUGMODE_PARSER

#include <iostream>
#include "String.h"
#include "Kernel.hpp"

using namespace std;
using namespace myAlgorithm;
using namespace Kernel;

class ParserForCommand {
private:
    Insert insert;
    Update update;
    Select select;
    Delete deleteA;
public:
    ParserForCommand() {
        insert = Insert();
        update = Update();
        select = Select();
        deleteA = Delete();
        _init();
    };

    int Parser(ifstream &is) {
        myAlgorithm::String firstWord;
        is >> firstWord;
        if (firstWord == "register") {
            myAlgorithm::String p_name, p_word, p_email, p_phone;
            is >> p_name >> p_word >> p_email >> p_phone;
            int id = 0;
            long long test = p_phone.toLong();
//            if(test == 42311888){
//                cout << "Fuck Here!\n";
//            }
            Status ret = insert.I_addUser(p_name, p_word, p_email, p_phone.toLong(), id);
            if (ret == Success) cout << id << "\n"; else cout << "-1\n";
            return true;
        }
        if (firstWord == "buy_ticket") {
            myAlgorithm::String p_id, p_num, p_train_id, p_loc1, p_loc2, p_data, p_ticketK;
            is >> p_id >> p_num >> p_train_id >> p_loc1 >> p_loc2 >> p_data >> p_ticketK;
            Status ret = insert.I_addUserBookedTicket(p_id, p_num, p_train_id,
                                                      Pair<short, short>((short) p_loc1, (short) p_loc2), Date(p_data),
                                                      p_ticketK);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "add_train") {


#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "add_train\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for (int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
            cout << "\n";
#endif
        }
        if (firstWord == "login") {
            myAlgorithm::String p_id, p_word;
            is >> p_id >> p_word;
            int ppp = p_id;
            Status ret = select.I_selectUser(ppp, p_word);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "query_profile") {
            myAlgorithm::String p_id;
            is >> p_id;
            myAlgorithm::String p_name, p_email, p_word;
            long long p_phone;
            UserPrivilege p_up;
            //TODO : BUG HERE(Require User Priviliege)
            Status ret = select.I_selectUser((int) p_id, p_name, p_email, p_phone, p_up);
            if (ret == NoThisUser) cout << "0\n";
            else
                cout << p_name << " " << p_word << " " << p_email << " " << p_phone << " "
                     << (p_up == Admin ? "2\n" : "1\n");
            return true;
        }
        if (firstWord == "query_ticket") {
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_ticket\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for (int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
            cout << "\n";
#endif
        }
        if (firstWord == "query_transfer") {
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_transfer\n";
//#endif
            String arg[4];
            for (int i = 0; i < 4; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for (int i = 0; i < 4; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
            cout << "\n";
#endif
        }
        if (firstWord == "query_order") {
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_order\n";
//#endif
            String arg[4];
            for (int i = 0; i < 3; ++i) is >> arg[i];
//#ifdef DEBUGMODE_PARSER
            cout << "Args: ";
            for (int i = 0; i < 3; ++i)
                cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
            cout << "\n";
#endif
        }
        if (firstWord == "query_train") {
//            String p_id;
//            is >> p_id;
//            train ret = train();
//            Status rett = select.I_selectTrain(p_id, ret);
//            TODO : Output Train
//            cout << ret.t_id << " " << ret.t_name << ret.t_catalog << " ";
//            if (rett != Success) cout << "0\n"; else cout << "\n";
            return true;
        }
        if (firstWord == "modify_profile") {
            myAlgorithm::String p_name, p_word, p_email, p_id, p_phone;
            is >> p_id >> p_name >> p_word >> p_email >> p_phone;
            long long pp_p = p_phone;
            Status ret = update.I_updateUser((short) p_id, p_name, p_word, p_email, pp_p);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "modify_privilege") {
            short p_id1, p_id2, privilege;
            is >> p_id1 >> p_id2 >> privilege;
            Status ret = update.I_updateUserPrivilege(p_id1, p_id2, privilege);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "sale_train") {
            String p_id;
            is >> p_id;
            Status ret = update.I_updateTrainSellingStatus(p_id);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "modify_train") {
#ifdef DEBUGMODE_PARSER
            cout << __LINE__;
#endif
        }
        if (firstWord == "refund_ticket") {
            myAlgorithm::String p_id, p_num, p_tid, p_loc1, p_loc2, p_date, p_tkk;
            is >> p_id >> p_num >> p_tid >> p_loc1 >> p_loc2 >> p_date >> p_tkk;
            Status ret = deleteA.I_deleteUserBookedTicket((int) p_id, (Date) p_date, p_tid,
                                                          Pair<short, short>(p_loc1, p_loc2), (int) p_tkk, (int) p_num);
        }
        if (firstWord == "delete_train") {
            String p_id;
            is >> p_id;
            Status ret = deleteA.I_deleteTrain(p_id);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
            return true;
        }
        if (firstWord == "exit") {
            _exit();
            cout << "BYE\n";
            return false;
//            return true;
        }
        if (firstWord == "clean") {
            deleteA.I_deleteAll();
            cout << "1\n";
            return true;
        }
        if(firstWord == "fuck"){
            return false;
        }
    }

    ~ParserForCommand() {

    }
};


#endif //INC_2018DATASTRUCTUREBIGWORK_PARSERFORCOMMAND_H
