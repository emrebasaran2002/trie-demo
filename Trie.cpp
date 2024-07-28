#include "Trie.hpp"

Trie::node_t* Trie::duplicate(const Trie::node_t& other) {
    node_t* node = new node_t;
    node->parent = nullptr;

    // Copy the present flag.
    node->present = other.present;
    
    // Copy the children.
    for (const auto& x : other.children) {
        node->children[x.first] = duplicate(*x.second);
    }

    return node;
}

void Trie::destroy(Trie::node_t* node) {
    // Recursively destroy the children.
    for (const auto& x : node->children) {
        destroy(x.second);
    }
    
    delete node;
}

void Trie::visit(
    const Trie::node_t& node, // The node being visited.
    std::ostream& out, // Output stream to print to.
    std::string& str, // The current string that has been accumulated.
    bool& first // True if nothing has yet been printed.
) {
    // If present, print the string.
    if (node.present) {
        if (!first) {
            out << ", ";
        }
        out << '"' << str << '"';
        first = false;
    }

    // Recursively visit all the children.
    for (const auto& x : node.children) {
        str.push_back(x.first);
        visit(*x.second, out, str, first);
        str.pop_back();
    }
}

Trie::Trie(): root{nullptr} {}

Trie::~Trie() {
    if (this->root != nullptr) {
        destroy(this->root);
    }
}

Trie::Trie(const Trie& other) {
    if (other.root == nullptr) {
        this->root = nullptr;
    } else {
        this->root = duplicate(*other.root);
    }
}

Trie& Trie::operator=(const Trie& other) {
    Trie temp {other};
    std::swap(this->root, temp.root);
    return *this;
}

Trie::Trie(Trie&& other): root{other.root} {
    other.root = nullptr;
}

Trie& Trie::operator=(Trie&& other) {
    std::swap(this->root, other.root);
    return *this;
}

void Trie::add(const std::string& str) {
    if (this->root == nullptr) {
        this->root = new node_t;
        this->root->present = false;
        this->root->parent = nullptr;
    }

    // Find the node that corresponds to the string.
    node_t* node = this->root;
    for (char chr : str) {
        if (node->children.count(chr) == 0) {
            node_t* child = new node_t;
            child->present = false;
            child->link = chr;
            child->parent = node;
            node->children[chr] = child;
        }
        node = node->children[chr];
    }

    node->present = true;
}

void Trie::remove(const std::string& str) {
    if (this->root == nullptr) {
        return;
    }

    // Find the node that corresponds to the string.
    node_t* node = this->root;
    for (char chr : str) {
        if (node->children.count(chr) == 0) {
            return;
        }
        node = node->children[chr];
    }

    node->present = false;

    // Remove the unnecessary nodes along the path.
    while (node != nullptr && !node->present && node->children.size() == 0) {
        if (node->parent != nullptr) {
            node->parent->children.erase(node->link);
        }
        node_t* temp = node;
        node = node->parent;
        delete temp;
    }
}

bool Trie::contains(const std::string& str) const {
    if (this->root == nullptr) {
        return false;
    }

    // Find the node that corresponds to the stirng.
    node_t* node = this->root;
    for (char chr : str) {
        if (node->children.count(chr) == 0) {
            return false;
        }
        node = node->children[chr];
    }

    return node->present;
}

std::ostream& operator<<(std::ostream& out, const Trie& trie) {
    out << '[';
    if (trie.root != nullptr) {
        std::string str;
        bool first = true;
        Trie::visit(*trie.root, out, str, first);
    }
    out << ']';
    return out;
}
