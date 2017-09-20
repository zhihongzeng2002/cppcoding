#include <iostream>
#include <stdlib.h>
#include <exception>
#include <queue>
#include <algorithm>
#include "primitive.h"
#include "search.h"
#include "meta.h"
#include "graph.h"
#include <regex>
#include "bst.h"
#include "arraystring.h"
#include <stdexcept>
#include <random>
#include "stackqueue.h"
//#include <iterator>
#include "concurrency.h"
#include "oop.h"
#include "sorting.h"
#include "moderate.h"
#include "hard.h"
#include "misc.h"
#include "leet.h"
#include "linkedlist.h"
#include "heap.h"
#include "hashtables.h"
#include "meta.h"
#include "prob.h"
#include "discrete.h"
#include "selftest.h"

int test_search(int argc, char **argv);
int test_Primitive(int argc, char ** argv);
int test_vector_cbegin(int argc, char ** argv);
int test_priority_queue(int argc, char ** argv);
int test_meta(int argc, char ** argv);
int test_graph(int argc, char ** argv);
void printVector(const vector<int> &arr);
vector<int> buildVector(int argc, char ** argv);
vector<string> buildVectorString(int argc, char ** argv);
vector<double> buildVectorDouble(int argc, char **argv);
void metaTest(int argc, char ** argv);
void graphTest(int argc, char ** argv);
void hardTest(int argc, char ** argv);
void moderateTest(int argc, char ** argv);
void miscTest(int argc, char ** argv);
void leetTest(int argc, char **argv);
void testArrayString(int argc, char ** argv);
void testLinkedList(int argc, char **argv);
void testStackQueue(int argc, char ** argv);
void testHeap(int argc, char **argv);
void testSorting(int argc, char **argv);
void testHashTables(int argc, char ** argv);
void testMeta(int argc, char **argv);
void testProb(int argc, char **argv);
void testBST(int argc, char ** argv);

// from nutonomy interview
typedef struct node {
  int data;
  shared_ptr<node> left, right;
} node_t;

// Return a 1 if a value is found, return 0 otherwise
int search_bst(shared_ptr<node_t> root, int value) {
if (root==nullptr) return 0;
if (root->data==value) return 1;
else if (root->data<value )
   return search_bst(root->right, value);
else
   return search_bst(root->left, value);


}

int search_bst_iterative(shared_ptr<node_t> root, int value) {
shared_ptr<node_t> curr = root;
while (curr) {
    if(root->data==value) return 1;
    else if (root->data < value)
        curr=curr->right;
    else
        curr=curr->left;
}
return 0;
}

void test_find_bst() {
    TreeN<int> * node = new TreeN<int>;
    cout << find_bst_recursive(node, 5) << endl;
    cout << find_bst_iterative(node, 5) << endl;
    delete node;
}

class mycomparison
{
public:
    bool operator()(const int lhs, const int rhs)
    {
        return lhs>rhs;
    }
};

//void test_regex_search(const std::string& input)
//{
//    std::regex rgx("([0-9][0-9]):([0-5][0-9])((am)|(pm))");
//    std::smatch match;

//    if (std::regex_match(input, rgx))
//    {
//        std::cout << "Match\n";

//    }
//    else
//        std::cout << "No match\n";
//}

void practice_priority_queue() {
    int myints[]={10,60,50,20};

    std::priority_queue<int> second (myints,myints+4);
    cout << second.top() << endl;
    std::priority_queue<int, std::vector<int>, std::greater<int> >
                              third (myints,myints+4);
    cout << third.top() << endl;
}

void practice_heap() {
    std::vector<int> v { 3, 1, 4, 1, 5, 9 };

    std::cout << "initially, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::make_heap(v.begin(), v.end());

    std::cout << "after make_heap, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    std::pop_heap(v.begin(), v.end());
    auto largest = v.back();
    v.pop_back();
    std::cout << "largest element: " << largest << '\n';

    std::cout << "after removing the largest element, v: ";
    for (auto i : v) std::cout << i << ' ';
    std::cout << '\n';

    cout << "after sort_heap: " << endl;
    sort_heap(v.begin(), v.end());
    for (auto i : v) cout << i << " ";
    cout << endl;

}

template<typename T, typename Comp>
void printMax(T a, T b) {
    cout << (a>b ? a : b) << endl;
    Comp comp;
    cout << comp(a, b) << endl;
}

void printStack(stack<int> & s) {
    stack<int> t;
    while (!s.empty()) {
        cout << s.top() << " ";
        t.push(s.top());
        s.pop();
    }
    cout <<endl;
    while (!t.empty()) {
        s.push(t.top());
        t.pop();
    }
}

int count5(int n) {
    int count=0;
//    for ( int i=5; n/i>0 && n%5==0; i*=5)
//        count++;
    while (n>0 && n%5==0) {
        count++;
        n /= 5;
    }
    return count;
}

void testSearch(int argc, char ** argv) {
    Search t;
    vector<int> A = buildVector(argc, argv);
    pair<int, int> ret = t.findSubtractionPairInSortedArray(A, -3);
    cout << ret.first << " " << ret.second << endl;
}

void testDiscrete(int argc, char ** argv) {
    Discrete d;
    cout << d.find_max_floor(atoi(argv[1]), atoi(argv[2])) << endl;
}

void testConcurrency(int argc, char ** argv) {
    Concurrency t;
//    t.testConsumerProducer();
    t.testDataBuff();
}

void test_findLongestSeq(int argc, char **argv) {
    vector<int> A;
    for (int i=1; i<argc; i++)
        A.emplace_back(atoi(argv[i]));
    cout << findLongestContinueSeq(A) << endl;
}

void test_merge_quick_sort(vector<int> &A) {
//    Heap x;
//    cout << x.getMedian(A) << endl;
    cout << Selftest::getMedian(A);
//    Selftest::SortSmallEqualLarge(A, 5);
//    Selftest::quickSort(A, 0, A.size()-1);
//    Selftest::mergeSort(A, 0, A.size()-1);
//    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

}

/**
 * @brief find_sub_word
 * @param s
 * @param word
 * @return
 */
int find_sub_word(string s, string word) {
    int count = 0, start = 0;
    while (true) {
        size_t found = s.find(word, start);
        if (found != string::npos) {
            count++;
            start = found+word.size();
        } else
            break;
    }
    return count;
}

int find_word(string s, string word) {
    int count = 0, start = 0;
    string punctuation_space(" `~!@#$%^&*()_+\"=-[]{}|\\;:',.<>/?");
    while (true) {
        size_t end = s.find_first_of(punctuation_space, start);
        if (end != string::npos) {
            int x = s.compare(max(0, int(end-word.size())), word.size(), word);
            if (!x) {
                count++;
            }
            start = end+1;
        } else
            break;
    }
    // for the last word without " " at the end
    if (s.size()>=word.size()) {
        if (!s.compare(s.size()-word.size(), word.size(), word))
            count++;
    }
    return count;
}

int main_vecna_search() {
  std::string input = "The Dogman was no ordinary dog, nor man, but rather a peculiar dog-like man who barked like a dog, and panted like a dog, he even ate like a dog.  He owned a dog named Doglips, and interestingly enough, his favorite food was hotdogs.dog";
  std::cout << "Counting dogs (case sensitive):" << endl;
  cout << input << endl;
  std::cout << "---The word \"dog\" appears (single word and sub-word like hogdog) " << find_sub_word(input, "dog") << " times." << std::endl;
  std::cout << "---The word \"dog\" appears as a single word " << find_word(input, "dog") << " times." << std::endl;
  cout << endl;
  transform(input.begin(), input.end(), input.begin(), ::tolower);
  std::cout << "Counting dogs (case insensitive):" << endl;
  cout << input << endl;
  std::cout << "---The word \"dog\" appears (single word and sub-word like hogdog) " << find_sub_word(input, "dog") << " times." << std::endl;
  std::cout << "---The word \"dog\" appears as a single word " << find_word(input, "dog") << " times." << std::endl;
}


int main_vecna_sort() {
  int unsorted[100] = {};
  srand (time(NULL));
  for (int i = 0; i < 100; i++) {
    unsorted[i] = rand() % 100;
  }
  std::cout << "Here are the unsorted numbers:" << std::endl;
  for (int i = 0; i < 100; i++) {
    std::cout << unsorted[i] << " ";
  }
  std::cout << std::endl;
//  int sorted[100] = {};
//  for (int i = 0; i < 100; i++) {
//    int hi = -1;
//    int hiIndex = -1;
//    for (int j = 0; j < 100; j++) {
//      if (unsorted[j] > hi) {
//        hi = unsorted[j];
//        hiIndex = j;
//      }
//    }
//    sorted[i] = hi;
//    unsorted[hiIndex] = -1;
//  }
  Selftest::quickSort(unsorted, 0, 99);
  std::cout << "Here are the sorted numbers:" << std::endl;
  for (int i = 0; i < 100; i++) {
    std::cout << unsorted[i] << " ";
  }
  std::cout << std::endl;
}

void print2D(vector<vector<int> > &a) {
    for (int i=0; i<a.size(); i++) {
        for (int j=0; j<a.front().size(); j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

int numberOfPaths(vector < vector < int > > a) {
    print2D(a);
    if (a.empty() || a[0][0]==0) return 0;
    vector<vector<int> > B(a.size(), vector<int>(a.front().size(), 0));
    printf("%d-%d\n", B.size(), B.front().size());
    B[0][0]=1;
    print2D(B);
    for (int i=0; i<a.size(); i++) {
        for (int j=0; j<a.front().size(); j++) {
                printf("before %d ", B[i][j]);
            if (!i && !j) continue;
            if (a[i][j]==1) {
                if (i)
                    B[i][j]+=B[i-1][j];
                if (j)
                    B[i][j]+=B[i][j-1];
//                B[i][j] = i==0?0:B[i-1][j] + j==0?0:B[i][j-1];
//                printf("%d.%d: %d ",i, j, B[i][j]);
            }
//            printf("\n");
        }
    }
    print2D(B);
    return B.back().back();

}

int main(int argc, char **argv)
{
    vector<vector<int> > B;
    B.emplace_back(vector<int>(2,1));
    B.emplace_back(vector<int>(2,1));
    cout << numberOfPaths(B) << endl;
//    vector<string> A;
//    for (int i=1; i<argc; i++) {
//        A.emplace_back(string(argv[i]));
//    }

//    Selftest::bigNumberSort(A);
//    sort(A.begin(), A.end(), [](const string &a, const string &b){ return stoi(a)<stoi(b);});
//    copy(A.begin(), A.end(), ostream_iterator<string>(cout, " "));

//    auto ans = Selftest::longestSubArrLessK(A, 184);
//    cout << ans.first << " " << ans.second << endl;
    //    auto A = Primitive::generate_primes_sieveofEratosthenes(atoi(argv[1]));
//    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
//    Selftest::printUglyNumber(atoi(argv[1]));
//    cout << Selftest::add_noplus(atoi(argv[1]), atoi(argv[2])) << endl;
//    Selftest::optimalParse(string(argv[1], )
//    Selftest::insertBit(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));
//    Selftest::test_sortStack(A);
//    Selftest::test_reverseList(A);
//    Selftest::sortPartialSortedArr(A);
//    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
//    auto ans = Selftest::masterMind(string(argv[1]), string(argv[2]));
//    cout << ans.first << " " << ans.second << endl;
//    Selftest::printUglyNumber(atoi(argv[1]));
//    Selftest::longestCommonSubstring(string(argv[1]), string(argv[2]));
//    Selftest::subArrayGivenSum(A, 7);
//    cout << Selftest::longestContinousSubArray(A) << endl;
//    cout << Selftest::maxSubArrSum(A) << endl;
//    test_merge_quick_sort(A);


//    test_findLongestSeq(argc, argv);
//    test_find_bst();
//    testConcurrency(argc, argv);
//    leetTest(argc, argv);
//    testMeta(argc, argv);
//    test_Primitive(argc, argv);
//    testDiscrete(argc, argv);
//    leetTest(argc, argv);
//    testBST(argc, argv);
//    leetTest(argc, argv);
//    testProb(argc, argv);
//    testMeta(argc, argv);
//    test_graph(argc, argv);
//    leetTest(argc, argv);
//    testMeta(argc, argv);
//    testHashTables(argc, argv);
//    testSorting(argc, argv);
//    std::unordered_map<std::string,std::string> mymap = {
//              {"house","maison"},
//              {"apple","pomme"},
//              {"tree","arbre"},
//              {"book","livre"},
//              {"door","porte"},
//              {"grapefruit","pamplemousse"}
//    };

//    unsigned n = mymap.bucket_count();

//    std::cout << "mymap has " << n << " buckets.\n";

//    for (unsigned i=0; i<n; ++i) {
//        std::cout << "bucket #" << i << " contains: "<< mymap.bucket_size(i) << endl ;
//      for (auto it = mymap.begin(i); it!=mymap.end(i); ++it)
//        std::cout << "[" << it->first << ":" << it->second << "] ";
//      std::cout << "\n";
//    }
//    testSearch(argc, argv);
//    testStackQueue(argc, argv);
//    testArrayString(argc, argv);
//    testHeap(argc, argv);
//    testLinkedList(argc, argv);
//    testArrayString(argc, argv);
//    test_Primitive(argc, argv);
//    leetTest(argc, argv);
//    miscTest(argc, argv);
//    hardTest(argc, argv);

//    moderateTest(argc, argv);

//    graphTest(argc, argv);

//    metaTest(argc, argv);


    return 0;
}

void testBST(int argc, char **argv) {
    BST<int> t;
    auto A = buildVector(argc, argv);
    auto n=t.buildBSTfromVector(A, 0, A.size()-1);
    t.printTree(n);
    cout << endl;
    t.preorder_iterative(n);
    t.postorder_iterative(n);
}

void testProb(int argc, char **argv){
    Prob t;
    auto A = buildVector(argc, argv);
    auto ret = t.off_sampling(A, 3);
    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

}

void testMeta(int argc, char **argv) {
    Meta t;
    try {
        vector<int> A={3, 5, 1, 5};
        t.loadBalance(A, atoi(argv[1]));
//        vector<int> B={4, 2, 2, 2};
//        t.jobAssignment_clientsSevers(A, B);
//        unordered_set<string> D={"dog", "cat", "and"};
//        auto ret = t.word_breaking_better(string(argv[1]), D);
//        copy(ret.begin(), ret.end(), ostream_iterator<string>(cout, " "));
//        cout << endl;
//        cout << t.check_Collatz(atoi(argv[1])) << endl;
//        cout << t.check_Collatz_recursive(atoi(argv[1])) << endl;
//    auto ret = t.min_expression_seq(atoi(argv[1]));
//    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
    } catch (exception & e) {
        cout << e.what() << endl;
    }

//    cout << t.calc_ways_walk_in2darray(atoi(argv[1]), atoi(argv[2])) << endl;
//    unordered_set<string> D;
//    D.insert("dog");
//    D.insert("cat");
//    D.insert("at");
//    cout << t.stringConstruct(string(argv[1]), D) << endl;

//    vector<int> A = buildVector(argc, argv);
//    auto ret = t.findLongestSubarrySumLessEqualK(A, 10);
//    cout << ret.first << " " << ret.second << endl;
//    ret = t.findLongestSubarrySumLessEqualK_queue(A, 10);
//    cout << ret.first << " " << ret.second << endl;

}

void testHashTables(int argc, char **argv) {
    HashMap<string, int> h(10);
    pair<string, int> x("a", 1);
    pair<string, int> y("b", 2);
    pair<string, int> z("c", 3);
    h.insert(x);
    h.insert(y);
    h.insert(z);
    int ret;
    h.lookup("a", ret);
    cout << ret << endl;
    h.lookup("b", ret);
    cout << ret << endl;
    h.lookup("c", ret);
    cout << ret << endl;
    cout << "----------" << endl;
    cout << h.getsize() << endl;
    h.erase("a");
    cout << h.getsize() << endl;
    h.erase("b");
    cout << h.getsize() << endl;
    h.erase("c");
    cout << h.getsize() << endl;

}

void testSorting(int argc, char **argv) {
    Sorting t;
    vector<int> A = buildVector(argc, argv);
    t.flipSort(A);
//    t.radixSort(A);
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void testHeap(int argc, char ** argv) {
    Heap h;
    vector<int> A = buildVector(argc, argv);
    vector<int> ret = h.findKClosestMedian(A, 3);
    copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
//    vector<string> fins({"f1.csv", "f2.csv"});
//string out("out.csv");
//    h.mergeSortedFiles(fins, out);
}

void testStackQueue(int argc, char **argv) {
    Stackqueue t;
    cout << t.reverserPolishNotation(string(argv[1])) << endl;
}

void testLinkedList(int argc, char **argv) {
    LinkedList t;
    vector<int> A = buildVector(argc, argv);
    shared_ptr<LinkedList::Node> head = t.buildList(A);
    t.print(head);;
    t.print(head);;
//    shared_ptr<LinkedList::Node> even;// = t.evenOddList2(head);
//    even = t.evenOddList3(head);
//    t.print(even);
//    t.print(head);
}

void leetTest(int argc, char ** argv) {
    Leet t;
    try {
        cout << t.findLargestPalindromicSubstr_nlogn(string(argv[1])) << endl;
        cout << t.findLargestPalindromicSubstr_DP(string(argv[1])) << endl;
//        t.generateParentheses(atoi(argv[1]));
//        vector<string> D={"foo", "bar"};
//        string s("barfoothefoobarman");
//        auto ret=t.substringWithAllWords_efficient(s, D);
//        copy(ret.begin(), ret.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//        string s(")()())");
//        cout << t.longestValidParentheses2(s) << endl;
//        cout << t.longestValidParentheses3_better(s) << endl;
//        vector<int> A = buildVector(argc, argv);
//        t.combinationSum(A, 8);
//        t.combinationSum2(A, 8);

//        t.jumpGame(A);
//        if (prev.empty()) {
//            cout << "empty string" << endl;
//        } else
//            cout << "last word=" << << endl;

//        t.permutations_k(A, 3);
//        t.combinations(atoi(argv[1]), atoi(argv[2]));
//        t.numDistinctSubsequence(string(argv[1]), string(argv[2]));
        //["hot","dot","dog","lot","log"]
//        unordered_set<string> D;
//        D.emplace("hot");
//        D.emplace("dot");
//        D.emplace("dog");
//        D.emplace("lot");
//        D.emplace("log");
//        D.emplace("cog");
//        auto ret=t.wordLadder2(argv[1], argv[2], D);
//        for (auto &r: ret) {
//            copy(r.begin(), r.end(), ostream_iterator<string>(cout, " "));
//            cout << endl;
//        }
//        t.zigzagConrversion2(string(argv[1]), 3);
//        cout << t.convertIntToRoman(atoi(argv[1])) << endl;
//        auto s = t.convertIntToRoman(atoi(argv[1]));
//        cout << t.convertRomanToInt(s) << endl;
//        t.generateParentheses(atoi(argv[1]));
//        auto A = buildVector(argc, argv);
//        t.sum4_efficient(A, 0);
//        auto head = t.buildList(A);
//        t.printList(head);
//        t.swapNodesInPairs(head);
////        t.reverseNodesKGroup(head, 3);
//        t.printList(head);
//        t.removeElem(A, 3);
//        printVector(A);
//        t.removeDuplicatesArray(A);
//        printVector(A);
//        string s("(()");
//        cout << t.longestValidParentheses(s) << endl;

//        cout << t.longestValidParentheses2(s) << endl;
//        cout << t.firstMissingPositive(A) << endl;
//        cout << t.trapRainWater(A) << endl;
////        cout << endl;
//        cout << t.trapRainWater2(A) << endl;
//        cout << t.jumpGame2(A) << endl;
//        t.subset3_duplicates(A);
//        t.subset2_better(A);
//        t.permutations(A);
//        cout << t.lengthLastWord(string(" ")) << endl;
//        cout << t.lengthLastWord(string(" 12")) << endl;
//        cout << t.lengthLastWord(string(" 123 1234  1")) << endl;
//        cout << t.lengthLastWord(string(" 1 12345  ")) << endl;
//        cout << t.minimumWindowSubstring(string(argv[1]), string(argv[2])) << endl;
//        cout << t.minimumWindowSubstring_sequential(string(argv[1]), string(argv[2])) << endl;
//        t.combinations(atoi(argv[1]), atoi(argv[2]));
//        auto A = buildVector(argc, argv);list
//        shared_ptr<Leet::LNode> n(new Leet::LNode());
//        auto head=t.buildList(A);
//        t.printList(head);
//        t.plusOne(head);
//        t.printList(head);
//        t.removeDuplicates2(head);
//        cout << t.isScrambleStrings(string(argv[1]), string(argv[2])) << endl;
//        t.grayCode(atoi(argv[1]));
//        cout << t.decodeWays(string(argv[1])) << endl;
//        auto A = buildVector(argc, argv);
//        t.subset2(A);
//        cout << "-----" << endl;
//        t.subset2_better(A);
//        cout << t.uniqueBST(atoi(argv[1])) << endl;
//        auto ret = t.uniqueBST2(atoi(argv[1]));
//        cout << ret.size() << endl;
//        cout << t.interleavingString(string(argv[1]), string(argv[2]), string(argv[3])) << endl;
//        auto A= buildVector(argc, argv);
//        auto root = t.buildTree_LNodeRightNeighbor(A);
//        t.flattenBinaryTree(root);
//            auto node = root;
//            while (node){
//                cout << node->data << " ";
//                node=node->right;
//            }


//        t.pascalTriangle(atoi(argv[1]));
//        vector<vector<int> >A={
//            {2},
//            {3,4},
//            {6,5,7},
//            {4,1,8,3}};
//        cout << t.triangle(A) << endl;

//        cout << t.numDistinctSubsequence(string(argv[1]), string(argv[2])) << endl;
//        string s("race a car");
//        cout << t.validPalindrome(s) << endl;
//        auto A = buildVector(argc, argv);
//        cout << t.longestConsecutiveSequence(A) << endl;
//        vector<vector<char> > A = {{'X', 'X','X'},
//                                   {'X', 'O', 'X'},
//                                   {'X','X', 'X'}};
//        t.surroundedRegion_efficient(A);
//        for (auto &a : A) {
//            copy(a.begin(), a.end(), ostream_iterator<char>(cout, " "));
//            cout << endl;
//        }
//        t.palindromePartition(string(argv[1]));
//         auto A= buildVector(argc, argv);
//         cout << t.appearOnce_otherAppearThreeTimes(A) << endl;
//         cout << t.appearOnce_otherAppearThreeTimes_noextraspace(A) << endl;
//         cout << t.appearOnce_otherAppearThreeTimes_mostefficient(A) << endl;
//        unordered_set<string> dict;
//        dict.emplace("cat");
//        dict.emplace("dog");
//        dict.emplace("sand");
//        dict.emplace("cats");
//        dict.emplace("and");
//        t.wordBreak_efficient_print(string(argv[1]), dict);


//        cout << t.longestNonRepeatSubstr(string(argv[1])) << endl;
//        cout << t.longestNonRepeatSubstr2(string(argv[1])) << endl;

//        vector<int> A = buildVector(argc, argv);
//        shared_ptr<Leet::LNode> node=nullptr;
//        shared_ptr<Leet::LNode> node2=nullptr;
//        for (auto &a : A) {
//            cout << "--------" << endl;
//            t.insertNodeCyclicList(node, a);
//            t.printNodeCyclicList(node);
//            t.insertNodeCyclicList(node2, a);
//            t.printNodeCyclicList(node2);
//        }

        //        string s(argv[1]);
//        cout << t.findLargestPalindromicSubstr(s) << endl;
//        cout << t.findLargestPalindromicSubstr_nlogn(s) << endl;

//        cout << t.isPalindromeInt(atoi(argv[1])) << endl;
//        cout << t.isPalindromeInt_2(atoi(argv[1])) << endl;
//        vector<int> A = buildVector(argc, argv);
//        cout << t.distanceMaximum(A) << endl;
//        cout << t.distanceMaximum_nlogn(A) << endl;
//        auto ret = t.distanceMaximum_better(A);
//        cout << ret.first << " " << ret.second << " " << ret.second-ret.first << endl;
//        cout << t.maxSubarrayProduct(A) << endl;
//        cout << t.editDist(string(argv[1]), string(argv[2])) << endl;
//        cout << t.editDist_efficientSpace(string(argv[1]), string(argv[2])) << endl;
//        int A[]={1,2,3, 6, 8};
//        int B[]={4,5, 7, 9, 10};
//        cout << t.findKsmallestUnion_log(A,5, B,5, atoi(argv[1])) << endl;
//        vector<int> A{1, 2,3};
//        vector<int> B{4,5, 7};
//        cout << t.findKsmallestSumUnion(A, B, atoi(argv[1])) << endl;
//        cout << t.findKsmallestSumUnion(A, B, atoi(argv[1])) << endl;
//        cout << t.medianSortedArrayUnion(A, B) << endl;
//        cout << t.findKsmallestUnion_log2(A, B, atoi(argv[1])) << endl;
//        cout << t.regexMatch("aa", "a") << endl;
//        cout << t.regexMatch("aa", "^aa") << endl;
//        cout << t.regexMatch("aaa", "a") << endl;
//        cout << t.regexMatch("aa", "a*") << endl;
//        cout << t.regexMatch("aa", ".*") << endl;
//        cout << t.regexMatch("ab", ".*") << endl;
//        cout << t.regexMatch("aab", "c*a*b") << endl;
//        cout << t.regexMatch("aab", "c*a*b$") << endl;
//        cout << t.regexMatch("aa", "c*a*") << endl;
//        cout << t.regexMatch("aab", ".*a*b") << endl;

//        cout << t.wildcardMatching("aa", "a") << endl;
//        cout << t.wildcardMatching("aa", "aa") << endl;
//        cout << t.wildcardMatching("aaa", "a") << endl;
//        cout << t.wildcardMatching("aa", "a*") << endl;
//        cout << t.wildcardMatching("aa", "?*") << endl;
//        cout << t.wildcardMatching("ab", "?*") << endl;
//        cout << t.wildcardMatching("aab", "c*a*b") << endl;
//        cout << t.wildcardMatching("aab", "*a*b") << endl;
//        cout << t.isPalindromeInt(atoi(argv[1])) << endl;
//        cout << t.isPalindromeInt_recursive(atoi(argv[1])) << endl;
//        vector<int> A = buildVector(argc, argv);
//        Leet::LRUCache tstLRU(3);
//        for (auto &a : A) {
//            tstLRU.set(a, 1);
//            tstLRU.printSeq();
//        }
//        shared_ptr<Leet::LNode> head = t.buildList(A);
//        t.sortList(head);
//        t.printList(head);
//        cout << t.paintersPartition(A, 3) << endl;
//        cout << t.paintersPartition_efficient(A, 3) << endl;
//        cout << t.longestNonRepeatSubstr(string(argv[1])) << endl;
//        string res=t.convertIntToRoman(atoi(argv[1]));
//        cout << res << endl;
//        cout << t.convertRomanToInt(res) << endl;
//        cout << t.reverseInt_noSpace(atoi(argv[1])) << endl;
//        vector<int> A = buildVector(argc, argv);
//        vector<vector<int> > res = t.sum4_efficient(A, 10);
//        for (auto &x: res) {
//            copy(x.begin(), x.end(), ostream_iterator<int>(cout , " "));
//            cout << endl;
//        }
//        cout << t.divideInts(atoi(argv[1]), atoi(argv[2])) << endl;
//        cout << atoi(argv[1])/atoi(argv[2]) << endl;
//        cout << t.wildcardMatching(string(argv[1]), string(argv[2])) << endl;
//        cout << t.multiplyStrings(string(argv[1]), string(argv[2])) << endl;
//        cout << t.multiplyStrings_efficient(string(argv[1]), string(argv[2])) << endl;
//        cout << t.multiplyStrings_moreefficient(string(argv[1]), string(argv[2])) << endl;

//        vector<vector<string> > res = t.NQueens(8);
//        for (auto &x:res) {
//            copy(x.begin(), x.end(), ostream_iterator<string>(cout, "\n"));
//            cout << endl;
//        }
//        cout << res.size() << endl;
//        vector<int> A = buildVector(argc, argv);
//        cout << t.jumpGame(A) << endl;
//        cout << t.addBinaryStrings(string(argv[1]), string(argv[2])) << endl;
//        vector<string> A{"this", "is", "an", "example", "of", "text", "justification", "and", "example", "of", "123", "of", "123", "of", "123"};
//        vector<string> res = t.textJustify(A, 16);
//        copy(res.begin(), res.end(), ostream_iterator<string>(cout, "\n"));
//        cout << t.textMessiness(A, 16) << endl;
//        vector<vector<int> >A{
//            {1,3,5,7},
//            {2,4, 6, 8},
//            {3, 5, 7, 9}
//        };
//        t.searchSorted2D_2(A, atoi(argv[1]));
//        cout << t.callNumber(atoi(argv[1])) << endl;
//        cout << t.powInt(atof(argv[1]), atoi(argv[2])) << endl;
//        vector<int> A = buildVector(argc, argv);
//        cout << t.trapRainWater(A) << endl;

//        cout << t.isScrambleStrings(string(argv[1]), string(argv[2])) << endl;
//        t.restoreIPAddress(string(argv[1]));
//        vector<int> A = buildVector(argc, argv);
//        shared_ptr<Leet::TNode> root = t.buildTree_LNodeRightNeighbor2(A);
//        t.printLNodeRightNeighbor(root);
//        t.connectLNodeRightNeighbor_anyTree(root);
//        t.printLNodeRightNeighbor(root);
//        cout << t.maxProfit_onebuysell(A) << endl;
//        cout << t.maxProfit_twobuysell(A) << endl;
//        cout << t.maxProfit_unlimit(A) << endl;
//        cout << t.maxProfit_kbuysell(A, 2) << endl;
//        cout << t.longestConsecutiveSequence(A) << endl;
//        cout << t.appearOnce_otherAppearThreeTimes_noextraspace(A) << endl;

//        string s(argv[1]);
//        unordered_set<string> dict;
//        dict.emplace("cat");
//        dict.emplace("dog");
//        dict.emplace("sand");
//        dict.emplace("cats");
//        dict.emplace("and");
//        cout << t.wordBreak_efficient(s, dict) << endl;
//        vector<string> res=t.wordBreak(s, dict);
//        copy(res.begin(), res.end(), ostream_iterator<string>(cout, " "));
//        cout << endl;
//        t.wordBreak(s, dict);
//        vector<int> A = buildVector(argc, argv);
//        shared_ptr<Leet::LNode> head = t.buildList(A);
//        t.reorderList(head);
//        vector<vector<int> > A{
//            {5,3,0,0,7,0,0,0,0},
//            {6,0,0,1,9,5,0,0,0},
//            {0,9,8,0,0,0,0,6,0},
//            {8,0,0,0,6,0,0,0,3},
//            {4,0,0,8,0,3,0,0,1},
//            {7,0,0,0,2,0,0,0,6},
//            {0,6,0,0,0,0,2,8,0},
//            {0,0,0,4,1,9,0,0,5},
//            {0,0,0,0,8,0,0,7,9}
//        };
//        if (!t.solveSudoku(A))
//            cout << "there is no solution" << endl;

//        vector<int> A = buildVector(argc, argv);
//        pair<int, int> res = t.findRangeofValue(A, 8);
//        cout << res.first << " " << res.second << endl;
//        t.nextPermutation(A);
//        copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//        vector<int> perm{2,0,1,3};
//        vector<int> A{0,1,2,3};
//        t.permuteArr(perm, A);
//        copy(perm.begin(), perm.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//        copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;

//        cout << t.longestValidParentheses(")(()()(()))())")<< endl;
//        vector<string> s{"abc", "foo", "xy", "uo", "bar","hk", "foo", "tyu"};
////        string s("barfoothefoobarman");
//        vector<string> dict{"foo", "bar"};
//        pair<int, int> res = t.minCoverage_stream(s, dict);
//        cout << res.first << " " << res.second << endl;
//        vector<int> res = t.substringWithAllWords(s, dict);
//        copy(res.begin(), res.end(), ostream_iterator<int>(cout, ":"));
//        cout << endl;
//        cout << t.strStr(string(argv[1]), string(argv[2])) << endl;
//        string res;
//        t.phoneNumberRepresentation(atoi(argv[1]), res);
//        vector<int> A = buildVector(argc, argv);
//        shared_ptr<Leet::LNode> head = t.buildList(A);
//        t.printList(head);
//        t.printList(t.reverseList_recursive(head));
//        head = t.buildList(A);
//        t.printList(t.reverseList_iterative(head));
//        head = t.buildList(A);
//        t.printList(t.reverseList_kgroup(head, 2));

//        t.threeSum(A);
//        vector<string> S{"abcde", "abcdg", "abx"};
//        cout << t.commonPrefix(S) << endl;
//        vector<int> heights = buildVector(argc, argv);
//        cout << t.findLargestContainer(heights) << endl;
//        cout << t.findLargestContainer_N(heights) << endl;
//        string s(argv[1]);
//        cout << t.zigzagConvert(s, 4) << endl;
//        vector<int> A{0,1,4,6};
//        vector<int> B{2,3,5};
//        cout << t.medianSortedArrayUnion(A, B) << endl;
//        vector<int> A = buildVector(argc, argv);
//        t.sortColor_onepass_constSpace(A, 2);
//        shared_ptr<Leet::TNode> tree = t.arrToTree(A, 0, A.size()-1);
//        t.recoverBST(tree);
//        vector<int> arr = t.treeToArr(tree);
//        copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;
//        vector<int> res = t.pascalTriangle(atoi(argv[1]));
//        copy(res.begin(), res.end(), ostream_iterator<int>(cout, " "));
//        cout << endl;

//        vector<vector<int> > A;
//        A.push_back({2});
//    A.push_back({3,4});
//A.push_back({6,5,7});
//A.push_back({4,1,8,3});

//        cout << t.triangle(A) << endl;
//        vector<string> res = t.grayCode(atoi(argv[1]));
//        copy(res.begin(), res.end(), ostream_iterator<string>(cout, " "));
//        cout << endl;
//        vector<int> A=buildVector(argc, argv);
//        cout << t.candyproblem(A) << endl;
//        vector<string> A{"4", "13", "5", "/", "+"};
//        cout <<A.size() << endl;
//        cout << t.evalReversePolishNotation(A) << endl;
//        cout << t.longestNonRepeatSubstr(string(argv[1])) << endl;
//    vector<int> A = buildVector(argc, argv);
//    A= t.maxSlidingWindow(A, 3);
//    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " "));
//    cout << endl;
    //    cout << t.paintersPartition(A, 3) << endl;
//    t.distanceMaximum(A) ;
//    t.distanceMaximum_nlogn(A) ;
    } catch (exception &e) {
        cout << e.what() << endl;
    }

//    cout << t.findLargestPalindromicSubstr(string(argv[1])) << endl;
//    cout << t.isPalindromeInt(atoi(argv[1])) << endl;
}

void testArrayString(int argc, char **argv) {
    ArrayString t;
    string r(argv[1]);
    string s(argv[2]);
//    cout << r << "-" << s << endl;
    cout << t.regexMatch(r, s) << endl;
//    t.replace_remove(s);
//    cout << s << endl;
}

void miscTest(int argc, char ** argv) {
    Misc mscTest;
    vector<int> A = buildVector(argc, argv);
    cout << mscTest.maxDiff_DP(A) << endl;
    cout << mscTest.maxDiff_divide(A) << endl;
    cout << mscTest.maxDiff_subArray(A) << endl;

//    mscTest.testprintA();
//    vector<vector<int> > A{{1,2,3}, {4,5,6}, {7,8,9}, {10,11,12}};
//    mscTest.printMatrixClockwisely(A);
//    vector<int> A = buildVector(argc, argv);
//    try {
//    cout << mscTest.findMajorityNum(A) << endl;
//    } catch (exception &e) {
//        cout << e.what() << endl;
//    }

//    cout << mscTest.getLongestSymmetrySubString(string(argv[1])) << endl;
//    mscTest.calcProbDices(atoi(argv[1]));
//    cout << endl;
//    mscTest.calcProbDices_DP(atoi(argv[1]));
//    cout << mscTest.addWithConstrains(atoi(argv[1])) << endl;
//    vector<int> a = buildVector(argc, argv);
//    cout << mscTest.minRotateSortArray(a) << endl;
//    mscTest.findMinIntCombination(a);
//    mscTest.printNDigits(atoi(argv[1]));
//    mscTest.printUglyNum(15);
//    cout << mscTest.findLongestCommonSubarray(string(argv[1]), string(argv[2])) << endl;
//    vector<int> pushV{1,2,3,4,5};
//    cout << mscTest.findLastElmentInRemove_efficient(pushV, atoi(argv[1])) << endl;
//    mscTest.findContinuousSequence3(15);
//    cout << endl;
//    mscTest.findContinuousSequence2(10, 15);
//    mscTest.ArrayToOddEvenArray(pushV);
//    vector<int> popV{4,5,3,1,2};
//    cout << mscTest.checkPushPop(pushV, popV) << endl;
}

void metaTest(int argc, char ** argv) {
        Meta mtest;
        vector<int> table{0, 1,5, 8,9,10};
        cout << mtest.maxRodCutting(4, table) << endl;
        vector<int> C{25, 5, 10,5, 10,5, 10,25,1,25,1, 25,1, 25,5, 10};
        for (auto &x: C)
            cout << x << ",";
        cout << endl;

    //    vector<vector<int> > T(C.size(), vector<int>(C.size(), -1));
    //    cout << mtest.coins_game(C, 0, C.size()-1, T) << endl;

    //    cout << mtest.calc_ways_walk_in2darray(atoi(argv[1]), atoi(argv[2])) << endl;
    //    Sorting stest;
    //    stest.testMaxNumTasks();
    //    stest.calcCharFrequency_nomap(string(argv[1]));
    //    stest.testCountPerson();
    //    OOP optest;
    //    optest.tail(string(argv[1]), atoi(argv[2]));
    //    Concurrency contest;
    //    contest.testCollatz(atoi(argv[1]));
    //    contest.testDataBuff();
    //    contest.testConsumerProducer();
    //    contest.testReaderWriter();
    //    contest.testDinnerPhilosophers();

    //    Meta testMeta;

    //    vector<Meta::Box> boxes;
    //    boxes.emplace_back(3,2,1);
    //    boxes.emplace_back(5, 7, 6);
    //    boxes.emplace_back(4, 3, 3);
    //    testMeta.buildTallestTower(boxes);
    //    string s10("1^0|0|1");
    //    cout<< testMeta.computeWaysParseExpression(s10, true) << endl;
    //    testMeta.findQueesPositions(atoi(argv[1]));
    //    testMeta.makeCoinSet(atoi(argv[1]));
    //    Graph testGraph;
    //    testGraph.findPath_test(3,3);
    //    Meta testMeta;
    //    cout << testMeta.multiply(atoi(argv[1]), atoi(argv[2])) << endl;
}

void graphTest(int argc, char ** argv) {
        Graph graphtest;
        vector<vector<int> > grapharr={{0, 2, 0, 6, 0},
                                  {2, 0, 3, 8, 5},
                                  {0, 3, 0, 0, 7},
                                  {6, 8, 0, 0, 9},
                                  {0, 5, 7, 9, 0},
                                 };
        graphtest.min_spanning_tree_Kruskal(grapharr);

        graphtest.testSCC();

        GraphList g(6);
        g.addEdge(5,2);
        g.addEdge(5,0);
        g.addEdge(4,0);
        g.addEdge(4,1);
        g.addEdge(2,3);
        g.addEdge(3,1);

        g.topologicalSort();
}

void moderateTest(int argc, char **argv) {
    Moderate modTest;
    unordered_set<string> dict;
    dict.emplace("is");
    dict.emplace("like");
    dict.emplace("brother");

    modTest.parseSentence2(string(argv[1]), dict);
//        vector<int> A = buildVector(argc, argv);
//    cout << modTest.findMaxSubarray(A) << endl;
//    cout << modTest.printInterger_better(atoi(argv[1])) << endl;

//    vector<int> A = buildVector(argc, argv);
//    modTest.findSubarrayToSorted(A);
//    modTest.masterMind(string(argv[1]), string(argv[2]));
//    cout << modTest.calcMax(atoi(argv[1]), atoi(argv[2])) << endl;
//    Meta mtest;
//    vector<vector<int> > G({{3, 0, 6, 5, 0, 8, 4, 0, 0},
//{5, 2, 0, 0, 0, 0, 0, 0, 0},
//{0, 8, 7, 0, 0, 0, 0, 3, 1},
//{0, 0, 3, 0, 1, 0, 0, 8, 0},
//{9, 0, 0, 8, 6, 3, 0, 0, 5},
//{0, 5, 0, 0, 9, 0, 6, 0, 0},
//{1, 3, 0, 0, 0, 0, 2, 5, 0},
//{0, 0, 0, 0, 0, 0, 0, 7, 4},
//{0, 0, 5, 2, 0, 6, 3, 0, 0}});
//    mtest.solve_Sudoku(G);
}

void hardTest(int argc, char **argv) {
        Hard htest;
//        vector<vector<int> > G={{0, 0, 0, 1, 0},
//                                  {1, 0, 0, 0, 1},
//                                  {0, 0, 0, 0, 1},
//                                  {0, 0, 0, 0, 1},
//                                  {0, 1, 0, 0, 0},
//                                 };
//        tuple<int, int, int> res = htest.findMaxBlackBorderSquare(G);
//        cout << get<0>(res) << " " << get<1>(res) << " " << get<2>(res) << endl;
//            vector<vector<int> > G={{0, 0, 0, 0, 0},
//                                      {0, 0, 3, 8, 5},
//                                      {0, 3, 0, 0, 7},
//                                      {0, 8, 0, 0, -9},
//                                      {0, -5, -7, -9, 0},
//                                     };
//            cout << htest.findMaxSub2DArray(G) << endl;

//        vector<string> arr{"b", "ib", "s", "bibs", "a", "bibss", ""};
//        htest.searchString_trie("bibs", arr);
        cout << htest.countDigit_bruteforce(atoi(argv[1]), atoi(argv[2])) << endl;
        cout << htest.countDigit_efficient(atoi(argv[1]), atoi(argv[2])) << endl;
//                vector<int> A = buildVector(argc, argv);
//        htest.shuffleCards(A, 3);
//        cout << htest.addTwoInts(atoi(argv[1]), atoi(argv[2])) << endl;
}

int test_graph(int argc, char ** argv)
{
    Graph test;
    vector<vector<bool> > maze = {{false, true, false},
                                 {false, false, false},
                                 {false, true, false}};
    vector<Coord> ret = test.findPath2DMaze(maze, Coord(0, 0), Coord(2,2));
    for (auto &x : ret) {
        cout << x.y << " " << x.x << endl;
    }
    ret = test.findPath2DMaze_BFS(maze, Coord(0, 0), Coord(2,2));
    for (auto &x : ret) {
        cout << x.y << " " << x.x << endl;
    }
//    vector<vector<int> > maze=test.buildMaze(argc, argv);
//    Coordinate start(0,0);
//    Coordinate exit(atoi(argv[1])-1, atoi(argv[2])-1);
//    test.printPathInMaze_BFS(maze, start, exit);
    return 0;
}

int test_meta(int argc, char **argv)
{
    vector<int> arr=buildVector(argc-1, &argv[1]);
    printVector(arr);

    int k=atoi(argv[1]);

    Meta test;
    cout << test.count_score_permutation(k, arr) << endl;
//    cout << test.MaxMarginCoinGame(arr) << endl;

    return 0;

}

vector<double> buildVectorDouble(int argc, char **argv)
{
    vector<double> output;
    for (int i=1; i<argc; i++)
    {
        output.push_back(atof(argv[i]));
        cout << output.back() << endl;
    }
    cout << endl;
    return output;
}

vector<int> buildVector(int argc, char **argv)
{
    vector<int> arr;
    for (int i=1; i<argc; i++)
        arr.push_back(atoi(argv[i]));
    return arr;
}

vector<string> buildVectorString(int argc, char **argv)
{
    vector<string> arr;
    cout << argc << endl;
    for (int i=1; i<argc; i++) {
        arr.push_back(string(argv[i]));
        cout << argv[i] << " " << arr.back() << endl;
    }
    return arr;
}

void printVector(const vector<int> &arr)
{
    for (int i=0; i< arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}

int test_priority_queue(int argc, char **argv)
{
    priority_queue<int, vector<int>, greater<int> > q;
    for (int i=1; i<argc; i++)
        q.push(atoi(argv[i]));

    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
    return 0;
}

int test_vector_cbegin(int argc, char ** argv)
{
    vector<int> arr;
    for (int i=1; i<argc; i++)
        arr.push_back(atoi(argv[i]));

    std::random_shuffle(arr.begin(), arr.end());
    printVector(arr);
    std::nth_element(arr.begin(), arr.begin()+(arr.size()>>1), arr.end());
    printVector(arr);
//    vector<int>::reverse_iterator it=arr.rbegin();
//    for (; it != arr.rend(); it++)
//        cout << *it << " ";
//    cout << endl;
    return 0;
}

int test_search(int argc, char **argv)
{
    Search test;
    cout << test.sqrt_bySearch(atoi(argv[1])) << endl;
    return 0;
}

int test_Primitive(int argc, char ** argv)
{
    Primitive test;
    cout << test.divided_x_y_efficient(atoi(argv[1]), atoi(argv[2])) << endl;
//    cout << test.stringToInt(string(argv[1])) << endl;
//    cout << test.intToString(atoi(argv[1])) << endl;
//    vector<int> A=buildVector(argc, argv);
//    vector<int> D;
//    test.print_power_set_k_recursive(A, 0, 2, D);
//    test.print_power_set_2(A);
//    cout << test.divided_x_y_efficient(atoi(argv[1]), atoi(argv[2])) << endl;
//    cout << test.add_no_operator(atoi(argv[1]), atoi(argv[2])) << endl;
//    vector<int> A(buildVector(argc, argv));
//    test.print_power_set_better(A);
//    cout << "--------" << endl;
//    test.print_power_set_2(A);

//    cout << test.parity_best(atoi(argv[1])) << endl;
//    cout << test.parity(atoi(argv[1])) << endl;
    return 0;

    cout << test.is_prime(atoi(argv[1])) << endl;
    return 0;

    cout << test.sqrt_no_operator(atoi(argv[1])) << endl;
//    cout << test.multiply_no_operator(atoi(argv[1]), atoi(argv[2])) << endl;
    return 0;

    vector<int> result = test.generate_primes_from_1_n(atoi(argv[1]));

    for (int i=0; i<result.size(); i++)
        cout << result[i] << endl;
    return 0;

    cout << test.GCD(atoi(argv[1]), atoi(argv[2])) << endl;
    return 0;

    try
    {
//        cout << test.convert_base(string(argv[1]), atoi(argv[2]), atoi(argv[3])) << endl;
        vector<unsigned int> arr;
        for (int i=1; i<argc; i++)
        {
            arr.push_back(atoi(argv[i]));
        }
        string s=test.encode_ints_to_string(arr);
        cout << s << endl;
        vector<unsigned int> result = test.decode_string_to_ints(s);

        for (int i=0; i<result.size(); i++)
            cout << result[i] << endl;

//        cout << endl;

//        vector<int> oneset;
//        test.print_power_set(arr, 0, oneset);
//    cout << test.closest_int_same_bits(atoi(argv[1])) << endl;
    }
    catch (string & e)
    {
        cout << e << endl;

    }

    return 0;
}

