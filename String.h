//
// Created by Peter Zheng on 2018/05/05.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_STRING_H
#define INC_2018DATASTRUCTUREBIGWORK_STRING_H

#include <iostream>
#include "CoreData.h"

namespace myAlgorithm {
    class String {
    private:
        enum Language {
            CHINESE,
            ENGLISH
        };
        int size = 512;
        char *data = nullptr;
        int len;
        Language locale;

        void extendSpace();

        void smallerSpace();

    public:
        String();

        explicit String(const String &rhs);

        explicit String &operator=(const String &rhs);

        explicit String(const int &initalSize);

        explicit String(const char &ch);

        explicit String(const char ch[], int loc);

        const char operator[](const int &index) const;

        char operator[](const int &index);

        friend String operator+(const String &lhs, const String& rhs);

        String operator+(const String &lhs, const char& ch);

        String &operator+=(const char& ch);

        String &operator+=(const String &rhs);

        const int length() const;

        const bool empty() const;

        const int captity() const;

        bool insert(const char &ch, const int &index);

        bool erase(const int &index);

        void changeLocale(int To);

        bool operator==(const String &rhs);

        bool operator!=(const String &rhs);

        bool operator<=(const String &rhs);

        bool operator>=(const String &rhs);

        bool operator<(const String &rhs);

        bool operator>(const String &rhs);

        void clear();

        friend std::ostream &operator<<(std::ostream &os, const String &rhs);

        friend std::istream &operator>>(std::istream &is, String &rhs);

        friend std::wistream &operator>>(std::wistream &wis, String &ws);

        friend std::wostream &operator<<(std::wostream &os, const String &rhs);


    };

}


#endif //INC_2018DATASTRUCTUREBIGWORK_STRING_H
