/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>
#include <queue>


// #ifndef DS_BPLUSTREE
// #define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
// template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf() const;
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.

	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;

	// BPlusTreeNode* get_parent() const { return parent; } 
	// std::vector<T> get_keys() const { return keys; }
	// std::vector<BPlusTreeNode*> get_children() const { return children; }

	//We need this to let BPlusTree access private members
	// friend class BPlusTree<T>; 
private:  // change from private to protected so that the child class can access
	bool contains(const T& key,std::size_t low,std::size_t high);

};

template <class T>
bool BPlusTreeNode<T>::is_leaf() const {
	// for(unsigned int i=0; i<children.size(); i++){
	// 	if(children[i]){
	// 		return false;
	// 	}
	// }
    if (children.empty())
        return true;
    else
		return false;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

/////////////////////////////////
// template <class T>
// class BPlusTreeNodeDerived: public BPlusTreeNode<T> {
// public:
//     void print();
//     void insert(T& x);
//     BPlusTreeNodeDerived* find(T& x);
// };
template <class T>
class BPlusTree {
	public:
		BPlusTree(const int& d) { degree = d; root=new BPlusTreeNode<T>(); }
		void print() {  print_sub(root); }
		void insert(const T& x) { insert_sub(find(root, x), x); }
		int get_degree() { return degree; }
	private:
		int degree;
		BPlusTreeNode<T>* root;

		void print_sub(BPlusTreeNode<T>* node) {
			std::queue<BPlusTreeNode<T>* > q;
			if (node != NULL)
				q.push(node);

			while (!q.empty()){
				BPlusTreeNode<T>* node = q.front();
				q.pop();
				for (auto& k: node->keys)
					std::cout << k << " ";
				std::cout << "\n";

				for (auto& n: node->children)
					q.push(n);
			}    
		}		

		void insert_sub(BPlusTreeNode<T>* node, const T& x) {
			if (node == NULL) {
				node = new BPlusTreeNode<T>();
			}

			auto& keys = node->keys;
			auto& children = node->children;
			keys.push_back(x);
			if (keys.size() >= degree) {
				int half = keys.size() / 2;
				std::vector<T> half_left(keys.begin(), keys.begin + half);
				int split = keys[half]

				if (node->is_leaf())
					std::vector<T> half_right(keys.begin+half, keys.end());
				else
					std::vector<T> half_right(keys.begin+half+1, keys.end());

				node->keys = half_left;
				if (!node->is_leaf())
					node->children = std::vector<BPlusTreeNode<T>* >(node->children.begin(), children.begin(), children.end());

				BPlusTreeNode<T>* right_node(new BPlusTreeNode());
				right_node->keys = half_right;

				if (!node->is_leaf()) {
					right_node->children.push_back(right_node->children.begin(), children.begin()+half, children.end());
				}
				
				insert_sub(node->parent, half_right[0]);
			}

		}

		BPlusTreeNode<T>* find(BPlusTreeNode<T>* node, const T& x) {
			if (node->is_leaf()) 
				return node;

			auto& keys = node->keys;
			auto& children = node->children;

			if (x < keys[0])
				return find(children[0], x);

			for (int i=1; i<keys.size()-1; i++) {
				if (x >= keys[i] && x < keys[i+1])
					return find(children[i], x);
			}

			return find(children[keys.size()-1], x);
		}
};



