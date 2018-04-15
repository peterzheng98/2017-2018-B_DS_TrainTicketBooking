//
// Created by Peter Zheng on 2018/04/10.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_KERNEL_H
#define INC_2018DATASTRUCTUREBIGWORK_KERNEL_H

#include "CoreData.h"
#include "BigNum.hpp"

using namespace myAlgorithm;

class ticket {
private:
    Pair<int, int> tk_position;
    Pair<Date, Date> tk_time;
    Date tk_date;
    int tk_catalog;
    int tk_id;
    Vector<int> tk_ticketRemain;
    TicketOnSale tk_onSale;
    Vector<int> tk_price;
public:
    Pair<int, int> M_position() const;

    Pair<Date, Date> M_time() const;

    Date M_date() const;

    int M_catalog() const;

    int M_id() const;

    Vector<int> M_ticketRemain() const;

    TicketOnSale M_onSale() const;

    Vector<int> M_price() const;
};

class train {
private:
    int t_id;
    int t_trainID;
    wchar_t *t_name;
    int t_stationNumber;
    int t_priceNumber;
    wchar_t *t_levelName;
    Vector<ticket> t_ticketInside;
public:
    int M_id() const;

    int M_trainID() const;

    wchar_t *M_name() const;

    int M_stationNumber() const;

    int M_priceNumber() const;

    wchar_t *M_levelName() const;

    Vector<ticket> M_ticketInside() const;
};

class user {
private:
    long long p_id;
    wchar_t *p_username;
    wchar_t *p_password;
    BigNum<short> p_passwordHash;
    wchar_t *p_email;
    long long p_phone;
    Set<ticket> p_ticketBooked;
public:
    long long M_id() const;

    wchar_t *M_username() const;

    wchar_t *M_password() const;

    BigNum<short> M_passwordHash() const;

    wchar_t *M_email() const;

    long long M_phone() const;

    Set<ticket> M_ticketBooked() const;

    UserPrivilege M_privilege() const;
};


namespace Kernel {
    class Interface { virtual ~Interface() {} };

    class Insert : public Interface {
    public:
        Status I_addUser(wchar_t *p_name, wchar_t *p_word, wchar_t *p_email, long long p_phone, int &p_id);

        Status
        I_addUserBookedTicket(int p_id, int tk_num, int tk_id, Pair<int, int> tk_position, Date tk_date, int tk_kind);

        Status I_addTrainTicket(int tk_id, wchar_t *t_name, int t_stationNum, int t_priceNum,
                                const Vector<ticket> &t_ticketInside);
    };

    class Select : public Interface {
    public:
        Status I_selectUser(int p_id, wchar_t *p_word);

        Status I_selectUser(wchar_t *p_name, wchar_t *p_word);

        Status I_selectUser(int p_id, wchar_t &*p_name, wchar_t &*p_email, long long &p_phone);

        Status
        I_selectTicket(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum, Vector<ticket> &ret);

        Status I_selectTicketTransfer(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum,
                                      Vector<ticket> &ret);

        Status I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog, int &num, Vector<ticket> &ret);

        Status I_selectTrain(int p_id, train &ret);
    };

    class Update : public Interface {
    public:
        Status I_updateUser(int p_id, wchar_t &*p_name, wchar_t &*p_email, long long &p_phone);

        Status I_updateUserPrivilege(int p_id, int p_id2, int p_privilege);

        Status I_updateTrainSellingStatus(int t_id);

        Status I_updateTrain(int t_id, train data);
    };

    class Delete : public Interface {
    public:
        Status I_deleteUserBookedTicket(int p_id, Date p_date, int tk_id, Pair<int, int> tk_location, int tk_kind);

        Status I_deleteTrain(int p_id);
    };

    class Grant : public Interface{
    public:
    };

};


#endif //INC_2018DATASTRUCTUREBIGWORK_KERNEL_H
