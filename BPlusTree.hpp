//
// Created by FineArtz on 2018/05/08
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
#define INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H

#include <cstdio>
#include <fstream>
#include <functional>
#include <cstring>
#include "Vector.h"

namespace myAlgorithm{

static const char WRITE_PATH[256] = "../../tmp/records.txt";
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
    struct Index{
        Key key;
        off_t child;
    };

    struct Record{
        Key key;
        Val value;
    };

    static const size_t M = 10;//(4096 - 3 * sizeof(off_t) - sizeof(size_t)) / (sizeof(Index));
    static const size_t L = 10;//(4096 - 3 * sizeof(off_t) - sizeof(size_t)) / (sizeof(Record));

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

    struct CoreData{
        off_t root = 0, slot = 0, pos = UNIT;
        size_t _size = 0;
        int height = 0;
    };

    CoreData core;

    Compare comp;

#ifndef _NO_DEBUG
private:
#else
public:
#endif
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

private:
    off_t alloc(){
        off_t s = core.slot;
        core.slot += UNIT;
        write(&core, core.pos);
        return s;
    }

    template <class T>
    size_t read(T *val, off_t offset){
#ifndef _NO_DEBUG
        openFile();
#endif
        fseek(fp, offset, SEEK_SET);
        char ch[UNIT];
        size_t s = fread(ch, UNIT, 1, fp);
        *val = *(reinterpret_cast<T *>(ch));
#ifndef _NO_DEBUG
        closeFile();
#endif
        return s;
    }

    template <class T>
    size_t write(T *val, off_t offset, char *mode = "rb+"){
#ifndef _NO_DEBUG
        openFile(mode);
#endif
        fseek(fp, offset, SEEK_SET);
        char *ch;
        ch = reinterpret_cast<char *>(val);
        size_t s = fwrite(ch, UNIT, 1, fp);
#ifndef _NO_DEBUG
        closeFile();
#endif
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
        if (tn.size == 0)
            return end(tn);
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
        if (ln.size == 0)
            return end(ln);
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

    void updateNodeParentPos(Index *first, Index *last, off_t newParent){
        TreeNode tn;
        while (first != last){
            read(&tn, first->child);
            tn.parent = newParent;
            write(&tn, first->child);
            ++first;
        }
    }

    void updateLeafParentPos(Index *first, Index *last, off_t newParent) {
        LeafNode ln;
        while (first != last) {
            read(&ln, first->child);
            ln.parent = newParent;
            write(&ln, first->child);
            ++first;
        }
    }

    void updateChildIndex(off_t parent, const Key &oldKey, const Key &newKey){
        if (parent == 0)
            return;
        TreeNode tn;
        read(&tn, parent);
        if (tn.size == 0) {
            tn.index[0].key = newKey;
            ++tn.size;
            write(&tn, parent);
            updateChildIndex(tn.parent, oldKey, newKey);
        }
        else {
            Index *id = binarySearchKey(tn, oldKey);
            if (id == end(tn))
                return;
            id->key = newKey;
            write(&tn, parent);
            if (id == end(tn) - 1)
                updateChildIndex(tn.parent, oldKey, newKey);
        }
    }

    void updateChildPos(off_t parent, const Key &oldKey, off_t newPos) {
        if (parent == 0)
            return;
        TreeNode tn;
        read(&tn, parent);
        if (tn.size == 0) {
            return;
        }
        else {
            Index *id = binarySearchKey(tn, oldKey);
            if (id == end(tn))
                return;
            id->child = newPos;
            write(&tn, parent);
        }
    }

    /*
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

        updateChildIndex(t.parent, t.record[0].key, rn.record[1].key);
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

        updateChildIndex(rn.parent, rn.record[0].key, readPos->key);
        copyBackRecord(writePos, end(t), end(t + 1));
        *writePos = *readPos;
        ++t.size;

        copyRecord(readPos + 1, end(rn), readPos);
        --rn.size;
        write(&rn, pos);
        return true;
    }*/

    void removeIndex(off_t offset, const Key &key, bool mode = false){
        TreeNode tn;
        read(&tn, offset);
        if (tn.size == 0)
            return;
        int l = 0, r = tn.size - 1, mid;
        while (l < r){
            mid = (l + r) >> 1;
            if (comp(tn.index[mid].key, key))
                l = mid + 1;
            else
                r = mid;
        }
        copyIndex(begin(tn) + l + 1, end(tn), begin(tn) + l);
        --tn.size;
        if (tn.size == 0) {
            if (tn.prev != 0) {
                TreeNode sib;
                read(&sib, tn.prev);
                removeTreeNode(&sib, &tn);
                if (sib.parent == core.root && sib.prev == 0 && sib.succ == 0) {
                    core.root = tn.prev;
                    sib.parent = 0;
                    --core.height;
                    write(&core, core.pos);
                }
                write(&sib, tn.prev);
            }
            else if (tn.succ != 0){
                TreeNode sib;
                read(&sib, tn.succ);
                sib.prev = 0;
                if (sib.parent == core.root && sib.prev == 0 && sib.succ == 0) {
                    core.root = tn.succ;
                    sib.parent = 0;
                    --core.height;
                    write(&core, core.pos);
                }
                write(&sib, tn.succ);
            }
            removeIndex(tn.parent, key);
        }
        else {
            if (tn.succ != 0) {
                TreeNode sib;
                read(&sib, tn.succ);
                if (sib.parent == tn.parent && tn.size + sib.size <= M) {
                    mergeKey(tn, sib, mode);
                    if (tn.parent == core.root && tn.prev == 0 && tn.succ == 0) {
                        core.root = offset;
                        tn.parent = 0;
                        --core.height;
                        write(&core, core.pos);
                    }
                    write(&tn, offset);
                }
                else
                    write(&tn, offset);
            }
            else
                write(&tn, offset);
        }
    }

    void createTreeNode(off_t offset, TreeNode *tn, TreeNode *nx){
        nx->parent = tn->parent;
        nx->succ = tn->succ;
        nx->prev = offset;
        tn->succ = alloc();
        if (nx->succ != 0){
            TreeNode on;
            read(&on, nx->succ);
            on.prev = tn->succ;
            write(&on, nx->succ);
        }
    }
    void createLeafNode(off_t offset, LeafNode *ln, LeafNode *nx){
        nx->parent = ln->parent;
        nx->succ = ln->succ;
        nx->prev = offset;
        ln->succ = alloc();
        if (nx->succ != 0){
            LeafNode on;
            read(&on, nx->succ);
            on.prev = ln->succ;
            write(&on, nx->succ);
        }
    }
    void removeTreeNode(TreeNode *pr, TreeNode *tn){
        pr->succ = tn->succ;
        if (pr->succ != 0){
            TreeNode on;
            read(&on, tn->succ);
            on.prev = tn->prev;
            write(&on, tn->succ);
        }
    }
    void removeLeafNode(LeafNode *pr, LeafNode *ln){
        pr->succ = ln->succ;
        if (pr->succ != 0){
            LeafNode on;
            read(&on, ln->succ);
            on.prev = ln->prev;
            write(&on, ln->succ);
        }
    }

    void mergeLeaf(LeafNode *des, LeafNode *from){
        copyRecord(begin(*from), end(*from), end(*des));
        Key oldKey = des->record[des->size - 1].key;
        Key key = from->record[from->size - 1].key;
        off_t offset = from->prev;
        des->size += from->size;
        updateChildPos(des->parent, key, offset);
        removeLeafNode(des, from);
        removeIndex(des->parent, oldKey, true);
    }
    void mergeKey(TreeNode &des, TreeNode &from, bool mode = false){
        copyIndex(begin(from), end(from), end(des));
        Key oldKey = des.index[des.size - 1].key;
        Key key = from.index[from.size - 1].key;
        off_t offset = from.prev;
        des.size += from.size;
        updateChildPos(des.parent, key, offset);
        if (!mode)
            updateNodeParentPos(begin(from), end(from), offset);
        else
            updateLeafParentPos(begin(from), end(from), offset);
        removeTreeNode(&des, &from);
        removeIndex(des.parent, oldKey);
    }

    off_t findKey(const Key &key, bool mode = false) {
        TreeNode tn;
        read(&tn, core.root);
        if (tn.size == 0)
            return tn.index[0].child;
        //if (core.height == 6)
        //    system("PAUSE");
        Index *id;
        for (int i = 1; i <= core.height - 2; ++i){
            id = binarySearchKey(tn, key);
            read(&tn, id->child);
        }
        id = binarySearchKey(tn, key);
        if (mode)
            return id->child;
        if (comp(id->key, key) || comp(key, id->key))
            return 0;
        else
            return id->child;
    }

    void insertNewIndex(off_t offset, const Key &key, off_t child, bool mode = false){
        TreeNode tn;
        read(&tn, offset);
        if (tn.size != M){
            int i;
            for (i = tn.size; i > 0; --i){
                if (!comp(key, tn.index[i - 1].key))
                    break;
                tn.index[i] = tn.index[i - 1];
            }
            tn.index[i].key = key;
            tn.index[i].child = child;
            if (i == tn.size){
                updateChildIndex(tn.parent, tn.index[i - 1].key, key);
            }
            ++tn.size;
            write(&tn, offset);
        }
        else if (tn.succ != 0){
            TreeNode sib;
            read(&sib, tn.succ);
            if (sib.size != M){
                copyBackIndex(begin(sib), end(sib), end(sib) + 1);
                copyIndex(end(tn) - 1, end(tn), begin(sib));
                if (!mode)
                    updateNodeParentPos(begin(sib), begin(sib) + 1, tn.succ);
                else
                    updateLeafParentPos(begin(sib), begin(sib) + 1, tn.succ);
                ++sib.size;
                --tn.size;
                write(&sib, tn.succ);
                int i;
                for (i = tn.size; i > 0; --i) {
                    if (!comp(key, tn.index[i - 1].key))
                        break;
                    tn.index[i] = tn.index[i - 1];
                }
                tn.index[i].key = key;
                tn.index[i].child = child;
                if (i == tn.size) {
                    updateChildIndex(tn.parent, tn.index[i - 1].key, key);
                }
                else {
                    updateChildIndex(tn.parent, sib.index[0].key, tn.index[tn.size].key);
                }
                ++tn.size;
                write(&tn, offset);
            }
            else{
                TreeNode newNode;
                createTreeNode(sib.prev, &tn, &newNode);
                int newPos = tn.succ;
                read(&sib, newNode.succ);
                Key old = tn.index[tn.size - 1].key;
                copyIndex(end(tn) - M / 3, end(tn), begin(newNode));
                tn.size -= M / 3;
                newNode.size += M / 3;
                copyIndex(begin(sib), begin(sib) + M / 3, end(newNode));
                sib.size -= M / 3;
                newNode.size += M / 3;
                copyIndex(begin(sib) + M / 3, begin(sib) + M, begin(sib));
                if (!mode)
                    updateNodeParentPos(begin(newNode), end(newNode), newPos);
                else
                    updateLeafParentPos(begin(newNode), end(newNode), newPos);
                updateChildIndex(tn.parent, old, tn.index[tn.size - 1].key);
                insertNewIndex(tn.parent, newNode.index[newNode.size - 1].key, sib.prev);
                TreeNode tmptn;
                read(&tmptn, offset);
                if (tmptn.parent > 0) {
                    tn.parent = tmptn.parent;
                    newNode.parent = tmptn.parent;
                    sib.parent = tmptn.parent;
                }
                write(&tn, offset);
                write(&newNode, newPos);
                write(&sib, newNode.succ);
                if (comp(key, tn.index[tn.size - 1].key))
                    insertNewIndex(newNode.prev, key, child);
                else
                    insertNewIndex(tn.succ, key, child);
            }
        }
        else{
            TreeNode newNode;
            createTreeNode(offset, &tn, &newNode);
            int newPos = tn.succ;
            Key old = tn.index[tn.size - 1].key;
            copyIndex(end(tn) - M / 2, end(tn), begin(newNode));
            tn.size -= M / 2;
            newNode.size = M / 2;
            if (!mode)
                updateNodeParentPos(begin(newNode), end(newNode), newPos);
            else
                updateLeafParentPos(begin(newNode), end(newNode), newPos);
            if (tn.parent != 0){
                updateChildIndex(tn.parent, old, tn.index[tn.size - 1].key);
                insertNewIndex(tn.parent, newNode.index[newNode.size - 1].key, tn.succ);
                TreeNode tmptn;
                read(&tmptn, offset);
                if (tmptn.parent > 0) {
                    tn.parent = tmptn.parent;
                    newNode.parent = tmptn.parent;
                }
                write(&tn, offset);
                write(&newNode, newPos);
                if (comp(key, tn.index[tn.size - 1].key))
                    insertNewIndex(newNode.prev, key, child);
                else
                    insertNewIndex(tn.succ, key, child);
            }
            else{
                TreeNode newRoot;
                int rootPos = alloc();
                newRoot.prev = newRoot.succ = newRoot.parent = 0;
                newRoot.size = 2;
                newRoot.index[0].key = tn.index[tn.size - 1].key;
                newRoot.index[0].child = newNode.prev;
                newRoot.index[1].key = newNode.index[newNode.size - 1].key;
                newRoot.index[1].child = newPos;
                write(&newRoot, rootPos);
                core.root = rootPos;
                ++core.height;
                write(&core, core.pos);
                tn.parent = newNode.parent = rootPos;
                write(&tn, offset);
                write(&newNode, newPos);
                if (comp(key, tn.index[tn.size - 1].key))
                    insertNewIndex(newNode.prev, key, child);
                else
                    insertNewIndex(tn.succ, key, child);
            }
        }
    }

#ifdef _NO_DEBUG
    private:
#else
    public:
#endif //_NO_DEBUG
    std::pair<Record, bool> nextRecord(Record rc){
        off_t pos = findKey(rc.key, true);
        LeafNode ln;
        read(&ln, pos);
        int l = 0, r = ln.size - 1, mid;
        while (l < r){
            mid = (l + r) >> 1;
            if (comp(ln.record[mid].key, rc.key))
                l = mid + 1;
            else
                r = mid;
        }
        if (comp(ln.record[l].key, rc.key) || comp(rc.key, ln.record[l].key))
            return std::make_pair(Record(), false);
        if (l != ln.size - 1)
            return std::make_pair(ln.record[l + 1], true);
        else{
            Key des = ln.record[ln.size - 1].key;
            off_t pos = ln.parent;
            bool flag = false;
            int layer = 1;
            TreeNode tn;
            read(&tn, pos);
            int l, r, mid;
            while (pos != core.root){
                l = 0;
                r = tn.size - 1;
                while (l < r){
                    mid = (l + r) >> 1;
                    if (comp(tn.index[mid].key, des))
                        l = mid + 1;
                    else
                        r = mid;
                }
                if (l != tn.size - 1){
                    flag = true;
                    break;
                }
                pos = tn.parent;
                read(&tn, pos);
                ++layer;
            }
            if (flag){
                if (layer == 1){
                    LeafNode chd;
                    read(&chd, tn.index[l + 1].child);
                    return std::make_pair(chd.record[0], true);
                }
                read(&tn, tn.index[l + 1].child);
                for (int i = 1; i < layer - 1; ++i){
                    read(&tn, tn.index[0].child);
                }
                LeafNode chd;
                read(&chd, tn.index[0].child);
                return std::make_pair(chd.record[0], true);
            }
            else{
                l = 0;
                r = tn.size - 1;
                while (l < r){
                    mid = (l + r) >> 1;
                    if (comp(tn.index[mid].key, des))
                        l = mid + 1;
                    else
                        r = mid;
                }
                if (l == tn.size - 1)
                    return std::make_pair(Record(), false);
                else{
                    if (layer == 1){
                        LeafNode chd;
                        read(&chd, tn.index[l + 1].child);
                        return std::make_pair(chd.record[0], true);
                    }
                    read(&tn, tn.index[l + 1].child);
                    for (int i = 1; i < layer - 1; ++i){
                        read(&tn, tn.index[0].child);
                    }
                    LeafNode chd;
                    read(&chd, tn.index[0].child);
                    return std::make_pair(chd.record[0], true);
                }
            }
        }
    }

public:
    BPlusTree(bool CLEAR = false, const char *PATH = WRITE_PATH) {
        strcpy(path, PATH);
        if (CLEAR) {
            openFile("w+");
            closeFile();
            openFile();
            TreeNode rt;
            alloc();
            alloc();
            core.root = alloc();
            LeafNode ln;
            ln.parent = core.root;
            rt.index[0].child = alloc();
            write(&rt, core.root);
            write(&ln, rt.index[0].child);
            core.height = 2;
            write(&core, core.pos);
        }
        else{
            openFile();
            read(&core, UNIT);
        }
    }

    std::pair<Val, bool> search(const Key &key){
        off_t pos = findKey(key, true);
        LeafNode ln;
        read(&ln, pos);
        Record *rc = binarySearchRecord(ln, key);
        if (rc != end(ln) && !comp(rc->key, key) && !comp(key, rc->key))
            return std::make_pair(rc->value, true);
        else
            return std::make_pair(Val(), false);
    }

    Vector<Val> searchFirst(const Key &key){
        Vector<Val> ans;
        off_t pos = findKey(key, true);
        LeafNode ln;
        read(&ln, pos);
        Record *rc = binarySearchRecord(ln, key);
        std::pair<Record, bool> rd;
        rd.second = true;
        if (rc != end(ln) && rc->key.first() == key.first()){
            ans.push_back(rc->value);
            rd.first = *rc;
            while (rd.second){
                rd = nextRecord(rd.first);
                if (!rd.second)
                    break;
                if (rd.first.key.first() == key.first())
                    ans.push_back(rd.first.value);
                else
                    break;
            }
        }
        return ans;
    }
    
    Vector<Val> searchFirstAndSecond(const Key &key){
        Vector<Val> ans;
        off_t pos = findKey(key, true);
        LeafNode ln;
        read(&ln, pos);
        Record *rc = binarySearchRecord(ln, key);
        std::pair<Record, bool> rd;
        rd.second = true;
        if (rc != end(ln) && rc->key.first() == key.first() && rc->key.second() == key.second()){
            ans.push_back(rc->value);
            rd.first = *rc;
            while (rd.second){
                rd = nextRecord(rd.first);
                if (!rd.second)
                    break;
                if (rd.first.key.first() == key.first() && rd.first.key.second() == key.second())
                    ans.push_back(rd.first.value);
                else
                    break;
            }
        }
        return ans;
    }

    void insert(const Key &key, const Val &value){
        off_t childPos = findKey(key, true);
        LeafNode ln;
        read(&ln, childPos);
        if (ln.size != L){
            int i;
            for (i = ln.size; i > 0; --i){
                if (!comp(key, ln.record[i - 1].key))
                    break;
                ln.record[i] = ln.record[i - 1];
            }
            ln.record[i].key = key;
            ln.record[i].value = value;
            if (i == ln.size){
                updateChildIndex(ln.parent, ln.record[i - 1].key, key);
            }
            ++ln.size;
            write(&ln, childPos);
            ++core._size;
            write(&core, core.pos);
        }
        else if (ln.succ != 0){
            LeafNode sib;
            read(&sib, ln.succ);
            if (sib.size != L){
                copyBackRecord(begin(sib), end(sib), end(sib) + 1);
                copyRecord(end(ln) - 1, end(ln), begin(sib));
                ++sib.size;
                --ln.size;
                write(&sib, ln.succ);
                int i = ln.size;
                for (i = ln.size; i > 0; --i) {
                    if (!comp(key, ln.record[i - 1].key))
                        break;
                    ln.record[i] = ln.record[i - 1];
                }
                ln.record[i].key = key;
                ln.record[i].value = value;
                if (i == ln.size) {
                    updateChildIndex(ln.parent, ln.record[i - 1].key, key);
                }
                else {
                    updateChildIndex(ln.parent, sib.record[0].key, ln.record[ln.size].key);
                }
                ++ln.size;
                write(&ln, childPos);
                ++core._size;
                write(&core, core.pos);
            }
            else{
                LeafNode newNode;
                createLeafNode(sib.prev, &ln, &newNode);
                int newPos = ln.succ;
                read(&sib, newNode.succ);
                Key old = ln.record[ln.size - 1].key;
                copyRecord(end(ln) - L / 3, end(ln), begin(newNode));
                ln.size -= L / 3;
                newNode.size += L / 3;
                copyRecord(begin(sib), begin(sib) + L / 3, end(newNode));
                sib.size -= L / 3;
                newNode.size += L / 3;
                copyRecord(begin(sib) + L / 3, begin(sib) + L, begin(sib));
                updateChildIndex(ln.parent, old, ln.record[ln.size - 1].key);
                insertNewIndex(ln.parent, newNode.record[newNode.size - 1].key, sib.prev, true);
                LeafNode tmpln;
                read(&tmpln, childPos);
                if (tmpln.parent > 0) {
                    ln.parent = tmpln.parent;
                    newNode.parent = tmpln.parent;
                    sib.parent = tmpln.parent;
                }
                write(&ln, childPos);
                write(&newNode, newPos);
                write(&sib, newNode.succ);
                insert(key, value);
            }
        }
        else{
            LeafNode newNode;
            createLeafNode(childPos, &ln, &newNode);
            int newPos = ln.succ;
            Key old = ln.record[ln.size - 1].key;
            copyRecord(end(ln) - L / 2, end(ln), begin(newNode));
            ln.size -= L / 2;
            newNode.size = L / 2;
            updateChildIndex(ln.parent, old, ln.record[ln.size - 1].key);
            insertNewIndex(ln.parent, newNode.record[newNode.size - 1].key, ln.succ, true);
            LeafNode tmpln;
            read(&tmpln, childPos);
            if (tmpln.parent > 0) {
                ln.parent = tmpln.parent;
                newNode.parent = tmpln.parent;
            }
            write(&ln, childPos);
            write(&newNode, newPos);
            insert(key, value);
        }
    }

    void erase(const Key &key){
        off_t pos = findKey(key, true);
        if (pos == 0)
            return;
        LeafNode ln;
        read(&ln, pos);
        int l = 0, r = ln.size - 1, mid;
        while (l < r){
            mid = (l + r) >> 1;
            if (comp(ln.record[mid].key, key))
                l = mid + 1;
            else
                r = mid;
        }
        if (l == ln.size - 1) {
            --ln.size;
            if (ln.size != 0) {
                updateChildIndex(ln.parent, ln.record[l].key, ln.record[l - 1].key);
            }
            else {
                if (ln.prev != 0) {
                    LeafNode sib;
                    read(&sib, ln.prev);
                    removeLeafNode(&sib, &ln);
                    write(&sib, ln.prev);
                }
                else if (ln.succ != 0) {
                    LeafNode sib;
                    read(&sib, ln.succ);
                    sib.prev = 0;
                    write(&sib, ln.succ);
                }
                removeIndex(ln.parent, ln.record[l].key, true);
            }
        }
        else {
            copyRecord(begin(ln) + l + 1, end(ln), begin(ln) + l);
            --ln.size;
            if (ln.succ != 0) {
                LeafNode sib;
                read(&sib, ln.succ);
                if (sib.parent == ln.parent && ln.size + sib.size <= L)
                    mergeLeaf(&ln, &sib);
            }
        }
        write(&ln, pos);
        --core._size;
        write(&core, core.pos);
    }

    void update(const Key &key, const Val &value){
        off_t pos = findKey(key);
        if (pos == 0)
            return;
        LeafNode ln;
        read(&ln, pos);
        int l = 0, r = ln.size - 1, mid;
        while (l < r){
            mid = (l + r) >> 1;
            if (comp(key, ln.record[mid].key))
                l = mid + 1;
            else
                r = mid;
        }
        ln.record[l].value = value;
        write(&ln, pos);
    }
    
    size_t size(){
        return core._size; 
    }

    bool empty(){
        return (core._size == 0);
    }
};

}

#endif //INC_2018DATASTRUCTUREBIGWORK_BPLUSTREE_H
