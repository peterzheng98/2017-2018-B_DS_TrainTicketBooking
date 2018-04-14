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
    return nullptr;
}

wchar_t *user::M_password() const {
    return nullptr;
}

BigNum<short> user::M_passwordHash() const {
    return BigNum<short>();
}

wchar_t *user::M_email() const {
    return nullptr;
}

long long user::M_phone() const {
    return 0;
}

Set<ticket> user::M_ticketBooked() const {
    return Set<ticket>();
}

UserPrivilege user::M_privilege() const {
    return NotRegister;
}

Pair<int, int> ticket::M_position() const {
    return Pair<int, int>();
}

Pair<Date, Date> ticket::M_time() const {
    return Pair<Date, Date>();
}

Date ticket::M_date() const {
    return Date();
}

int ticket::M_catalog() const {
    return 0;
}

int ticket::M_id() const {
    return 0;
}

Vector<int> ticket::M_ticketRemain() const {
    return Vector<int>();
}

TicketOnSale ticket::M_onSale() const {
    return Available;
}

Vector<int> ticket::M_price() const {
    return Vector<int>();
}

int train::M_id() const {
    return 0;
}

int train::M_trainID() const {
    return 0;
}

wchar_t *train::M_name() const {
    return nullptr;
}

int train::M_stationNumber() const {
    return 0;
}

int train::M_priceNumber() const {
    return 0;
}

wchar_t *train::M_levelName() const {
    return nullptr;
}

Vector<ticket> train::M_ticketInside() const {
    return Vector<ticket>();
}
