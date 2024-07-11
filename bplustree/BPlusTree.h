/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
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

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
	public:
	//default constructor
	BPlusTree() {
		degree = 0;
		root = NULL;
	}
	//full constructor
	BPlusTree(int d) {
		degree = d;
		root = NULL;
	}
	//copy constructor
	BPlusTree(const BPlusTree& b) {
		degree = b.degree;
		root = new BPlusTreeNode<T>();
		for (unsigned int i = 0; i < b.root->keys.size(); i++) {
			root->keys.push_back(b.root->keys[i]);
		}
	}
	//destructor
	~BPlusTree() {
		clearTree(root);
	}
	//destructor helper
	void clearTree(BPlusTreeNode<T>* node) {
		//base case, reached a null node
		if (node == NULL) {
			return;
		}

		//base case 2, reached a leaf node
		if (node->is_leaf()) {
			delete node;
			return;
		}

		//general case, go through children and delete
		for (unsigned int i = 0; i < node->children.size(); i++) {
			clearTree(node->children[i]);
		}
	}

	// get degree
	//find
	BPlusTreeNode<T>* find(T key, BPlusTreeNode<T>* node) {
		//edge case if the tree is not constructed yet
		if (node == NULL) return NULL;

		//base case – if leaf node
		if (node->is_leaf()) {
			return node;
		} else {
			//general case, send the find function into the appropriate node
			//if less than the first item or greater than last item, use first/last child node
			if (key < node->keys[0]) {
				return find(key, node->children[0]);
			}

			//if not either greater than all values or less than, loop through middle children
			for (unsigned int i = 1; i < node->keys.size() - 1; i++) {
				if (key > node->keys[i - 1] && key < node->keys[i + 1]) {
					return find(key, node->children[i]);
				}
			}

			//if value not between any of the intermediate values, must be a value at the end
			return find(key, node->children[node->children.size() - 1]);
		}
	}
	BPlusTreeNode<T>* find(T key) {
		return find(key, root);
		//1: determine the node
		//2: determine if the node contains the value
	}

	//insert new layer
	void addLayer(BPlusTreeNode<T>* node) {
		int mid = node->keys.size() / 2;
		std::vector<T> temp;
		temp.push_back(node->keys[mid]);

		for (int i = 0; i < 2; i++) {
			node->children.push_back(new BPlusTreeNode<T>());
			node->children[i]->parent = node;
		}

		//add values lower than mid value to left
		int i = 0;
		while (node->keys[i] < temp[0] && i < node->keys.size()) {
			node->children[0]->keys.push_back(node->keys[i]);
			i++;
		}
		//add rest of values to right
		while (i < node->keys.size()) {
			node->children[1]->keys.push_back(node->keys[i]);
			i++;
		}

		//set the current node to the mid value
		node->keys.clear();
		node->keys = temp;
	}

	//add node to layer above
	void addAbove(BPlusTreeNode<T>* node, BPlusTreeNode<T>* parentNode, int i) {
		//base case, if parent NULL, then at top layer and new node should be added
		if (parentNode == NULL) {
			addLayer(node);
			return;
		}

		//remove last value from node, put it in parent node
		T val = node->keys[node->keys.size() - 1];
		node->keys.pop_back();

		bool inserted = false;
		std::vector<T> temp;
		for (unsigned int i = 0; i < parentNode->keys.size(); i++) {
			if (parentNode->keys[i] > val) {
				temp.push_back(val);
				inserted = true;
			}
			temp.push_back(parentNode->keys[i]);
		}
		//if no value was bigger, then this new value must be biggest
		if (!inserted) temp.push_back(val);
		parentNode->keys = temp;

		//if degree over the limit, go to parent of parent
		if (parentNode->keys.size() >= degree) {
			addAbove(parentNode, parentNode->parent, i + 1);
		} else {
			//if not, then generate new nodes down to the last layer
			int j = 0;
			BPlusTreeNode<T>* current = parentNode;
			while(j < i) {
				j++;
				current->children.push_back(new BPlusTreeNode<T>());
				current = current->children[parentNode->children.size() - 1];
				current->keys.push_back(val);
			}
		}
	}

	//insert
	void insert (T key, BPlusTreeNode<T>* node) {
		//base case, we are at a leaf
		if (node->is_leaf()) {
			//add it to current node in the right place
			bool inserted = false;
			std::vector<T> temp;
			for (unsigned int i = 0; i < node->keys.size(); i++) {
				if (node->keys[i] > key) {
					temp.push_back(key);
					inserted = true;
				}
				temp.push_back(node->keys[i]);
			}
			//if no value was bigger, then this new value must be biggest
			if (!inserted) temp.push_back(key);
			node->keys = temp;

			//if keys goes over the limit, add more nodes
			if (node->keys.size() >= degree) {
				addAbove(node, node->parent, 1);
			}
			return;
		}

		//general case, if not a leaf, then must find leaf where key can be inserted
		//if less than the first item, use first node
		if (key < node->keys[0]) {
			insert(key, node->children[0]);
			return;
		}

		//if not either greater than all values or less than, loop through middle children
		for (unsigned int i = 1; i < node->keys.size() - 1; i++) {
			if (key > node->keys[i - 1] && key < node->keys[i + 1]) {
				insert(key, node->children[i]);
				return;
			}
		}

		//if value not between any of the intermediate values, must be a value at the end
		insert(key, node->children[node->children.size() - 1]);
	}
	//1: insert which node to insert key into
	//2: decide where in the node the key should be inserted
	void insert (T key) {
		//case in which there is no pre-existing root node
		if (!root) {
			root = new BPlusTreeNode<T>();
			root->keys.push_back(key);
			return;
		}

		insert(key, root);
	}

	void print_sideways_recurse(std::ostream& output, BPlusTreeNode<T>* node, int depth) {
		//base case, reaching the end of a node
		if (node == NULL) return;

		//general case, recurse for both left and right nodes
		//get mid
		int mid = node->keys.size() / 2;

		//print everything to the right of mid
		int i = 0;
		while (i < mid) {
			print_sideways_recurse(output, node->children[i], depth + 1);
			i++;
		}

		//print self
		std::string spaces (depth * 4, ' ');
		output << spaces;
		for (unsigned int i = 0; i < node->keys.size(); i++) {
			output << node->keys[i];
		}
		output << std::endl;

		//print all other children nodes
		while (i < node->keys.size()) {
			print_sideways_recurse(output, node->children[i], depth + 1);
			i++;
		}

	}

	void print_sideways(std::ostream& output) {
		if (root == NULL) {
			output << "Tree is empty." << std::endl;
		}
		else {
			print_sideways_recurse(output, root, 0);
		}
	}

	void print_BFS(std::ostream& output) {
		if (root == NULL) {
			output << "Tree is empty." << std::endl;
		} else {
			//breadth wide print
			std::vector<BPlusTreeNode<T>* > current;
			std::vector<BPlusTreeNode<T>* > next;
			current.push_back(root);

			while (current.size() != 0) {
				//loop through every node in current
				for (unsigned int i = 0; i < current.size(); i++) {
					//print out every value
					for (unsigned int j = 0; j < current[i]->keys.size(); j++) {
						output << current[i]->keys[j];
						if (j != current[i]->keys.size() - 1) output << ",";
					}

					//add every child to next
					for (unsigned int j = 0; j < current[i]->children.size(); j++) {
						next.push_back(current[i]->children[j]);
					}
					output << "    ";
				}
				current.clear();
				current = next;
				next.clear();

				output << std::endl;
			}
		}
	}
	private:
	int degree;
	BPlusTreeNode<T>* root;
};

#endif
