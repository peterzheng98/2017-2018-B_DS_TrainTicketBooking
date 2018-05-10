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

    struct Index{
        Key key;
        off_t child;
    };

    struct Record{
        Key key;
        Val value;
    };

    struct LeafNode{
        off_t parent = 0;
        off_t prev = 0, succ = 0;
        size_t size = 0;
        Record record[L];
    };

    struct TreeNode{
        off_t parent = 0;
        off_t prev = 0, succ = 0;
        size_t size = 0;
        Index index[M];
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
    Index *begin(TreeNode &tn){
        return tn.index;
    }
    Record *begin(LeafNode &ln){
        return ln.record;
    }
    Index *end(TreeNode &tn){
        return tn.index + tn.size;
    }
    Record *end(LeafNode &ln){
        return ln.record + ln.size;
    }

    void copyIndex(Index *first, Index *last, Index *des){
        while (first != last){
            *des = *first;
            ++first;
            ++des;
        }
    }
    void copyRecord(Record *first, Record *last, Record *des){
        while (first != last){
            *des = *first;
            ++first;
            ++des;
        }
    }
    void copyBackIndex(Index *first, Index *last, Index *des){
        while (last != first){
            *(des - 1) = *(last - 1);
            --last;
            --des;
        }
    }
    void copyBackRecord(Record *first, Record *last, Record *des){
        while (last != first){
            *(des - 1) = *(last - 1);
            --last;
            --des;
        }
    }

    Index *binarySearchKey(TreeNode &tn, const Key &key){
        size_t l = 0, r = tn.size - 1, mid;
        while (l < r){
            mid = (l + r) / 2;
            if (comp(tn.index[mid].key, key))
                l = mid + 1;
            else
                r = mid;
        }
        return tn.index + l;
    }

    Record *binarySearchRecord(LeafNode &ln, const Key &key){
        size_t l = 0, r = ln.size - 1, mid;
        while (l < r){
            mid = (l + r) / 2;
            if (comp(ln.record[mid].key, key))
                l = mid + 1;
            else
                r = mid;
        }
        return ln.record + l;
    }

    void updateParentIndex(Index *first, Index *last, off_t newParent){
        TreeNode tn;
        while (first != last){
            read(tn, first->child);
            tn.parent = newParent;
            write(tn, first->child);
            ++first;
        }
    }

    void updateChildIndex(off_t parent, const Key &oldKey, const Key &newKey){
        TreeNode tn;
        read(&tn, parent);
        Index *id = binarySearchKey(&tn, oldKey);
        if (id == end(tn))
            return;
        id->key = newKey;
        write(&tn, parent);
        if (id == end(tn) - 1)
            updateChildIndex(tn.parent, oldKey, newKey);
    }

    bool getKeyFromRight(TreeNode &t, off_t offset){
        off_t pos = t.succ;
        TreeNode rn;
        read(&rn, pos);
        Index *readPos = begin(rn), *writePos = end(t);
        if (rn.size <= M * 3 / 2)
            return false;

        TreeNode parent;
        read(&parent, t.parent);
        Index *keyInParent = binarySearchKey(parent, t.index[t.size - 1].key);
        keyInParent->key = readPos->key;
        write(&parent, t.parent);

        *writePos = *readPos;
        ++t.size;

        updateParentIndex(readPos, readPos + 1, offset);
        copyIndex(readPos + 1, end(rn), readPos);
        --rn.size;
        write(rn, pos);
        return true;
    }

    bool getKeyFromLeft(TreeNode &t, off_t offset){
        off_t pos = t.prev;
        TreeNode rn;
        read(&rn, pos);
        Index *readPos = end(rn) - 1, *writePos = begin(t);
        if (rn.size <= M * 3 / 2)
            return false;

        TreeNode parent;
        read(&parent, t.parent);
        Index *keyInParent = binarySearchKey(parent, rn.index[0].key);
        writePos->key = keyInParent->key;
        keyInParent->key = (readPos - 1)->key;
        write(&parent, t.parent);

        copyBackIndex(writePos, end(t), end(t) + 1);
        *writePos = *readPos;
        ++t.size;

        updateParentIndex(readPos, readPos + 1, offset);
        copyIndex(readPos + 1, end(rn), readPos);
        --rn.size;
        write(rn, pos);
        return true;
    }

    bool getRecordFromRight(LeafNode &t){
        off_t pos = t.succ;
        LeafNode rn;
        read(&rn, pos);
        Record *readPos = begin(rn), *writePos = end(t);
        if (rn.size <= L * 2 / 3)
            return false;

        updateChildIndex(t.parent, t.Record[0].Key, rn.Record[1].Key);
        *writePos = *readPos;
        ++t.size;

        copyRecord(readPos + 1, end(rn), readPos);
        --rn.size;
        write(&rn, pos);
        return true;
    }

    bool getRecordFromLeft(LeafNode &t){
        off_t pos = t.prev;
        LeafNode rn;
        read(&rn, pos);
        Record *readPos = end(rn) - 1, *writePos = begin(t);
        if (rn.size <= L * 2 / 3)
            return false;

        updateChildIndex(rn.parent, rn.Record[0].Key, readPos->key);
        copyBackRecord(writePos, end(t), end(t + 1));
        *writePos = *readPos;
        ++t.size;

        copyRecord(readPos + 1, end(rn), readPos);
        --rn.size;
        write(&rn, pos);
        return true;
    }
};

}

#endif //INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
