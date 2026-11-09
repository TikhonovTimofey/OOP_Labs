#ifndef LAB1_TRIE_NODE_T_H
#define LAB1_TRIE_NODE_T_H
#include <map>
#include <iostream>


class node_t {
    friend class Trie;
public:
    node_t();


private:
    std::map<unsigned char, node_t *> children;
    bool end;
};


#endif //LAB1_TRIE_NODE_T_H
