//
// Created by Peter Zheng on 2018/04/22.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_ENGINE_H
#define INC_2018DATASTRUCTUREBIGWORK_ENGINE_H
namespace myAlgorithm {
    class Engine {
        template<class T>
        class BPlusTree {
            const int NUMBER_OF_SON = 10; // 结点最多的儿子数目
            const int SIZE_BLOCK = 4096;
            struct Node {
                Node *prev, *next;

            };
        };
    };
}

#endif //INC_2018DATASTRUCTUREBIGWORK_ENGINE_H
