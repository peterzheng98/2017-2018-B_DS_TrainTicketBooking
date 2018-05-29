//
// Created by Peter Zheng on 2018/05/28.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_VECTOR_H
#define INC_2018DATASTRUCTUREBIGWORK_VECTOR_H

#include <iostream>

namespace myAlgorithm {
    template<class T>
    class Vector {
    private:
        T *_data;
        int _len;
        int _arraylen;

        void ExtendSpace() {
            _arraylen = int(_arraylen * 1.5);
            T *tmp = (T *) ::operator new[](sizeof(T) * _arraylen);
            for (int i = 0; i < _len; ++i) {
                new(tmp + i) T(_data[i]);
            }
            for (int j = 0; j < _arraylen; ++j) {
                _data[j].~T();
            }
            ::operator delete[](_data);
            _data = tmp;
        }

        void CreateSpace() {
            _data = (T *) ::operator new[](sizeof(T) * 10);
            _arraylen = 10;
        }

    public:
        ~Vector() {
            for (int i = 0; i < _arraylen; i++) _data[i].~T();
            ::operator delete[](_data);
            _data = nullptr;
            _len = 0;
            _arraylen = 0;
        }

        Vector(const Vector &v) {
//            T* tmp = _data;
            _data = (T *) ::operator new[](sizeof(T) * v._arraylen);
            _len = v._len;
            _arraylen = v._arraylen;
            for (int i = 0; i < _len; i++) new(_data + i) T(v[i]);
            //delete[] tmp;
        }

        Vector &operator=(const Vector &v) {
            if (&v != this) {
                delete[] this->_data;
                _data = (T *) ::operator new[](sizeof(T) * v._arraylen);
                _len = v._len;
                _arraylen = v.arraylen;
                for (int i = 0; i < _len; i++) new(_data + i) T(v[i]);
            }
            return *this;
        }

        explicit Vector() {
            _data = (T *) ::operator new[](sizeof(T) * 10);
            _arraylen = 10;
            _len = 0;
        }

        void push_back(T item) {
            if (_arraylen <= 0) CreateSpace();
            if (_len == _arraylen) ExtendSpace();
            new(_data + _len) T(item);
            _len++;
        }

        void pop_back() {
            if (_len <= 0) throw "Empty";
            _len--;
        }

        bool empty() const {return _len == 0; }

        void clear(){
            for(int i = 0; i < _len; i++) _data[i].~T();
            ::operator delete[](_data);
            _data = (T *) ::operator new[](sizeof(T) * 10);
            _arraylen = 10;
            _len = 0;
        }

        int size() const {
            return _len;
        }

        T &operator[](int index) {
            if (index >= _len || index < 0) throw "out of range";
            return _data[index];
        }

        const T &operator[](int index) const {
            if (index >= _len || index < 0) throw "out of range";
            return _data[index];
        }

        T at(int index) {
            if (index >= _len || index < 0) throw "out of range";
            return _data[index];
        }

        const T at(int index) const {
            if (index >= _len || index < 0) throw "out of range";
            return _data[index];
        }

        T back() {
            if (_len <= 0) throw std::invalid_argument("Empty");
            return _data[_len - 1];
        }

        const T back() const {
            if (_len <= 0) throw std::invalid_argument("Empty");
            return _data[_len - 1];
        }

        const T front() const {
            if (_len <= 0) throw std::invalid_argument("empty");
            return _data[0];
        }

    public:
        class iterator {
        public:
            using value_type        = T;
            using pointer           = T *;
            using reference         = T &;
            using size_type         = size_t;
            using difference_type   = std::ptrdiff_t;

            iterator(Vector <T> *v, int index) {
                _v = v;
                _index = index;
            }

            iterator() = default;

            iterator(const iterator &) = default;

            iterator &operator=(const iterator &) = default;

        private:
            Vector <T> *_v;
            int _index;
        public:
            Vector <T> *getVect() {
                return _v;
            }

            int vetSize() {
                return (*_v).size();
            }

            iterator operator+(difference_type offset) {
                return iterator(_v, _index + offset);
            }

            iterator &operator+=(difference_type offset) {
                iterator ite(_v, _index + offset);
                *this = ite;
                return *this;
            }

            iterator operator-(difference_type offset) {
                return iterator(_v, _index - offset);
            }

            iterator &operator-=(difference_type offset) {
                iterator ite(_v, _index - offset);
                *this = ite;
                return *this;
            }

            iterator &operator++() {
                *this += 1;
                return *this;
            }

            iterator operator++(int) {
                iterator cur(_v, _index);
                *this += 1;
                return cur;
            }

            iterator &operator--() {
                *this -= 1;
                return *this;
            }

            iterator operator--(int) {
                iterator cur(_v, _index);
                *this -= 1;
                return cur;
            }

            bool operator==(const iterator &v) const {
                return v._v == _v && v._index == _index;
            }

            bool operator!=(const iterator &v) const {
                return !(v._v == _v && v._index == _index);
            }

            reference operator*() const {
                return _v->_data[_index];
            }

            pointer operator->() const {
                return &(_v->_data[_index]);
            }
        };

        iterator begin() {
            return iterator(this, 0);
        }

        iterator end() {
            return iterator(this, _len);
        }

        class const_iterator {
        public:
            using value_type        = const T;
            using pointer           = T *;
            using reference         = const T &;
            using size_type         = size_t;
            using difference_type   = std::ptrdiff_t;

            const_iterator(const Vector <T> *v, int index) : _v((Vector < T > *)

            v) {
                _index = index;
            }

            const_iterator() = default;

            const_iterator(const const_iterator &) = default;

            const_iterator &operator=(const const_iterator &) = default;

        private:
            Vector <T> *_v;
            int _index;
        public:
            const_iterator operator+(difference_type offset) {
                return const_iterator(_v, _index + offset);
            }

            const_iterator &operator+=(difference_type offset) {
                const_iterator ite(_v, _index + offset);
                *this = ite;
                return *this;
            }

            const_iterator operator-(difference_type offset) {
                return const_iterator(_v, _index - offset);
            }

            const_iterator &operator-=(difference_type offset) {
                const_iterator ite(_v, _index - offset);
                *this = ite;
                return *this;
            }

            const_iterator &operator++() {
                *this += 1;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator cur(_v, _index);
                *this += 1;
                return cur;
            }

            const_iterator &operator--() {
                *this -= 1;
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator cur(_v, _index);
                *this -= 1;
                return cur;
            }

            bool operator==(const const_iterator &v) const {
                return v._v == _v && v._index == _index;
            }

            bool operator!=(const const_iterator &v) const {
                return !(v._v == _v && v._index == _index);
            }

            reference operator*() const {
                return _v->_data[_index];
            }

            pointer operator->() const {
                return &(_v->_data[_index]);
            }
        };

        const_iterator cbegin() const noexcept {
            return const_iterator(this, 0);
        }

        const_iterator cend() const noexcept {
            return const_iterator(this, _len);
        }

        void insert(iterator ite, T index) {
            T *tmp = new T[ite.vetSize() + 2];
            int i = 0;
            for (iterator it = ite.getVect()->begin(); it != ite; it++) {
                tmp[i] = *it;
                i++;
            }
            tmp[i] = index;
            i++;
            for (iterator it = ite; it != ite.getVect()->end(); it++) {
                tmp[i] = *it;
                i++;
            }
            for (int i = 0; i < _len; i++) _data[i].~T();
            ::operator delete[](_data);
            _data = tmp;
            _len = ite.vetSize() + 1;
            _arraylen = ite.vetSize() + 2;
        }

        void erase(iterator ite) {
            T *tmp = new T[ite.vetSize()];
            int i = 0;
            for (iterator it = ite.getVect()->begin(); it != ite; it++) {
                tmp[i] = *it;
                i++;
            }
            for (iterator it = ite + 1; it != ite.getVect()->end(); it++) {
                tmp[i] = *it;
                i++;
            }
            for (int i = 0; i < _len; i++) _data[i].~T();
            ::operator delete[](_data);
            _data = tmp;
            _len = ite.vetSize() - 1;
            _arraylen = ite.vetSize();
        }
    };

}

#endif //INC_2018DATASTRUCTUREBIGWORK_VECTOR_H
