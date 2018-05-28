//
// Created by Peter Zheng on 2018/05/05.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_STRING_H
#define INC_2018DATASTRUCTUREBIGWORK_STRING_H

#include <iostream>
#include <fstream>
#include "CoreData.h"

namespace myAlgorithm {
    class String {
        friend std::ostream &operator<<(std::ostream &os, const String &rhs);

        friend std::istream &operator>>(std::istream &is, String &rhs);

        friend std::wistream &operator>>(std::wistream &wis, String &ws);

        friend std::wostream &operator<<(std::wostream &os, const String &rhs);

        friend std::ifstream &operator>>(std::ifstream &is, String &rhs);

        friend std::ofstream &operator<<(std::ofstream &os, const String &rhs);

        friend String operator+(const String &lhs, const String &rhs);

        friend String operator+(const String &lhs, const char &ch);

    public:
        enum Language {
            CHINESE,
            ENGLISH
        };
        Language locale;
    public:
        const static short sizeMax = 128; // 128 bits char
    private:
        char data[sizeMax];
        int len = 0;

    public:
        String() {
            len = 0;
            for(int i = 0;i < len;i++) data[i] = 0;
        }

        String(const String &rhs) {
            len = rhs.len;
            for (int i = 0; i < len; i++) data[i] = rhs.data[i];
            locale = rhs.locale;
        }

        String &operator=(const String &rhs) {
            if (this == &rhs) return *this;

            len = rhs.length();
            for (int i = 0; i < len; i++) data[i] = rhs[i];
            locale = rhs.Locale();
            return *this;
        }

        explicit String(const char &ch) {
            len = 1;
            data[0] = ch;
            locale = ENGLISH;
        }

        explicit String(const char ch[], int loc = 1) {
            len = strlen(ch);
            for (int i = 0; i < len; i++) data[i] = ch[i];
            locale = (Language) loc;
        }

        const Language Locale() const { return locale; }

        const int length() const { return len; }

        const bool empty() const { return len == 0; }

        const char operator[](const int &index) const {
            if (index < 0 || index >= len) throw 1; //TODO: out of bound
            return data[index];
        }

        char operator[](const int &index) {
            if (index < 0 || index >= len) throw 1; //TODO: out of bound
            return data[index];
        }

        String &operator+=(const String &rhs) {
            if (rhs.empty()) return *this;

            if (len + rhs.length() > sizeMax) throw 1; //TODO: string too long
            int newLen = len + rhs.length();
            for (int i = len; i < newLen; ++i) data[i] = rhs[i - len];
            return *this;
        }

        String &operator+=(const char &ch){
            if (len + 1 > sizeMax) throw 1; //TODO: string too long
            data[len] = ch;
            len++;
            return *this;
        }

        bool insert(const char &ch, const int &index) {
            if (index < 0 || index > len) throw 1;//TODO: out of bound
            if (len + 1 > sizeMax) throw 1; //TODO: string too long

            for (int i = len; i > index; --i) data[i] = data[i - 1];
            data[index] = ch;
            len++;
            return true;
        }

        bool erase(const int &index) {
            if (index < 0 || index >= len) throw 1; //TODO: throw out of bound
            for (int i = index; i < len - 1; ++i) data[i] = data[i + 1];
            len--;
            return true;
        }

        void changeLocale(int To) {
            if (To != 0 && To != 1) throw 1; // TODO: throw invalid option
            locale = (Language) To;
        }

        bool operator==(const String &rhs) {
            if (rhs.len != len) return false;
            for (int i = 0; i < rhs.len; ++i) if (data[i] != rhs[i]) return false;
            return true;
        }

        bool operator==(const char *rhs) {
            if (strlen(rhs) != len) return false;
            for (int i = 0; i < len; ++i) if (data[i] != rhs[i]) return false;
            return true;
        }

        bool operator!=(const String &rhs) {
            if (rhs.len != len) return true;
            for (int i = 0; i < rhs.len; ++i) if (data[i] != rhs[i]) return true;
            return false;
        }

        bool operator!=(const char *rhs) {
            if (strlen(rhs) != len) return true;
            for (int i = 0; i < len; ++i) if (data[i] != rhs[i]) return true;
            return false;
        }

        bool operator<=(const String &rhs) {
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return false;
                if (data[i] < rhs[i]) return true;
            }

            if (len > rhs.length()) return false;
            if (len < rhs.length()) return true;
            return true;
        }

        bool operator>=(const String &rhs) {
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return true;
                if (data[i] < rhs[i]) return false;
            }

            if (len > rhs.length()) return true;
            if (len < rhs.length()) return false;
            return true;
        }

        bool operator<(const String &rhs) {
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return false;
                if (data[i] < rhs[i]) return true;
            }

            return len <= rhs.length();
        }

        bool operator>(const String &rhs) {
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return true;
                if (data[i] < rhs[i]) return false;
            }
            return len > rhs.length();
        }

        void clear(){
            for(int i = 0; i < sizeMax; ++i) data[i] = 0;
            len = 0;
        }
    };
    String operator+(const String &lhs, const String &rhs) {
        String ret(lhs);
        ret += rhs;
        return ret;
    }

    String operator+(const String &lhs, const char &ch) {
        String ret(lhs);
        ret += ch;
        return ret;
    }

    std::istream &operator>>(std::istream &is, String &rhs) {
        rhs.clear();
        rhs.locale = String::ENGLISH;
        char ch;
        ch = getchar();
        while (isspace(ch)) ch = getchar();
        while (!isspace(ch)) {
            rhs.data[rhs.len++] = ch;
            ch = getchar();
        }
        is.unget();
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const String &rhs) {
        if (rhs.locale != String::ENGLISH) throw 1; //TODO: throw locale error(not English)
        for (int i = 0; i < rhs.length(); i++)
            os << rhs.data[i];
        return os;
    }

    std::wostream &operator<<(std::wostream &os, const String &rhs) {
        if (rhs.locale != String::CHINESE) throw 1; //TODO: throw locale error(not Chinese)
        for (int i = 0; i < rhs.length(); i++)
            os << rhs.data[i];
        return os;
    }

    std::wistream &operator>>(std::wistream &wis, String &ws) {
        ws.clear();
        ws.locale = String::CHINESE;
        char ch;
        ch = getchar();
        while (iswspace(ch)) ch = getchar();
        while (!iswspace(ch)) {
            ws.data[ws.len++] = ch;
            ch = getchar();
        }
        wis.unget();
        return wis;
    }

    std::ifstream &operator>>(std::ifstream &is, String &rhs) {
        rhs.clear();
        rhs.locale = String::ENGLISH;
        char ch;
        is.get(ch);
        while (isspace(ch)) is.get(ch);
        while (!isspace(ch)) {
            rhs.data[rhs.len++] = ch;
            is.get(ch);
        }
        return is;
    }

    std::ofstream &operator<<(std::ofstream &os, const String &rhs) {
        if (rhs.locale != String::ENGLISH) throw 1; //TODO: throw locale error(not English)
        for (int i = 0; i < rhs.length(); i++)
            os << rhs.data[i];
        return os;
    }
}


#endif //INC_2018DATASTRUCTUREBIGWORK_STRING_H
