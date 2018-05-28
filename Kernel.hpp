//
// Created by Peter Zheng on 2018/04/10.
// Filled by FineArtz on 2018/05/24.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
#define INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP

#include "CoreData.h"
#include "BigNum.hpp"
#include "String.h"
#include "Set.hpp"
#include "BPlusTree.hpp"

using namespace myAlgorithm;

namespace Kernel{
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
private:
    Pair<short, short> tk_position;
    Pair<Date, Date> tk_time;
    Date tk_date;
    short tk_catalog;
    int tk_ticketID;
    String tk_trainID;
    float tk_price;
public:
    Pair<short, short> M_position() const{
        return tk_position;
    }

    Pair<Date, Date> M_time() const{
        return tk_time;
    }

    Date M_date() const{
        return tk_date;
    }

    short M_catalog() const{
        return tk_catalog;
    }

    String M_trainID() const{
        return tk_trainID;
    }

    float M_price() const{
        return tk_price;
    }
};

class ticketKey{
private:
    Pair<short, short> station;
    String trainID;
public:
    ticketKey() = default;
    ticketKey(const Pair<short, short> &stt)
        : station(stt);
    ticketKey(const Pair<short, short> &stt, const String &tid)
        : station(stt), trainID(tid) {}
    ticketKey(const ticket &tk)
        : station(tk.tk_position), trainID(tk.tk_trainID) {}
    bool operator <(const ticketKey &tk) const{
        return station < tk.station || (station == tk.station && trainID < tk.trainID);
    }
};

class train {
    friend class Kernel::Insert;
    friend class Kernel::Select;
    friend class Kernel::Update;
private:
    String t_id;
    String t_name;
    short t_station[60];
    short t_ticketRemain[5][60];
    short t_stationNum;
    short t_tickedKind;
    short t_catalog;
public:
    train() = default;

    train(const train &tr)
        : t_id(tr.t_id), t_name(tr.t_name), t_stationNum(tr.t_stationNum), t_tickedKind(tr.t_tickedKind), t_catalog(tr.t_catalog){
        for (int i = 0; i < t_stationNum; ++i)
            t_station[i] = tr.t_station[i];
        for (int i = 0; i < t_tickedKind; ++i)
            for (int j = 0; j < t_stationNum; ++j)
                t_ticketRemain[i][j] = tr.t_ticketRemain[i][j];
    }

    String M_id() const{
        return t_id;
    }

    String M_name() const{
        return t_name;
    }

    const short *M_station() const{
        return t_station;
    }

    short M_stationNum() const{
        return t_stationNum;
    }

    short M_catalog() const{
        return t_catalog;
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
    long long p_phone;
    UserPrivilege p_userPrivilege;
public:
    user() = default;

    user(int id, const String &nme, const String &pwd, const String &eml, long long phn)
        : p_id(id), p_username(nme), p_password(pwd), p_email(eml), p_phone(phn){
        p_userPrivilege = (id == 2018 ? Admin : User);
    }

    int M_id() const{
        return p_id;
    }

    String M_username() const{
        return p_username;
    }

    String M_password() const{
        return p_password;
    }

    String M_email() const{
        return p_email;
    }

    long long M_phone() const{
        return p_phone;
    }

    UserPrivilege M_privilege() const{
        return p_userPrivilege;
    }
};

static int nowId = 2018;
static int ticketId = 0;

BPlusTree<int, user> userIdTree(false, "tmp/user.dat");
BPlusTree<String, int> userNameTree(false, "tmp/userName.dat");
BPlusTree<ticketKey, ticket> ticketTree(false, "tmp/ticket.dat");
BPlusTree<int, ticket> ticketIdTree(false, "tmp/ticketId.dat");
BPlusTree<int, int> userTicketTree(false, "tmp/userTicket.dat");
BPlusTree<String, train> trainTree(false, "tmp/train.dat");

namespace Kernel {
    class Interface { virtual ~Interface() {} };

    class Insert : public Interface {
    public:
        Status I_addUser(String p_name, String p_word, String p_email, long long p_phone, int &p_id){
            auto nameHasExisted = userNameTree.search(p_name);
            if (nameHasExisted.second){
                p_id = 0;
                return NameHasExisted;
            }
            user newUser(nowId, p_name, p_word, p_email, p_phone);
            p_id = nowId++;
            userIdTree.insert(p_id, newUser);
            userNameTree.insert(p_name, p_id);
            return Success;
        }

        Status I_addUserBookedTicket(int p_id, int tk_num, String tk_id, Pair<short, short> tk_position, Date tk_date, int tk_kind){
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            ticketKey newTk(tk_position, tk_id);
            auto tkSel = ticketTree.search(newTk);
            if (!tkSel.second)
                return NoThisTrain;
            auto trSel = trainTree.search(tk_id);
            if (!trSel.second)
                return NoThisTrain;
            train upTrain(trSel.first);
            short i, j;
            for (i = 0; i < upTrain.t_stationNum; ++i)
                if (i == tk_position.first())
                    break;
            for (j = 0; j < upTrain.t_stationNum; ++j)
                if (j == tk_position.second())
                    break;
            if (i >= j || i == upTrain.t_stationNum || j == upTrain.t_stationNum)
                return NoThisTrain;
            for (short k = i; k < j; ++k){
                if (upTrain.t_ticketRemain[tk_kind][k] < tk_num)
                    return NoRemainTicket;
                else
                    upTrain.t_ticketRemain[tk_kind][k] -= tk_num;
            }
            trainTree.update(tk_id, upTrain);
            int ticketID = tkSel.first.tk_ticketID;
            userTicketTree.insert(p_id, ticketID);
            return Success;
        }

        Status I_addTrainTicket(int tk_id, String t_name, int t_stationNum, int t_priceNum);

        

        ~Insert();
    };

    class Select : public Interface {
    public:
        Status I_selectUser(int p_id, String p_word){
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second){
                return NoThisUser;
            }
            if (userSel.first.M_password() != p_word)
                return NoThisUser;
            return Success;
        }

        Status I_selectUser(String p_name, String p_word){
            auto userNameSel = userNameTree.search(p_name);
            if (!userNameSel.second)
                return NoThisUser;
            auto userSel = userIdTree.search(userNameSel.first);
            if (!userSel.second)
                return NoThisUser;
            if (userSel.first.M_password() != p_word)
                return NoThisUser;
            return Success;
        }

        Status I_selectUser(int p_id, const String &p_name, const String &p_email, long long &p_phone){
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            if (userSel.first.M_email() != p_email || userSel.first.M_username() != p_name || userSel.first.M_phone() != p_phone)
                return NoThisUser;
            return Success;
        }

        Status I_selectTicket(Pair<short, short> tk_position, Date tk_date, short tk_catalog, Vector<ticket> &ret){
            ret.clear();
            ticketKey tkKey(tk_position);
            Vector<ticket> vt = ticketKey.searchFirst(tkKey);
            for (int i = 0; i < vt.size(); ++i){
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
            short totStation, Vector<ticket> &ret){
            ret.clear();
            Vector<ticket> vt1, vt2;
            ticket ans1, ans2;
            Date minTime;
            for (short i = 0; i < totStation; ++i){
                if (i != tk_position.first() && t != tk_position.second())
                I_selectTicket(Pair<short, short>(tk_position.first(), i), tk_date, tk_catalog, vt1);
                I_selectTicket(Pair<short, short>(i, tk_position.second()), tk_date, tk_catalog, vt2);
                for (int j = 0; j < vt1.size(); ++j){
                    for (int k = 0; k < vt2.size(); ++k){
                        if (minTime < vt2[k].tk_time.second() - vt1[j].tk_time.first()){
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
            ret.push_bakc(ans2);
        }

        Status I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog, int &num, Vector<ticket> &ret){
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            for (auto it = userSel.first.p_ticketBooked.begin(); it != userSel.first.p_ticketBooked.end(); ++it){
                if (it->tk_date == p_date && it->tk_catalog == tk_catalog)
                    ret.push_back(*it);
            }
            if (ret.empty())
                return NoTicketBooked;
            return Success;
        }

        Status I_selectTrain(int p_id, train &ret){
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            ret = trainSel.first;
            return Success;
        }

        ~Select();
    };

    class Update : public Interface {
    public:
        Status I_updateUser(int p_id, const String &p_name, const String &p_email, long long &p_phone){
            auto userSel = userIdTree.search(p_id);
            if (!userSel.second)
                return NoThisUser;
            user newUser = userSel.first;
            newUser.p_username = p_name;
            newUser.p_email = p_email;
            newUser.p_phone = p_phone;
            userIdTree.update(p_id, newUser);
            return Success;
        }

        Status I_updateUserPrivilege(int p_id, int p_id2, int p_privilege){
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

        Status I_updateTrainSellingStatus(int t_id);

        Status I_updateTrain(int t_id, train data){
            auto trainSel = trainTree.search(t_id);
            if (!trainSel.second)
                return NoThisTrain;
            trainTree.update(t_id, data);
            if (trainSel.first.M_stationFrom() == data.M_stationFrom())
                trainFromTree.update(trainKeyFrom(trainSel.first), data);
            else{
                trainFromTree.erase(trainKeyFrom(trainSel.first));
                trainFromTree.insert(trainKeyFrom(data), data);
            }
            if (trainSel.first.M_stationTo() == data.M_stationTo())
                trainToTree.update(trainKeyTo(trainSel.first), data);
            else{
                trainToTree.erase(trainKeyTo(trainSel.first));
                trainToTree.insert(trainKeyTo(data), data);
            }
        }

        ~Update();
    };

    class Delete : public Interface {
    public:
        Status I_deleteUserBookedTicket(int p_id, Date p_date, int tk_id, Pair<int, int> tk_location, int tk_kind);

        Status I_deleteTrain(int p_id){
            auto trainSel = trainTree.search(p_id);
            if (!trainSel.second)
                return NoThisTrain;
            trainTree.erase(p_id);
            trainFromTree.erase(trainKeyFrom(trainSel.first));
            trainToTree.erase(trainKeyTo(trainSel.first));
        }

        ~Delete();
    };

}


#endif //INC_2018DATASTRUCTUREBIGWORK_KERNEL_HPP
