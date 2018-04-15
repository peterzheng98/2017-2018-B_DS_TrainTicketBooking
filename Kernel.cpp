//
// Created by Peter Zheng on 2018/04/10.
//

#include "Kernel.h"

Status Kernel::Insert::I_addUser(wchar_t *p_name, wchar_t *p_word, wchar_t *p_email, long long p_phone, int &p_id) {
    return NoRemainTicket;
}

Status Kernel::Insert::I_addUserBookedTicket(int p_id, int tk_num, int tk_id, Pair<int, int> tk_position, Date tk_date,
                                             int tk_kind) {
    return NoRemainTicket;
}

Status Kernel::Insert::I_addTrainTicket(int tk_id, wchar_t *t_name, int t_stationNum, int t_priceNum,
                                        const Vector<ticket> &t_ticketInside) {
    return NoRemainTicket;
}


Status Kernel::Select::I_selectUser(int p_id, wchar_t *p_word) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectUser(wchar_t *p_name, wchar_t *p_word) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectUser(int p_id, wchar_t &*p_name, wchar_t &*p_email, long long &p_phone) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectTicket(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum,
                                      Vector<ticket> &ret) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectTicketTransfer(Pair<int, int> tk_position, Date tk_date, int tk_catalog, int &retNum,
                                              Vector<ticket> &ret) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectUserBookedTicket(int p_id, Date p_date, int tk_catalog, int &num, Vector<ticket> &ret) {
    return NoRemainTicket;
}

Status Kernel::Select::I_selectTrain(int p_id, train &ret) {
    return NoRemainTicket;
}

Status Kernel::Update::I_updateUser(int p_id, wchar_t &*p_name, wchar_t &*p_email, long long &p_phone) {
    return NoRemainTicket;
}

Status Kernel::Update::I_updateUserPrivilege(int p_id, int p_id2, int p_privilege) {
    return NoRemainTicket;
}

Status Kernel::Update::I_updateTrainSellingStatus(int t_id) {
    return NoRemainTicket;
}

Status Kernel::Update::I_updateTrain(int t_id, train data) {
    return NoRemainTicket;
}

Status Kernel::Delete::I_deleteUserBookedTicket(int p_id, Date p_date, int tk_id, Pair<int, int> tk_location, int tk_kind) {
    return NoRemainTicket;
}

Status Kernel::Delete::I_deleteTrain(int p_id) {
    return NoRemainTicket;
}

wchar_t *user::M_username() const {
    return p_username;
}

wchar_t *user::M_password() const {
    return p_password;
}

BigNum<short> user::M_passwordHash() const {
    return BigNum<short>(p_passwordHash);
}

wchar_t *user::M_email() const {
    return p_email;
}

long long user::M_phone() const {
    return p_phone;
}

Set<ticket> user::M_ticketBooked() const {
    return Set<ticket>(p_ticketBooked);
}

UserPrivilege user::M_privilege() const {
    if(p_id % 10 == 0) return Admin;
    if(p_id % 10 == 1) return User;
    return NotRegister;
}

long long user::M_id() const {
    return p_id;
}

Pair<int, int> ticket::M_position() const {
    return Pair<int, int>(tk_position);
}

Pair<Date, Date> ticket::M_time() const {
    return Pair<Date, Date>(tk_time.first(), tk_time.second());
}

Date ticket::M_date() const {
    return Date(tk_date);
}

int ticket::M_catalog() const {
    return tk_catalog;
}

int ticket::M_id() const {
    return tk_id;
}

Vector<int> ticket::M_ticketRemain() const {
    return Vector<int>(tk_ticketRemain);
}

TicketOnSale ticket::M_onSale() const {
    return tk_onSale;
}

Vector<int> ticket::M_price() const {
    return Vector<int>(tk_price);
}

int train::M_id() const {
    return t_id;
}

int train::M_trainID() const {
    return t_trainID;
}

wchar_t *train::M_name() const {
    return t_name;
}

int train::M_stationNumber() const {
    return t_stationNumber;
}

int train::M_priceNumber() const {
    return t_priceNumber;
}

wchar_t *train::M_levelName() const {
    return t_levelName;
}

Vector<ticket> train::M_ticketInside() const {
    return Vector<ticket>(t_ticketInside);
}
