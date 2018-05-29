//
// Created by Peter Zheng on 2018/04/10.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
#define INC_2018DATASTRUCTUREBIGWORK_COREDATA_H

#ifndef INC_IOSTREAM
#define INC_IOSTREAM

#include <iostream>

#endif


enum Status {
    Success,
    NameHasExisted,
    NoThisUser,
    NoRemainTicket,
    NoThisTrain,
    NoTicketBooked,
    NoPrivilege,
    TrainHasBeenOnSale
};

enum UserPrivilege {
    Admin,
    User,
    NotRegister
};

namespace myAlgorithm {
    class Utilities {
    public:
        template<class T>
        inline static T min(const T &a, const T &b) {
            return a > b ? b : a;
        }

        template<class T>
        inline static T max(const T &a, const T &b) {
            return a > b ? a : b;
        }
    };

    /*
     * Shouldn't be used for pointer!!
     */
    template<class T, class U>
    class Pair {
    private:
        T t1;
        U t2;
    public:
        Pair() = default;

        Pair(const T &T1, const U &T2) : t1(T1), t2(T2) {}

        Pair(const Pair &rhs) {
            t1 = rhs.t1;
            t2 = rhs.t2;
        }

        Pair &operator=(const Pair &rhs) {
            if (&rhs == this) return *this;
            t1 = rhs.first();
            t2 = rhs.second();
            return *this;
        }

        T first() { return t1; }

        const T first() const { return t1; }

        U second() { return t2; }

        const U second() const { return t2; }

        void setFirst(T _t1) {
            t1 = _t1;
        }

        void setSecond(U _t2) {
            t2 = _t2;
        }

        void setData(T _t1, U _t2) {
            t1 = _t1;
            t2 = _t2;
        }

        bool operator <(const Pair<T, U> &p) const{
            return t1 < p.t1 || (t1 == p.t1 && t2 < p.t2);
        }

        bool operator ==(const Pair<T, U> &p) const{
            return t1 == p.t1 && t2 == p.t2;
        }

        bool operator!=(const Pair<T, U> &p) const{
            return t1 != p.t1 || t2 != p.t2;
        }
    };

    /*
     * Shouldn't be used for pointer!!
     */
    template<class T, class U, class K>
    class TriplePair {
    private:
        T t1;
        U t2;
        K t3;
    public:
        TriplePair() = default;

        TriplePair(const T &T1, const U &T2, const K &T3) : t1(T1), t2(T2), t3(T3) {}

        TriplePair(const TriplePair &rhs) {
            t1 = rhs.t1;
            t2 = rhs.t2;
            t3 = rhs.t3;
        }

        TriplePair &operator=(const TriplePair &rhs) {
            if (&rhs == this) return *this;
            t1 = rhs.first();
            t2 = rhs.second();
            t3 = rhs.third();
            return *this;
        }

        T first() const {
            return t1;
        }

        const U second() const {
            return t2;
        }

        const K third() const {
            return t3;
        }

        void setFirst(T _t1) {
            t1 = _t1;
        }

        void setSecond(U _t2) {
            t2 = _t2;
        }

        void setThird(K _t3) {
            t3 = _t3;
        }

        void setData(T _t1, U _t2, K _t3) {
            t1 = _t1;
            t2 = _t2;
            t3 = _t3;
        }
    };


}


#endif //INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
