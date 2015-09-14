#include "mytrie.h"
#include "string.h"
#include <iostream>

MyTrie::MyTrie()
{    
    root=shared_ptr<TrieNode>(new TrieNode('\0'));
}

void MyTrie::addWord(char *str)
{
    if (!str || *str=='\0') return;

    shared_ptr<TrieNode> currentNode=root;
    for (int i=0; i<strlen(str); i++)
    {
        if (currentNode->children.find(str[i])==currentNode->children.end())
        {
            shared_ptr<TrieNode> node(new TrieNode(str[i]));
            currentNode->children.insert(std::pair<char, shared_ptr<TrieNode> >(str[i], node));
//            cout << i << "-" << str[i] << " ";
        }

        currentNode=currentNode->children.find(str[i])->second;
    }
    currentNode->wordMarker=true;
}

bool MyTrie::searchWord(char *str)
{
    if (!str || !root) return false;
    if (*str=='\0') return true;

    shared_ptr<TrieNode> currentNode=root;
    for (int i=0; i<strlen(str); i++)
    {
        if (currentNode->children.find(str[i])==currentNode->children.end())
            return false;
//        cout << i << "->" << currentNode->children.find(str[i])->first << " ";
        currentNode=currentNode->children.find(str[i])->second;
    }

    return currentNode->wordMarker;

}

void MyTrie::printTrie(shared_ptr<TrieNode> nodeptr)
{
    if (!nodeptr) return;

    cout << nodeptr->s << endl;
    map<char, shared_ptr<TrieNode> >::iterator itr=nodeptr->children.begin();
    for (; itr != nodeptr->children.end(); itr++)
    {
        printTrie(itr->second);
    }

}

void TrieString::addString(string &str)
{
    if (str.empty()) return;
    for (int i=0; i<str.size(); i++)
    {
        string sub=str.substr(i);
        rootptr->addString(sub, i);
    }
}

vector<int> TrieString::searchString(string &str)
{
    if (str.empty()) return vector<int>();
    return rootptr->search(str);
}

void TrieStringNode::addString(string &str, int _index)
{
    if (str.empty())
    {
        indexes.push_back(_index);
        return;
    }

    char key = str[0];
//    cout << key << endl;

    if (children.find(key)==children.end())
    {
        shared_ptr<TrieStringNode> nodeptr(new TrieStringNode(key));
        children.insert(pair<char, shared_ptr<TrieStringNode> >(key, nodeptr));
    }
    indexes.push_back(_index);
    string substr=str.substr(1);
    children.find(key)->second->addString(substr, _index);
}

vector<int> TrieStringNode::search(string &str)
{
    if (str.size()==0)
    {
//        cout << __LINE__ << ":" << indexes.size() << endl;
        return indexes;
    }

    char key = str[0];
    if (children.find(key) == children.end())
        return vector<int>();

//    cout << key << endl;
    string substr=str.substr(1);
    return children.find(key)->second->search(substr);
}
