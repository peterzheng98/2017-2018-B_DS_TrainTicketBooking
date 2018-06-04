//
// Created by Peter Zheng on 2018/04/10.
// Filled by FineArtz on 2018/05/24.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
#define INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP

#include <cstdio>
#include "CoreData.h"
#include "BigNum.hpp"
#include "String.h"
#include "Set.hpp"
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
    Pair<short, short> tk_position;
    Pair<Time, Time> tk_time;
    Date tk_date;
    short tk_catalog;
    int tk_ticketID;
    String tk_trainID;
    float tk_price[11];
    int tk_remain[11];

    ticket() = default;

    ticket(const ticket &tik)
            : tk_position(tik.tk_position), tk_time(tik.tk_time), tk_date(tik.tk_date),
              tk_catalog(tik.tk_catalog), tk_ticketID(tik.tk_ticketID), tk_trainID(tk_trainID) {
        for (int i = 0; i < 11; ++i) {
            tk_price[i] = tik.tk_price[i];
            tk_remain[i] = tik.tk_remain[i];
        }
    }

    Pair<short, short> M_position() const {
        return tk_position;
    }

    Pair<Time, Time> M_time() const {
        return tk_time;
    }

    Date M_date() const {
        return tk_date;
    }

    short M_catalog() const {
        return tk_catalog;
    }

    String M_trainID() const {
        return tk_trainID;
    }

    const float *M_price() const {
        return tk_price;
    }

    const int *M_remain() const {
        return tk_remain;
    }
};

class ticketKey {
private:
    Pair<short, short> station;
    String trainID;
    Date date;
public:
    ticketKey() = default;

    ticketKey(const Pair<short, short> &stt, const Date &dt)
            : station(stt), date(dt) {}

    ticketKey(const Pair<short, short> &stt, const String &tid, const Date &dt)
            : station(stt), trainID(tid), date(dt) {}

    ticketKey(const ticket &tk)
            : station(tk.tk_position), trainID(tk.tk_trainID) {}

    bool operator<(const ticketKey &tk) const {
        return station < tk.station || (station == tk.station && date < tk.date)
               || (station == tk.station && date < tk.date && trainID < tk.trainID);
    }

    Pair<short, short> first() const {
        return station;
    }

    Date second() const {
        return date;
    }
};

struct userTicket{
    int ticketId;
    int userId;
    int ticketNum[11];

    userTicket &operator =(const userTicket &utk){
        ticketId = utk.ticketId;
        userId = utk.userId;
        for (int i = 0; i < 11; ++i)
            ticketNum[i] = utk.ticketNum[i];
    }
}

class train {
    friend class Kernel::Insert;

    friend class Kernel::Select;

    friend class Kernel::Update;

    friend class Kernel::Delete;

public:
    String t_id;
    String t_name;
    short t_station[60];
    Time t_time[60][2];
    float t_price[60][5];
    short t_stationNum;
    short t_ticketKind;
    short t_ticketName[5];
    short t_catalog;
    bool t_onSale;
public:
    train() = default;

    train(const train &tr)
            : t_id(tr.t_id), t_name(tr.t_name), t_stationNum(tr.t_stationNum), t_ticketKind(tr.t_ticketKind),
              t_catalog(tr.t_catalog), t_onSale(tr.t_onSale) {
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

    String M_id() const {
        return t_id;
    }

    String M_name() const {
        return t_name;
    }

    const short *M_station() const {
        return t_station;
    }

    short M_stationNum() const {
        return t_stationNum;
    }

    short M_catalog() const {
        return t_catalog;
    }

    bool M_isOnSale() const {
        return t_onSale;
    }
};

class user {
    friend class Kernel::Select;

    friend class Kernel::Update;

private:
    int p_id;
    String p_username;
    String p_password;
    String p_email;
    String p_phone;
    UserPrivilege p_userPrivilege;
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

    user &operator=(const user &rhs) {
        if (this == &rhs) return *this;
        p_id = rhs.M_id();
        p_username = rhs.M_username();
        p_password = rhs.M_password();
        p_email = rhs.M_email();
        p_phone = rhs.M_phone();
        p_userPrivilege = rhs.M_privilege();
        return *this;
    }

    int M_id() const {
        return p_id;
    }

    String M_username() const {
        return p_username;
    }

    String M_password() const {
        return p_password;
    }

    String M_email() const {
        return p_email;
    }

    String M_phone() const {
        return p_phone;
    }

    UserPrivilege M_privilege() const {
        return p_userPrivilege;
    }
};

static int nowId = 2018;
static int base = 15096;
static int mo = 204251;
static int ticketId = 1;
static Date startDate(2018, 6, 1), endDate(2018, 6, 30);

BPlusTree<int, user> userIdTree(false, "user.dat");
//BPlusTree<String, int> userNameTree(true, "userName.dat");
BPlusTree<ticketKey, ticket> ticketTree(false, "ticket.dat");
BPlusTree<int, ticket> ticketIdTree(false, "ticketId.dat");
BPlusTree<Pair<int, int>, userTicket> userTicketTree(false, "userTicket.dat");
BPlusTree<String, train> trainTree(false, "train.dat");

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
        if(kind == "一等座") return 11;
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
    }

    inline myAlgorithm::String short2Kind(const short& sha){
        if(sha == 11) return "一等座";
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
    }

    inline int trainStation2Short(const myAlgorithm::String &station) {
        int l = 0, r = 2714, ansx = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(InternalData::InternalStation[mid] >= station) r = mid - 1, ansx = mid;
            else l = mid + 1;
        }
        return ansx;
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

        Status I_addUserBookedTicket(int p_id, int tk_num, String tk_id, Pair<short, short> tk_position, Date tk_date,
                                     int tk_kind) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            ticketKey newTk(tk_position, tk_id, tk_date);
            auto tkSel = ticketTree.search(newTk);
            if (!tkSel.second)
                return NoThisTrain;
            auto trSel = trainTree.search(tk_id);
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
            Vector<ticketKey> vtk;
            for (short k = i; k < j; ++k) {
                ticketKey tik(Pair<short, short>(upTrain.t_station[k], upTrain.t_station[k + 1]),
                              tk_id, tk_date);
                auto tikSel = ticketTree.search(tik);
                if (!tikSel.second || tikSel.first.tk_remain[tk_kind] < tk_num)
                    return NoRemainTicket;
                else
                    vtk.push_back(tik);
            }
            for (int i = 0; i < vtk.size(); ++i) {
                auto tikSel = ticketTree.search(vtk[i]);
                tikSel.first.tk_remain[tk_kind] -= tk_num;
                ticketTree.update(vtk[i], tikSel.first);
            }
            int ticketID = tkSel.first.tk_ticketID;
            auto utt = userTicketTree.search(Pair<int, int>(p_id, ticketID));
            if (utt.second){
                utt.first.ticketNum[tk_kind] += tk_num;
                userTicketTree.update(Pair<int, int>(p_id, ticketID), utt.first);
            }
            else{
                userTicket utk;
                utk.ticketId = ticketID;
                utk.userId = p_id;
                utk.ticketNum[tk_kind] = tk_num;
                userTicketTree.insert(Pair<int, int>(p_id, ticketID), utk);
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
            if (userSel.first.M_password() != p_word)
                return NoThisUser;
            return Success;
        }

        Status I_selectUser(int p_id, String &p_name, String &p_email, String &p_phone, UserPrivilege &up) {
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            p_name = userSel.first.M_username();
            p_email = userSel.first.M_email();
            p_phone = userSel.first.M_phone();
            up = userSel.first.M_privilege();
            return Success;
        }

        Status I_selectTicket(Pair<short, short> tk_position, Date tk_date, short tk_catalog, Vector<ticket> &ret) {
            ret.clear();
            ticketKey tkKey(tk_position, tk_date);
            Vector<ticket> vt = ticketTree.searchFirstAndSecond(tkKey);
            for (int i = 0; i < vt.size(); ++i) {

                auto trSel = trainTree.search(vt[i].tk_trainID);
                if (trSel.first.t_catalog & tk_catalog)
                    ret.push_back(vt[i]);
            }
            if (ret.empty())
                return NoThisTrain;
            else
                return Success;
        }

        Status I_selectTicketTransfer(Pair<short, short> tk_position, Date tk_date, short tk_catalog,
                                      short totStation, Vector<ticket> &ret) {
            ret.clear();
            Vector<ticket> vt1, vt2;
            ticket ans1, ans2;
            int minTime;
            for (short i = 0; i < totStation; ++i) {
                if (i != tk_position.first() && i != tk_position.second())
                    I_selectTicket(Pair<short, short>(tk_position.first(), i), tk_date, tk_catalog, vt1);
                I_selectTicket(Pair<short, short>(i, tk_position.second()), tk_date, tk_catalog, vt2);
                for (int j = 0; j < vt1.size(); ++j) {
                    for (int k = 0; k < vt2.size(); ++k) {
                        if (minTime < vt2[k].tk_time.second() - vt1[j].tk_time.first()) {
                            minTime = vt2[k].tk_time.second() - vt1[j].tk_time.first();
                            ans1 = vt1[j];
                            ans2 = vt2[k];
                        }
                    }
                }
            }
            if (ans1.tk_ticketID == 0 || ans2.tk_ticketID == 0)
                return NoThisTrain;
            ret.push_back(ans1);
            ret.push_back(ans2);
            return Success;
        }

        Status I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog, Vector<ticket> &ret, Vector<int*> &num) {
            ret.clear();
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            auto vb = userTicketTree.searchFirst(Pair<int, int>(p_id, 0));
            for (int i = 0; i < vb.size(); ++i) {
                auto tikSel = ticketIdTree.search(vb[i].ticketId);
                if (tikSel.second && tikSel.first.tk_date == p_date && tikSel.first.tk_catalog & tk_catalog) {
                    ret.push_back(tikSel.first);
                    num.push_back(vb[i].ticketNum);
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
            train tr = trSel.first;
            for (short i = 0; i < tr.t_stationNum; ++i) {
                for (short j = i + 1; j < tr.t_stationNum; ++j) {
                    for (Date d = startDate; d != endDate; d = d.nextDate()) {
                        ticket newTik;
                        newTik.tk_position = Pair<short, short>(tr.t_station[i], tr.t_station[j]);
                        newTik.tk_time = Pair<Time, Time>(tr.t_time[i][1], tr.t_time[j][0]);
                        newTik.tk_date = d;
                        newTik.tk_catalog = tr.t_catalog;
                        newTik.tk_ticketID = ticketId++;
                        newTik.tk_trainID = tr.t_id;
                        for (short p = 0; p != tr.t_ticketKind; ++p) {
                            short q = tr.t_ticketName[p];
                            newTik.tk_remain[q] = 2000;
                            newTik.tk_price[q] = tr.t_price[j][p] - tr.t_price[i][p];
                        }
                        ticketTree.insert(ticketKey(newTik), newTik);
                        ticketIdTree.insert(newTik.tk_ticketID, newTik);
                    }
                }
            }
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
            auto tik = userTicketTree.searchFirst(Pair<int, int>(p_id, 0));
            if (tik.empty())
                return NoRemainTicket;
            for (int i = 0; i < tik.size(); ++i) {
                auto tikIdSel = ticketIdTree.search(tik[i].first());
                if (!tikIdSel.second)
                    continue;
                if (tikIdSel.first.tk_date != p_date
                    || tikIdSel.first.tk_position != tk_location
                    || tikIdSel.first.tk_trainID != tk_id)
                    continue;
                if (tik[i].ticketNum[tk_kind] < tk_num)
                    return NoRemainTicket;
                else{
                    userTicket utk = tik[i];
                    utk.ticketNum[tk_kind] -= tk_num;
                    userTicketTree.update(Pair<int, int>(p_id, tik[i].first()), utk);
                }
                auto tikSel = ticketTree.search(ticketKey(tikIdSel.first));
                if (tikSel.second) {
                    tikIdSel.first.tk_remain[tk_kind] += tk_num;
                    ticketTree.update(ticketKey(tikIdSel.first), tikIdSel.first);
                } else {
                    ticket newTik = tikSel.first;
                    newTik.tk_remain[tk_kind] = tk_num;
                    ticketTree.insert(ticketKey(newTik), newTik);
                }
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
