#ifndef MYTRIE_H
#define MYTRIE_H

#include <map>
#include <memory>
#include <vector>
#include <string>

using namespace std;

struct TrieNode
{
    char s;
    bool wordMarker;
    std::map<char, shared_ptr<TrieNode> > children;

    TrieNode(char _s): s(_s), wordMarker(false)
    {}
};

class MyTrie
{
public:
    MyTrie();

    void addWord(char *str);
    bool searchWord(char *str);
    void printTrie(shared_ptr<TrieNode> nodeptr);

    shared_ptr<TrieNode> getRoot()
    {
        return root;
    }

//    int countWords(char *str);
//    int countPrefixes(char *str);

private:
    shared_ptr<TrieNode> root;
};

class TrieStringNode
{
    char value;
    map<char, shared_ptr<TrieStringNode> > children;
    std::vector<int> indexes;

public:
    TrieStringNode(){}
    TrieStringNode(char _value): value(_value){}
    void addString(string & str, int _index);
    std::vector<int> search(string & str);

};

class TrieString
{
    shared_ptr<TrieStringNode> rootptr;
public:
    TrieString()
    {
        rootptr=shared_ptr<TrieStringNode>(new TrieStringNode);
    }
    void addString(string & str);
    vector<int> searchString(string & str);

};

#endif // MYTRIE_H
