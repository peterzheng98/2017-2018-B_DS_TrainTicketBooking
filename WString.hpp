//
// Created by FineArtz on 2018/04/11
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_WSTRING_HPP
#define INC_2018DATASTRUCTUREBIGWORK_WSTRING_HPP

#include <iostream>
#include <cstring>
#include <cstddef>
#include <cwchar>
#include <stdexcept>

namespace myAlgorithm{
class WString{
    friend WString operator +(const WString &ws1, const WString &ws2);
    friend WString operator +(const WString &ws, wchar_t ch);
    friend std::istream &operator >>(std::istream &is, WString &ws);
    friend std::ostream &operator <<(std::ostream &os, const WString &ws);
public:
    using value_type        = wchar_t;
    using reference         = wchar_t &;
    using const_reference   = const wchar_t &;
    using pointer           = wchar_t *;
    using const_pointer     = const wchar_t *;
    using difference_type   = std::ptrdiff_t;
    using size_type         = size_t;
private:
    wchar_t s[50];
    size_type _size = 0;;
public:
    //contructors
    WString() = default;
    WString(const WString &other) : _size(other._size) {
        for (size_type i = 0; i < other._size; ++i)
            s[i] = other.s[i];
    }
    WString(const wchar_t *other) : _size(wcslen(other)) {
        for (size_type i = 0; i < _size; ++i)
            s[i] = other[i];
    }
    WString &operator =(const WString &other){
        if (this == &other)
            return *this;
        memset(s, 0, sizeof(s));
        _size = other._size;
        for (size_type i = 0; i < other._size; ++i)
            s[i] = other.s[i];
    }
    ~WString(){}

    wchar_t &operator [](int x){
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: index out of range");
        return s[x];
    }
    const wchar_t &operator [](int x) const {
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: index out of range");
        return s[x];
    }
    wchar_t &at(int x){
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: index out of range");
        return s[x];
    }
    const wchar_t &at(int x) const {
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: index out of range");
        return s[x];
    }

    bool operator ==(const WString &rhs){
        if (_size != rhs._size)
            return false;
        for (size_type i = 0; i < rhs._size; ++i)
            if (s[i] != rhs.s[i])
                return false;
        return true;
    }
    bool operator !=(const WString &rhs){
        return !(*this == rhs);
    }

    bool operator <(const WString &rhs){
        if (rhs._size == 0)
            return false;
        if (_size == 0)
            return true;
        for (size_type i = 0; i < _size; ++i){
            if (s[i] > rhs.s[i])
                return false;
            if (s[i] < rhs.s[i])
                return true;
        }
        return (_size < rhs._size);
    }
    bool operator <=(const WString &rhs){
        return (*this < rhs || *this == rhs);
    }
    bool operator >(const WString &rhs){
        if (_size == 0)
            return false;
        if (rhs._size == 0)
            return true;
        for (size_type i = 0; i < _size; ++i){
            if (s[i] > rhs.s[i])
                return true;
            if (s[i] < rhs.s[i])
                return false;
        }
        return (_size > rhs._size);
    }
    bool operator >=(const WString &rhs){
        return (*this > rhs || *this == rhs);
    }

    const wchar_t &front() const {
        if (_size == 0)
            throw std::runtime_error("WString: front of empty container");
        return s[0];
    }
    const wchar_t &back() const {
        if (_size == 0)
            throw std::runtime_error("WString: front of empty container");
        return s[_size - 1];
    }

    bool empty(){
        return _size == 0;
    }
    size_type size(){
        return _size;
    }
    size_type length(){
        return _size;
    }
    void clear(){
        memset(s, 0, sizeof(s));
        _size = 0;
    }

    void insert(int x, wchar_t ch){
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: insert out of range");
        for (size_type i = _size; i > x; --i)
            s[i] = s[i - 1];
        s[x] = ch;
        ++_size;
    }
    void erase(int x){
        if (x < 0 || x >= _size)
            throw std::out_of_range("WString: erase out of range");
        for (size_type i = x; i < _size - 1; ++i)
            s[i] = s[i + 1];
        --_size;
    }
    void push_back(wchar_t ch){
        s[_size++] = ch;
    }
    void pop_back(){
        if (_size == 0)
            throw std::runtime_error("WString: pop_back of empty container");
        --_size;
    }

    void append(wchar_t ch){
        s[_size++] = ch;
    }
    void append(const WString &ws){
        for (size_type i = 0; i < ws._size; ++i)
            s[_size++] = ws[i];
    }

    WString &operator +=(wchar_t ch){
        s[_size++] = ch;
        return *this;
    }
    WString &operator +=(const WString &ws){
        for (size_type i = 0; i < ws._size; ++i)
            s[_size++] = ws[i];
        return *this;
    }
};

WString operator +(const WString &ws1, const WString &ws2){
    WString ret(ws1);
    ret += ws2;
    return ret;
}
WString operator +(const WString &ws, wchar_t ch){
    WString ret(ws);
    ret.s[ret._size++] = ch;
    return ret;
}
std::istream &operator >>(std::istream &is, WString &ws){
    ws.clear();
    wchar_t ch;
    ch = getwchar();
    while (iswspace(ch))
        ch = getwchar();
    while (!iswspace(ch)){
        ws.s[ws._size++] = ch;
        ch = getwchar();
    }
    is.unget();
    return is;
}
std::ostream &operator <<(std::ostream &os, const WString &ws){
    for (WString::size_type i = 0; i < ws._size; ++i)
        os << ws.s[i];
    return os;
}

}


#endif
