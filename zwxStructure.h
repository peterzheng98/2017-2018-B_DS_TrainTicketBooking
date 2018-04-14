//
// Created by Peter Zheng on 2018/03/20.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_ZWXSTRUCTURE_H
#define INC_2018DATASTRUCTUREBIGWORK_ZWXSTRUCTURE_H

#include <utility>
#include <functional>
#include <cmath>
#include <cstdlib>
enum instruction{
    NAME,
    PASSWORD,
    EMAIL,
    PHONE,
    ID,
    PRIVILEDGE,
    LOC,
    DATE,
    CATALOG,
    TICKED_KIND,
    TRAIN_ID,
    NUM,
    TIME,
    PRICE,
    DES
};



namespace zwxStructureBase {
    template<typename T>
    class vector {
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
        ~vector() {
            for (int i = 0; i < _arraylen; i++) _data[i].~T();
            ::operator delete[](_data);
            _data = nullptr;
            _len = 0;
            _arraylen = 0;
        }

        vector(const vector &v) {
            _data = (T *) ::operator new[](sizeof(T) * v._arraylen);
            _len = v._len;
            _arraylen = _len + 1;
            for (int i = 0; i < _len; i++) new(_data + i) T(v[i]);
        }

        vector(vector &&v) noexcept {
            if (&v != this) {
                this->_data = std::move(v._data);
                this->_arraylen = std::move(v._arraylen);
                this->_len = std::move(v._len);
            }
        }

        vector &operator=(const vector &v) {
            if (&v != this) {
                for (int i = 0; i < _arraylen; i++) _data[i].~T();
                ::operator delete[](_data);
                this->_data = (T *) ::operator new[](sizeof(T) * v._arraylen);
                this->_len = v._len;
                this->_arraylen = _len + 1;
                for (int i = 0; i < _len; i++) new(this->_data + i) T(v[i]);
//                this->_data = v._data;
                this->_len = v._len;
                this->_arraylen = v._arraylen;
            }
            return *this;
        }

        vector &operator=(vector &&v) noexcept {
            if (&v != this) {
                delete[] this->_data;
                this->_data = std::move(v._data);
                this->_len = std::move(v._len);
                this->_arraylen = std::move(v._arraylen);
            }
            return *this;
        }

        explicit vector() {
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

            iterator(vector<T> *v, int index) {
                _v = v;
                _index = index;
            }

            iterator() = default;

            iterator(const iterator &) = default;

            iterator &operator=(const iterator &) = default;

        private:
            vector<T> *_v;
            int _index;
        public:
            vector<T> *getVect() {
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

            const_iterator(const vector<T> *v, int index) : _v((vector<T> *) v) {
                _index = index;
            }

            const_iterator() = default;

            const_iterator(const const_iterator &) = default;

            const_iterator &operator=(const const_iterator &) = default;

        private:
            vector<T> *_v;
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

    template<typename T, class Compare = std::less<T>>
    class priority_queue {
    private:
        Compare cmp = Compare();

        struct Node {
            T *key = (T *) ::operator new[](sizeof(T));
            int dist;
            Node *left;
            Node *right;

            Node() {}

            Node(T *lkey, int ldist, Node *ll, Node *lright) {
                new(key) T(lkey[0]);
                dist = ldist;
                left = ll;
                right = lright;

            }

            Node(T lkey, int ldist, Node *ll, Node *lright) {
                new(key) T(lkey);
                dist = ldist;
                left = ll;
                right = lright;

            }

            Node(T lkey) {
                key = lkey;
                left = nullptr;
                right = nullptr;
                dist = 0;
            }
        };

        Node *mRoot;


        template<typename U>
        inline void swap(U &a, U &b) {
            U tmp = a;
            a = b;
            b = tmp;
        }

        Node *MergeIn(Node *a, Node *b) {
            if (a == nullptr) return b;
            if (b == nullptr) return a;
            if (cmp(*(a->key), *(b->key))) swap<Node *>(a, b);
            a->right = MergeIn(b, a->right);
            if ((a->left != nullptr ? a->left->dist : -1) < (a->right != nullptr ? a->right->dist : -1))
                swap<Node *>(a->left, a->right);
            if (a->right == nullptr) a->dist = 0;
            else a->dist = a->right->dist + 1;
            return a;
        }

        void deleteup(Node *p) {
            if (p == nullptr) return;
            if (p->left != nullptr) deleteup(p->left);
            if (p->right != nullptr) deleteup(p->right);
            //TODO : Special Destructor
            p->key->~T();
            ::operator delete[](p->key);
            delete p;
            p = nullptr;
        }

    public:
        int len;

        /**
         * TODO constructors
         */
        priority_queue() {
            mRoot = nullptr;
            len = 0;
        }

        void DeepCopy(Node *Current, Node *&Copied) {
            if (Current == nullptr) return;
            if (Current->left != nullptr) DeepCopy(Current->left, Copied);
            if (Current->right != nullptr) DeepCopy(Current->right, Copied);
            Node *tmp2 = new Node(Current->key, 0, nullptr, nullptr);
            Copied = MergeIn(Copied, tmp2);
            return;
        }

        priority_queue(const priority_queue &other) {
            mRoot = nullptr;
            DeepCopy(other.mRoot, mRoot);
            len = other.len;
        }

        /**
         * TODO deconstructor
         */
        ~priority_queue() {
            if (len != 0)deleteup(mRoot);
        }

        /**
         * TODO Assignment operator
         */
        priority_queue &operator=(const priority_queue &other) {
            if (other.mRoot != this->mRoot) {
                deleteup(mRoot);
                mRoot = nullptr;
                DeepCopy(other.mRoot, mRoot);
                len = other.len;
            }
            return *this;
        }

        /**
         * get the top of the queue.
         * @return a reference of the top element.
         * throw container_is_empty if empty() returns true;
         */
        const T &top() const {
            if (len == 0) throw container_is_empty();
            return mRoot->key[0];
        }

        /**
         * TODO
         * push new element to the priority queue.
         */
        void push(const T &e) {
            Node *p = new Node(e, 0, nullptr, nullptr);
            mRoot = MergeIn(p, mRoot);
            len++;
        }

        /**
         * TODO
         * delete the top element.
         * throw container_is_empty if empty() returns true;
         */
        void pop() {
            if (len == 0) throw container_is_empty();
            Node *tmp = mRoot;
            mRoot = MergeIn(mRoot->left, mRoot->right);
            tmp->key->~T();
            ::operator delete[](tmp->key);
            delete tmp;
            tmp = nullptr;
            len--;
        }

        /**
         * return the number of the elements.
         */
        size_t size() const {
            return len;
        }

        /**
         * check if the container has at least an element.
         * @return true if it is empty, false if it has at least an element.
         */
        bool empty() const {
            return len == 0;
        }

        /**
         * return a merged priority_queue with at least O(logn) complexity.
         */
        void merge(priority_queue &other) {
            mRoot = MergeIn(mRoot, other.mRoot);
            len += other.len;
            other.len = 0;
            other.mRoot = nullptr;

        }
    };

    class string {
    private:
        vector<char> data;
    public:
        string() = default;

        string(const string &rhs) {
            data = rhs.data;
        }

        string(string &&rhs) noexcept {
            data = std::move(rhs.data);
        }

        string &operator=(const string &rhs) {
            if(&rhs != this) data = rhs.data;
            return *this;
        }

        string &operator=(string&& rhs) noexcept {
            if(&rhs != this) data = std::move(rhs.data);
            return *this;
        }

        int length() const{
            return data.size();
        }

        char& operator[](const int& ptr){
            return data[ptr];
        }

        const char& operator[](const int& ptr) const{
            return data[ptr];
        }



    };

    template<typename T>
    class BPlusTree{
        
    };
}


namespace zwxUtility {
    class SQLLocation {
    private:

    };
}


namespace zwxException {
    class zwxExceptionBase {
    public:
        virtual char *what() const = 0;

        virtual int code() const = 0;

        virtual void setCode(const char *&errorMessage, const int &code) = 0;

        virtual ~zwxExceptionBase() {}
    };

    class SQLException : public zwxExceptionBase {
    private:


    };

    class RuntimeError : public zwxExceptionBase{
    private:

    };

    class SystemError : public RuntimeError{
    public:
        void DeleteAll(){
        }
    };
}

#endif //INC_2018DATASTRUCTUREBIGWORK_ZWXSTRUCTURE_H
