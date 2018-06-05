//
// Created by Peter Zheng on 2018/06/03.
//
#define  _NO_DEBUG

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include "String.h"
#include "Kernel.hpp"

using namespace std;
using namespace myAlgorithm;
using namespace Kernel;
const short TOT_STATION = 2175;
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
    //freopen("2.in", "r", stdin);
    //freopen("ans.out", "w", stdout);
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
            short p_loc1_s = trainStation2Short(p_loc1), p_loc2_s = trainStation2Short(p_loc2);
            short p_tick_s = kind2short(p_ticketK);
            Status ret = insert.I_addUserBookedTicket(p_id, p_num, p_train_id,
                    Pair<short, short>(p_loc1_s, p_loc2_s), Date(p_data), p_tick_s);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
        }
        if (firstWord == "add_train") {
            myAlgorithm::String p_tid, p_name, p_catalog, p_num_s, p_num_p;
            cin >> p_tid >> p_name >> p_catalog >> p_num_s >> p_num_p;
            int limit = p_num_p, limits = p_num_s;
            short pr[5];
            myAlgorithm::String tk_name;
            for (int i = 0; i < limit; ++i) {
                cin >> tk_name;
                pr[i] = kind2short(tk_name);
            }
            short catalog = catalog2Short(p_catalog[0]);
            Status ret = Success, ret1 = insert.I_addTrain(p_tid, p_name, catalog, limits, limit, pr);
            for (int i = 0; i < limits; ++i) {
                myAlgorithm::String s_name, artime, sttime, sotime, s_price;
                float prc[5];
                cin >> s_name >> artime >> sttime >> sotime;
                int s_num = trainStation2Short(s_name);
                Time tm1 = artime, tm2 = sttime;
                for (int j = 0; j < limit; ++j) {
                    cin >> s_price;
                    prc[j] = s_price.toFloat();
                }
                Status ret2 = insert.I_addTrainTicket(p_tid, s_num, tm1, tm2, prc);
                if (ret2 != Success)
                    ret = NoThisTrain;
            }
            if (ret1 != Success)
                ret = NoThisTrain;
            if (ret == Success) cout << "1\n"; else cout << "0\n";
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
            Status ret = selectA.I_selectUser((int) p_id, p_name, p_email, p_phone, p_up);
            if (ret == NoThisUser) cout << "0\n";
            else
                cout << p_name << p_word << " " << p_email << " " << p_phone << " "
                     << (p_up == Admin ? "2\n" : "1\n");

        }
        if (firstWord == "query_ticket") {
            myAlgorithm::String s_st1, s_st2, s_date, s_cata;
            cin >> s_st1 >> s_st2 >> s_date >> s_cata;
            myAlgorithm::Vector<ticket> ans;
            short st1 = trainStation2Short(s_st1), st2 = trainStation2Short(s_st2);
            Date dt = s_date;
            short cata = 0;
            for (int i = 0; i < s_cata.length(); ++i)
                cata |= catalog2Short(s_cata[i]);
            Status ret = selectA.I_selectTicket(Pair<short, short>(st1, st2), dt, cata, ans);
            //cout << "here1\n";
            if (ret == Success && ans.size() != 0) {
                cout << ans.size() << "\n";
                train tr;
                //cout << "here2\n";
                for (int i = 0; i < ans.size(); ++i) {
                    selectA.I_selectTrain(ans[i].tk_trainID, tr);
                    cout << ans[i].tk_trainID << " ";
                    cout << s_st1 << " " << ans[i].tk_date << " " << ans[i].tk_time.first() << " ";
                    cout << s_st2 << " " << ans[i].tk_date << " " << ans[i].tk_time.second() << " ";
                    for (int j = 0; j < tr.t_ticketKind; ++j) {
                        short p = tr.t_ticketName[j];
                        cout << short2Kind(p) << " " << ans[i].tk_remain[p] << " " << ans[i].tk_price[p] << " ";
                    }
                    cout << "\n";
                }
            } else {
                cout << "0\n";
            }
            //cout << "here3\n";
        }
        if (firstWord == "query_transfer") {
            myAlgorithm::String s_st1, s_st2, s_date, s_cata;
            cin >> s_st1 >> s_st2 >> s_date >> s_cata;
            short st1 = trainStation2Short(s_st1), st2 = trainStation2Short(s_st2);
            Date dt = s_date;
            short cata = 0;
            for (int i = 0; i < s_cata.length(); ++i)
                cata |= catalog2Short(s_cata[i]);
            myAlgorithm::Vector<ticket> ans;
            Status ret = selectA.I_selectTicketTransfer(Pair<short, short>(st1, st2), dt, cata, TOT_STATION, ans);
            if (ret == Success && !ans.empty()) {
                train tr;
                for (int i = 0; i < ans.size(); ++i) {
                    selectA.I_selectTrain(ans[i].tk_trainID, tr);
                    cout << ans[i].tk_trainID << " ";
                    cout << s_st1 << " " << ans[i].tk_date << " " << ans[i].tk_time.first() << " ";
                    cout << s_st2 << " " << ans[i].tk_date << " " << ans[i].tk_time.second() << " ";
                    for (int j = 0; j < tr.t_ticketKind; ++j) {
                        short p = tr.t_ticketName[j];
                        cout << short2Kind(p) << " " << ans[i].tk_remain[p] << " " << ans[i].tk_price[p] << " ";
                    }
                    cout << "\n";
                }
            }
        }
        if (firstWord == "query_order") {
            myAlgorithm::String p_id, t_date, t_cata;
            cin >> p_id >> t_date >> t_cata;
            short catalog = 0;
            for (int i = 0; i < t_cata.length(); ++i)
                catalog |= catalog2Short(t_cata[i]);
            Date dat = t_date;
            myAlgorithm::Vector<ticket> vtk;
            myAlgorithm::Vector<int> vtknum[12];
            Status ret = selectA.I_selectUserBookedTicket((int) p_id, dat, catalog, vtk, vtknum);
            if (ret == Success && vtk.size() != 0) {
                cout << "1\n";
                myAlgorithm::String st1, st2;
                train tr;
                for (int i = 0; i < vtk.size(); ++i) {
                    selectA.I_selectTrain(vtk[i].tk_trainID, tr);
                    cout << vtk[i].tk_trainID << " ";
                    st1 = short2trainStation(vtk[i].tk_position.first());
                    st2 = short2trainStation(vtk[i].tk_position.second());
                    cout << st1 << " " << vtk[i].tk_date << " " << vtk[i].tk_time.first() << " ";
                    cout << st2 << " " << vtk[i].tk_date << " " << vtk[i].tk_time.second() << " ";
                    for (int j = 0; j < tr.t_ticketKind; ++j) {
                        short p = tr.t_ticketName[j];
                        cout << short2Kind(p) << " " << vtknum[p][i] << " " << vtk[i].tk_price[p] << " ";
                    }
                    cout << '\n';
                }
            } else
                cout << "0\n";
        }
        if (firstWord == "query_train") {
            String p_id;
            cin >> p_id;
            train tr;
            Status ret = selectA.I_selectTrain(p_id, tr);
            if (ret == Success) {
                cout << tr.t_id << " " << tr.t_name << " ";
                cout << short2Catalog(tr.t_catalog) << " " << tr.t_stationNum << " " << tr.t_ticketKind << " ";
                for (int i = 0; i < tr.t_ticketKind; ++i)
                    cout << short2Kind(tr.t_ticketName[i]) << " ";
                cout << "\n";
                for (int i = 0; i < tr.t_stationNum; ++i) {
                    cout << short2trainStation(tr.t_station[i]) << " ";
                    cout << tr.t_time[i][0] << " " << tr.t_time[i][1] << " ";
                    int timeInterval = tr.t_time[i][1] - tr.t_time[i][0];
                    if (timeInterval == 0) cout << "xx:xx ";
                    else
                        cout << Time(tr.t_time[i][1] - tr.t_time[i][0]) << " ";
                    for (int j = 0; j < tr.t_ticketKind; ++j) {
                        if (i == 0)
                            cout << "￥" << tr.t_price[i][j] << " ";
                        else
                            cout << "￥" << tr.t_price[i][j] - tr.t_price[i - 1][j] << " ";
                    }
                    cout << "\n";
                }
            } else
                cout << "0\n";
        }
        if (firstWord == "modify_profile") {
            myAlgorithm::String p_name, p_word, p_email, p_id, p_phone;
            cin >> p_id >> p_name >> p_word >> p_email >> p_phone;
            Status ret = update.I_updateUser((int) p_id, p_name, p_word, p_email, p_phone);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "modify_privilege") {
            myAlgorithm::String p_id1, p_id2, privilege;
            cin >> p_id1 >> p_id2 >> privilege;
            Status ret = update.I_updateUserPrivilege((int) p_id1, (int) p_id2, (short) privilege);
            if (ret == Success) cout << "1\n"; else cout << "0\n";

        }
        if (firstWord == "sale_train") {
            String p_id;
            cin >> p_id;
            Status ret = update.I_updateTrainSellingStatus(p_id);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
        }
        if (firstWord == "modify_train") {
            train tr;
            myAlgorithm::String p_tid, p_name, p_catalog, p_num_s, p_num_p;
            cin >> p_tid >> p_name >> p_catalog >> p_num_s >> p_num_p;
            tr.t_id = p_tid;
            tr.t_name = p_name;
            int limit = p_num_p, limits = p_num_s;
            tr.t_stationNum = 0;
            tr.t_ticketKind = limit;
            myAlgorithm::String tk_name;
            for (int i = 0; i < limit; ++i) {
                cin >> tk_name;
                tr.t_ticketName[i] = kind2short(tk_name);
            }
            tr.t_catalog = catalog2Short(p_catalog[0]);
            Status ret = Success, ret1 = update.I_updateTrain(p_tid, tr), ret2 = Success;
            for (int i = 0; i < limits; ++i) {
                myAlgorithm::String s_name, artime, sttime, sotime, s_price;
                float prc[5];
                cin >> s_name >> artime >> sttime >> sotime;
                int s_num = trainStation2Short(s_name);
                Time tm1 = artime, tm2 = sttime;
                for (int j = 0; j < limit; ++j) {
                    cin >> s_price;
                    prc[j] = s_price.toFloat();
                }
                if (ret1 == Success) ret2 = insert.I_addTrainTicket(p_tid, s_num, tm1, tm2, prc);
                if (ret2 != Success)
                    ret = NoThisTrain;
            }
            if (ret1 != Success)
                ret = NoThisTrain;
            if (ret == Success) cout << "1\n"; else cout << "0\n";
        }
        if (firstWord == "refund_ticket") {
            myAlgorithm::String p_id, p_num, p_tid, p_loc1, p_loc2, p_date, p_tkk;
            cin >> p_id >> p_num >> p_tid >> p_loc1 >> p_loc2 >> p_date >> p_tkk;
            short p_loc1_s = trainStation2Short(p_loc1), p_loc2_s = trainStation2Short(p_loc2);
            Status ret = deleteA.I_deleteUserBookedTicket((int) p_id, (Date) p_date, p_tid,
                                                          Pair<short, short>(p_loc1_s, p_loc2_s), kind2short(p_tkk),
                                                          (int) p_num);
            if (ret == Success) cout << "1\n"; else cout << "0\n";
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
            break;
        }
        if (firstWord == "clean") {
            deleteA.I_deleteAll();
            cout << "1\n";
        }
        if (firstWord == "fuck") {
            cout << "SLASH\n";
        }

    }
    //fclose(stdin);
    //fclose(stdout);
    return 0;

}