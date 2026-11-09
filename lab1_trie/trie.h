#ifndef LAB1_TRIE_TRIE_H
#define LAB1_TRIE_TRIE_H
#include <iostream>
#include "node_t.h"
#include <vector>

class Trie {
public:
    Trie();
    ~Trie();
    Trie(const Trie& other);
    Trie(Trie&& other) noexcept;
    Trie& operator=(const Trie& other);
    Trie& operator=(Trie&& other) noexcept;
    void insert(std::string_view str);
    bool contains(std::string_view str) const;
    size_t prefix_count(std::string_view pref) const;
    std::vector<std::string> words_with_prefix(
      std::string_view pref, size_t limit = 0) const;

    bool operator==(const Trie& other) const;
    bool operator!=(const Trie& other) const;
    bool erase(std::string_view str);
    bool empty() const;
    size_t size() const;
    void clear();

private:
    size_t count_dfs(node_t* node) const;
    void pref_dfs(const node_t* node, std::string str, size_t limit, std::vector<std::string>& words) const;
    void print_dfs(const node_t* node, std::string& str, std::ostream& ost) const;
    bool compare_dfs(const node_t* node, const node_t* node2) const;
    void clear_dfs(node_t* node);
    node_t* copy_dfs(node_t* node);
    friend std::ostream& operator<<(std::ostream& ost, const Trie& trie);
    node_t* root;

};


#endif //LAB1_TRIE_TRIE_H
