#include <iostream>
#include <memory>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
     int val;
     shared_ptr<ListNode> next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, shared_ptr<ListNode> next) : val(x), next(next) {}

     void print() {
        cout << val << " ";
         shared_ptr<ListNode> temp(next);
         while(temp != nullptr) {
             cout << temp->val << " ";
             temp = temp->next;
         } 
         cout << endl;
     }
 };

class Solution {
public:
    shared_ptr<ListNode> addTwoNumbers(shared_ptr<ListNode> l1, shared_ptr<ListNode> l2) {

        shared_ptr<ListNode> dummy(new ListNode());
        shared_ptr<ListNode> temp = dummy;
        int carry = 0;
        
        while(l1 != nullptr || l2 != nullptr || carry) {
            int sum = 0;
            if(l1 != nullptr) {
                sum += l1->val;
                l1 = l1->next;
            }
            if(l2 != nullptr) {
                sum += l2->val;
                l2 = l2->next;
            }
            sum += carry;
            carry = sum / 10;
            shared_ptr<ListNode> node(new ListNode(sum % 10));
            temp->next = node;
            temp = temp->next;
        }
        return dummy->next;       
    }
};

int main() {

    shared_ptr<ListNode> root1(new ListNode(2));
    root1->next = shared_ptr<ListNode>(new ListNode(4));
    root1->next->next = shared_ptr<ListNode>(new ListNode(3));
    root1->print();

    shared_ptr<ListNode> root2(new ListNode(5));
    root2->next = shared_ptr<ListNode>(new ListNode(6));
    root2->next->next = shared_ptr<ListNode>(new ListNode(9));
    root2->print();

    shared_ptr<ListNode> ans = Solution().addTwoNumbers(root1, root2);
    ans->print();

    return 0;
}