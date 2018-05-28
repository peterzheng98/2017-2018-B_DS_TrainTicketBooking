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

class ticket {
    friend class Kernel::Select;
    friend class Kernel::Update;
private:
    Pair<int, int>  tk_position;
    Pair<Date, Date> tk_time;
    Date tk_date;
    int tk_catalog;
    int tk_id;
    Vector<int> tk_ticketRemain;
    TicketOnSale tk_onSale;
    Vector<int> tk_price;
public:
    Pair<int, int> M_position() const{
        return tk_position;
    }

    Pair<Date, Date> M_time() const{
        return tk_time;
    }

    Date M_date() const{
        return tk_date;
    }

    int M_catalog() const{
        return tk_catalog;
    }

    int M_id() const{
        return tk_id;
    }

    Vector<int> M_ticketRemain() const{
        return tk_ticketRemain;
    }

    TicketOnSale M_onSale() const{
        return tk_onSale;
    }

    Vector<int> M_price() const{
        return tk_price;
    }
};

class trainKeyFrom;
class trainKeyTo;

class train {
    friend class trainKeyFrom;
    friend class trainKeyTo;
    friend class Kernel::Select;
    friend class Kernel::Update;
private:
    int t_id;
    int t_trainID;
    String t_name;
    int t_stationFrom, t_stationTo;
    int t_priceNumber;
    String t_levelName;
    Vector<ticket> t_ticketInside;
public:
    int M_id() const{
        return t_id;
    }

    int M_trainID() const{
        return t_trainID;
    }

    String M_name() const{
        return t_name;
    }

    int M_stationFrom() const{
        return t_stationFrom;
    }

    int M_stationTo() const{
        return t_stationTo;
    }

    int M_priceNumber() const{
        return t_priceNumber;
    }

    String M_levelName() const{
        return t_levelName;
    }

    Vector<ticket> M_ticketInside() const{
        return t_ticketInside;
    }
};

class user {
    friend class Kernel::Select;
    friend class Kernel::Update;
private:
    int p_id;
    String p_username;
    String p_password;
    BigNum<short> p_passwordHash;
    String p_email;
    long long p_phone;
    Set<ticket> p_ticketBooked;
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

    BigNum<short> M_passwordHash() const{
        return p_passwordHash;
    }

    String M_email() const{
        return p_email;
    }

    long long M_phone() const{
        return p_phone;
    }

    Set<ticket> M_ticketBooked() const{
        return p_ticketBooked;
    }

    UserPrivilege M_privilege() const{
        return p_userPrivilege;
    }
};

class trainKeyFrom{
private:
    int t_id;
    int t_stationFrom;
public:
    trainKeyFrom(int id = 0, int stationFrom = 0)
        : t_id(id), t_stationFrom(stationFrom) {}
    trainKeyFrom(const train &t)
        : t_id(t.t_id), t_stationFrom(t.t_stationFrom) {}
    bool operator <(const trainKeyFrom &tkf) const{
        return t_stationFrom < tkf.t_stationFrom || (t_stationFrom == tkf.t_stationFrom && t_id < tkf.t_id);
    }
};

class trainKeyTo{
private:
    int t_id;
    int t_stationTo;
public:
    trainKeyTo(int id = 0, int stationTo = 0)
        : t_id(id), t_stationTo(stationTo) {}
    trainKeyTo(const train &t)
        : t_id(t.t_id), t_stationTo(t.t_stationTo) {}
    bool operator <(const trainKeyTo &tkf) const{
        return t_stationTo < tkf.t_stationTo || (t_stationTo == tkf.t_stationTo && t_id < tkf.t_id);
    }
};

static int nowId = 2018;

BPlusTree<int, user> userIdTree(false, "tmp/user.dat");
BPlusTree<String, int> userNameTree(false, "tmp/userName.dat"); 
BPlusTree<trainKeyFrom, train> trainFromTree(false, "tmp/trainFrom.dat");
BPlusTree<trainKeyTo, train> trainToTree(false, "tmp/trainTo.dat");
BPlusTree<int, train> trainTree(false, "tmp/train.dat");

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

        Status I_addUserBookedTicket(int p_id, int tk_num, int tk_id, Pair<int, int> tk_position, Date tk_date, int tk_kind);

        Status I_addTrainTicket(int tk_id, String t_name, int t_stationNum, int t_priceNum,
                                const Vector<ticket> &t_ticketInside);

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

        Status
        I_selectTicket(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum, Vector<ticket> &ret);

        Status I_selectTicketTransfer(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum,
                                      Vector<ticket> &ret);

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
