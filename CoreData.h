//
// Created by Peter Zheng on 2018/04/10.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
#define INC_2018DATASTRUCTUREBIGWORK_COREDATA_H

#ifndef INC_IOSTREAM
#define INC_IOSTREAM

//#include <iostream>

#endif


enum Status {
    Success,
    NoThisUser,
    NoRemainTicket,
    NoThisTrain,
};

enum UserPrivilege {
    Admin,
    User,
    NotRegister,
};

enum TicketOnSale {
    Available,
    Unavailable
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

        T first() const {
            return t1;
        }

        const U second() const {
            return t2;
        }

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

        bool operator==(const TriplePair& rhs){
            return t1 == rhs.first() &&
                   t2 == rhs.second() &&
                   t3 == rhs.third();
        }
    };

    class Date {
    protected:
        TriplePair<short, short, short> dataOfDate;
    public:
        Date() = default;

        Date(short year, short month, short day) {
            dataOfDate.setData(year, month, day);
        }

        Date(const Date &rhs) {
            dataOfDate = rhs.dataOfDate;
        }

        Date &operator=(const Date &rhs) {
            if (&rhs == this) return *this;
            dataOfDate.setData(rhs.getYear(), rhs.getMonth(), rhs.getDay());
            return *this;
        }

        const short getYear() const {
            return dataOfDate.first();
        }

        const short getMonth() const {
            return dataOfDate.second();
        }

        const short getDay() const {
            return dataOfDate.third();
        }

        inline bool M_isLeapYear() const {
            return (dataOfDate.first() % 4 == 0 && dataOfDate.first() % 100 != 0) || (dataOfDate.first() % 400 == 0);
        }

        inline bool M_isLeapYear(int year) const {
            return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        }

        inline int M_dayInTheYear() const {
            short day = dataOfDate.third();
            short month = dataOfDate.second();
            short Day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (M_isLeapYear()) Day[1] = 29;
            for (int i = 0; i < month - 1; i++) day += Day[i];
            return day;
        }

        inline int M_dayInTheYear(int year, int month, int day) const {
            int Day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if (M_isLeapYear(year)) Day[1] = 29;
            for (int i = 0; i < month - 1; i++) day += Day[i];
            return day;
        }

        int operator-(const Date &rhs) const {
            int year1 = dataOfDate.first();
            int month1 = dataOfDate.second();
            int day1 = dataOfDate.third();
            int year2 = rhs.getYear();
            int month2 = rhs.getMonth();
            int day2 = rhs.getDay();
            if (year1 == year2 && month1 == month2)
                return day1 > day2 ? day1 - day2 : day2 - day1;
            if (year1 == year2) {
                int d1, d2;
                d1 = M_dayInTheYear();
                d2 = rhs.M_dayInTheYear();
                return d1 > d2 ? d1 - d2 : d2 - d1;
            }
            if (year1 > year2) {
                int t;
                t = year1;
                year1 = year2;
                year2 = t;
                t = month1;
                month1 = month2;
                month2 = t;
                t = day1;
                day1 = day2;
                day2 = t;
            }
            int d1, d2, d3;
            if (M_isLeapYear())
                d1 = 366 - M_dayInTheYear(year1, month1, day1);
            else
                d1 = 365 - M_dayInTheYear(year1, month1, day1);
            d2 = rhs.M_dayInTheYear(year2, month2, day2);
            d3 = 0;
            for (int i = year1 + 1; i < year2; i++)
                if (M_isLeapYear(i)) d3 += 366; else d3 += 365;
            return d1 + d2 + d3;
        }

        friend std::ostream &operator<<(std::ostream &os, const Date &data) {
            os << data.getYear() << "-" << data.getMonth() << "-" << data.getDay();
            return os;
        }

        friend std::istream &operator>>(std::istream &is, Date &data) {
            short t1, t2, t3;
            char ch, ch2;
            is >> t1 >> ch >> t2 >> ch2 >> t3;
            return is;
        }

        bool operator==(const Date& rhs){
            return dataOfDate == rhs.dataOfDate;
        }

        bool operator>=(const Date& rhs){
            Date Cmp = Date(1, 1, 1);
            int res1 = *this - (Cmp);
            int res2 = rhs - Cmp;
            return res1 >= res2;
        }

        bool operator>(const Date& rhs){
            Date Cmp = Date(1, 1, 1);
            int res1 = *this - (Cmp);
            int res2 = rhs - Cmp;
            return res1 > res2;
        }

        bool operator<=(const Date& rhs){
            Date Cmp = Date(1, 1, 1);
            int res1 = *this - (Cmp);
            int res2 = rhs - Cmp;
            return res1 <= res2;
        }

        bool operator<(const Date& rhs){
            Date Cmp = Date(1, 1, 1);
            int res1 = *this - (Cmp);
            int res2 = rhs - Cmp;
            return res1 < res2;
        }

        bool operator!=(const Date& rhs){
            return !(dataOfDate == rhs.dataOfDate);
        }
    };
}


#endif //INC_2018DATASTRUCTUREBIGWORK_COREDATA_H
