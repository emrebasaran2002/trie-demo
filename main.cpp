#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>
#include "Trie.hpp"

struct Test final {
    std::string name;
    void (*func)();

    Test(const std::string& name, void (*func)()): name{name}, func{func} {}
};

// Helper for verifying the contents of a trie, using the << operator.
void checkContents(const Trie& trie, const std::string& expected) {
    std::ostringstream stream;
    stream << trie;
    const std::string actual = stream.str();
    assert(actual == expected);
}


void emptyTrieTest() {
    Trie trie;
    checkContents(trie, "[]");
}

void copyAssignmentOperator() {
    Trie trie1;
    Trie trie2;

    trie1.add("hello");
    trie1.add("world");
    trie1 = trie2;
    checkContents(trie1, "[]");
    checkContents(trie2, "[]");

    trie1.add("emre");
    trie2.add("duru");
    trie1 = trie2;
    checkContents(trie1, "[\"duru\"]");
    checkContents(trie2, "[\"duru\"]");

    trie1.remove("duru");
    trie2.add("emre");
    trie1 = trie2;
    checkContents(trie1, "[\"duru\", \"emre\"]");
    checkContents(trie2, "[\"duru\", \"emre\"]");

    trie1.remove("duru");
    trie1.remove("emre");
    trie1.add("abc");
    trie1 = trie1;
    checkContents(trie1, "[\"abc\"]");   
    checkContents(trie2, "[\"duru\", \"emre\"]");
}

int main(void) {
    std::vector<Test> tests;
    tests.emplace_back("emptyTrieTest", &emptyTrieTest);
    tests.emplace_back("copyAssignmentOperator", &copyAssignmentOperator);
    
    for (const Test& test : tests) {
        std::cout << "Running: " << test.name << std::endl;
        test.func();
    }

    std::cout << "All tests pass. :)" << std::endl;
    return 0;
}
