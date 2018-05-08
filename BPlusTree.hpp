//
// Created by FineArtz on 2018/05/08
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
#define INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H

#include <iostream>
#include <fstream>
#include <functional>
#include <cstring>
#include "Exception.hpp"

namespace myAlgorithm{

template <  
    class Key, 
    class Compare = std::less<Key> 
>
class BPlusTree{
public:
    using key_type          = Key;
    using value_type        = Key;
	using key_compare       = Compare;
	using size_type         = size_t;
    using difference_type   = std::ptrdiff_t;

protected:
    struct _ListNode{
        _ListNode *prev = nullptr, *succ = nullptr;

        _ListNode(_ListNode *p = nullptr, _ListNode *s = nullptr)
            : prev(p), subb(s);
    };

    struct _TreeNode{
        
    };

private:

};

}

template <class T, 
#endif //INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
