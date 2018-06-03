//
// Created by Peter Zheng on 2018/06/03.
//
#define  _NO_DEBUG
#include <iostream>
#include <fstream>
#include <cstdio>
#include "String.h"
#include "Kernel.hpp"

using namespace std;
using namespace myAlgorithm;
using namespace Kernel;
Insert insert;
Update update;
Select selectA;
Delete deleteA;

void whereIsMyFile() {
    ofstream f1("user.dat", ios::ate),
            f2("ticket.dat", ios::ate),
            f3("ticketId.dat", ios::ate),
            f4("userTicket.dat", ios::ate),
            f5("train.dat", ios::ate),
            f6("id.dat", ios::ate);
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    f5.close();
    f6.close();

}

int main() {
    insert = Insert();
    update = Update();
    selectA = Select();
    deleteA = Delete();
    _init();


    myAlgorithm::String firstWord = "";
    while (firstWord != "exit") {
        cin >> firstWord;

        if (firstWord == "register") {
            myAlgorithm::String p_name, p_word, p_email, p_phone;
            cin >> p_name >> p_word >> p_email >> p_phone;
            int id = 0;
            Status ret = insert.I_addUser(p_name, p_word, p_email, p_phone, id);
            if (ret == Success) cout << id << "\n"; else cout << "-1\n";

        }
        if (firstWord == "buy_ticket") {
            myAlgorithm::String p_id, p_num, p_train_id, p_loc1, p_loc2, p_data, p_ticketK;
            cin >> p_id >> p_num >> p_train_id >> p_loc1 >> p_loc2 >> p_data >> p_ticketK;
            Status ret = insert.I_addUserBookedTicket(p_id, p_num, p_train_id,
                                                      Pair<short, short>((short) p_loc1, (short) p_loc2), Date(p_data),
                                                      p_ticketK);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "add_train") {


#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "add_train\n";
    //#endif
                String arg[4];
                for (int i = 0; i < 4; ++i) cin >> arg[i];
    //#ifdef DEBUGMODE_PARSER
                cout << "Args: ";
                for (int i = 0; i < 4; ++i)
                    cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
                cout << "\n";
#endif
        }
        if (firstWord == "login") {
            myAlgorithm::String p_id, p_word;
            cin >> p_id >> p_word;
            int ppp = p_id;
            Status ret = selectA.I_selectUser(ppp, p_word);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "query_profile") {
            myAlgorithm::String p_id;
            cin >> p_id;
            myAlgorithm::String p_name, p_email, p_word, p_phone;
            UserPrivilege p_up;
            //TODO : BUG HERE(Require User Priviliege)
            Status ret = selectA.I_selectUser((int) p_id, p_name, p_email, p_phone, p_up);
            if (ret == NoThisUser) cout << "0\n";
            else
                cout << p_name << " " << p_word << " " << p_email << " " << p_phone << " "
                     << (p_up == Admin ? "2\n" : "1\n");

        }
        if (firstWord == "query_ticket") {
#ifdef DEBUGMODE_PARSER
            cout << "Line: " << __LINE__ << "query_ticket\n";
    //#endif
                String arg[4];
                for (int i = 0; i < 4; ++i) cin >> arg[i];
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
                for (int i = 0; i < 4; ++i) cin >> arg[i];
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
                for (int i = 0; i < 3; ++i) cin >> arg[i];
    //#ifdef DEBUGMODE_PARSER
                cout << "Args: ";
                for (int i = 0; i < 3; ++i)
                    cout << "[" << i + 1 << "] : [" << arg[i] << "]   ";
                cout << "\n";
#endif
        }
        if (firstWord == "query_train") {
//            String p_id;
//            cin >> p_id;
//            train ret = train();
//            Status rett = selectA.I_selectTrain(p_id, ret);
//            TODO : Output Train
//            cout << ret.t_id << " " << ret.t_name << ret.t_catalog << " ";
//            if (rett != Success) cout << "0\n"; else cout << "\n";

        }
        if (firstWord == "modify_profile") {
            myAlgorithm::String p_name, p_word, p_email, p_id, p_phone;
            cin >> p_id >> p_name >> p_word >> p_email >> p_phone;
            Status ret = update.I_updateUser((short) p_id, p_name, p_word, p_email, p_phone);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "modify_privilege") {
            myAlgorithm::String p_id1, p_id2, privilege;
            cin >> p_id1 >> p_id2 >> privilege;
            Status ret = update.I_updateUserPrivilege((short) p_id1, (short) p_id2, (short) privilege);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "sale_train") {
            String p_id;
            cin >> p_id;
            Status ret = update.I_updateTrainSellingStatus(p_id);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "modify_train") {
#ifdef DEBUGMODE_PARSER
            cout << __LINE__;
#endif
        }
        if (firstWord == "refund_ticket") {
            myAlgorithm::String p_id, p_num, p_tid, p_loc1, p_loc2, p_date, p_tkk;
            cin >> p_id >> p_num >> p_tid >> p_loc1 >> p_loc2 >> p_date >> p_tkk;
            Status ret = deleteA.I_deleteUserBookedTicket((int) p_id, (Date) p_date, p_tid,
                                                          Pair<short, short>(p_loc1, p_loc2), (int) p_tkk, (int) p_num);
        }
        if (firstWord == "delete_train") {
            String p_id;
            cin >> p_id;
            Status ret = deleteA.I_deleteTrain(p_id);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "exit") {
            _exit();
            cout << "BYE\n";
//            exit(0);
            break;
//            
        }
        if (firstWord == "clean") {
            deleteA.I_deleteAll();
            cout << "1\n";

        }
        if (firstWord == "fuck") {
        }

    }
    return 0;

}