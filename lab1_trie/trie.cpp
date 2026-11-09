#include "trie.h"

#include <filesystem>
#include <vector>


Trie::Trie() {
    root = new node_t;
}


Trie::~Trie() {
    if (root == nullptr){return;}
    clear_dfs(root);
    delete root;
}


Trie::Trie(const Trie& other) {
    root = copy_dfs(other.root);
}


node_t* Trie::copy_dfs(node_t* node) {
    if (!node) {return nullptr;}
    auto* curr = new node_t;
    curr->end = node->end;
    for (const auto& [chr, child_node] : node->children) {
        curr->children[chr] = copy_dfs(child_node);
    }
    return curr;
}


Trie::Trie(Trie&& other) noexcept :root(other.root) {
    other.root = nullptr;
}


Trie& Trie::operator=(const Trie& other) {
    if (this == &other) {return *this;}
    clear_dfs(root);
    delete root;

    root = copy_dfs(other.root);
    return *this;
}


Trie& Trie::operator=(Trie&& other) noexcept {
    if (this == &other) {return *this;}
    clear_dfs(root);
    delete root;

    root = other.root;
    other.root = nullptr;
    return *this;
}


//Вставка
void Trie::insert(std::string_view str) {
    node_t* curr = root;
    for (char chr : str) {
        auto a = curr->children.find(static_cast<unsigned char>(chr));
        if (a != curr->children.end()) {
            curr = a->second;
        }
        else {
            auto* new_node = new node_t;
            curr->children[chr] = new_node;
            curr = new_node;
        }
    }
    curr->end = true;
}


//Проверка наличие строки
bool Trie::contains(std::string_view str) const{
    node_t* curr = root;
    for (char chr : str) {
        auto a = curr->children.find(static_cast<unsigned char>(chr));
        if (a != curr->children.end()) {
            curr = a->second;
        }
        else {
            return false;
        }
    }
    return curr->end;
}


//Подсчёт слов с префиксом
size_t Trie::count_dfs(node_t* node) const{
    size_t cnt = 0;
    if (node->end) {
        cnt++;
    }
    for (const auto& [chr, child_node] : node->children) {
        cnt += count_dfs(child_node);
    }
    return cnt;
}


size_t Trie::prefix_count(std::string_view pref) const{
    node_t* curr = root;
    for (char chr : pref) {
        auto a = curr->children.find(static_cast<unsigned char>(chr));
        if (a != curr->children.end()) {
            curr = a->second;
        }
        else {
            return 0;
        }
    }
    return count_dfs(curr);
}


//Вывод всех слов
void Trie::print_dfs(const node_t* node, std::string& str, std::ostream& os) const{
    for (const auto& [chr, child_node] : node->children) {
        str += chr;
        if (child_node->end) {
            os << str << std::endl;
        }
        print_dfs(child_node, str, os);
        str.pop_back();
    }
}


std::ostream& operator<<(std::ostream& os, const Trie& trie) {
    node_t* curr = trie.root;
    std::string s;
    trie.print_dfs(curr, s, os);
    return os;
}


//Сравнение деревьев
bool Trie::compare_dfs(const node_t* node, const node_t* node2) const{
    if (node->children.size() != node2->children.size()) {
        return false;
    }
    if (node->end != node2->end) {
        return false;
    }
    for (const auto& child : node->children) {
        auto a = node2->children.find(child.first);
        if (a == node2->children.end()) {
            return false;
        }
        if (!compare_dfs(child.second, a->second)) {
            return false;
        }
    }
    return true;
}


bool Trie::operator==(const Trie& other) const {
    return compare_dfs(root, other.root);
}


bool Trie::operator!=(const Trie& other) const {
    return !compare_dfs(root, other.root);
}


//служебные методы
bool Trie::empty() const {
    if (!root) {return true;}
    return root->children.empty();
}


size_t Trie::size() const {
    return prefix_count("");
}


void Trie::clear_dfs(node_t* node) {
    for (const auto& [chr, child_node] : node->children) {
        clear_dfs(child_node);
        delete child_node;
    }
    node->children.clear();
}


void Trie::clear() {
    if (!root) {return;}
    clear_dfs(root);
    delete root;
    root = new node_t;
}



//удаление строки
bool Trie::erase(std::string_view str) {
    node_t* curr = root;
    std::vector<node_t*> path;
    std::vector<char> path_symbol;
    for (char c : str) {
        path.push_back(curr);
        path_symbol.push_back(c);
        auto a = curr->children.find(static_cast<unsigned char>(c));
        if (a != curr->children.end()) {
            curr = a->second;
        }
        else {
            return false;
        }
    }
    if (curr->end) {
        curr->end = false;
        if (!curr->children.empty()) {
            return true;
        }
        //очистка незначащих узлов
        for (int i = str.size() - 1; i >= 0; --i) {
            node_t* parent = path[i];
            char ch = path_symbol[i];
            node_t* child_to_delete = parent->children[ch];

            parent->children.erase(ch);
            delete child_to_delete;

            if (parent->end || !parent->children.empty()) {
                break;
            }
        }
        return true;
    }
    return false;
}


void Trie::pref_dfs(const node_t* node, std::string str, size_t limit, std::vector<std::string>& words) const {
    if (limit > 0 && words.size() >= limit) {return;}

    for (const auto& [chr, child_node] : node->children) {
        str += chr;
        if (child_node->end) {
            words.push_back(str);
            if (limit > 0 && words.size() >= limit) {
                str.pop_back();
                return;
            }
        }
        pref_dfs(child_node, str, limit, words);
        str.pop_back();
    }
}

std::vector<std::string> Trie::words_with_prefix(
      std::string_view pref, size_t limit) const {
    node_t* curr = root;
    std::string str = "";

    for (char chr : pref) {
        auto a = curr->children.find(static_cast<unsigned char>(chr));
        if (a != curr->children.end()) {
            curr = a->second;
            str += chr;
        } else {
            return {};
        }
    }
    std::vector<std::string> words;
    if (curr->end) {
        words.push_back(str);
    }
    pref_dfs(curr, str, limit, words);
    return words;
}