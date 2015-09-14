#ifndef META_H
#define META_H

#include <vector>
#include "utilities.hpp"
#include <atomic>
#include <unordered_set>
#include <list>

using namespace std;

class Meta
{
public:
    Meta();

    //5.25
    class TournamentTree {
        struct TourNode {
            double cap;
            vector<int> items;
            TourNode(double _cap) : cap(_cap) {}
        };
        vector<TourNode> tree_;

        void insert_helper(int idx, int item, double cap) {
            int left = (1<<idx)+1, right = (1<<idx)+2;
            if (left<tree_.size()) {
                insert_helper(tree_[left].cap>cap ? left : right, item, cap);
                tree_[idx].cap = max(tree_[left].cap, tree_[right].cap);
            }
            else {
                tree_[idx].cap -= cap;
                tree_[idx].items.emplace_back(item);
            }

        }

    public:
        TournamentTree(int n, double capacity) : tree_((1<<n)-1, TourNode(capacity)) {
        }

        void insert(int item, double cap) {
            insert_helper(0, item, cap);
        }
    };

    // 15.22
    struct Tutor {
        int start, startLesson;
        Tutor(int x, int y) : start(x), startLesson(y) {}
        bool operator<(const Tutor & that) const {
            return start != that.start ? start < that.start : startLesson <that.startLesson;
        }
    };
    vector<vector<bool> > jobAssignment_clientsSevers(const vector<int> &tasks, const vector<int> &servers);
    int min_tutor(vector<int> requests);

    vector<int> loadBalance(const vector<int> &files, int nServer);

    bool stringConstruct(string s, const unordered_set<string> &D);
    bool matchSequnce2DArray(const vector<vector<int> > &A, const vector<int> &S);
    int maxSubarrayInCyclicArray(const vector<int> &A);

    //17.10
    list<int> min_expression_seq(int n);

    //17.
    bool check_Collatz(int n);
    bool check_Collatz_recursive(int n);

    //17.8
    bool solve_Sudoku(vector<vector<int> > &G);
    struct Jug {
        int low, high;
    };

    struct PairEqual {
        bool operator()(const pair<int, int> &x, const pair<int, int> &y) const {
            return x.first==y.first && x.second==y.second;
        }
    };

    struct PairHash {
        int operator()(const pair<int, int> &x) const {
            return hash<int>()(x.first) ^ hash<int>()(x.second);
        }
    };

    bool fillMilk(const vector<Jug> &J, int L, int H);

    // use the above idea
    // 1.define Vertex with vector<tuple<shared_ptr<Vertex>, int(cost), int(delay)> > edges;
    // 2. main function: int main(shared_ptr<Vertex> &src, shared_ptr<Vertex> & des, int delay);
    // 2. using shortest path algorhtm with weight as value+lamda*delay (langrange parameter), or
    //              use value as weight and with delay as hard constraint to decide whether push or skip
    //
    //recursive function: int helper(shared_ptr<Vertex> &root, shared_ptr<Vertex> & dsc, int delay, unordered_map<shared_ptr<Vertex>, int> > &table);
    //                        if (delay<0 || root==nullptr ) return INT_MAX;
    //                        else if (table.find(root)!=table.end()) return table.find(root)->second;
    //                        else if (root==dsc) return 0;
    //                        int minV=INT_MAX;
    //                        for (auto &x : root->edges)
    //                          {    int v=get<2>(x)+helper(get<1>(x), delay-get<3>(x), table);
    //                               if (minV>v) {minV=v;}
    //                          }
    //                        table.emplace(root, minV);
    //                        return minV;
    void findShortestPathWithDelayConstraint(){}

    int maxRodCutting(int len, vector<int> & table);

    struct Box {
        int w, h, d;
        static atomic<int> count;
        int id;
    public:
        Box(int width, int height, int depth) : w(width), h(height), d(depth), id(++count) { }

        bool operator<(const Box & that) const {
            return w>that.w;
        }
    };

    //15.17
    int max_fish(vector<vector<int> > &A);

    //15.18
    int coins_game(vector<int> &C, int a, int b, vector<vector<int> > &T);

    //15.15
    int score_combination(int k, vector<int> & scores);
    int score_permutation(int k, vector<int> & scores);

    int compute_binomial_coefficients(int n, int k);

    //15.16
    int calc_ways_walk_in2darray(int n, int m);
    int calc_ways_walk_in2darray_obstacle(const vector<vector<int> > &B);

    //15.11
    int levenshtein_distance(string A, string B);

    //15.12
    vector<string> word_breaking(string s, unordered_set<string> & dict);
    vector<string> word_breaking_better(string s, unordered_set<string> & dict);

    //15.13
    int find_pretty_print(const vector<string> & words, int L);

    template<typename T>
    double calc_tree_diameter(const unique_ptr<TreeNode<T> > &root);

    vector<Box> buildTallestTower(vector<Box> Boxes);

    vector<vector<int> > findQueesPositions(int chessSize);

    int computeWaysParseExpression(const string &exp, bool result);

    // makecoinchange
    vector<vector<int> > makeCoinSet(int n);

    // build  parenthesis pairs
    vector<string> generateParentheses(int count);

    // pick up coins from the last items of the line
    int MaxMarginCoinGame(std::vector<int> & arr);

    // pick up coins from the ends of the line
    int maxMargin_pick_up_coins(const vector<int> & coins);

    // combination: the number of combinations to select k elements from n elements
    int compute_combination_without_overflow(int n, int k);

    // combination: count the ways to get a score, with a set of score ways, e.g., (2,3,7) for football
    int count_score_combination(int k, const std::vector<int> & score_ways);

    int count_score_permutation(int k, const std::vector<int> & score_ways);
//    int count_score_permutation_const_space(int k, const std::vector<int> &score_ways);

    // problem 15.2
    template<typename T>
    int count_inverted_pairs(vector<T> & arr);

    pair<PointA, PointA> findClosestPoints(vector<PointA> & arr);

    int findMaxSumSubCircularArray(const vector<int> & arr);

    int findLongestNonDescreaseSubSequence(vector<int> &arr);
    vector<int> findLongestNonDescreaseSubSequence_vect(vector<int> &arr);

    int findLongestAlternatingSubSequence(vector<int> & arr);

    int findLongestBitonicSubSequence(vector<int> &arr);

    void findNonNegativeSubArraySumToK(vector<int> &arr, int k);

    // problem 15.7 but not use efficient frontier point
    pair<int, int> findLongestSubarrySumLessEqualK(vector<int> & arr, int k);
    pair<int, int> findLongestSubarrySumLessEqualK_queue(const vector<int> &A, int k);
    pair<int, int> findLongestSubarrySumLessEqualK_withoutqueue(const vector<int> &A, int k);

    ////**********************
    void findLongestSubArraySumLessThanK_general(vector<int> &arr, int k);

    int findLargestRectangleforArray(vector<int> & arr);
    //14.8 O(n)
    int findLargestRectangleforArray_linearTime(vector<int> & arr);

    /// problem
    int computeMaxRectangleMatrix(vector<vector<bool> > &arr);
    int computeMaxSquareMatrix(vector<vector<bool> > &arr);
    int computeMaxRectangleMatrix_mn(vector<vector<bool> > &arr);

    // 0-1 knapsack problem: 17.1, 17.2
    void knapsack(vector<pair<int, int> > & sweets, int weightlimit);

    struct Clock {
        int weight, value;
    };

    int knapsack_clock(vector<Clock> &G, int capacity);
    void knapsack_clock_2(vector<Clock> &G, int capacity);

    bool checkPresidentEletionTie(vector<int> & votelist);

    int multiply(int a, int b);

    // 15.10
    bool matchStringIn2DArrary(const vector<vector<int> > &A, const vector<int> &s);

//    struct Tutor {
//        int start;
//        vector<int> schedule;
//        Tutor(int _start) : start(_start) {
//            schedule.push_back(_start);
//        }
//        bool insertLesson(int lessonStart) {
//            if (lessonStart-start>2*60)
//                return false;
//            for (auto &x :schedule) {
//                if (x==lessonStart)
//                    return false;
//            }
//            schedule.push_back(lessonStart);
//            return true;

//        }
//    };

//    int needingTutors(vector<int> &lessons) {
//        vector<Tutor> tutors;
//        for (auto & lesson: lessons ) {
//            int i=0;
//            for (; i<tutors.size(); i++) {
//                if (tutors[i].insertLesson(lesson))
//                    break;
//            }
//            if (i==tutors.size()) {
//                tutors.push_back(Tutor(lesson));
//            }
//        }
//        return tutors.size();
//    }

};

//class Square {
//public:
//    PointA leftTop, rightBottom, mid;
//    int _size;
//    Square(PointA p1, PointA p2) : leftTop(p1), rightBottom(p2) {
//        _size=rightBottom.x-leftTop.x;
//        mid=PointA((leftTop.x+rightBottom.x)/2, (leftTop.y+rightBottom.y)/2);
//    }

//    PointA extend(Square B) {

//    }

//    Line cut(Square B) {
//        if (mid.x==B.mid.x && mid.y==B.mid.y) {
//            double largerSize =_size>B._size ? _size : B._size;
//            return Line(PointA(mid.x-largerSize, mid.y-largerSize), PointA(mid.x-largerSize, mid.y-largerSize));
//        } else {
//            //---it seems that book solution does not handle left square, right square, but varied size
//        }
//    }
//};

#include "meta.hpp"

#endif // META_H
