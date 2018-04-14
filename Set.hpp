// 
// Created by FineArtz on 2018/04/10
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_SET_HPP
#define INC_2018DATASTRUCTUREBIGWORK_SET_HPP

// only for std::less<T>
#include <functional>
#include <cstddef>
#include "exceptions.hpp"
using namespace sjtu;

namespace myAlgorithm {

template<
	class Key,
	class Compare = std::less<Key>
>
class Set {
public:
    class iterator;
    class const_iterator;
    friend class iterator;
    friend class const_iterator;

public:
    using key_type          = Key;
    using value_type        = Key;
	using key_compare       = Compare;
	using size_type         = size_t;
    using difference_type   = std::ptrdiff_t;

protected:
    //basic structs of Red-black Tree
    enum Colour {RED, BLACK};
    Compare comp;

    struct _ListNode;
    struct _TreeNode{
        value_type key;
        Colour colour = RED;
        _TreeNode *p = nullptr, *l = nullptr, *r = nullptr;
        _ListNode *ln = nullptr;

        _TreeNode() = default;
        _TreeNode(value_type k, _TreeNode *pp = nullptr, _TreeNode *ll = nullptr, _TreeNode *rr = nullptr) :
            key(k), p(pp), l(ll), r(rr) {}
        _TreeNode(const _TreeNode &t) :
            key(t.key), p(t.p), l(t.l), r(t.r), ln(t.ln) {}
    };

    struct _ListNode{
        _ListNode *prev = nullptr, *succ = nullptr;
        _TreeNode *tn = nullptr;

        _ListNode(_ListNode *p = nullptr, _ListNode *s = nullptr, _TreeNode *t = nullptr) :
            prev(p), succ(s), tn(t) {}
        _ListNode(const _ListNode &t) :
            prev(t.prev), succ(t.succ), tn(t.tn) {}
    };

protected:
    //inner functions of Red-black Tree
    void _leftRotate(_TreeNode *p){
        if (p == nullptr)
            return;
        _TreeNode *r = p->r;
        p->r = r->l;
        if (r->l != nullptr)
            r->l->p = p;
        r->p = p->p;
        if (p->p == nullptr)
            root = r;
        else if (p->p->l == p)
            p->p->l = r;
        else
            p->p->r = r;
        r->l = p;
        p->p = r;
    }
    void _rightRotate(_TreeNode *p){
        if (p == nullptr)
            return;
        _TreeNode *l = p->l;
        p->l = l->r;
        if (l->r != nullptr)
            l->r->p = p;
        l->p = p->p;
        if (p->p == nullptr)
            root = l;
        else if (p->p->r == p)
            p->p->r = l;
        else
            p->p->l = l;
        l->r = p;
        p->p = l;
    }

    void _fixInsertion(_TreeNode *x){
        x->colour = RED;
        while (x != nullptr && x != root && x->p->colour == RED){
            if (x->p == x->p->p->l){
                _TreeNode *y = x->p->p->r;
                if (y != nullptr && y->colour == RED){
                    x->p->colour = BLACK;
                    y->colour = BLACK;
                    x->p->p->colour = RED;
                    x = x->p->p;
                }
                else{
                    if (x == x->p->r){
                        x = x->p;
                        _leftRotate(x);
                    }
                    x->p->colour = BLACK;
                    x->p->p->colour = RED;
                    _rightRotate(x->p->p);
                }
            }
            else{
                _TreeNode *y = x->p->p->l;
                if (y != nullptr && y->colour == RED){
                    x->p->colour = BLACK;
                    y->colour = BLACK;
                    x->p->p->colour = RED;
                    x = x->p->p;
                }
                else{
                    if (x == x->p->l){
                        x = x->p;
                        _rightRotate(x);
                    }
                    x->p->colour = BLACK;
                    x->p->p->colour = RED;
                    _leftRotate(x->p->p);
                }
            }
        }
        root->colour = BLACK;
    }
    void _fixDeletion(_TreeNode *x){
        while (x != root && x->colour == BLACK){
            //if (x->p == nullptr)
            //    return;
            if (x == x->p->l){
                _TreeNode *sib = x->p->r;
                if (sib != nullptr && sib->colour == RED){
                    sib->colour = BLACK;
                    x->p->colour = RED;
                    _leftRotate(x->p);
                    sib = x->p->r;
                }
                if ((sib == nullptr || sib->r == nullptr || sib->r->colour == BLACK)
                 && (sib == nullptr || sib->l == nullptr || sib->l->colour == BLACK)){
                    if (sib != nullptr)
                        sib->colour = RED;
                    x = x->p;
                }
                else{
                    if (sib->r == nullptr || sib->r->colour == BLACK){
                        sib->l->colour = BLACK;
                        sib->colour = RED;
                        _rightRotate(sib);
                        sib = x->p->r;
                    }
                    sib->colour = x->p->colour;
                    x->p->colour = BLACK;
                    sib->r->colour = BLACK;
                    _leftRotate(x->p);
                    x = root;
                }
            }
            else{
                _TreeNode *sib = x->p->l;
                if (sib != nullptr && sib->colour == RED){
                    sib->colour = BLACK;
                    x->p->colour = RED;
                    _rightRotate(x->p);
                    sib = x->p->l;
                }
                if ((sib == nullptr || sib->r == nullptr || sib->r->colour == BLACK)
                 && (sib == nullptr || sib->l == nullptr || sib->l->colour == BLACK)){
                    if (sib != nullptr)
                        sib->colour = RED;
                    x = x->p;
                }
                else{
                    if (sib->l == nullptr || sib->l->colour == BLACK){
                        sib->r->colour = BLACK;
                        sib->colour = RED;
                        _leftRotate(sib);
                        sib = x->p->l;
                    }
                    sib->colour = x->p->colour;
                    x->p->colour = BLACK;
                    sib->l->colour = BLACK;
                    _rightRotate(x->p);
                    x = root;
                }
            }
        }
        x->colour = BLACK;
    }

    void _copy(_TreeNode *x, _TreeNode *y, _TreeNode *p = nullptr, int c = 0){
        if (y == nullptr)
            return;
        x = new _TreeNode(y->key);
        x->colour = y->colour;
        x->p = p;
        if (p == nullptr)
            root = x;
        else {
            if (c)
                p->r = x;
            else
                p->l = x;
        }
        _copy(x->l, y->l, x, 0);
        _copy(x->r, y->r, x, 1);
    }

    _ListNode *_buildList(_TreeNode *x, _ListNode *p){
        if (x->l != nullptr){
            p = _buildList(x->l, p);
        }
        p->succ = new _ListNode();
        p->succ->prev = p;
        p = p->succ;
        p->tn = x;
        x->ln = p;
        if (x->r != nullptr)
            p = _buildList(x->r, p);
        return p;
    }

    _TreeNode *_succ(_TreeNode *t){
        if (t == nullptr)
            return nullptr;
        if (t->r != nullptr){
            _TreeNode *p = t->r;
            while (p->l != nullptr)
                p = p->l;
            return p;
        }
        else{
            _TreeNode *p = t->p, *ch = t;
            while (p != nullptr && ch == p->r){
                ch = p;
                p = p->p;
            }
            return p;
        }
    }
    _TreeNode *_prev(_TreeNode *t){
        if (t == nullptr)
            return nullptr;
        if (t->l != nullptr){
            _TreeNode *p = t->l;
            while (p->r != nullptr)
                p = p->r;
            return p;
        }
        else{
            _TreeNode *p = t->p, *ch = t;
            while (p != nullptr && ch == p->l){
                ch = p;
                p = p->p;
            }
            return p;
        }
    }

    _TreeNode *_search(const Key &x) const{
        _TreeNode *p = root;
        while (p != nullptr){
            if (comp(x, p->key))
                p = p->l;
            else if (comp(p->key, x))
                p = p->r;
            else
                return p;
        }
        return nullptr;
    }

    bool _insert(const value_type &x){
        _TreeNode *t = root;
        if (t == nullptr){
            root = new _TreeNode(x);
            root->colour = BLACK;
            _ListNode *p = new _ListNode();
            root->ln = p;
            p->tn = root;
            p->prev = head;
            head->succ = p;
            p->succ = tail;
            tail->prev = p;
            ++_size;
            return true;
        }
        _TreeNode *p;
        int cmp = 0;
        do{
            p = t;
            if (comp(x, t->key)){
                t = t->l;
                cmp = -1;
            }
            else if (comp(t->key, x)){
                t = t->r;
                cmp = 1;
            }
            else
                return false;
        } while (t != nullptr);
        _TreeNode *e = new _TreeNode(x, p);
        if (cmp == -1)
            p->l = e;
        else
            p->r = e;
        _TreeNode *pr = _prev(e);
        _ListNode *pp = new _ListNode(), *q;
        if (pr == nullptr)
            q = head;
        else
            q = pr->ln;
        pp->tn = e;
        e->ln = pp;
        pp->prev = q;
        pp->succ = q->succ;
        q->succ = pp;
        pp->succ->prev = pp;
        ++_size;
        _fixInsertion(e);
        return true;
    }

    void _remove(const Key &x){
        _TreeNode *p = _search(x);
        if (p == nullptr)
            return;
        _ListNode *tt = p->ln;
        if (p->l != nullptr && p->r != nullptr){
            _TreeNode *s = _succ(p);
            _TreeNode *pp = new _TreeNode(*s);
            pp->colour = p->colour;
            pp->ln->tn = pp;
            pp->p = p->p;
            if (p->p != nullptr) {
                if (p == p->p->l)
                    p->p->l = pp;
                else
                    p->p->r = pp;
            }
            else
                root = pp;
            pp->l = p->l;
            if (p->l != nullptr)
                p->l->p = pp;
            pp->r = p->r;
            if (p->r != nullptr)
                p->r->p = pp;
            delete p;
            p = s;
        }
        tt->prev->succ = tt->succ;
        tt->succ->prev = tt->prev;
        delete tt;
        tt = nullptr;
        _TreeNode *t = (p->l != nullptr ? p->l : p->r);
        if (t != nullptr){
            t->p = p->p;
            if (p->p == nullptr)
                root = t;
            else if (p == p->p->l)
                p->p->l = t;
            else
                p->p->r = t;
            p->l = p->r = p->p = nullptr;
            if (p->colour == BLACK)
                _fixDeletion(t);
        }
        else if (p->p == nullptr)
            root = nullptr;
        else{
            if (p->colour == BLACK)
                _fixDeletion(p);
            if (p->p != nullptr){
                if (p == p->p->l)
                    p->p->l = nullptr;
                else if (p == p->p->r)
                    p->p->r = nullptr;
                p->p = nullptr;
            }
        }
        delete p;
        p = nullptr;
        --_size;
    }

    void _dispoSetree(_TreeNode *x) {
        if (x == nullptr)
            return;
        if (x->l != nullptr)
            _dispoSetree(x->l);
        if (x->r != nullptr)
            _dispoSetree(x->r);
        delete x;
    }
    void _disposeList() {
        _ListNode *p = head, *q;
        while (p != tail) {
            q = p->succ;
            delete p;
            p = q;
        }
        delete tail;
        head = tail = nullptr;
    }

protected:
    //inner members of Set
    _TreeNode *root = nullptr;
    _ListNode *head = new _ListNode(), *tail = new _ListNode();
    size_type _size = 0;

public:
    //public members
	class iterator {
        friend class Set;
        friend class const_iterator;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = Key;
	private:
        _ListNode *_ptr;
		Set *_container;
	public:
		iterator(_ListNode *_p = nullptr, Set *_c = nullptr) :
		    _ptr(_p), _container(_c) {}
		iterator(const iterator &other) :
		    _ptr(other._ptr), _container(other._container) {}
        iterator(const const_iterator &other) :
		    _ptr(other._ptr), _container(other._container) {}

		iterator operator ++(int) {
            if (_ptr == _container->tail)
                throw invalid_iterator();
            _ListNode *_p = _ptr;
            _ptr = _ptr->succ;
            return iterator(_p, _container);
		}
		iterator &operator ++() {
            if (_ptr == _container->tail)
                throw invalid_iterator();
            _ptr = _ptr->succ;
            return *this;
		}
		iterator operator --(int) {
            if (_ptr == _container->head->succ)
                throw invalid_iterator();
            _ListNode *_p = _ptr;
            _ptr = _ptr->prev;
            return iterator(_p, _container);
		}
		iterator &operator --() {
            if (_ptr == _container->head->succ)
                throw invalid_iterator();
            _ptr = _ptr->prev;
            return *this;
		}
		value_type &operator *() const {
            return _ptr->tn->key;
		}

		bool operator ==(const iterator &rhs) const {
            return (_ptr == rhs._ptr);
		}
		bool operator ==(const const_iterator &rhs) const {
            return (_ptr == rhs._ptr);
		}
		bool operator !=(const iterator &rhs) const {
            return (_ptr != rhs._ptr);
		}
		bool operator!=(const const_iterator &rhs) const {
            return (_ptr != rhs._ptr);
		}

		value_type *operator ->() const noexcept {
            return &(_ptr->tn->key);
		}
	};
	//end of class iterator

	class const_iterator {
		friend class Set;
        friend class iterator;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = Key;
	private:
        _ListNode *_ptr;
		const Set *_container;
    public:
		const_iterator(_ListNode *_p = nullptr, const Set *_c = nullptr) :
		    _ptr(_p), _container(_c) {}
        const_iterator(_ListNode *_p, Set *_c) :
		    _ptr(_p), _container(const_cast<const Set *>(_c)) {}
		const_iterator(const iterator &other) :
		    _ptr(other._ptr), _container(other._container) {}
        const_iterator(const const_iterator &other) :
		    _ptr(other._ptr), _container(other._container) {}

		const_iterator operator ++(int) {
            if (_ptr == _container->tail)
                throw invalid_iterator();
            _ListNode *_p = _ptr;
            _ptr = _ptr->succ;
            return const_iterator(_p, _container);
		}
		const_iterator &operator ++() {
            if (_ptr == _container->tail)
                throw invalid_iterator();
            _ptr = _ptr->succ;
            return *this;
		}
		const_iterator operator --(int) {
            if (_ptr == _container->head->succ)
                throw invalid_iterator();
            _ListNode *_p = _ptr;
            _ptr = _ptr->prev;
            return const_iterator(_p, _container);
		}
		const_iterator &operator --() {
            if (_ptr == _container->head->succ)
                throw invalid_iterator();
            _ptr = _ptr->prev;
            return *this;
		}
		const value_type &operator *() const {
            return _ptr->tn->key;
		}

		bool operator ==(const iterator &rhs) const {
            return (_ptr == rhs._ptr);
		}
		bool operator ==(const const_iterator &rhs) const {
            return (_ptr == rhs._ptr);
		}
		bool operator !=(const iterator &rhs) const {
            return (_ptr != rhs._ptr);
		}
		bool operator!=(const const_iterator &rhs) const {
            return (_ptr != rhs._ptr);
		}

		const value_type *operator ->() const noexcept {
            return &(_ptr->tn->key);
		}
	};
	//end of class const_iterator

    //constructors and destructor
	Set() {
        head->succ = tail;
        tail->prev = tail;
	}
	Set(const Set &other) {
        if (other.root != nullptr) {
            _copy(root, other.root);
            _ListNode *p = head;
            p = _buildList(root, p);
            p->succ = tail;
            tail->prev = p;
            _size = other._size;
        }
        else {
            head->succ = tail;
            tail->prev = head;
        }
	}

	Set &operator =(const Set &other) {
        if (this == &other)
            return *this;
        _dispoSetree(root);
        root = nullptr;
        _disposeList();
        if (other.root != nullptr) {
            _copy(root, other.root);
            head = new _ListNode();
            _ListNode *p = head;
            p = _buildList(root, p);
            tail = new _ListNode();
            p->succ = tail;
            tail->prev = p;
        }
        else {
            head = new _ListNode();
            tail = new _ListNode();
            head->succ = tail;
            tail->prev = head;
        }
        _size = other._size;
        return *this;
	}

	~Set() {
        _dispoSetree(root);
        root = nullptr;
        _disposeList();
    }

	iterator begin() {
        return iterator(head->succ, this);
	}
	const_iterator cbegin() const {
        return const_iterator(head->succ, this);
	}
	iterator end() {
        return iterator(tail, this);
	}
	const_iterator cend() const {
        return const_iterator(tail, this);
	}

	bool empty() const {
        return root == nullptr;
	}

	size_type size() const {
        return _size;
	}

	void clear() {
        _dispoSetree(root);
        root = nullptr;
        _size = 0;
        _disposeList();
        head = new _ListNode();
        tail = new _ListNode();
        head->succ = tail;
        tail->prev = head;
	}

	std::pair<iterator, bool> insert(const value_type &value) {
        bool b = _insert(value);
        _TreeNode *p = _search(value.first);
        return std::make_pair(iterator(p->ln, this), b);
	}

	void erase(iterator pos) {
        if (pos._container != this || pos._ptr == tail)
            throw invalid_iterator();
        _remove(pos->first);
	}

	size_type count(const Key &key) const {
        return (_search(key) == nullptr ? 0 : 1);
	}

	iterator find(const Key &key) {
        _TreeNode *p = _search(key);
        if (p == nullptr)
            return iterator(tail, this);
        return iterator(p->ln, this);
	}
	const_iterator find(const Key &key) const {
        _TreeNode *p = _search(key);
        if (p == nullptr)
            return const_iterator(tail, this);
        return const_iterator(p->ln, this);
	}
};

}

#endif
