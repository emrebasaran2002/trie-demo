#include "Trie.hpp"
#include <vector>

Trie::node_t::node_t(): present{false}, children{} {}

Trie::node_t::~node_t() {
    // Delete the whole subtree!
    for (const auto& child : this->children) {
        delete child.second;
    }
}

Trie::node_t::node_t(const Trie::node_t& other):
    present{other.present},
    children{}
{
    // Recursively copy all children.
    for (const auto& child : other.children) {
        this->children[child.first] = new node_t(*child.second);
    }
}

Trie::node_t::node_t(Trie::node_t&& other):
    present{other.present},
    children{std::move(other.children)}
{
    other.children.clear();
}

Trie::node_t& Trie::node_t::operator=(const Trie::node_t& other) {
    // Guard against self-assignment.
    if (this != &other) {
        // Copy the present field.
        this->present = other.present;

        // Delete all children of this.
        for (const auto& child : this->children) {
            delete child.second;
        }
        this->children.clear();
        
        // Copy all the children.
        for (const auto& child : other.children) {
            this->children[child.first] = new node_t {*child.second};
        }
    }
    return *this;
}

Trie::node_t& Trie::node_t::operator=(Trie::node_t&& other) {
    // Guard against self-assignment.
    if (this != &other) {
        // Copy the present field.
        this->present = other.present;

        // Delete all children of this.
        for (const auto& child : this->children) {
            delete child.second;
        }

        // Move all children of other into this.
        this->children = std::move(other.children);
        other.children.clear();
    }
    return *this;
}

Trie::Trie(): root{nullptr} {}

Trie::~Trie() {
    delete this->root;
}

Trie::Trie(const Trie& other): root{other.root ? new node_t{*other.root} : nullptr} {}

Trie::Trie(Trie&& other): root{other.root} {
    other.root = nullptr;
}

Trie& Trie::operator=(const Trie& other) {
    // Guard against self-assignment.
    if (this != &other) {
        delete this->root;
        if (other.root) {
            this->root = new node_t{*other.root};
        } else {
            this->root = nullptr;
        }
    }
    return *this;
}

Trie& Trie::operator=(Trie&& other) {
    // Guard against self-assignment.
    if (this != &other) {
        delete this->root;
        this->root = other.root;
        other.root = nullptr;
    }
    return *this;
}

void Trie::add(const std::string& str) {
    // If there is no root, add a root to the tree.
    if (this->root == nullptr) {
        this->root = new node_t;
    }

    // Navigate to the node corresponding to the string.
    node_t* ptr = this->root;
    for (char chr : str) {
        if (ptr->children.count(chr) == 0) {
            ptr->children[chr] = new node_t;
        }
        ptr = ptr->children[chr];
    }

    ptr->present = true;
}

bool Trie::contains(const std::string& str) const {
    if (this->root == nullptr) {
        return false;
    }

    // Navigate to the node corresponding to the string.
    node_t* ptr = this->root;
    for (char chr : str) {
        if (ptr->children.count(chr) == 0) {
            return false;
        }
        ptr = ptr->children[chr];
    }

    return ptr->present;
}

void Trie::remove(const std::string& str) {
    if (this->root == nullptr) {
        return;
    }

    // Find the chain of pointers leading to the node that corresponds to
    // the given string.
    std::vector<node_t*> stack;
    stack.push_back(this->root);
    for (char chr : str) {  
        node_t* current = stack.back();
        if (current->children.count(chr) == 0) {
            return;
        }
        stack.push_back(current->children[chr]);
    }

    stack.back()->present = false;

    // Clean up unnecessary nodes in the chain.
    while (true) {
        node_t* current = stack.back();
        stack.pop_back();

        // Reached a node that can't be deleted, cleanup is over.
        if (current->present || current->children.size() != 0) {
            break;
        }

        delete current;
        if (stack.size() == 0) {
            this->root = nullptr;
            break;
        } else {
            stack.back()->children.erase(str[stack.size() - 1]);
        }
    }
}
