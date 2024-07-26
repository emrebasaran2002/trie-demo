#include <iostream>
#include "Trie.hpp"

int main(void) {
    Trie trie;

    trie.add("abc");
    trie.add("abd");
    trie.debug();
    std::cout << std::endl;

    std::cout << "a: " << trie.contains("a") << std::endl;
    std::cout << "b: " << trie.contains("b") << std::endl;
    std::cout << "ab: " << trie.contains("ab") << std::endl;
    std::cout << "abc: " << trie.contains("abc") << std::endl;
    std::cout << "abd: " << trie.contains("abd") << std::endl;
    std::cout << std::endl;

    trie.remove("abc");
    trie.debug();
    std::cout << std::endl;

    trie.remove("abd");
    trie.debug();
    std::cout << std::endl;

    std::cout << "Done!" << std::endl;
    return 0;
}
