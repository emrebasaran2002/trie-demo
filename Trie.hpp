#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

class Trie final {
    private:
        struct node_t final {
            bool present;
            std::map<char, node_t*> children;
            char link;
            node_t* parent;
        };

        node_t* root;

        // Duplicates the entire subtree of the supplied node.
        // The returned node has its parent set to null.
        static node_t* duplicate(const node_t&);

        // Deallocates the entire subtree of the supplied node.
        // Precondition: node != nullptr
        static void destroy(node_t*);

        static void visit(const node_t&, std::ostream&, std::string&, bool&);
    
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
    
    friend std::ostream& operator<<(std::ostream&, const Trie&);
};

#endif
