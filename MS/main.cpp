#include "tree.h"
#include <iostream>
#include "misc.h"
#include "search.h"
#include <vector>
#include <set>
#include "mystring.h"
//#include <stack>
#include "mylist.h"
#include <typeinfo>
#include <stack>
#include "stack.h"
#include <bitset>
#include "bits.h"
#include "limits.h"
#include "mytrie.h"
#include "randomnum.h"
#include <thread>
#include <future>
#include "recursion.h"
#include "matrix.h"
#include "mysort.h"
#include "test.h"
#include "myarray.h"
#include <sstream>

using namespace std;

void testIsBST(int *seq, int length)
{
    Tree test(seq, length);
    test.inorder();
    int t=INT_MIN;
    shared_ptr<TreeNode> node = test.getRootNode();
    cout << test.isBST_main(node) << endl;
}

int SizeOf(char *pString)
{
    cout << pString << endl;
    return sizeof(pString);
}

int main(int argc, char ** argv )
{
    if (argc<2)
    {
        cout << "No input argument" << endl;
        return -1;
    }

    cout << Misc::concatenateInts(atoi(argv[1]), atoi(argv[2])) << endl;
    return 0;

    cout << Microsoft::sqrtImplementation(atoi(argv[1]), 20) << endl;
    return 0;
        vector<int> data(argc-1);
        for (int i=1; i<argc; i++)
        {
            data[i-1]=atoi(argv[i]);
    //        cout << data[i-1] << " ";
        }

        MyList mylist(data);
        mylist.printList();
        cin.get();
        mylist.alternateNodes();
        cin.get();
        mylist.printList();
//    MyArray::printSubarrayWithSumClose0(data);
//    MyArray::printMaxElementsOfSubArray(data, 3);
    return 0;
//    cout << Microsoft::sqrtImplementation(double(atoi(argv[1])),atoi(argv[2])) << endl;
//    return 0;

//    Microsoft::sortBigData(data, true);

//    vector<vector<int> > arr;
//    int seq[]={2,33,55};
//    vector<int> v(seq, seq+3);
//    int seq1[]={29,30,88};
//    vector<int> v1(seq1, seq1+3);
//    int seq2[]={2,5,100};
//    vector<int> v2(seq2, seq2+3);
//    arr.push_back(v);
//    arr.push_back(v1);
//    arr.push_back(v2);

//    Microsoft::sortMultipleArray(arr);

//    vector<vector<int> > arr;
//        int seq[]={1,1,0};
//        vector<int> v(seq, seq+3);
//        int seq1[]={1,1,0};
//        vector<int> v1(seq1, seq1+3);
//        int seq2[]={1,0,0};
//        vector<int> v2(seq2, seq2+3);
//        arr.push_back(v);
//        arr.push_back(v1);
//        arr.push_back(v2);
//    cout << Amazon::findBiggestX(arr) << endl;

//    Tree t;
//    int index=0;
//    string x("a<b<e<>>c<>d<f<>>>");
//    shared_ptr<TreeNode> node =t.deserializeTree(x, index);
//    cout << endl;
//    t.printDFSChildren(node);

//    Amazon::printSourceCode();
//    string arr(argv[1]);
//    Amazon::sortStringWithMap(string(argv[2]), string(argv[1]));
//    cout << Amazon::caclNumToSwapBits(arr) << endl;
//    vector<string> data(argc-1);
//    for (int i=1; i<argc; i++)
//    {
//        data[i-1]=string(argv[i]);
//        cout << data[i-1] << " ";
//    }
//    cout<< endl<< endl;

////    e.g. “rat”, ”cat”, “abc”, “xyz”, “abcxyz”, “ratcatabc”, “xyzcatratabc”
//    cout << Amazon::findWordMadeOfMaxWords(data) << endl;
//    return 0;

//    Amazon::printAnagrams(data);

//    Amazon::printNumbersWithDigitDiff1(atoi(argv[1]));
//    return 0;
//    cout << Amazon::compressString(string(argv[1])) << endl;

//    istringstream x(string(argv[1]));
//    int value;
//    istringstream(string(argv[1])) >> value;
//    cout << atoi(string(argv[1]).c_str()) << endl;

//    1 1 1 1 1 1
//    0 0 0 0 1 0
//    1 1 0 0 0 1
//    1 0 0 0 0 0
//    1 1 1 0 0 0
//    vector<vector<int> > arr;
//    int seq[]={1,1,1,1,1,1};
//    vector<int> v(seq, seq+6);
//    int seq1[]={0,0,0,0,1,0};
//    vector<int> v1(seq1, seq1+6);
//    int seq2[]={1,1,0,0,0,1};
//    vector<int> v2(seq2, seq2+6);
//    int seq3[]={1,0,0,0,0,0};
//    vector<int> v3(seq3, seq3+6);
//    int seq4[]={1,1,1,0,0,0};
//    vector<int> v4(seq4, seq4+6);
//    arr.push_back(v);
//    arr.push_back(v1);
//    arr.push_back(v2);
//    arr.push_back(v3);
//    arr.push_back(v4);

//    Amazon::numBagHoldBarCodes_better(arr);
//    Amazon::printLongestSnake(arr);

//    Amazon::printMatrixFromOutToInside(arr);

//    cout << Amazon::numBagHoldBarCodes(arr) << endl;

//    cout << isPushPopMatch(pushVect, popVector) << endl;

//    Misc::computeProbabilitiesOfDiceSum(atoi(argv[1]));
//    return 0;
//            vector<int> data(argc-1);
//                for (int i=1; i<argc; i++)
//                {
//                    data[i-1]=atoi(argv[i]);
//                    cout << data[i-1] << " ";
//                }
//                cout<< endl<< endl;

//                MySort::mergeSort(data, 0, data.size()-1);

//                for (int i=0; i<data.size(); i++)
//                {
//                    cout << data[i] << " ";
//                }
//                cout<< endl<< endl;


//    int seq0[]={1,3,4,7,8};


//    MyList list0(seq0, 5);
//    int seq1[]={2,5,6,7,9};
//    MyList list1(seq1, 5);

//    list0.printList();
//    list1.printList();

//    shared_ptr<Node> node0=list0.getHead();
//    shared_ptr<Node> node1=list1.getHead();
//    shared_ptr<Node> mlist=list0.mergeLists(node0, node1);

//    while(mlist)
//    {
//        cout << mlist->value << " ";
//        mlist=mlist->pNext;
//    }

//    vector<vector<int> > arr(5, vector<int>(4, 0));
//    Matrix t;
//    t.findPathBetweenPoints(arr, Point2D(2,0), Point2D(4,3));
//        Tree t(atoi(argv[1]), atoi(argv[2]));
//        t.printTreeWithLevel();
//        t.printTreeFrame();

//        cout << t.checkBalanceTree2() << endl;

//    stack<int> t;
//    for (int i=0; i<argc-1; i++)
//        t.push(atoi(argv[i+1]));

//    sortStack2(t);
//    printStack<int>(t);
//    sortStack2<int>(t);

//    printStack<int>(t);

//    Tree t(atoi(argv[1]), atoi(argv[2]));
//    t.printTree();
//    shared_ptr<TreeNode> node=t.findFirstCommonAncestor2(t.getRootNode(), atoi(argv[3]), atoi(argv[4]) );
//    cout << node->value << endl;

//    map<int, string> table = Misc::buildMapFromNumToExcelHeader();
//    cout << Misc::mapNumToExcelHeader(atoi(argv[1]), table) << endl;
//    return 0;
//    int len=argc-1;
//    int *seq=new int [len];
//    for (int i=0; i<len; i++)
//        seq[i]=atoi(argv[i+1]);

//    MyList t(seq, len);
//    t.printList();
//    shared_ptr<Node> head=t.getHead();
//    t.printListReverse2(head);
//    t.deleteDup2();
//    t.printList();

//    delete []seq;
//    cout << Misc::divide(atoi(argv[1]), atoi(argv[2])) << endl;

//    int *a=new int [argc-1];
//    for (int i=1; i<argc; i++)
//    {
//        a[i-1]=atoi(argv[i]);
//        cout << a[i-1] << " ";
//    }
//    cout << endl;
//    Misc::radixsort(a, argc-1);
//    cout << endl;

//    delete []a;

//    int N=atoi(argv[1]);
//    int M=atoi(argv[2]);
//    cout << Misc::powerInt(N, M) << endl;
//    Bits::insert2(N, M, 2, 6);
//    cout << Bits::printBit(atoi(argv[1])) << endl;
//    return 0;
//    vector<string> result;
    Recursion t;
    vector<int> comb(4, 0);
    cout << t.combinationOfCoins(atoi(argv[1]), 0, comb) << endl;
    return 0;
//    t.HanoiTower(atoi(argv[1]));

//    t.testBuildTower(argc, argv);
//    t.getQueenPosition();

//    set<string> result=t.getAllParentheses(atoi(argv[1]));
//    for (set<string>::iterator itr=result.begin(); itr!=result.end(); itr++)
//        cout << *itr << endl;
//    return 0;

//    string str(argv[1]);
//    t.getPermutation(str, 0, result);
//    for (int i=0; i<result.size(); i++)
//    {
//        cout << result[i] << endl;
//    }
//    return 0;

//        vector<int> data(argc-1);
//            for (int i=1; i<argc; i++)
//            {
//                data[i-1]=atoi(argv[i]);
//                cout << data[i-1] << " ";
//            }
//            cout<< endl<< endl;

//      Recursion t;
//      vector<vector<int> > result=t.getSubSet(data, 0);

//      for (int i=0; i<result.size(); i++)
//      {
//          for (int j=0; j<result[i].size(); j++)
//          {
//              cout << result[i][j] << " ";
//          }
//          cout << endl;
//      }


//    Search t;
//    cout << t.findMagicIndex_nondistinctiveIntegers(data, 0, data.size()-1) << endl;
//    Recursion r;
//    int rows=3;
//    int cols=3;
//    vector<vector<int> > board(rows);
//    for (int i=0; i<rows; i++)
//        board[i]=vector<int>(cols, 0);
//    board[0][1]=1;

//    map<pair<int,int>, int> table;

//    r.print2DPath(board, 2, 1, 0, 0);


//    map<int, int> table;
//    cout << r.countWaysofStair(-1, table) << endl;
//    cout << r.countWaysofStair(0, table) << endl;
//    cout << r.countWaysofStair(1, table) << endl;
//    cout << r.countWaysofStair(2, table) << endl;
//    cout << r.countWaysofStair(3, table) << endl;
//    cout << r.countWaysofStair(4, table) << endl;

//    Tree t;
//    shared_ptr<TreeNode> rootptr=t.getRootNode();
//    for (int i=1; i<argc-1; i++)
//    {
//        t.buildBSTreeWithStream(rootptr, atoi(argv[i]));
//    }

//    t.printStreamBSTree(rootptr);

//    cout << t.getRankOfStreamBSTree(rootptr, atoi(argv[argc-1])) << endl;
//    Misc t;
//    t.testBuildTower(argc, argv);
//    return 0;
}
//    vector<vector<int> > arr;
//    int r0[]={15, 20, 70, 85};
//    int r1[]={20, 35, 80, 95};
//    int r3[]={30, 55, 95, 105};
//    vector<int> v1(r0, r0+4);
//    arr.push_back(v1);
//    v1=vector<int>(r1,r1+4);
//    arr.push_back(v1);
//    v1=vector<int>(r3, r3+4);
//    arr.push_back(v1);

//    Search t;
//    CellPosition x = t.findNumIn2DArray(arr, 105, CellPosition(0, 0), CellPosition(arr.size(), arr[0].size()));
//    x.print();

//    return 0;
//}
//    vector<int> data(argc-1);
//        for (int i=1; i<argc; i++)
//        {
//            data[i-1]=atoi(argv[i]);
//            cout << data[i-1] << " ";
//        }
//        cout << endl;

//        Search t;
//        string input;
//        while (true)
//        {
//            cout << "enter the targeted num: ";
//            getline(cin, input);
//            cout << t.findNumInRotatedSortedArray(data, 0, data.size()-1, atoi(input.c_str()));
//            cout << endl;
//        }
//        return 0;
        //    vector<string> words(argc-1);
//    for (int i=1; i<argc; i++)
//        words[i-1]=argv[i];

////    MyString::printWords(words);
//    MyString::sortAnagramsByhashing(words);
//    return 0;

//    int a[]={1,3,5,7};
//    int b[]={2,4,6};
//    vector<int> dataA(a,a+4);
//    vector<int> dataB(b,b+3);
//    Search t;
//    t.mergeTwoSortedData(dataA, dataB);

//    set<string> dict;
//    dict.insert("looked");
//    dict.insert("just");
//    dict.insert("like");
//    dict.insert("her");
//    dict.insert("brother");

//    string test(argv[1]);
//    string result;
//    int m=Misc::unconcatenating(test, dict, result);
//    cout << m << ":" << result << endl;

//    cout << (int)atoi(argv[1]) << endl;
//    Misc::printNumbers(atoi(argv[1]));
//    vector<int> data(argc-1);
//    for (int i=1; i<argc; i++)
//    {
//        data[i-1]=atoi(argv[i]);
//        cout << data[i-1] << " ";
//    }
////    for (const int & x: data) cout << x << endl;
////    cout << "show table is done" << endl;

//    cout << endl;
//    Misc::printAllPairsWithTargetSum(data, 10);
//    cout << Misc::findMinDistanceToSort(data) << endl;
//    string a(argv[1]), b(argv[2]);
//    Misc::guessHitGame(a, b);
//    int a=atof(argv[1]), b=atof(argv[2]);
//    cout << a << "," << b << endl;
//    cout << Misc::getMaxWithoutIf(a, b) << endl;

//    int a=strtol(argv[1], pend, 10);
//    int b=strtol(argv[2], pend, 10);
//    Misc::swapTwoNumbers(a, b);
//    cout << a << "," << b << endl;
//    return 0;

//    int seq[]={1,2,3,4,0,9};
//    vector<int> seqVector(seq, seq+6);
//    Misc::getMedianInStream(seqVector);
//    int x=atoi(argv[1]);
//    int y=atoi(argv[2]);
//    cout << x << "," << y << endl;
//    cout << Bits::addTwoNum(x, y) << endl;
//    RandomNum t;
//    t.shuffleCards(52);

//    TrieString mytrie;
//    string word("bibs"), sub(argv[1]);
//    mytrie.addString(word);
//    vector<int> position= mytrie.searchString(sub);
//    if (position.empty())
//    {
//        cout << "no found" << endl;
//        return 0;
//    }
//    cout << "find at ";
//    for (int i=0; i<position.size(); i++)
//    {
//        cout <<  position[i] << " ";
//    }
//    cout << endl;
//    return 0;

//    MyTrie mytrie;
//    char word[]="hello";
//    mytrie.addWord(word);

//    mytrie.addWord("hell");
//    mytrie.addWord("ballon");
//    mytrie.addWord("ballet");
//    mytrie.addWord("ball");

////    mytrie.printTrie(mytrie.getRoot());

//    cout << mytrie.searchWord("hello") << endl;
//    cout << mytrie.searchWord("hell")<< endl;
//    cout << mytrie.searchWord("ballon") << "," << mytrie.searchWord("ball")<< mytrie.searchWord("ballo")<< endl;

//    char str[]="abc";
//    vector<char> seq;
//    MyString::combination_2(str, seq);

//    char str1[]="hello world";
//    char str2[]="hello world";
//    char *str3="hello world";
//    char *str4="hello world";
//    int arr[]={1,2,3,4};
//    cout << "strlen=" << strlen(str1) << endl;
//    cout << "strlen str3=" << strlen(str3) << endl;
//    if (str1==str2)
//        cout << "str1 equals str2"<< endl;
//    else
//        cout << "str1 not equals str2" << endl;

//    if (str3==str4)
//        cout << "str3 equals str4"<< endl;
//    else
//        cout << "str3 not equals str4" << endl;

//    return 0;


//    int ages[] = {2,4,1,16,7,5,-11,9};
//    int k=sizeof(ages)/sizeof(int);
//    cout << Misc::getMaxDiff(ages, k) << endl;
//    try{
//        Search::sortAge(ages, k);
//        for (int i=0; i<k; i++) cout << ages[i] << ' ';
//        cout << endl;

//    }
//    catch (exception &e)
//    {
//            cout << e.what() << endl;
//    }
//    char str1[] = "hello world";
//    char str2[] = "hello world";
//    char* str3 = "hello world";
//    char* str4 = "hello world";
//    if(str1 == str2)
//    printf("str1 and str2 are same.\n");
//    else
//    printf("str1 and str2 are not same.\n");
//    if(*str3 == *str4)
//    printf("str3 and str4 are same.\n");
//    else
//    printf("str3 and str4 are not same.\n");

    //	return 0;


            //    Bits *test=NULL;
//    test->printTest();
//    int k=10;
//    int seq[10];
//    for (int i=0; i<k;  i++)
//        seq[i]=i;
//    Tree test(seq, sizeof(seq)/sizeof(int));
//    vector<list<shared_ptr<TreeNode> > > result= test.getLevelLists();
//    test.printLevelLists(result);

//    test.findFirstCommonNodeWithAdditionalSpace(7, 9);
//    test.findFirstCommonAncestor(test.getRootNode(), 7, 9);

//    MyList test(seq, sizeof(seq)/sizeof(int));
//    test.printList();
//    test.deleteDups();
//    test.printList();
//    double x=3.875;
//    string y=Bits::convertDecimalToBinary(x);
//    cout << y << endl;

//    int M=32, N=5;
//    cout << bitset<16>(M) << endl << bitset<16>(N) << endl;

//    Bits::insert(M, N, 2, 4);
//    cout << bitset<32>(M) << endl;



//    string mystring=y.to_string<char, char_traits<char>, allocator<char> >();
//    cout << mystring << endl;
//    cout << Bits::printBit(k).c_str() << endl;
//    cout << string("test") << endl;

//    Tree test(1, 10);
////    test.BDS();
////    test.findFirstCommonAncestor(test.getRootNode(), 7, 4);
////    cout << endl;
//    vector<list<shared_ptr<TreeNode> > > result= test.getLevelLists();
//    test.printLevelLists(result);
//    vector<int> path;
//    test.findSumPath(test.getRootNode(), 10, path);


//    stack<int> test;
////    Stack<int>::simulateHanoiTower(6);
//        int seq[]={4,3,6,7,8,1,0};

//    for (int i=0; i< 7; i++)
//        test.push(seq[i]);

//    Stack<int>::sortStack(test);
//    Stack<int>::simulateHanoiTower(i);



    //    int seq[]={4,3,6,7,8,1,0};
//    stack<int> mystack;
//    int k=sizeof(seq)/sizeof(int);
//    for (int i=0; i<k; i++)
//        mystack.push(seq[i]);

//    Stack<int>::reverseStack(mystack);

//    for (int i=0; i<k; i++)
//    {
//        cout << mystack.top() << endl;
//        mystack.pop();
//    }

//    char seq[]="They are students.";
//    MyString::deleteChars(seq,"aeio");

//    int seq[]={1,2,3,3,5,5,6,6, 2, 10};
//    int x=0, y=0;
//    Search::findOnceNumBetter(seq, sizeof(seq)/sizeof(int), x, y);
//    cout << x << ':' << y << endl;
//    test.printList();

////    for (int i=7; i>=0; i--)
//        for (int i=-1; i<7; i++)
//    {
//        test.deleteNode(i);
//        test.printList();
//    }

    //    char seq[]="1234abc";
//    CMyString test(seq);
//    cout << test.getData() << endl;
//    CMyString test2(test);
//    cout << test2.getData() << endl;

//    CMyString test3("098");
//    cout << test3.getData() << endl;
//    test2=test3;
//    cout << test3.getData() << endl;


//    // testCases: nullptr, BST, NonBST
//    testIsBST(nullptr, 0);

//    // testCase: BST
//    int seq[]={1,2,3,4,5};
//    testIsBST(seq, sizeof(seq)/sizeof(int));

//    // testCase: nonBST
//    int seq3[]={1,2,3,4,1};
//    testIsBST(seq3, sizeof(seq3)/sizeof(int));

//    int **Seq=new int * [3];

//    Seq[0]=nullptr;
//    int s[]={1,2,3,4,5}; Seq[1]=s;
//    int s2[]={2,3,4,1,6}; Seq[2]=s2;

//    for (int i=0; i<3; i++)
//    {
//        Tree test(Seq[i], sizeof(Seq[i])/sizeof(int));
//        cout << "tree inorder: " << endl;
//        test.inorder();
//        int t=INT_MIN;
//        cout << "BST: " << test.isBST(test.getRootNode(), t) << endl;
//    }
    // test
//    int seq[]={1,5,3,4,5,6};
//    Tree test(seq, sizeof(seq)/sizeof(int));
//    test.inorder();
//    int seq[]= {1,2,3,4,5};
//    cout << typeid(seq).name() << endl;
//    cout << typeid(1.4567).name() << endl;
//    cout << typeid(float).name() << endl;
//    MyList x(seq, sizeof(seq)/sizeof(int));
//    x.printList();
//    shared_ptr<Node> t;
//    for (int i=-1; i< 7; i++)
//    {
//        t=x.findNthToLast(i);
//        if (t)
//            cout << i << ':' <<  t->value << endl;
//        else
//            cout << "n is not right" << endl;
//    }
    //    // test reorderOddEven
//    int seq[]={1,2,3,4,5,6,7};
//    Misc::reorder(seq, sizeof(seq)/sizeof(int));

    // test permutation of a string
//    char str[]="abc";
//    MyString::combination(str);
//    MyString::permutation(str);

//    for (int i=-1; i<9; i++)
//    {
//    Tree test(1,i);
//    cout << test.getTreeDepth(test.getRootNode()) << ":" << test.getTreeDepth_2(test.getRootNode()) << endl;
//    }
    //    for (int i=-1; i< 15; i++)
//    Misc::sequenceSum(15);
//    cout << Misc::jumpStair_main(-20) << endl;
//    cout << Misc::jumpStair_main(1) << endl;
//    cout << Misc::jumpStair_main(2) << endl;
//    cout << Misc::jumpStair_main(3) << endl;
//    cout << Misc::jumpStair_main(4) << endl;

//    cout << Misc::numOfOnes(10) << endl;

//    char str[]="acdef";
//    MyString::rotation(str, 12);
//    cout << str << endl;

//    try
//    {
//    for (int i=-1; i<8; i++)
//    cout << Misc::fibonacci(i) << ':';

//    cout << endl;
//    }
//    catch (exception &e)
//    {
//        cout << e.what() << endl;
//    }

//    Tree test(1,9);
//    test.BDS();
//    test.mirrorBST_iterative(test.getRootNode());
//    test.BDS();
//    return 0;
//}

void printNum(int num)
{
    if (num==0) return;
    printNum(num/10);
    int x=num%10;
    cout << x << ' ';
}

char *lastchar(char *String, char ch)
{
    char *pStr = NULL;

    // traverse the entire string

    while( * String  != '\0' )
    {
        if( *String == ch )
            pStr = String;
        String++;
    }

    return pStr;
}

void testLCS()
{
    char seq1[]="BDCABA";
    char seq2[]="ABCBDAB";

    MyString::LCS(seq2, seq1);
    MyString::LCSubstring(seq1, seq2);

}

void testFindTwoNumbersWithSum()
{
    int test[]={1, 2,3,4,5,6,7,7};
    if (!Search::findSumOfTwoNumbers(test, sizeof(test)/sizeof(int), 8))
        cout << "there are not two numbers whose sum is targetSum" << endl;

}

void testVerifySeqOfBST()
{
    int numArray[]={5,7,6,9,11,10,8};

    int nums = sizeof(numArray)/sizeof(int);
    cout << "The BST sequence is =" << Tree::verifySequenceOfBST(numArray, nums) << endl;

}

void testMiscFindKLeastNumbers()
{
    int numArray[]={4, 10, 7, 5, 12, 0, 6, 3, 5, 5,5,5};

    vector<int> data(numArray, numArray+sizeof(numArray)/sizeof(int));
    multiset<int> leastNums;
    Misc::findKLeastNumbers(data, leastNums, 6);

}

void testMiscFindGreatestSumofSubArrary()
{
    int testArray[]={1, -2, 3, 10, -4, 7, 2, -5};
    int greatestSum;
    if (Misc::findGreatestSumOfSubArray(testArray, sizeof(testArray)/sizeof(int), greatestSum))
        cout << greatestSum << endl;

}

void testSort()
{
    int numArray[]={4, 10, 7, 5, 12, 0, 6, 3};
    Search::print(numArray, sizeof(numArray)/sizeof(int));
//    Search::mergeSort(numArray, 0, sizeof(numArray)/sizeof(int)-1);
    Search::quickSort(numArray, 0, sizeof(numArray)/sizeof(int)-1);
    Search::print(numArray, sizeof(numArray)/sizeof(int));

    try
    {
        cout << Search::BinarySearch(numArray, -1, 0, sizeof(numArray)/sizeof(int)-1) << endl;
    }
    catch (exception & e)
    {
        cout << e.what() << endl;
    }

}

void testStack()
{
    Stack<int> test;
    int data[] = {3,4,2,1, 0,0,2,3,1};

    for (int i=0; i<sizeof(data)/sizeof(int); i++)
    {
        test.push(data[i]);
        cout << test.minValue() << " ";
    }
    cout << endl;
//    cout << test.getDataSize() << endl;
    for (int i=0; i<8; i++)
    {
        test.pop();
        cout << test.minValue() << " ";
    }
    cout << endl;
}

void testTree()
{
    int numArray[]={4, 5, 7, 10, 12};
    Tree test(numArray, 5);
    test.preorder();
    test.BDS();

    list<int> path;
    int curSum=0;
    test.findPath(test.getRootNode(), 16, path, curSum);

}
