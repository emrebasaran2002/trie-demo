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

void copyAssignmentOperatorTest() {
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

void copyConstructorTest() {
    Trie trie;
    Trie* trieCopy;

    trieCopy = new Trie {trie};
    checkContents(*trieCopy, "[]");
    delete trieCopy;

    trie.add("emre");
    trie.add("duru");
    trieCopy = new Trie {trie};
    checkContents(*trieCopy, "[\"duru\", \"emre\"]");

    trie.remove("emre");
    trie.add("aynur");
    trieCopy->remove("duru");
    trieCopy->add("mustafa");
    checkContents(trie, "[\"aynur\", \"duru\"]");
    checkContents(*trieCopy, "[\"emre\", \"mustafa\"]");
    delete trieCopy;
}

void moveAssignmentOperatorTest() {
    Trie trie1;
    Trie trie2;

    trie1.add("emre");
    trie1.add("duru");
    trie2 = std::move(trie1);
    checkContents(trie2, "[\"duru\", \"emre\"]");

    trie2.add("aynur");
    trie2.add("mustafa");
    trie1 = std::move(trie2);
    checkContents(trie1, "[\"aynur\", \"duru\", \"emre\", \"mustafa\"]");

    trie1.remove("aynur");
    trie1.add("mom");
    trie1.remove("mustafa");
    trie1.add("dad");
    trie2 = std::move(trie1);
    checkContents(trie2, "[\"dad\", \"duru\", \"emre\", \"mom\"]");

    trie1 = Trie{};
    trie2 = Trie{};
    checkContents(trie1, "[]");
    checkContents(trie2, "[]");

    trie1.add("hello");
    trie2.add("world");
    trie1 = std::move(trie2);
    checkContents(trie1, "[\"world\"]");
}

void moveConstructorTest() {
    Trie* trie1;
    Trie* trie2;

    trie1 = new Trie;
    trie2 = new Trie{std::move(*trie1)};
    checkContents(*trie2, "[]");
    delete trie1;
    delete trie2;

    trie1 = new Trie;
    trie1->add("hello");
    trie1->add("world");
    trie2 = new Trie{std::move(*trie1)};
    checkContents(*trie2, "[\"hello\", \"world\"]");
    delete trie1;
    delete trie2;
}

int main(void) {
    std::vector<Test> tests;
    tests.emplace_back("emptyTrieTest", &emptyTrieTest);
    tests.emplace_back("copyAssignmentOperatorTest", &copyAssignmentOperatorTest);
    tests.emplace_back("copyConstructorTest", &copyConstructorTest);
    tests.emplace_back("moveAssignmentOperatorTest", &moveAssignmentOperatorTest);
    tests.emplace_back("moveConstructorTest", &moveConstructorTest);
    
    for (const Test& test : tests) {
        std::cout << "Running: " << test.name << std::endl;
        test.func();
    }

    std::cout << "All tests pass. :)" << std::endl;
    return 0;
}
