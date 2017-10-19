#include "graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <set>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <numeric>
#include <random>

Graph::Graph()
{
}

bool findPath2DMaze_helper(vector<vector<bool> > &A, Coord start, Coord exit, vector<Coord> &path) {
    if (start==exit) return true;
    if (start.y<0 || start.y >= A.size() || start.x<0 || start.x >= A.front().size() || A[start.y][start.x])
        return false;

    vector<Coord> Direct({Coord(1, 0), Coord(-1, 0), Coord(0, 1), Coord(0,-1)});
    A[start.y][start.x]=true;
    for (auto &d : Direct) {
        if (findPath2DMaze_helper(A, start+d, exit, path)) {
            path.emplace_back(start+d);
            return true;
        }
    }
    return false;
}

vector<Coord> Graph::findPath2DMaze(vector<vector<bool> > A, Coord start, Coord exit) {
    vector<Coord> path;

    findPath2DMaze_helper(A, start, exit, path);
    reverse(path.begin(), path.end());

    return path;
}

static bool CoordValidate(Coord start, vector<vector<bool> > &A) {
    return  start.y>=0 && start.y < A.size() && start.x>=0 && start.x < A.front().size() && !A[start.y][start.x];

}

vector<Coord> Graph::findPath2DMaze_BFS(vector<vector<bool> > A, Coord start, Coord exit) {
    vector<Coord> path;
    vector<vector<Coord> > table(A.size(), vector<Coord>(A.front().size()));
    queue<Coord> Q;
    if (CoordValidate(start, A))
        Q.emplace(start);
    vector<Coord> Direct ={Coord(1, 0), Coord(-1, 0), Coord(0, 1), Coord(0,-1)};

    while (!Q.empty() && Q.front() != exit) {
        Coord curr = Q.front();
        A[curr.y][curr.x]=true;
        Q.pop();
        for(auto &d : Direct){
            Coord next(curr+d);
            if (CoordValidate(next, A)) {
                table[next.y][next.x]=curr;
                Q.emplace(next);
            }
        }
    }

    if (!Q.empty()) {
        auto cur = Q.front();
        while (cur != start) {
            path.emplace_back(table[cur.y][cur.x]);
            cur = table[cur.y][cur.x];
        }
    }
    reverse(path.begin(), path.end());

    return path;
}

struct Edge {
    int src, des, weight;
    Edge(int i, int j, int k): src(i), des(j), weight(k) {}
    bool operator<(const Edge &y) const {
        return weight < y.weight;
    }
    bool operator==(const Edge &y) const {
        return src==y.src && des ==y.des;
    }
};

// O(ElogV)
void Graph::min_spanning_tree_Kruskal(vector<vector<int> > &G) {
    set<Edge> E;
    // sort the edges
    for (int i=0; i<G.size(); i++)
        for (int j=i+1; j<G[i].size(); j++)
            if (G[i][j])
                E.insert(Edge(i, j, G[i][j]));
//    sort(E.begin(), E.end());

    // build forest
    vector<int> idarray(G.size(), 0);
    iota(idarray.begin(), idarray.end(), 0);

//    int finalId=0;
    vector<Edge> res;
    while (!E.empty()) {
        auto x = *E.begin();
        if (idarray[x.src] != idarray[x.des]) {
            res.emplace_back(x);
            idarray[x.des]=idarray[x.src];
//            for (auto &t : idarray)
//            {
//                if (t==idarray[x.des])
//                    t=idarray[x.src];
//            }
        }
        E.erase(E.begin());
    }

    for (auto &x: res)
        cout << x.src << "-" << x.des << ":" << x.weight << endl;
}

struct PrimComp {
    bool operator()(const shared_ptr<Vertex> & x, const shared_ptr<Vertex> & y) const {
        return x->dist < y->dist;
    }
};

// O(V(logE))
void Graph::min_spanning_tree_Prim(vector<shared_ptr<Vertex> > &G) {
    for (auto & g : G) {
        g->mstdist=numeric_limits<int>::max();
        g->prev=nullptr;
    }
    (*G.begin())->mstdist=0;

    set<shared_ptr<Vertex>, PrimComp > table;
    for (auto g : G)
        table.insert(g);

    vector<Edge> res;
    while (!table.empty()) {
        auto t = *table.begin();
        res.emplace_back(t->prev->idx, t->idx, t->mstdist);// t->mstdis should not be included

        for (auto & x: t->edges) {
            if (x.first->prev==nullptr || x.first->mstdist > t->mstdist+x.second) {
                if (table.find(x.first) != table.end())
                    table.erase(x.first);
                x.first->prev=t;
                x.first->mstdist=t->mstdist+x.second;
                table.insert((x.first));
            }
        }
        table.erase(table.begin());
    }
    for (auto &x: res)
        cout << x.src << "-" << x.des << ":" << x.weight << endl;
}

void strongConnectedComponent_helper(shared_ptr<Graph::Ver> & curr, stack<shared_ptr<Graph::Ver> > &s, int visit) {
    curr->discover=visit;
    curr->leave=visit++;
    cout << "before:" << curr->id << "->" << curr->discover << "," << curr->leave << endl;
    s.push(curr);

    for (auto &next: curr->edges) {
        if (next->discover != -1) {
            curr->leave = min(curr->leave, next->discover);
        } else {
            strongConnectedComponent_helper(next, s, visit);
            curr->leave = min(curr->leave, next->leave);
        }

    }
    cout << "after:"<< curr->id << "->" << curr->discover << "," << curr->leave << endl;
    if (curr->discover==curr->leave) {
        shared_ptr<Graph::Ver> w;
        do {
            w = s.top();
            s.pop();
            cout << w->id << " ";
        } while (w != curr);
        cout << endl;
    }
}

void Graph::calcStrongConnectedComponents(vector<shared_ptr<Ver> > &G) {
    stack<shared_ptr<Ver> > s;
    int visit=0;
    for (auto &g: G) {
        if (g->discover == -1) {
            strongConnectedComponent_helper(g, s, visit);
        }
    }
}

void Graph::testSCC() {
    vector<shared_ptr<Ver> > G;
    G.emplace_back(new Ver(0));
    G.emplace_back(new Ver(1));
    G.emplace_back(new Ver(2));
    G.emplace_back(new Ver(3));
    G.emplace_back(new Ver(4));
    G[0]->edges.emplace_back(G[3]);
    G[0]->edges.emplace_back(G[2]);
    G[2]->edges.emplace_back(G[1]);
    G[1]->edges.emplace_back(G[0]);
    G[3]->edges.emplace_back(G[4]);
//    cout << G[0]->id << "," << G[0]->discover << "," << G[0]->edges.size() << endl;
//    cout << G[0]->edges.front()->id << endl;
    calcStrongConnectedComponents(G);
}

static bool is_cycle_for_all_DFS(shared_ptr<Graph::Ver> & curr, shared_ptr<Graph::Ver> & prev, int visit) {
    curr->discover=visit++;
    curr->leave = numeric_limits<int>::max();
    for (auto &next: curr->edges) {
        if (next != prev) {
            if (next->discover != -1)
                curr->leave= min(curr->leave, next->discover);
            else {
                if (!is_cycle_for_all_DFS(next, curr, visit))
                    return false;
                curr->leave=min(curr->leave, next->leave);
            }
        }
    }

    return !prev || curr->leave < curr->discover;
}

bool Graph::is_cycle_for_all(shared_ptr<Ver> &G) {
    if (!G) return true;
    shared_ptr<Ver> prev=nullptr;
    return is_cycle_for_all_DFS(G, prev, 0);
}

static void DFS_local(shared_ptr<Graph::Ver> & node) {
    for (auto & x: node->edges) {
        if (x->id==-1) {
            x->id=node->id;
            DFS_local(x);
        }
    }
}

bool Graph::are_constraints_satisfied(const vector<Constraint> &E, const vector<Constraint> &I) {
    unordered_map<int, shared_ptr<Ver> > table;
    for (auto & x: E) {
        table[x.a]->edges.emplace_back(table[x.b]);
        table[x.b]->edges.emplace_back(table[x.a]);
    }

    int group=0;
    for (auto &x: table) {
        if (x.second->id==-1) {
            x.second->id = group++;
            DFS_local(x.second);
        }
    }

    for (auto &x : I) {
        if (table[x.a]->id != -1 && table[x.b]->id != -1 && table[x.a]==table[x.b])
            return false;
    }
    return true;
}

void build_extend_contacts_helper(shared_ptr<Graph::ContactVert> & curr,
                                  int visitTime, vector<shared_ptr<Graph::ContactVert> > &extendcontacts) {
    for (auto &x : curr->edges) {
        if (x->visitTime != visitTime) {
            x->visitTime=visitTime;
            extendcontacts.push_back(x);
            build_extend_contacts_helper(x, visitTime, extendcontacts);
        }
    }
}

void Graph::build_extended_contacts(vector<shared_ptr<ContactVert> > &G) {
    for (int i=0; i<G.size(); i++) {
        G[i]->visitTime=i;
        build_extend_contacts_helper(G[i], i, G[i]->extendContacts);
    }
}

bool Graph::DSF_graph(shared_ptr<Graph::Vert> & curr, shared_ptr<Graph::Vert> & pre) {
    if (curr->color==Vert::Gray)
        return true;

    curr->color=Vert::Gray;
    for (auto & x : curr->edges) {
        if (x != pre && x->color != Vert::Black)
        {
            if (DSF_graph(x, curr))
                return true;
        }
    }
    curr->color = Vert::Black;
    return false;

}

bool Graph::isGraphCycleExist(shared_ptr<Vert> &G) {
    if (G) {
        shared_ptr<Vert> pre=nullptr;
        return DSF_graph(G, pre);
    }
    return false;
}

static bool BSF_v(shared_ptr<Graph::Ver> & v) {
    queue<shared_ptr<Graph::Ver> > q;
    q.emplace(v);

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        for (auto &x : t->edges) {
            if (x->id==-1) {
                x->id=t->id+1;
                q.emplace(x);
            } else if (x->id==t->id)
                return false;
        }
    }
    return true;

}

bool Graph::isCutEdgeByHalfSide(vector<shared_ptr<Ver> > &G) {
    for (auto & g: G) {
        if (g->id==-1) {
            if (!BSF_v(g))
                return false;
        }
    }
    return true;
}

int Graph::findShortestTransform(string s, string e, unordered_set<string> &dict) {
    if (dict.find(s)!= dict.end()) return -1;

    queue<pair<string, int> > q;
    dict.erase(s);
    q.push(pair<string, int>(s, 0));

    while (!q.empty()) {
        auto t = q.front();
        q.pop();
        if (t.first==e)
            return t.second;

        string str(t.first);
        for (int i=0; i<t.first.size(); i++) {
            for (int j=0; j<26; j++) {
                str[i]='a'+j;
                if (dict.find(str) != dict.end()) {
                    dict.erase(str);
                    q.emplace(str, t.second+1);
                }
            }
            str[i]=t.first[i];
        }
    }
    return -1;
}

static bool isValid(const Coordinate & p, vector<vector<bool> > & M) {
    return p.x>=0 && p.x<M.back().size() && p.y>=0 && p.y <M.size() && M[p.y][p.x]==false;
}

static bool findPath_helper(Coordinate & start, Coordinate & end, vector<vector<bool> > & A, vector<Coordinate> & path) {
    if (start==end)
        return true;
    cout << "push: " << start.y << "," << start.x << endl;
    path.push_back(start);
    A[start.y][start.x]=true;
    vector<Coordinate> direct{Coordinate(1, 0), Coordinate(0, 1), Coordinate(-1, 0), Coordinate(0, -1)};
    for (auto d: direct) {
        Coordinate next=start+d;
        if (isValid(next, A)) {
            if (findPath_helper(next, end, A, path))
                return true;
        }
    }
        cout << "popback: " << path.back().y << "," << path.back().x << endl;
        path.pop_back();
//    for (auto x: path)
//        cout << x.y << "," << x.x << "->";
//    cout << endl;
    return false;
}

vector<Coordinate> Graph::findPath_test(int rows, int cols) {
    vector<vector<bool> > M(rows, vector<bool>(cols, false));
    M[1][0]=true;
    M[1][1]=true;
    cout << M.size() << "," << M.back().size() << ":" << M[0][0] << endl;
    Coordinate start(0, 0);
    Coordinate end(2,2);
    vector<Coordinate> path= findPath(start, end, M);
    for (auto x: path) {
        cout << x.y << "," << x.x << "->";
    }
    cout << endl;
}

vector<Coordinate> Graph::findPath(Coordinate &start, Coordinate &end, vector<vector<bool> > &M) {
    vector<Coordinate> path;
    if (isValid(start, M))
        findPath_helper(start, end, M, path);
    return path;
}

void DFS0(shared_ptr<Graph::TVertex> v, stack<shared_ptr<Graph::TVertex> > & result)
{
    v->visited = true;
    for (auto & x : v->edges)
    {
        if (!x->visited)
            DFS0(x, result);
    }
    result.push(v);
}

stack<shared_ptr<Graph::TVertex> > buildOrderedVertice(vector<shared_ptr<Graph::TVertex> > & arr)
{
    stack<shared_ptr<Graph::TVertex> > result;
    if (arr.empty()) return result;

    for (auto & x : arr)
    {
        if (!x->visited)
            DFS0(x, result);
    }
    return result;
}

int Graph::findLongestPath(vector<shared_ptr<TVertex> > &arr)
{
    stack<shared_ptr<TVertex> > orderedV = buildOrderedVertice(arr);

    int maxLength=0;
    while (!orderedV.empty())
    {
        shared_ptr<TVertex> u= orderedV.top();
        orderedV.pop();

        int maxLength = max(maxLength, u->dist);
        for (auto & t : u->edges)
        {
            t->dist = max(t->dist, u->dist+1);
        }
    }

    return maxLength;
}

void findShortestPath_Floyd_Warshall(vector<vector<double> > & distmap)
{
    for (int i=0; i<distmap.size(); i++)
        for (int j=0; j<distmap.size(); j++)
            for (int k=0; k<distmap.size(); k++)
            {
                if (distmap[i][k] != numeric_limits<double>::max() && distmap[k][j] != numeric_limits<double>::max()
                        && distmap[i][j]>distmap[i][k]+distmap[k][j])
                    distmap[i][j]=distmap[i][k]+distmap[k][j];
            }
}

Graph::HighwaySection Graph::findBestHighwayProposal(const vector<HighwaySection> &existing, const vector<HighwaySection> &proposals,
                                              const int a, const int b, const int numCity)
{
    vector<vector<double> > distmap(numCity, vector<double>(numCity, numeric_limits<double>::max()));

    for (auto & t : existing)
    {
        distmap[t.x][t.y] = t.dist;
        distmap[t.y][t.x] = t.dist;
    }

    for (int i=0; i<numCity; i++)
        distmap[i][i]= 0;


    findShortestPath_Floyd_Warshall(distmap);

    HighwaySection bestproposal(-1, -1, 0.0);
    int mindist=distmap[a][b];
    for (auto & p : proposals)
    for (int i=0; i<distmap.size(); i++)
        for (int j=0; j<distmap.size(); j++)
        {
            if (distmap[a][i] != numeric_limits<double>::max() && distmap[j][b] != numeric_limits<double>::max()
                    && mindist > distmap[a][i]+p.dist+distmap[j][b])
            {
                mindist = distmap[a][i]+p.dist+distmap[j][b];
                bestproposal = p;
            }

            if (distmap[a][j] != numeric_limits<double>::max() && distmap[i][b] != numeric_limits<double>::max()
                    && mindist > distmap[a][j]+p.dist+distmap[i][b])
            {
                mindist = distmap[a][j]+p.dist+distmap[i][b];
                bestproposal = p;
            }
        }

    return bestproposal;
}

bool Graph::findArbitrary_Bellman_Ford(vector<vector<double> > &G)
{
    for (auto & edgelist : G)
        for (auto &edge : edgelist)
            edge = -log10(edge);

    vector<double> dist(G.size(), numeric_limits<double>::max());
    dist[0]=0;
    bool update=false;

    for (int i=0; i<G.size(); i++)
        for (int j=0; j<G.front().size(); j++)
        {
            if (dist[i] != numeric_limits<double>::max()
                    && dist[j] > dist[i] + G[i][j])
            {
                update=true;
                dist[j]=dist[i]+G[i][j];
            }
        }

    if (!update)
        return false;

    for (int i=0; i<G.size(); i++)
        for (int j=0; j<G.front().size(); j++)
        {
            if (dist[i] != numeric_limits<double>::max()
                    && dist[j] > dist[i] + G[i][j])
            {
                return true;
            }
        }

    return false;
}

void printVertex(shared_ptr<Vertex> & s)
{
    if (s)
    {
    printVertex(s->prev);
    cout << s->idx << endl;
    }
}

void Graph::findShortestPath(shared_ptr<Vertex> &s, shared_ptr<Vertex> &e) {
    s->dist=pair<int, int>(0, 0);
    set<shared_ptr<Vertex>, VertexComp> table;
    table.insert(s);

    while (!table.empty()) {
        auto x = *table.begin();
        if (x==e)
            break;
        table.erase(table.begin());

        for ( auto & t: x->edges) {
            int dist1 = x->dist.first + t.second;
            int dist2 = x->dist.second + 1;
            if (dist1 < t.first->dist.first || dist1 == t.first->dist.first && dist2 < t.first->dist.second) {
                table.erase(t.first);
                t.first->dist=pair<int, int>(dist1, dist2);
                t.first->prev=x;
                table.insert(t.first);
            }
        }
    }
    printVertex(e);
}

//void Graph::findShortestPath(shared_ptr<Vertex> &s, shared_ptr<Vertex> &e)
//{
//    s->dist = make_pair(0,0);
//    set<shared_ptr<Vertex> > vset;
//    vset.insert(s);

//    while(!vset.empty())
//    {
//        shared_ptr<Vertex> cur = *vset.begin();
//        if (cur == e)
//            break;
//        vset.erase(vset.begin());

//        for (auto & x : cur->edges)
//        {
//            int v_dist = x.second + cur->dist.first;
//            int v_numvertex = cur->dist.second + 1;
//            if (v_dist < x.first->dist.first || (v_dist == x.first->dist.first && v_numvertex < x.first->dist.second))
//            {
//                auto itr = vset.find(x.first);
//                if ( itr!= vset.end())
//                    vset.erase(itr);
//                x.first->dist = make_pair(v_dist, v_numvertex);
//                x.first->prev = cur;
//                vset.insert(x.first);
//            }
//        }
//    }

//    // print
//    printVertex(e);



//}

static bool printPathInMaze_recursive_help(vector<vector<int> > &maze, Coordinate & start, Coordinate & exit, vector<Coordinate> & path, vector<Coordinate> & directions)
{
    if (start==exit)
    {
        path.push_back(start);
        return true;
    }
    if ( start.x < 0 || start.y < 0 || start.y >= maze.size() || start.x >= maze[0].size() || maze[start.y][start.x]==1 )
        return false;

    maze[start.y][start.x]=1;
    cout << "visiting: " << start.y << " " << start.x << endl;

    for ( auto direct : directions)
    {
        path.push_back(start);
        Coordinate next=start+direct;
        if (printPathInMaze_recursive_help(maze, next, exit, path, directions))
            return true;
        path.pop_back();

    }
    return false;

}

/**
 * @brief Graph::printPathInMaze_recursive
 * @param maze: 1=block or visited, otherwise 0
 * @param start
 * @param exit
 */
void Graph::printPathInMaze_recursive(vector<vector<int> > &maze, Coordinate &start, Coordinate &exit)
{
    vector<Coordinate> path;
    vector<Coordinate> directions;
    directions.push_back(Coordinate(1, 0));
    directions.push_back(Coordinate(-1, 0));
    directions.push_back(Coordinate(0, 1));
    directions.push_back(Coordinate(0, -1));

    cout << "enter maze" << endl;
    if (!printPathInMaze_recursive_help(maze, start, exit, path, directions))
    {
        cout << "there is no path" << endl;
    }

    // PRINT
    for (int i=0; i<path.size(); i++)
    {
        cout << "->" << path[i].y << ", " << path[i].x;
    }
    cout << endl;
}

enum Direction
{
    Undefine=0, Up, Down, Right, Left
};

static bool is_available(Coordinate start, vector<vector<int> > & table)
{
    return start.x>=0 && start.y >=0 && start.y<table.size() && start.x < table[0].size() && table[start.y][start.x]==Undefine;
}

static bool printPathInMaze_BFS_helper(vector<vector<int> > & maze, Coordinate & start, Coordinate exit)
{
    if (start==exit)
    {
        cout << "start==exit" << endl;
        return true;
    }

    vector<pair<Coordinate, Direction> > neighbors;
    neighbors.push_back(pair<Coordinate, Direction>(Coordinate(1, 0), Up));
    neighbors.push_back(pair<Coordinate, Direction>(Coordinate(-1, 0), Down));
    neighbors.push_back(pair<Coordinate, Direction>(Coordinate(0, 1), Right));
    neighbors.push_back(pair<Coordinate, Direction>(Coordinate(0, -1), Left));

    queue<Coordinate> q;
    q.push(start);
    maze[start.y][start.x]=Up;

    Coordinate next(0,0);
    while (!q.empty())
    {
        Coordinate t=q.front();
        q.pop();
//        cout << "t:" << t.y << "," << t.x << endl;

        for (auto neig : neighbors)
        {
            next=t+neig.first;
            if (is_available(next, maze))
            {
                maze[next.y][next.x]=neig.second;
                q.push(next);
                if (next==exit)
                    return true;

            }
        }
    }

    return false;

}

void Graph::printPathInMaze_BFS(vector<vector<int> > &maze, Coordinate &start, Coordinate &exit)
{
    if (!printPathInMaze_BFS_helper(maze, start, exit))
    {
        cout << "there is no path" << endl;
        return;
    }

    // get the path
    stack<Coordinate> path;
    Coordinate next=exit;
    while (next!=start)
    {
//        cout << "path reve:" << next.y << "," << next.x << "," << maze[next.y][next.x] << endl;
        path.push(next);
        if (maze[next.y][next.x]==Down)
            next.y +=1;
        else if (maze[next.y][next.x]==Up)
            next.y -=1;
        else if (maze[next.y][next.x]==Right)
            next.x -=1;
        else if (maze[next.y][next.x]==Left)
            next.x +=1;
    }
    path.push(next);
    // print
    while (!path.empty())
    {
        Coordinate t=path.top();
        cout << t.y << "," << t.x << "->";
        path.pop();
    }
    cout << endl;

}

vector<vector<int> >  Graph::buildMaze(int argc, char **argv)
{
    int height = atoi(argv[1]);
    int width = atoi(argv[2]);

    cout << "height:width=" << height << ":" << width << endl;

    vector<vector<int> > maze(height, vector<int>(width));
    int count=3;
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            maze[i][j]=atoi(argv[count]);
            cout << argv[count] << " ";
            count++;
        }
        cout << endl;
    }
    return maze;
}

void Graph::findPath_BSF(Coordinate &enter, Coordinate & exit, vector<vector<int> > &maze) {
    if (!is_available(enter, maze)) return;
    queue<Coordinate> q;
    maze[enter.y][enter.x]=Up;
    q.push(enter);

    vector<pair<Coordinate, Direction> > neighbors;
    neighbors.emplace_back(Coordinate(1, 0), Right);
    neighbors.emplace_back(Coordinate(-1, 0), Left);
    neighbors.emplace_back(Coordinate(1, 0), Up);
    neighbors.emplace_back(Coordinate(1, 0), Down);

    Coordinate next(enter);
    while (!q.empty()) {
        Coordinate x = q.front();
        q.pop();

        for (auto &d : neighbors) {
            next = x+d.first;
            if (is_available(next, maze)) {
                maze[next.y][next.x]=d.second;
                q.push(next);
                if (next==exit) {
                    while (!q.empty())
                        q.pop();
                    break;
                }
            }
        }

    }

    if (next!=exit) return;

    stack<Coordinate> path;
        while (next != enter) {
            path.push(next);
            if (maze[next.y][next.x]==Up)
                next.y -=1;
            else if (maze[next.y][next.x]==Down)
                next.y +=1;
            else if (maze[next.y][next.x]==Left)
                next.x +=1;
            else if (maze[next.y][next.x]==Right)
                next.x -=1;
        }
        path.push(next);

        while (!path.empty()) {
            cout << path.top().y << path.top().x << endl;
            path.pop();
        }

}

void GraphList::addEdge(int id_par, int id_child) {
    adj[id_par].push_back(id_child);
}

void GraphList::topologicalSort() {
    stack<int> s;
    vector<bool> visited(numVert, false);

    for (int i=0; i<numVert; i++) {
        if (!visited[i])
            topologicalSort_helper(i, visited, s);
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

void GraphList::topologicalSort_helper(int id, vector<bool> &visited, stack<int> &s) {
    visited[id]=true;
    for (auto i=adj[id].begin(); i != adj[id].end(); i++) {
        if (!visited[*i]) {
            cout << "go to " << *i << endl;
            topologicalSort_helper(*i, visited, s);
        }
    }
    s.push(id);
}
