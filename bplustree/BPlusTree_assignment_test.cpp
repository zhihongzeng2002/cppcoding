#include "bplustree_assignment.h"
#include <string>

int main(int argc, char* argv[]){
    std::cout << "empty tree\n";
    BPlusTree<char> empty_tree(3);
    empty_tree.print();

    std::cout << "number tree\n"; 
    BPlusTree<int> tree(3);
    for (int i=0; i<9; i++) { 
        std::cout << "add .............." << i << "\n";
        tree.insert(i);  
        tree.print();
    }

    std::cout << "string tree\n";
    BPlusTree<char> str_tree(4); 
    std::string test("abcdefghijkl");
    for (int i=0; i<test.size(); i++) { 
        char c = test[i];
        std::cout << "add .............." << c << "\n";
        str_tree.insert(c);  
        str_tree.print();
    }

}  