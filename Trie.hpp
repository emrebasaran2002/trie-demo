#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <string>
#include <map>

class Trie final {
    private:
        struct node_t final {
            bool present;
            std::map<char, node_t*> children;

            node_t();
            ~node_t();

            node_t(const node_t&);
            node_t(node_t&&);
            node_t& operator=(const node_t&);
            node_t& operator=(node_t&&);

            void debug(std::string&) const;
        };

        node_t* root;
    
    public:
        Trie();
        ~Trie();

        Trie(const Trie&);
        Trie(Trie&&);
        Trie& operator=(const Trie&);
        Trie& operator=(Trie&&);

        void add(const std::string&);
        void remove(const std::string&);
        bool contains(const std::string&) const;

        void debug() const;
};

#endif
