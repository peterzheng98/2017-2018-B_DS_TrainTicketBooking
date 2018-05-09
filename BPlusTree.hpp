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

static const char WRITE_PATH[20] = "tmp\\records.dat";
static const int UNIT = 4096;

template <  
    class Key, 
    class Val,
    class Compare = std::less<Key> 
>
class BPlusTree{
public:
    using key_type          = Key;
    using value_type        = Val;
	using key_compare       = Compare;
	using size_type         = size_t;
    using difference_type   = std::ptrdiff_t;

private:
    static const size_t M = (4096 - 3 * sizeof(off_t) - sizeof(size_t)) / (sizeof(Key) + sizeof(off_t));
    static const size_t L = (4096 - 3 * sizeof(off_t) - sizeof(size_t)) / (sizeof(Key) + sizeof(Val));

    struct _LeafNode{
        off_t parent = 0;
        off_t prev = 0, succ = 0;
        size_t size = 0;
        Key index[L];
        Val record[L];
    };

    struct _TreeNode{
        off_t parent = 0;
        off_t prev = 0, succ = 0;
        size_t size = 0;
        Key index[M];
        off_t children[M];
    };

private:
    char path[1024];
    mutable FILE *fp = nullptr;
    mutable int fileLevel = 0;

    off_t root = 0, slot = 0;

    Compare comp;

private:
    void openFile(const char *mode = "rb+") const{
        if (fileLevel == 0)
            fp = fopen(path, mode);
        ++fileLevel;
    }
    
    void closeFile() const{
        if (fileLevel == 1)
            fclose(fp);
        --fileLevel;
    }

    off_t alloc(){
        off_t s = slot;
        slot += UNIT;
        return s;
    }

    template <class T>
    size_t read(T *val, off_t offset){
        openFile();
        fseek(fp, offset, SEEK_SET);
        char ch[UNIT];
        size_t s = fread(reinterpret_cast<void *>(ch), UNIT, 1, fp);
        val = reinterpret_cast<T *>(ch);
        closeFile();
        return s;
    }

    template <class T>
    size_t write(T *val, off_t offset){
        openFile();
        fseek(fp, offset, SEEK_SET);
        char ch[UNIT] = reinterpret_cast<char *>(val);
        size_t s = fwrite(reinterpret_cast<void *>(ch), UNIT, 1, fp);
        closeFile();
        return s;
    }

private:
    //bool moveKeyFromRight()
};

}

#endif //INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
