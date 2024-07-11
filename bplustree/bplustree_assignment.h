/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <iostream>
#include <queue>
#include <memory>

using namespace std;

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(nullptr) {};
	bool is_leaf() const;
	bool contains(const T& key);
    std::vector<T>& get_keys() { return keys; }
    std::vector<shared_ptr<BPlusTreeNode<T> > >& get_children() { return children; }
    shared_ptr<BPlusTreeNode<T> >& get_parent() { return parent; }
    void set_parent(const shared_ptr<BPlusTreeNode<T> > input_parent) { parent = input_parent; }
    void set_keys(const vector<T> &input_keys) { keys = input_keys;}
    void set_children(const vector<shared_ptr<BPlusTreeNode<T> > >& input_children) { children = input_children; }

private:  // change from private to protected so that the child class can access
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<shared_ptr<BPlusTreeNode<T> > > children;
	shared_ptr<BPlusTreeNode<T> > parent;

};

template <class T>
bool BPlusTreeNode<T>::is_leaf() const {
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

template <class T>
class BPlusTree {
	public:
		BPlusTree(const int& d): degree(d), root(new BPlusTreeNode<T>()) { }
		void print() {  print_sub(root); }
		void insert(const T& x) { auto node = find(root, x); root = insert_sub(node, x, nullptr, nullptr); }
	private:
		int degree;
		shared_ptr<BPlusTreeNode<T> > root;

		void print_sub(shared_ptr<BPlusTreeNode<T> > node) {
			std::queue<shared_ptr<BPlusTreeNode<T> > > q;
            std::queue<shared_ptr<BPlusTreeNode<T> > > q2;
            if (node)
                q.push(node);

			while (!q.empty()){
				shared_ptr<BPlusTreeNode<T> > node = q.front();
				q.pop();

				for (auto& k: node->get_keys())
					std::cout << k << " ";
                auto parent = node->get_parent();
                if (parent) {
                    cout << "(";
                    for (auto& t: parent->get_keys())
                        cout << t << " ";
                    cout << ")";

                }
				std::cout <<  "==>";

				for (auto& n: node->get_children())
					q2.push(n);
                if (q.empty() && !q2.empty()) {
                    q.swap(q2);
                    cout << "\n";
                }

			}    
            cout << "\n";
		}		

		shared_ptr<BPlusTreeNode<T> > insert_sub(shared_ptr<BPlusTreeNode<T> > node, const T& x, \
                        shared_ptr<BPlusTreeNode<T> > child_left, shared_ptr<BPlusTreeNode<T> > child_right) {
			if (node == nullptr) {
				node = shared_ptr<BPlusTreeNode<T> >(new BPlusTreeNode<T>());
			}

			auto& keys = node->get_keys();
			auto& children = node->get_children();

            keys.push_back(x);
            if (children.empty() && child_left!=nullptr) {
                children.push_back(child_left);
                child_left->set_parent(node);
            }
            if (child_right != nullptr) {
                children.push_back(child_right);
                child_right->set_parent(node);
            }
            
            // node split when key size is larger than the degree
			if (keys.size() >= degree) {
                auto children_copy = children;

                // create half_left_node and half_right_node
				int half = int(keys.size() / 2);
				std::vector<T> half_left(keys.begin(), keys.begin() + half);
				int split = keys[half];

                vector<T> half_right;
				if (node->is_leaf())
					half_right = vector<T>(keys.begin()+half, keys.end());
				else {
					half_right = vector<T>(keys.begin()+half+1, keys.end());
                }

                // update the current node as the half_left_node
				node->set_keys(half_left);
				if (!node->is_leaf()) {
					node->set_children(vector<shared_ptr<BPlusTreeNode<T> > >(children_copy.begin(), children_copy.begin()+half+1));
                }

                // create the half_right node
				shared_ptr<BPlusTreeNode<T> > right_node(new BPlusTreeNode<T>());
				right_node->set_keys(half_right);
				if (!node->is_leaf()) {
					right_node->set_children(vector<shared_ptr<BPlusTreeNode<T> > >(children_copy.begin()+half+1, children_copy.end()));
                    // update the children parent pointer of the half_right node
                    for (auto c: right_node->get_children()) {
                        c->set_parent(right_node);
                    }
				}
				return insert_sub(node->get_parent(), split, node, right_node);
			}
            else {
                // trace back to the root node
                auto curr = node;
                while (curr->get_parent())
                    curr = curr->get_parent();
                return curr;
            }

		}

		/// @brief recursively find the leaf node where the inserted x should be located 
		/// @param node search start node
		/// @param x search key
		/// @return destination leaf node 
		shared_ptr<BPlusTreeNode<T> > find(shared_ptr<BPlusTreeNode<T> > node, const T& x) {
			if (node->is_leaf()) {
				return node;
            }

			auto& keys = node->get_keys();
			auto& children = node->get_children();

			if (x < keys[0])
				return find(children[0], x);

			for (int i=0; i<keys.size()-1; i++) {
				if (x >= keys[i] && x < keys[i+1])
					return find(children[i+1], x);
			}

			return find(children[keys.size()], x);
		}
};



