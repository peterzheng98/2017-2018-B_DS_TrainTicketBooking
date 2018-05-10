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
        int size = 512;
        char *data = nullptr;
        int len;


        void extendSpace(){
            size = size << 1;
            char *newCharSeq = new char[size];
            char *oldCharSeq = data;
            for (int i = 0; i < len; i++) newCharSeq[i] = oldCharSeq[i];
            data = newCharSeq;
            delete oldCharSeq;
        }

        void smallerSpace(){
            size = size >> 1;
            char *newCharSeq = new char[size];
            char *oldCharSeq = data;
            for (int i = 0; i < len; i++) newCharSeq[i] = oldCharSeq[i];
            data = newCharSeq;
            delete oldCharSeq;
        }

    public:
        String(){
            size = 512;
            data = new char[size];
            len = 0;
            locale = ENGLISH;
        }

        String(const String &rhs){
            size = rhs.size;
            len = rhs.len;
            locale = rhs.locale;
            char *charSeq = new char[size];
            for (int i = 0; i < len; i++) charSeq[i] = rhs.data[i];
            data = charSeq;
        }

        String &operator=(const String &rhs){
            if (this == &rhs) return *this;

            if (size != 0 && data != nullptr) delete data;
            size = rhs.captity();
            len = rhs.length();
            data = new char[size];

            for (int i = 0; i < len; i++) data[i] = rhs[i];
            return *this;
        }

        explicit String(const int &initalSize){
            if (initalSize <= 0) throw 1; // TODO: throw invalid length
            size = initalSize;
            data = new char[size];
            len = 0;
            locale = ENGLISH;
        }

        explicit String(const char &ch){
            len = 1;
            size = 512;
            data = new char[size];
            data[0] = ch;
            locale = ENGLISH;
        }

        explicit String(const char ch[], int loc){
            if (loc != 0 && loc != 1) throw 1; // TODO: throw invalid option
            locale = (Language) loc;
            size = (strlen(ch) << 1 > 512 ? strlen(ch) << 1 : 512);
            data = new char[size];
            for (int i = 0; i < strlen(ch); i++) data[i] = ch[i];
            len = strlen(ch);
        }

        const char operator[](const int &index) const{
            if (index < 0 || index >= len) throw 1; // TODO: throw out of bound
            return data[index];
        }

        char operator[](const int &index){
            if (index < 0 || index >= len) throw 1; // TODO: throw out of bound
            return data[index];
        }

        String &operator+=(const char &ch){
            if (len + 1 >= size) extendSpace();
            data[len] = ch;
            len++;
            return *this;
        }

        String &operator+=(const String &rhs){
            if (rhs.empty()) return *this;

            if (rhs.len + len > size) extendSpace();
            for (int i = len; i < rhs.len + len; ++i) data[i] = rhs[i - len];
            len = rhs.len + len;
            return *this;
        }

        const int length() const{
            return len;
        }

        const bool empty() const{
            return len == 0;
        }

        const int captity() const{
            return size;
        }

        bool insert(const char &ch, const int &index){
            if (index < 0 || index > len) throw 1; //TODO: throw out of bound
            if (len + 1 > size) extendSpace();
            for (int i = len; i > index; --i) data[i] = data[i - 1];
            data[index] = ch;
            len++;
            return true;
        }

        bool erase(const int &index){
            if (index < 0 || index >= len) throw 1; //TODO: throw out of bound
            for (int i = index; i < len - 1; ++i) data[i] = data[i + 1];
            len--;
            if (len < (size / 2 - 1)) smallerSpace();
            return true;
        }

        void changeLocale(int To){
            if (To != 0 && To != 1) throw 1; // TODO: throw invalid option
            locale = (Language) To;
        }

        bool operator==(const String &rhs){
            if (rhs.len != len) return false;
            for (int i = 0; i < rhs.len; ++i) if (data[i] != rhs[i]) return false;
            return true;
        }

        bool operator==(const char* rhs){
            if(strlen(rhs) != len) return false;
            for(int i = 0; i < len; ++i) if(data[i] != rhs[i]) return false;
            return true;
        }

        bool operator!=(const String &rhs){
            if (rhs.len != len) return true;
            for (int i = 0; i < rhs.len; ++i) if (data[i] != rhs[i]) return true;
            return false;
        }

        bool operator!=(const char* rhs){
            if(strlen(rhs) != len) return true;
            for(int i = 0; i < len; ++i) if(data[i] != rhs[i]) return true;
            return false;
        }

        bool operator<=(const String &rhs){
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return false;
                if (data[i] < rhs[i]) return true;
            }

            if (len > rhs.length()) return false;
            if (len < rhs.length()) return true;
            return true;
        }

        bool operator>=(const String &rhs){
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return true;
                if (data[i] < rhs[i]) return false;
            }

            if (len > rhs.length()) return true;
            if (len < rhs.length()) return false;
            return true;
        }

        bool operator<(const String &rhs){
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return false;
                if (data[i] < rhs[i]) return true;
            }

            return len <= rhs.length();
        }

        bool operator>(const String &rhs){
            int minL = Utilities::min<int>(len, rhs.length());
            for (int i = 0; i < minL; i++) {
                if (data[i] > rhs[i]) return true;
                if (data[i] < rhs[i]) return false;
            }
            return len > rhs.length();
        }

        void clear(){
            char *old = data;
            delete old;
            data = new char[size];
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
            if (rhs.len >= rhs.size - 1) rhs.extendSpace();
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
            if (ws.len >= ws.size - 1) ws.extendSpace();
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
            if (rhs.len >= rhs.size - 1) rhs.extendSpace();
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
