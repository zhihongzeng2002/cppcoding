#ifndef SELFTEST_H
#define SELFTEST_H

#include <vector>
#include <unordered_map>
#include <list>
#include <memory>
#include <string>
#include <unordered_set>
#include <stack>
#include <regex>

using namespace std;

namespace Selftest
{
    class TicTocGame {
        vector<vector<int> > B; // 0 for empty, 1 for player 1, and 2 for player 2
    public:
        TicTocGame() {}
        TicTocGame(int n): B(vector<vector<int> >(n, vector<int>(n, 0))) {}
        bool move(int player, int y, int x);
        int check();
    };

    struct Coor {
        int y, x;
        bool operator==(const Coor &one) const {
            return one.y==y && one.x==x;
        }
        bool operator!=(const Coor &one) const {
            return y != one.y || x != one.x;
        }
        Coor operator+(const Coor &two) const {
            Coor ans(*this);
            ans.y += two.y;
            ans.x += two.x;
            return ans;
        }
        Coor operator-(const Coor &two) const {
            Coor ans(*this);
            ans.y -= two.y;
            ans.x -= two.x;
            return ans;
        }
    };

    void robotMoveAtoB(vector<vector<bool> > B, Coor start, Coor exit);

    void mergeSort(vector<int> &A, int s, int e);
    void quickSort(vector<int> &A, int s, int e);
    void quickSort2(vector<int> &A, int s, int e);
    void quickSort(int *A, int s, int e);

    void SortSmallEqualLarge(vector<int> &A, int k);

    class LRU {
        list<pair<int, int> > A;
        unordered_map<int, list<pair<int, int> >::iterator> T;
        int maxsize;
    public:
        LRU(int _size): maxsize(_size) {}
        void insert(int x, int price);
        bool check(int x, int &price);
        void remove(int x);


    };

    double getMedian(vector<int> &A);
    vector<int> merge_arr(const vector<vector<int> > &A);

    vector<vector<int> > sort_k_increase_descrease_arr(const vector<int> &A);

    void online_median(istringstream &sin);

    struct Node {
        int data;
        shared_ptr<Node> next, jump;
        Node(int x): data(x), next(nullptr), jump(nullptr) {}
    };

    struct TNode {
        int data;
        shared_ptr<TNode> left, right, parent;
        TNode(int x): data(x), left(nullptr), right(nullptr) {}
        TNode(int x, shared_ptr<TNode> &_left, shared_ptr<TNode> &_right): data(x), left(_left), right(_right) {}
    };

    shared_ptr<Node> buildOddEvenList_again(shared_ptr<Node> &head);
    string findMajorityWord(istringstream &sin);
    int findNearestRepetition(const vector<int> &A) ;

    shared_ptr<Node> copyComplexList(shared_ptr<Node> &H);

    shared_ptr<TNode> copyTree(const shared_ptr<TNode> & root);

    struct Vertex {
        int data;
        int visit = -1;
        vector<pair<shared_ptr<Vertex>, int> > edgeStrength;
        vector<shared_ptr<Vertex> > edges;
        string user;
        vector<shared_ptr<Vertex> > contacts, extend_contacts;
//        unordered_set<shared_ptr<Vertex> > extend_friends;
    };

    struct HashCode {
        int operator()(const shared_ptr<Vertex> &v) {
            return hash<int>()(v->data) ^ hash<string>()(v->user);
        }
    };

    void build_extended_contacts(vector<shared_ptr<Vertex> > &G);
    bool shortestTransform(string &s, string &e, unordered_set<string> &D);
    bool shortestTransform_DFS(string &s, string &e, unordered_set<string> &D);

    pair<int, int> findPairInSortedArr(vector<int> &A, int k);

    int binary_search_unknown_len(vector<int> & A, int k);

    int findStartCircularSortedArr(const vector<int> &A);
    int findStartCircularSorted_RepeatedArr(const vector<int> &A);

    int find_missing_element(ifstream &ifs);

    int combinationCoins(int x, vector<int> &coins);
    int numberOfPath(int x, vector<int> & steps);
    int numberOfPath2D(vector<vector<int> > &A);

    void indirect_sortfile(const string &srcfile, const string &desfile);

    void printMatrixSpiralOrder(vector<vector<int> > &A);

    pair<int, int> longestIncreaseSubArr(const vector<int> &A);

    int maxProfit2BuySell(const vector<int> &A);
    vector<pair<int, int> > sequenceIn2DArr(const vector<vector<int> > &A, vector<int> &s);

    void bst_inorder_iterative(const shared_ptr<TNode> &root);
    void bst_preorder_iterative(const shared_ptr<TNode> &root);
    void bst_postorder_iterative(const shared_ptr<TNode> &root);
    void bst_inorder_iterative_with_parentnode(const shared_ptr<TNode> &root);

    bool isBST(const shared_ptr<TNode> & root);
    bool isBST_iterative(const shared_ptr<TNode> & root);

    shared_ptr<TNode> fistAppearNode(const shared_ptr<TNode> & root, int k);
    //15.4
    bool minBSTfind(const shared_ptr<TNode> &root, int k);
    shared_ptr<TNode> bstTolist(shared_ptr<TNode> &root);
    shared_ptr<TNode> bstTolist_ncomplexity(shared_ptr<TNode> &root);
    shared_ptr<TNode> listTobst(shared_ptr<TNode> &head);

    shared_ptr<TNode> merge2doubleList(shared_ptr<TNode> &A, shared_ptr<TNode> &B);

    vector<int> bst_findKLargest(shared_ptr<TNode> root, int k);
    shared_ptr<TNode> LCA_iterative(const shared_ptr<TNode> &root, const shared_ptr<TNode> &a, const shared_ptr<TNode> &b);
    shared_ptr<TNode> build_bst_from_markedsequence_preorder(const vector<int> &A);
    shared_ptr<TNode> build_bst_from_markedsequence_postorder(const vector<int> &A);
    void print_envolope_bst(shared_ptr<TNode> &root);

    int longestContinousSubArray(const vector<int> &A);
    int maxSubArrSum(const vector<int> &A);
    pair<int,int> maxSubArray(const vector<int> &A);
    pair<int, int> longestSubArrLessK(const vector<int> &A, int k);

    void subArrayGivenSum(const vector<int> &A, int k);
    void longestCommonSubstring(const string &x, const string &y);

    void printUglyNumber(int k);
    enum Color {
        black, white
    };
    void flip_color(vector<vector<Color> > &A, pair<int, int> &p, Color &c);

    vector<string> wordBreaking(const string &s, unordered_set<string> &D);
    vector<string> wordBreaking_iterative(const string &s, unordered_set<string> &D);

    void generateParentheses(int n);
    int fibonacci(int n); // time O(n), but matrix exponentiation can be O(lgN) (https://www.nayuki.io/page/fast-fibonacci-algorithms)
    void unittest();

    // book Cracking.. problem 15.7 page 438
    pair<int, int> masterMind(string s, string d);
    // book Cracking, problem 15.8
    void sortPartialSortedArr(vector<int> & A);
    void optimalParse(const string s, unordered_set<string> &D);
    int add_noplus(int x, int y);
    int generateRandom_a_b(int a, int b);
    double generateRandFromProb(const vector<double> &A, const vector<double> &prob);

    // Note: the following functions have not been test
    // Cracker problem 2.5 #
    shared_ptr<Node> addition_signficantLast(const shared_ptr<Node> &a, const shared_ptr<Node> &b);
    shared_ptr<Node> addition_signficantFirst(const shared_ptr<Node> &a, const shared_ptr<Node> &b);
    // problem 2.6
    shared_ptr<Node> find_start_cyclic_list(const shared_ptr<Node> &a);
    bool isPalindrome(const shared_ptr<Node> &a);
    shared_ptr<Node> reverseList(shared_ptr<Node> &n);
    void test_reverseList(vector<int> &A);

    //cracker 3.6
    void sortStack(stack<int> &S);
    void test_sortStack(vector<int> &A);
    void sortStack_additionStack_iterative(stack<int> &S);

    // cracker tree and graph
    shared_ptr<TNode> createTreeFromArray(vector<int> &A);
    shared_ptr<TNode> nextNode(shared_ptr<TNode> &n);
    shared_ptr<TNode> LCA_again(shared_ptr<TNode> &root, shared_ptr<TNode> &a, shared_ptr<TNode> &b);
    void findSumPath(shared_ptr<TNode> &root, int k);
    void findSumPath_arr(shared_ptr<TNode> &root, int k);

    // cracker bit manipulation
    int insertBit(int n, int m, int i, int j);
    string printBinary(double x);

    int largestSubSquare(const vector<vector<int> > &A);
    int largestSubSquare_n3(const vector<vector<int> > &A);
    bool abs_sorted_sum3(const vector<int> &A, int k);

    //elements: 15.8
    int largest_rect_arr(const vector<int> &A);
    // elements: 15.9
    int largest_rect_2Dmatrix(const vector<vector<int> > &A);
    // elements: 15.14
    int compute_binomial_coefficients(int n, int k);

    bool findPairWithSum_unsorted(const vector<int> &A, int sum);

    void bigNumberSort(vector<string> &A);
    void stableSort(vector<pair<int, string> > &A);

    void search_replace(string &s, vector<string> &r);

    // interview
    float TossCoins_kHead(const vector<float> &P, int k);
    // elememts: 20.8
    float houseVote_majority(const vector<float> &P);
    // elements: 17.1
    long ties_election(const vector<int> &V);
    void printBizzBuzzGame(int n, int bizz, int buzz);
    bool meetingConflict(vector<pair<int, int> > &A);

    //    regex. major.minor~beta|alpha|rc[0-9]
    // 23345.784~beta10 "\d+\.\d+(~(beta|alpha|rc)*\d*)*"
    bool regexMatch(const string &s, const regex e);
    void regexSearch(const string &s0, const regex e);

    // a set of runners who start at different places in the line and different speeds, check whether there is any collision at the race, assumming the runners will run forever, and along the line
    bool collision(vector<pair<int, int> > &A);
    //    24bit represent red, green, blue, return red, blue, black, white, amigu which is closest to the pixel color
    void closesetColor(const string pixels);

//    message reassembly
//    120 bytes long, divide 10 fragments.

//    bool readFragment(uint8_t output_data[16])
//    bool readMessage(uint8_t output[120]);

    int levinson_dist(string &s, string &t);

    // interview in 10/2017
    void random_permutation(vector<int> &A);
}



#endif // SELFTEST_H
