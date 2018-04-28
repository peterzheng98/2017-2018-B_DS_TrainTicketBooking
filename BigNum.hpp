//
// Created by Peter Zheng on 2018/04/15.
// Modified by Peter Zheng on 2018/4/28. (Upd Ver.1 : Add operator==,!=,<,>,<=,>=)
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_BIGNUM_H
#define INC_2018DATASTRUCTUREBIGWORK_BIGNUM_H

#ifndef INC_IOSTREAM
#define INC_IOSTREAM

#include <iostream>

#endif

namespace myAlgorithm {
    template<class T = int>
    class BigNum {
    private:
        T data[30010];
        int len;
    public:
        BigNum() = default;

        BigNum(const BigNum &rhs) {
            len = rhs.len;
            for (int i = 0; i < len; i++) data[i] = rhs.data[i];
        }

        BigNum(T rdata[], int rlen) {
            len = rlen;
            for (int i = 0; i < rlen; i++) data[i] = rdata[i];
        }

        explicit BigNum(int i) {
            len = 0;
            while (i != 0) {
                data[len++] = i % 10;
                i = i / 10;
            }
        }

        explicit BigNum(T i) {
            len = 0;
            while (i != 0) {
                data[len++] = i % 10;
                i = i / 10;
            }
        }

        BigNum &operator=(const BigNum &rhs) {
            if (this == &rhs) return *this;
            len = rhs.len;
            for (int i = 0; i < len; i++) data[i] = rhs[i];
        }

        int length() const {
            return len;
        }

        T operator[](int index) const {
            if (index < 0 || index >= len) throw std::invalid_argument("fuck");
            return data[index];
        }

        BigNum operator+(const BigNum &rhs) {
            T rdata[30010];
            int rlen = 0;
            rlen = len > rhs.length() ? len : rhs.length();
            for (int i = 1; i <= rlen; i++) {
                rdata[i] = rdata[i] + data[i] + rhs[i];
                rdata[i + 1] = rdata[i + 1] + rdata[i] / 10;
                rdata[i] = rdata[i] % 10;
            }
            rlen++;
            while ((rdata[rlen] == 0) && (rlen > 1)) rlen--;
            return BigNum(rdata, rlen);
        }

        BigNum &operator+=(const BigNum &rhs) {
            *this = operator+(rhs);
            return *this;
        }

        BigNum operator-(const BigNum &rhs) {
            T rdata[30010];
            int rlen = 0;
            rlen = len;
            for (int i = 1; i <= rlen; i++) {
                rdata[i] = data[i] + 10 - rhs[i];
                data[i + 1] = data[i + 1] - 1 + rdata[i] / 10;
                rdata[i] = rdata[i] % 10;
            }
            rlen++;
            while (rdata[rlen] == 0 && rlen > 0) rlen--;
            return BigNum(rdata, rlen);
        }

        BigNum &operator-=(const BigNum &rhs) {
            *this = operator-(rhs);
            return *this;
        }

        BigNum operator*(const BigNum &rhs) {
            T rdata[30010];
            int rlen = 0;
            int j;
            for (int i = 1; i <= len; i++) {
                for (j = 1, rlen = i - 1; j <= rhs.length(); j++)
                    rdata[++rlen] += rhs[j] * data[i];
                for (int i = 1; i <= rlen; i++)
                    if (rdata[i] >= 10) {
                        if (rdata[rlen] >= 10) rlen++;
                        rdata[i + 1] += rdata[i] / 10;
                        rdata[i] %= 10;
                    }
            }
            return BigNum(rdata, rlen);
        }

        BigNum M_multiplyFastFourierTransform(const BigNum &rhs){
            //ToDo: FFT
        }

        BigNum &operator*=(const BigNum &rhs) {
            *this = operator*(rhs);
            return *this;
        }

        BigNum &operator++() {
            *this += BigNum(1);
            return *this;
        }

        BigNum operator++(int) {
            auto tmp = *this;
            *this += BigNum(1);
            return tmp;
        }

        BigNum &operator--() {
            *this -= BigNum(1);
            return *this;
        }

        BigNum operator--(int) {
            auto tmp = *this;
            *this -= BigNum(1);
            return tmp;
        }

        operator int() {
            int ans = 0;
            for (int i = len - 1; i >= 0; i--) ans = ans * 10 + data[i];
            return ans;
        }

        operator double() {
            double ans = 0;
            for (int i = len - 1; i >= 0; i--) ans = ans * 10 + data[i];
            return ans;
        }

        operator long long() {
            long long ans = 0;
            for (int i = len - 1; i >= 0; i--) ans = ans * 10 + data[i];
            return ans;
        }

        operator short() {
            short ans = 0;
            for (int i = len - 1; i >= 0; i--) ans = ans * 10 + data[i];
            return ans;
        }

        friend std::ostream &operator<<(std::ostream &os, const BigNum &bg) {
            for (int i = bg.length() - 1; i >= 0; i--) os << bg[i];
            return os;
        }

        bool operator==(const BigNum& rhs){
            if(len != rhs.length()) return false;
            for(int i = 0; i < len;i++) if(data[i] != rhs[i]) return false;
            return true;
        }

        bool operator!=(const BigNum& rhs){
            return !operator==(rhs);
        }

        bool operator<(const BigNum& rhs){
            if(rhs.length() > len) return true;
            if(len > rhs.length()) return false;
            for(int i = len - 1; i >= 0;i--){
                if(data[i] < rhs[i]) return true;
                if(data[i] > rhs[i]) return false;
            }
            return false;
        }
        bool operator>(const BigNum& rhs){
            if(operator==(rhs)) return false;
            return !(operator<(rhs));
        }

        bool operator>=(const BigNum& rhs){
            if(operator==(rhs)) return true;
            return operator>(rhs);
        }

        bool operator<=(const BigNum& rhs){
            if(operator==(rhs)) return true;
            return operator<(rhs);
        }
    };
}


#endif