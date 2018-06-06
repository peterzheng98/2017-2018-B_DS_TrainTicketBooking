//
// Created by Peter Zheng on 2018/05/28.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_DATEANDTIME_H
#define INC_2018DATASTRUCTUREBIGWORK_DATEANDTIME_H

#include "CoreData.h"
#include "String.h"

namespace myAlgorithm {
    class Date {
        friend std::ostream &operator<<(std::ostream &os, const Date &data);

    private:
        TriplePair<short, short, short> dataOfDate;
    public:
        Date() = default;

        Date(const String &rhs) {
            String r1, r2, r3;
            bool Result = true;
            split('-', rhs, r1, r2, String::__SPLIT_STRING_WITHOUT_CHAR, Result);
            if (!Result) dataOfDate = TriplePair<short, short, short>(0, 0, 0);
            else {
                String r22 = r2;
                split('-', r22, r2, r3, String::__SPLIT_STRING_WITHOUT_CHAR, Result);
                if (!Result) dataOfDate = TriplePair<short, short, short>(0, 0, 0);
                else {
                    dataOfDate = TriplePair<short, short, short>((short) r1, (short) r2, (short) r3);
                }
            }
        }

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

        friend std::istream &operator>>(std::istream &is, Date &data) {
            short t1, t2, t3;
            char ch, ch2;
            is >> t1 >> ch >> t2 >> ch2 >> t3;
            return is;
        }

        bool operator==(const Date &rhs) const {
            return dataOfDate.first() == rhs.dataOfDate.first()
                   && dataOfDate.second() == rhs.dataOfDate.second()
                   && dataOfDate.third() == rhs.dataOfDate.third();
        }

        bool operator!=(const Date &rhs) const {
            return dataOfDate.first() != rhs.dataOfDate.first()
                   || dataOfDate.second() != rhs.dataOfDate.second()
                   || dataOfDate.third() != rhs.dataOfDate.third();
        }

        bool operator<(const Date &rhs) const {
            return dataOfDate.first() < rhs.getYear()
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() < rhs.getMonth())
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() == rhs.getMonth() &&
                       dataOfDate.third() < rhs.getDay());
        }

        bool operator<=(const Date &rhs) const {
            return dataOfDate.first() <= rhs.getYear()
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() <= rhs.getMonth())
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() == rhs.getMonth() &&
                       dataOfDate.third() <= rhs.getDay());
        }

        bool operator>(const Date &rhs) const {
            return dataOfDate.first() > rhs.getYear()
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() > rhs.getMonth())
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() == rhs.getMonth() &&
                       dataOfDate.third() > rhs.getDay());
        }

        bool operator>=(const Date &rhs) const {
            return dataOfDate.first() >= rhs.getYear()
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() >= rhs.getMonth())
                   || (dataOfDate.first() == rhs.getYear() && dataOfDate.second() == rhs.getMonth() &&
                       dataOfDate.third() >= rhs.getDay());
        }

        Date nextDate() {
            short yy, mm, dd;
            yy = getYear(), mm = getMonth(), dd = getDay();
            short Day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            dd++;
            if (M_isLeapYear(yy)) Day[1] = 29;
            if (dd > Day[mm - 1]) dd -= Day[mm - 1], mm++;
            if (mm > 12) yy++;
            return Date(yy, mm, dd);
        }
    };

    Date nextDate(const Date &rhs) {
        short yy, mm, dd;
        yy = rhs.getYear(), mm = rhs.getMonth(), dd = rhs.getDay();
        short Day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        dd++;
        if (rhs.M_isLeapYear(yy)) Day[1] = 29;
        if (dd > Day[mm - 1]) dd -= Day[mm - 1], mm++;
        if (mm > 12) yy++;
        return Date(yy, mm, dd);
    }

    std::ostream &operator<<(std::ostream &os, const Date &data) {
        printf("%04d-%02d-%02d", data.getYear(), data.getMonth(), data.getDay());
        return os;
    }

    class Time {
        friend std::ostream &operator<<(std::ostream &os, const Time &rhs);

        friend Time operator+(const Time &lhs, const Time &rhs);

//        friend Time operator-(const Time &lhs, const Time &rhs);

    private:
        Pair<short, short> dataOfTime;
    public:
        Time() { dataOfTime = Pair<short, short>(0, 0); }

        Time(const Time &rhs) : dataOfTime(rhs.dataOfTime) {}

        Time(const Time &rhs, int AddTime) {
            dataOfTime = rhs.dataOfTime;
            int min = dataOfTime.second();
            int hour = dataOfTime.first();
            min += AddTime;
            if (min < 0) {
                hour -= 100;
                min += 6000;
            }
            hour += min / 60;
            min = min % 60;
            while (hour < 0) hour += 24;
            dataOfTime.setData(hour, min);
        }

        Time(int minute){
            if(minute < 0) dataOfTime = Pair<short, short>(-1, -1);
            else dataOfTime = Pair<short, short>(minute / 60, minute % 60);
        }
        Time(int hh, int mm) : dataOfTime(Pair<short, short>(hh, mm)) {}

        Time(const String &source) {
            if (source == "xx:xx") dataOfTime = Pair<short, short>(-1, -1);
            else {
                String s1, s2;
                bool Result;
                split(':', source, s1, s2, String::__SPLIT_STRING_WITHOUT_CHAR, Result);
                if (!Result) dataOfTime = Pair<short, short>(0, 0);
                else {
                    int res1 = (int) s1;
                    int res2 = (int) s2;
                    if (res1 < 0 || res1 > 24 || res2 < 0 || res2 > 60) dataOfTime = Pair<short, short>(0, 0);
                    else dataOfTime = Pair<short, short>(res1, res2);
                }
            }
        }

        Time(const String &source, int AddTime) {
            String s1, s2;
            bool Result;
            split(':', source, s1, s2, String::__SPLIT_STRING_WITHOUT_CHAR, Result);
            if (!Result) dataOfTime = Pair<short, short>(0, 0);
            else {
                int res1 = (int) s1;
                int res2 = (int) s2;
                if (res1 < 0 || res1 > 24 || res2 < 0 || res2 > 60) dataOfTime = Pair<short, short>(0, 0);
                else dataOfTime = Pair<short, short>(res1, res2);
            }
            int min = dataOfTime.second();
            int hour = dataOfTime.first();
            min += AddTime;
            if (min < 0) {
                hour -= 100;
                min += 6000;
            }
            hour += min / 60;
            min = min % 60;
            while (hour < 0) hour += 24;
            dataOfTime.setData(hour, min);
        }

        int operator-(const Time &rhs) const {
            int h2 = rhs.getHour(), m2 = rhs.getMin();
            int h1 = dataOfTime.first(), m1 = dataOfTime.second();
            if (m2 == -1 && h2 == -1) return -1;
            if (h2 < h1) h2 += 24;
            if (m2 < m1) h2--, m2 += 60;
            int p = (h2 - h1) * 60 + (m2 - m1);
            return -p;
        }

        bool operator==(const Time &rhs) const {
            return rhs.getMin() == dataOfTime.second() && rhs.getHour() == dataOfTime.first();
        }

        bool operator!=(const Time &rhs) const {
            return rhs.getMin() != dataOfTime.second() || rhs.getHour() != dataOfTime.first();
        }

        bool operator<(const Time &rhs) const {
            return dataOfTime.first() < rhs.getHour()
                   || (dataOfTime.first() == rhs.getHour() && dataOfTime.second() < rhs.getMin());
        }

        bool operator<=(const Time &rhs) const {
            return dataOfTime.first() <= rhs.getHour()
                   || (dataOfTime.first() == rhs.getHour() && dataOfTime.second() <= rhs.getMin());
        }

        bool operator>(const Time &rhs) const {
            return dataOfTime.first() > rhs.getHour()
                   || (dataOfTime.first() == rhs.getHour() && dataOfTime.second() > rhs.getMin());
        }

        bool operator>=(const Time &rhs) const {
            return dataOfTime.first() >= rhs.getHour()
                   || (dataOfTime.first() == rhs.getHour() && dataOfTime.second() >= rhs.getMin());
        }

        int getHour() const { return dataOfTime.first(); }

        int getMin() const { return dataOfTime.second(); }

        int setHour(int hh) { dataOfTime.setFirst(hh); }

        int setMin(int mm) { dataOfTime.setSecond(mm); }
    };

    std::ostream &operator<<(std::ostream &os, const Time &rhs) {
        if(rhs.getHour() < 0 && rhs.getMin() < 0){
            os << "xx:xx";
            return os;
        }
        int hh = rhs.getHour(), mm = rhs.getMin();
        if(hh / 10 == 0) os << "0";
        os << rhs.getHour() << ":";
        if(mm / 10 == 0) os << "0";
        os << rhs.getMin();
        return os;
    }

    Time operator+(const Time &lhs, const Time &rhs) {
        int hh = lhs.getHour() + rhs.getHour();
        int mm = lhs.getMin() + rhs.getMin();
        hh = hh + mm / 60;
        mm = mm % 60;
        return Time(hh, mm);
    }
}

#endif //INC_2018DATASTRUCTUREBIGWORK_DATEANDTIME_H
