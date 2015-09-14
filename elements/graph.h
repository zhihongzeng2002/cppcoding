#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <memory>
#include <limits>
#include <unordered_set>
#include <list>
#include <stack>

using namespace std;

struct Coord {
    int y, x;
    Coord(int _y, int _x) : x(_x), y(_y) {}
    Coord() {}
    Coord(const Coord &that) {
        if (this != &that) {
            y=that.y;
            x=that.x;
        }
    }

    bool operator==(const Coord & that) const {
        return x==that.x && y==that.y;
    }
    bool operator!=(const Coord &that) const {
        return x != that.x || y != that.y;
    }
    Coord operator+(const Coord & that) const {
        Coord result(*this);
        result.x += that.x;
        result.y += that.y;
        return result;
    }
    Coord &operator=(const Coord &that) {
        if (this != &that) {
            x=that.x;
            y=that.y;
        }
        return *this;
    }
    Coord & operator+=(const Coord &that) {
        x += that.x;
        y += that.y;
        return *this;
    }
};

struct Coordinate
{
    int x, y;
    bool isVisited=false;
    Coordinate(int _y, int _x) : x(_x), y(_y) {}
    bool operator==( const Coordinate & that)  const
    {
        return x==that.x && y == that.y;
    }
    bool operator!=( const Coordinate & that)  const
    {
        return x!=that.x || y != that.y;
    }
//    Coordinate &operator+=( const Coordinate & that)
//    {
//        x+=that.x;
//        y+=that.y;
//        return *this;
//    }
    Coordinate operator+(const Coordinate & that) const
    {
        Coordinate result=*this;
        result.x += that.x;
        result.y += that.y;
        return result;
    }

//    Coordinate & operator=(const Coordinate & that)
//    {
//        if (this != &that)
//        {
//            x=that.x;
//            y=that.y;
//        }
//        return *this;
//    }
};

struct Vertex
{
    int idx;
    pair<int, int> dist;
    int mstdist;
    vector<pair<shared_ptr<Vertex>, int> > edges; // vertex, and edge weight
    enum visit
    {
        unvisit, visting, visited
    };
    visit visitFlag;
    shared_ptr<Vertex> prev;

    Vertex(int _idx) : idx(_idx), dist(make_pair<int, int>(0,0)), visitFlag(unvisit), prev(nullptr) {}
    Vertex() : dist(make_pair<int, int>(numeric_limits<int>::max(), 0)), visitFlag(unvisit), prev(nullptr), idx(0) {}

    bool operator<(const Vertex & that) const
    {
        return dist.first < that.dist.first || dist.first==that.dist.first && dist.second<that.dist.second;
    }
};

struct VertexComp {
    bool operator()(const shared_ptr<Vertex> &x, const shared_ptr<Vertex> & y) const {
        return x->dist.first!=y->dist.first ? x->dist.first!=y->dist.first : x->dist.second<y->dist.second;
    }
};

class Graph
{
public:
    Graph();

    //16.1
    vector<Coord> findPath2DMaze(vector<vector<bool> > A, Coord start, Coord exit);
    vector<Coord> findPath2DMaze_BFS(vector<vector<bool> > A, Coord start, Coord exit);

    void min_spanning_tree_Prim(vector<shared_ptr<Vertex> > &G);
    void min_spanning_tree_Kruskal(vector<vector<int> > &G);

    struct ContactVert {
        int visitTime=-1;
        vector<shared_ptr<ContactVert> > edges, extendContacts;
    };

    void build_extended_contacts(vector<shared_ptr<ContactVert> > & G);

    struct Vert {
        enum Color {
            White, Gray, Black
        } color;
        vector<shared_ptr<Vert> > edges;
    };
    bool DSF_graph(shared_ptr<Graph::Vert> & g, shared_ptr<Graph::Vert> & pre);
    bool isGraphCycleExist(shared_ptr<Vert> & G);

    struct Ver {
        int id=-1;
        int discover=-1,leave=-1;
        vector<shared_ptr<Ver> > edges;
        Ver(int n) : id(n) {}
    };

    struct Constraint {
        int a, b;
    };

    void calcStrongConnectedComponents(vector<shared_ptr<Ver> > &G);
    void testSCC();

    // 16.4
    bool is_cycle_for_all(shared_ptr<Ver> &G);

    //16.6
    bool are_constraints_satisfied(const vector<Constraint> &E, const vector<Constraint> &I);

    //16.3
    bool isCutEdgeByHalfSide(vector<shared_ptr<Ver> > &G);

    //15.12
    int findShortestTransform(string s, string e, unordered_set<string> &dict);

    vector<Coordinate> findPath_test(int rows, int cols);
    vector<Coordinate> findPath(Coordinate & start, Coordinate & end, vector<vector<bool> > & M);
    vector<vector<int> > buildMaze(int argc, char **argv);
    void printPathInMaze_recursive(vector<vector<int> > & maze, Coordinate &start, Coordinate &exit);
    void printPathInMaze_BFS(vector<vector<int> > & maze, Coordinate &start, Coordinate &exit);
    void findPath_BSF(Coordinate &enter, Coordinate & exit, vector<vector<int> > &maze);

    void findShortestPath(shared_ptr<Vertex> &s, shared_ptr<Vertex> &e);

    bool findArbitrary_Bellman_Ford(vector<vector<double> > &G);

    struct HighwaySection
    {
        int x, y;
        double dist;
        HighwaySection(int _x, int _y, double _dist)
            :x(_x), y(_y), dist(_dist) {}
    };

    HighwaySection findBestHighwayProposal(const vector<HighwaySection>& existing, const vector<HighwaySection> & proposals, const int a, const int b, const int numCity);

    struct TVertex
    {
        int dist;
        bool visited;
        vector<shared_ptr<TVertex> > edges;
        TVertex() : dist(1), visited(false) {}
    };

    int findLongestPath(vector<shared_ptr<TVertex> > &arr);
};

class GraphList {
    int numVert;
    vector<list<int> > adj;

public:
    GraphList(int n) : numVert(n), adj(numVert, list<int>()) {}
    void addEdge(int id_par, int id_child);
    void topologicalSort();
    void topologicalSort_helper(int id, vector<bool> & visited, stack<int> & s);
};

#endif // GRAPH_H
