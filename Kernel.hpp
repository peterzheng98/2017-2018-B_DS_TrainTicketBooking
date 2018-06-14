//
// Created by Peter Zheng on 2018/04/10.
// Filled by FineArtz on 2018/05/24.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
#define INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP

#include <stdint.h>
#include <cstdio>
#include "CoreData.h"
#include "String.h"
#include "BPlusTree.hpp"
#include "DateAndTime.h"
#include "Vector.h"
#include "InternalData.h"
using namespace myAlgorithm;

namespace Kernel {
    class Interface;

    class Insert;

    class Select;

    class Update;

    class Delete;
}

class ticketKey;

class ticket {
    friend class ticketKey;

    friend class Kernel::Insert;

    friend class Kernel::Select;

    friend class Kernel::Update;

    friend class Kernel::Delete;

public:
    short tk_position[47];
    short tk_positionNum = 0;
    Date tk_date;
    int tk_ticketID = 0;
    String tk_trainID;
    short tk_remain[47][5];

    ticket(){
        memset(tk_position, 0, sizeof(tk_position));
        memset(tk_remain, 0, sizeof(tk_remain));
    }

    ticket(const ticket &tik)
            : tk_positionNum(tik.tk_positionNum), tk_date(tik.tk_date), tk_ticketID(tik.tk_ticketID), tk_trainID(tik.tk_trainID) {
        memset(tk_position, 0, sizeof(tk_position));
        memset(tk_remain, 0, sizeof(tk_remain));
        for (int i = 0; i < tk_positionNum; ++i) {
            for (int j = 0; j < 5; ++j)
                tk_remain[i][j] = tik.tk_remain[i][j];
            tk_position[i] = tik.tk_position[i];
        }
    }
};

struct Ticket{
    Pair<short, short> tk_position;
    Pair<Time, Time> tk_time;
    Date tk_date;
    String tk_trainID;
    short tk_catalog = 0;
    float tk_price[12];
    int tk_remain[12];

    Ticket(){
        memset(tk_price, 0, sizeof(tk_price));
        memset(tk_remain, 0, sizeof(tk_price));
    }
    Ticket(const Ticket &tk)
            : tk_position(tk.tk_position), tk_time(tk.tk_time), tk_date(tk.tk_date),
              tk_trainID(tk.tk_trainID), tk_catalog(tk.tk_catalog) {
        for (short i = 0; i < 12; ++i){
            tk_price[i] = tk.tk_price[i];
            tk_remain[i] = tk.tk_remain[i];
        }
    }
};

class ticketKey {
private:
    String trainID;
    Date date;
public:
    ticketKey() = default;

    ticketKey(const Date &dt) : date(dt) {}

    ticketKey(const String &tid, const Date &dt) : trainID(tid), date(dt) {}

    ticketKey(const ticket &tk)
            : trainID(tk.tk_trainID), date(tk.tk_date) {}

    bool operator<(const ticketKey &tk) const {
        return date < tk.date || (date == tk.date && trainID < tk.trainID);
    }

    Date first() const {
        return date;
    }
};

struct userTicket{
    int ticketId = 0;
    int userId = 0;
    Pair<short, short> position;
    int ticketNum[12];

    userTicket(){
        memset(ticketNum, 0, sizeof(ticketNum));
    }
    userTicket(const userTicket &utk)
            : ticketId(utk.ticketId), userId(utk.userId), position(utk.position){
        for (int i = 0; i < 12; ++i)
            ticketNum[i] = utk.ticketNum[i];
    }
    userTicket &operator =(const userTicket &utk){
        ticketId = utk.ticketId;
        userId = utk.userId;
        position = utk.position;
        for (int i = 0; i < 12; ++i)
            ticketNum[i] = utk.ticketNum[i];
    }
};

struct userTicketKey{
    int userId = 0;
    int ticketId = 0;
    Pair<short, short> position = Pair<short, short>(0, 0);

    userTicketKey() = default;
    userTicketKey(const userTicketKey &utk)
            : ticketId(utk.ticketId), userId(utk.userId), position(utk.position) {}
    userTicketKey(const userTicket &utt)
            : ticketId(utt.ticketId), userId(utt.userId), position(utt.position) {}
    userTicketKey(int x, int y, int p, int q)
            : userId(x), ticketId(y), position(p, q) {}
    bool operator <(const userTicketKey &utk) const{
        return userId < utk.userId || (userId == utk.userId && position < utk.position)
                || (userId == utk.userId && position == utk.position && ticketId < utk.ticketId);
    }

    const int &first() const{
        return userId;
    }
    const Pair<short, short> &second() const{
        return position;
    }
};

class train {
    friend class Kernel::Insert;

    friend class Kernel::Select;

    friend class Kernel::Update;

    friend class Kernel::Delete;

public:
    String t_id;
    String t_name;
    short t_station[47];
    Time t_time[47][2];
    float t_price[47][5];
    short t_stationNum = 0;
    short t_ticketKind = 0;
    short t_ticketName[5];
    short t_catalog = 0;
    bool t_onSale = false;
public:
    train() {
        memset(t_station, 0, sizeof(t_station));
        memset(t_price, 0, sizeof(t_price));
        memset(t_time, 0, sizeof(t_time));
        memset(t_ticketName, 0, sizeof(t_ticketName));
    }

    train(const train &tr)
            : t_id(tr.t_id), t_name(tr.t_name), t_stationNum(tr.t_stationNum), t_ticketKind(tr.t_ticketKind),
              t_catalog(tr.t_catalog), t_onSale(tr.t_onSale) {
        memset(t_station, 0, sizeof(t_station));
        memset(t_price, 0, sizeof(t_price));
        memset(t_time, 0, sizeof(t_time));
        memset(t_ticketName, 0, sizeof(t_ticketName));
        for (short i = 0; i < t_stationNum; ++i) {
            t_station[i] = tr.t_station[i];
            t_time[i][0] = tr.t_time[i][0];
            t_time[i][1] = tr.t_time[i][1];
            for (short j = 0; j < t_ticketKind; ++j)
                t_price[i][j] = tr.t_price[i][j];
        }
        for (short j = 0; j < t_ticketKind; ++j)
            t_ticketName[j] = tr.t_ticketName[j];
    }
};

class user {
    friend class Kernel::Select;

    friend class Kernel::Update;

private:
    int p_id = 0;
    String p_username;
    String p_password;
    String p_email;
    String p_phone;
    UserPrivilege p_userPrivilege = User;
public:
    user() = default;

    user(int id, const String &nme, const String &pwd, const String &eml, const String &phn)
            : p_id(id), p_username(nme), p_password(pwd), p_email(eml), p_phone(phn) {
        p_userPrivilege = (id == 2018 ? Admin : User);
    }

    user(const user &rhs) {
        p_id = rhs.p_id;
        p_username = rhs.p_username;
        p_password = rhs.p_password;
        p_email = rhs.p_email;
        p_phone = rhs.p_phone;
        p_userPrivilege = rhs.p_userPrivilege;
    }

    user &operator =(const user &rhs) {
        if (this == &rhs) return *this;
        p_id = rhs.p_id;
        p_username = rhs.p_username;
        p_password = rhs.p_password;
        p_email = rhs.p_email;
        p_phone = rhs.p_phone;
        p_userPrivilege = rhs.p_userPrivilege;
        return *this;
    }
};

struct trainStationKey{
    short station = 0;
    String trainId;

    trainStationKey() = default;
    trainStationKey(short st) : station(st) {}
    trainStationKey(short st, const String &s) : station(st), trainId(s) {}

    bool operator <(const trainStationKey &tsk) const {
        return station < tsk.station || (station == tsk.station && trainId < tsk.trainId);
    }
    const short &first() const{
        return station;
    }
};

static int nowId = 2018;
static int base = 15096;
static int mo = 204251;
static int ticketId = 1;
static Date startDate(2018, 6, 1), endDate(2018, 6, 30);
static const int MAX_TICKET = 2000;

BPlusTree<int, user> userIdTree(false, "user.dat");
//BPlusTree<String, int> userNameTree(true, "userName.dat");
BPlusTree<ticketKey, ticket> ticketTree(false, "ticket.dat");
BPlusTree<int, ticketKey> ticketIdTree(false, "ticketId.dat");
BPlusTree<userTicketKey, userTicket> userTicketTree(false, "userTicket.dat");
BPlusTree<String, train> trainTree(false, "train.dat");
BPlusTree<trainStationKey, String> arriveTrainTree(false, "arriveTrain.dat");
BPlusTree<trainStationKey, String> leaveTrainTree(false, "leaveTrain.dat");

namespace Kernel {
    inline short catalog2Short(char cat){
        if(cat == 'G') return 1;
        if(cat == 'D') return 2;
        if(cat == 'C') return 4;
        if(cat == 'K') return 8;
        if(cat == 'T') return 16;
        if(cat == 'Z') return 32;
        if(cat == 'O') return 64;
    }

    inline myAlgorithm::String short2Catalog(const short& sha){
        if(sha == 1) return "G";
        if(sha == 2) return "D";
        if(sha == 4) return "C";
        if(sha == 8) return "K";
        if(sha == 16) return "T";
        if(sha == 32) return "Z";
        if(sha == 64) return "O";
    }

    inline short kind2short(const myAlgorithm::String& kind){
        if(kind == "一等座") return 0;
        if(kind == "二等座") return 1;
        if(kind == "动卧") return 2;
        if(kind == "商务座") return 3;
        if(kind == "无座") return 4;
        if(kind == "特等座") return 5;
        if(kind == "硬卧") return 6;
        if(kind == "硬座") return 7;
        if(kind == "软卧") return 8;
        if(kind == "软座") return 9;
        if(kind == "高级软卧") return 10;
        if(kind == "大师座") return 11;
    }

    inline myAlgorithm::String short2Kind(const short& sha){
        if(sha == 0) return "一等座";
        if(sha == 1) return "二等座";
        if(sha == 2) return "动卧";
        if(sha == 3) return "商务座";
        if(sha == 4) return "无座";
        if(sha == 5) return "特等座";
        if(sha == 6) return "硬卧";
        if(sha == 7) return "硬座";
        if(sha == 8) return "软卧";
        if(sha == 9) return "软座";
        if(sha == 10) return "高级软卧";
        if(sha == 11) return "大师座";
    }

    inline int trainStation2Short(const myAlgorithm::String &station) {
        int l = 0, r = 2714, ansx = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(InternalData::InternalStation[mid] >= station) r = mid - 1, ansx = mid;
            else l = mid + 1;
        }
        if (station == InternalData::InternalStation[ansx])
            return ansx;
        else
            return -1;
    }

    inline myAlgorithm::String short2trainStation(const short &idx) {
        return InternalData::InternalStation[idx];
    }

    void _init() {
        if (access("id.dat", 0) == -1) {
            FILE *tmpfp = fopen("id.dat", "wb+");
            fclose(tmpfp);
        }
        FILE *fp;
        fp = fopen("id.dat", "rw+");
        fscanf(fp, "%d%d", &nowId, &ticketId);
        fclose(fp);
    }

    void _exit() {
        FILE *fp = fopen("id.dat", "w+");
        fprintf(fp, "%d\n%d\n", nowId, ticketId);
        fclose(fp);
#ifdef _NO_DEBUG
        userIdTree.closeFile();
        ticketTree.closeFile();
        ticketIdTree.closeFile();
        userTicketTree.closeFile();
        trainTree.closeFile();
        arriveTrainTree.closeFile();
        leaveTrainTree.closeFile();
#endif
    }

    class Interface {
    public:
        ~Interface() {}
    };

    class Insert : public Interface {
    public:
        Insert() {}

        Status
        I_addUser(const String &p_name, const String &p_word, const String &p_email, const String &p_phone, int &p_id) {
            user newUser(nowId, p_name, p_word, p_email, p_phone);
            p_id = nowId++;
            userIdTree.insert(p_id, newUser);
            return Success;
        }

        Status I_addUserBookedTicket(int p_id, int tk_num, String t_id, Pair<short, short> tk_position, Date tk_date,
                                     int tk_kind) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            ticketKey newTk(t_id, tk_date);
            auto tkSel = ticketTree.search(newTk);
            if (!tkSel.second)
                return NoThisTrain;
            auto trSel = trainTree.search(t_id);
            if (!trSel.second)
                return NoThisTrain;
            train upTrain(trSel.first);
            short i, j;
            for (i = 0; i < upTrain.t_stationNum; ++i)
                if (upTrain.t_station[i] == tk_position.first())
                    break;
            for (j = 0; j < upTrain.t_stationNum; ++j)
                if (upTrain.t_station[j] == tk_position.second())
                    break;
            if (i >= j || i == upTrain.t_stationNum || j == upTrain.t_stationNum)
                return NoThisTrain;
            ticketKey tik(t_id, tk_date);
            auto tikSel = ticketTree.search(tik);
            if (!tikSel.second)
                return NoRemainTicket;
            int k;
            for (k = 0; k < 5; ++k)
                if (upTrain.t_ticketName[k] == tk_kind)
                    break;
            if (k == 5)
                return NoRemainTicket;
            short minn = 2000;
            for (int p = i + 1; p <= j; ++p)
                if (minn > tikSel.first.tk_remain[p][k])
                    minn = tikSel.first.tk_remain[p][k];
            if (minn < tk_num)
                return NoRemainTicket;
            for (int p = i + 1; p <= j; ++p)
                tikSel.first.tk_remain[p][k] -= tk_num;
            ticketTree.update(tik, tikSel.first);
            int ticketID = tkSel.first.tk_ticketID;
            userTicketKey utk(p_id, ticketID, tk_position.first(), tk_position.second());
            auto utt = userTicketTree.search(utk);
            if (utt.second){
                utt.first.ticketNum[tk_kind] += tk_num;
                userTicketTree.update(utk, utt.first);
            }
            else{
                userTicket utc;
                utc.ticketId = ticketID;
                utc.userId = p_id;
                utc.position = tk_position;
                utc.ticketNum[tk_kind] = tk_num;
                userTicketTree.insert(utk, utc);
            }
            return Success;
        }

        Status I_addTrain(const String &t_id, const String &t_name, short t_catalog, short t_sNum, short t_tKind,
                          short *t_tname) {
            train newTrain;
            newTrain.t_id = t_id;
            newTrain.t_name = t_name;
            newTrain.t_catalog = t_catalog;
            newTrain.t_ticketKind = t_tKind;
            newTrain.t_onSale = false;
            for (short i = 0; i < t_tKind; ++i)
                newTrain.t_ticketName[i] = t_tname[i];
            trainTree.insert(t_id, newTrain);
            return Success;
        }

        Status I_addTrainTicket(const String &tk_id, int t_stationNum, const Time &t1, const Time &t2, float *t_priceNum) {
            auto trSel = trainTree.search(tk_id);
            if (!trSel.second)
                return NoThisTrain;
            train &upTrain = trSel.first;
            upTrain.t_station[upTrain.t_stationNum] = t_stationNum;
            upTrain.t_time[upTrain.t_stationNum][0] = t1;
            upTrain.t_time[upTrain.t_stationNum][1] = t2;
            if (upTrain.t_stationNum != 0) {
                for (short i = 0; i < upTrain.t_ticketKind; ++i)
                    upTrain.t_price[upTrain.t_stationNum][i] =
                            upTrain.t_price[upTrain.t_stationNum - 1][i] + t_priceNum[i];
            }
            ++upTrain.t_stationNum;
            trainTree.update(tk_id, trSel.first);
            return Success;
        }

        ~Insert() {}
    };

    class Select : public Interface {
    public:
        Select() {}

        Status I_selectUser(int p_id, String p_word) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second) {
                return NoThisUser;
            }
            if (userSel.first.p_password != p_word)
                return NoThisUser;
            return Success;
        }

        Status I_selectUser(int p_id, String &p_name, String &p_email, String &p_phone, UserPrivilege &up) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            p_name = userSel.first.p_username;
            p_email = userSel.first.p_email;
            p_phone = userSel.first.p_phone;
            up = userSel.first.p_userPrivilege;
            return Success;
        }

        Status I_selectTicket(Pair<short, short> tk_position, Date tk_date, short tk_catalog, Vector<Ticket> &ret) {
            ret.clear();
            trainStationKey tsk1(tk_position.first()), tsk2(tk_position.second());
            auto vt1 = leaveTrainTree.searchFirst(tsk1);
            auto vt2 = arriveTrainTree.searchFirst(tsk2);
            for (int i = 0, j = 0; i < vt1.size() && j < vt2.size();){
                while (i < vt1.size() && vt1[i] < vt2[j])
                    ++i;
                while (i < vt1.size() && j < vt2.size() && vt2[j] < vt1[i])
                    ++j;
                if (i == vt1.size() || j == vt2.size())
                    break;
                if (vt1[i] == vt2[j]){
                    myAlgorithm::String vt = vt1[i];
                    auto trSel = trainTree.search(vt);
                    if (trSel.first.t_catalog & tk_catalog){
                        auto tk = ticketTree.search(ticketKey(vt, tk_date));
                        short p, q;
                        for (p = 0; p < trSel.first.t_stationNum; ++p)
                            if (trSel.first.t_station[p] == tk_position.first())
                                break;
                        for (q = 0; q < trSel.first.t_stationNum; ++q)
                            if (trSel.first.t_station[q] == tk_position.second())
                                break;
                        if (p < q && p != trSel.first.t_stationNum && q != trSel.first.t_stationNum){
                            Ticket tik;
                            tik.tk_trainID = trSel.first.t_id;
                            tik.tk_position = tk_position;
                            tik.tk_date = tk_date;
                            tik.tk_catalog = trSel.first.t_catalog;
                            tik.tk_time = Pair<Time, Time>(trSel.first.t_time[p][1], trSel.first.t_time[q][0]);
                            for (int j = 0; j < trSel.first.t_ticketKind; ++j) {
                                int n = trSel.first.t_ticketName[j];
                                tik.tk_remain[n] = 2000;
                                for (int k = p + 1; k <= q; ++k)
                                    if (tik.tk_remain[n] > tk.first.tk_remain[k][j])
                                        tik.tk_remain[n] = tk.first.tk_remain[k][j];
                                tik.tk_price[n] = trSel.first.t_price[q][j] - trSel.first.t_price[p][j];
                            }
                            ret.push_back(tik);
                        }
                    }
                    ++i;
                    ++j;
                }
            }
            if (ret.empty())
                return NoThisTrain;
            else
                return Success;
        }

        Status I_selectTicketTransfer(Pair<short, short> tk_position, Date tk_date, short tk_catalog,
                                      short totStation, Vector<Ticket> &ret) {
            ret.clear();
            Vector<Ticket> vt1, vt2;
            Ticket ans1, ans2;
            int minTime = 0;
            for (short i = 0; i < totStation; ++i) {
                if (i != tk_position.first() && i != tk_position.second()) {
                    I_selectTicket(Pair<short, short>(tk_position.first(), i), tk_date, tk_catalog, vt1);
                    I_selectTicket(Pair<short, short>(i, tk_position.second()), tk_date, tk_catalog, vt2);
                    for (int j = 0; j < vt1.size(); ++j) {
                        for (int k = 0; k < vt2.size(); ++k) {
                            if (vt1[j].tk_trainID == vt2[k].tk_trainID)
                                continue;
                            int dif = -(vt1[j].tk_time.first() - vt2[k].tk_time.second());
                            if (minTime == 0 || minTime > dif) {
                                minTime = -(vt1[j].tk_time.first() - vt2[k].tk_time.second());
                                ans1 = vt1[j];
                                ans2 = vt2[k];
                            }
                        }
                    }
                }
            }
            if (minTime == 0)
                return NoThisTrain;
            ret.push_back(ans1);
            ret.push_back(ans2);
            return Success;
        }

        Status I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog,
                                        Vector<Ticket> &ret, Vector<int> *num) {
            ret.clear();
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            userTicketKey utk(p_id, 0, 0, 0);
            auto vb = userTicketTree.searchFirst(utk);
            for (int i = 0; i < vb.size(); ++i) {
                auto tikSel1 = ticketIdTree.search(vb[i].ticketId);
                if (tikSel1.second) {
                    auto tikSel = ticketTree.search(tikSel1.first);
                    if (tikSel.second && tikSel.first.tk_date == p_date) {
                        auto trSel = trainTree.search(tikSel.first.tk_trainID);
                        if (trSel.second && trSel.first.t_catalog & tk_catalog) {
                            Ticket tik;
                            short p, q;
                            for (p = 0; p < trSel.first.t_stationNum; ++p)
                                if (trSel.first.t_station[p] == vb[i].position.first())
                                    break;
                            for (q = 0; q < trSel.first.t_stationNum; ++q)
                                if (trSel.first.t_station[q] == vb[i].position.second())
                                    break;
                            if (p < q && p != trSel.first.t_stationNum && q != trSel.first.t_stationNum) {
                                Ticket tik;
                                tik.tk_trainID = trSel.first.t_id;
                                tik.tk_position = vb[i].position;
                                tik.tk_date = p_date;
                                tik.tk_catalog = trSel.first.t_catalog;
                                tik.tk_time = Pair<Time, Time>(trSel.first.t_time[p][1], trSel.first.t_time[q][0]);
                                for (int j = 0; j < trSel.first.t_ticketKind; ++j) {
                                    int n = trSel.first.t_ticketName[j];
                                    tik.tk_price[n] = trSel.first.t_price[q][j] - trSel.first.t_price[p][j];
                                }
                                ret.push_back(tik);
                                for (int j = 0; j < 12; ++j)
                                    num[j].push_back(vb[i].ticketNum[j]);
                            }
                        }
                    }
                }
            }
            if (ret.empty())
                return NoTicketBooked;
            return Success;
        }

        Status I_selectTrain(const String &p_id, train &ret) {
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            if (!trainSel.first.t_onSale)
                return NoThisTrain;
            ret = trainSel.first;
            return Success;
        }

        ~Select() {}
    };

    class Update : public Interface {
    public:
        Update() {}

        Status I_updateUser(int p_id, const String &p_name, const String &p_pwd, const String &p_email,
                            const String &p_phone) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            user newUser = userSel.first;
            newUser.p_username = p_name;
            newUser.p_password = p_pwd;
            newUser.p_email = p_email;
            newUser.p_phone = p_phone;
            userIdTree.update(p_id, newUser);
            return Success;
        }

        Status I_updateUserPrivilege(int p_id, int p_id2, int p_privilege) {
            auto user1Sel = userIdTree.search(p_id);
            auto user2Sel = userIdTree.search(p_id2);
            if (!user1Sel.second || !user2Sel.second)
                return NoThisUser;
            if (user1Sel.first.p_userPrivilege != Admin)
                return NoPrivilege;
            if (user2Sel.first.p_userPrivilege == Admin && p_privilege == 1)
                return NoPrivilege;
            user2Sel.first.p_userPrivilege = (p_privilege == 1 ? User : Admin);
            userIdTree.update(p_id2, user2Sel.first);
            return Success;
        }

        Status I_updateTrainSellingStatus(const String &t_id) {
            auto trSel = trainTree.search(t_id);
            if (!trSel.second)
                return NoThisTrain;
            if (trSel.first.t_onSale)
                return TrainHasBeenOnSale;
            train &tr = trSel.first;
            for (Date d = startDate; d <= endDate; d.nextDate(1)) {
                ticket newTik;
                newTik.tk_date = d;
                newTik.tk_ticketID = ticketId++;
                newTik.tk_trainID = tr.t_id;
                newTik.tk_positionNum = tr.t_stationNum;
                for (short i = 0; i < tr.t_stationNum; ++i){
                    newTik.tk_position[i] = tr.t_station[i];
                    for (short p = 0; p != tr.t_ticketKind; ++p) {
                        newTik.tk_remain[i][p] = 2000;
                    }
                }
                ticketKey tkk(newTik);
                ticketTree.insert(tkk, newTik);
                ticketIdTree.insert(newTik.tk_ticketID, tkk);
            }
            for (short i = 1; i < tr.t_stationNum; ++i){
                trainStationKey tsk1(tr.t_station[i - 1], t_id);
                trainStationKey tsk2(tr.t_station[i], t_id);
                leaveTrainTree.insert(tsk1, t_id);
                arriveTrainTree.insert(tsk2, t_id);
            }
            tr.t_onSale = true;
            trainTree.update(t_id, tr);
            return Success;
        }

        Status I_updateTrain(const String &t_id, const train &data) {
            auto trainSel = trainTree.search(t_id);
            if (!trainSel.second)
                return NoThisTrain;
            if (trainSel.first.t_onSale)
                return TrainHasBeenOnSale;
            trainTree.update(t_id, data);
            return Success;
        }

        ~Update() {}
    };

    class Delete : public Interface {
    public:
        Delete() {}

        Status I_deleteUserBookedTicket(int p_id, Date p_date, const String &tk_id, Pair<short, short> tk_location,
                                        int tk_kind, int tk_num) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            userTicketKey utk(p_id, 0, tk_location.first(), tk_location.second());
            auto tik = userTicketTree.searchFirstAndSecond(utk);
            if (tik.empty())
                return NoRemainTicket;
            for (int n = 0; n < tik.size(); ++n) {
                auto tikIdSel1 = ticketIdTree.search(tik[n].ticketId);
                if (!tikIdSel1.second)
                    continue;
                auto tikIdSel = ticketTree.search(tikIdSel1.first);
                if (!tikIdSel.second)
                    continue;
                if (tikIdSel.first.tk_date != p_date || tikIdSel.first.tk_trainID != tk_id)
                    continue;
                if (tik[n].ticketNum[tk_kind] < tk_num)
                    return NoRemainTicket;
                else{
                    userTicket &utk = tik[n];
                    utk.ticketNum[tk_kind] -= tk_num;
                    userTicketTree.update(
                            userTicketKey(p_id, tik[n].ticketId,
                                          tk_location.first(), tk_location.second()),
                            utk);
                }
                train upTrain = trainTree.search(tikIdSel.first.tk_trainID).first;
                short i, j;
                for (i = 0; i < upTrain.t_stationNum; ++i)
                    if (upTrain.t_station[i] == tk_location.first())
                        break;
                for (j = 0; j < upTrain.t_stationNum; ++j)
                    if (upTrain.t_station[j] == tk_location.second())
                        break;
                if (i >= j || i == upTrain.t_stationNum || j == upTrain.t_stationNum)
                    return NoRemainTicket;
                short k = 0;
                for (k = 0; k < upTrain.t_ticketKind; ++k)
                    if (upTrain.t_ticketName[k] == tk_kind)
                        break;
                for (short p = i + 1; p <= j; ++p){
                    tikIdSel.first.tk_remain[p][k] += tk_num;
                }
                ticketTree.update(ticketKey(tikIdSel.first), tikIdSel.first);
                return Success;
            }
            return NoRemainTicket;
        }

        Status I_deleteTrain(const String &p_id) {
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            if (trainSel.first.t_onSale)
                return TrainHasBeenOnSale;
            trainTree.erase(p_id);
            return Success;
        }

        Status I_deleteAll() {
            userIdTree.clear();
            ticketTree.clear();
            ticketIdTree.clear();
            userTicketTree.clear();
            trainTree.clear();
            arriveTrainTree.clear();
            leaveTrainTree.clear();
            FILE *fp = fopen("id.dat", "w+");
            fprintf(fp, "2018\n1\n");
            fclose(fp);
            nowId = 2018;
            ticketId = 1;
            return Success;
        }

        ~Delete() {}
    };

}


#endif //INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
