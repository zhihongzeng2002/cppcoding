#include "recursion.h"
#include <iostream>
#include <algorithm>

/**
 * @brief Recursion::paintFill
 * @param screen
 * @param p
 * @param oldColor
 * @param newColor
 */
void Recursion::paintFill(vector<vector<Color> > &screen, Position p, Color oldColor, Color newColor)
{
    if (p.y < 0 || p.y >= screen.size() || p.x<0 || p.x >=screen[0].size()) return;

    if (screen[p.y][p.x]==oldColor)
    {
        screen[p.y][p.x]=newColor;

        paintFill(screen, Position(p.x-1, p.y), oldColor, newColor);
        paintFill(screen, Position(p.x+1, p.y), oldColor, newColor);
        paintFill(screen, Position(p.x, p.y-1), oldColor, newColor);
        paintFill(screen, Position(p.x, p.y+1), oldColor, newColor);
    }

}

void Recursion::paintFill(vector<vector<Color> > &screen, Position p, Color newColor)
{
    paintFill(screen, p, screen[p.y][p.x], newColor);
}

int Recursion::combinationOfCoins(int n, int index, vector<int> & comb)
{
    int x[]={25, 10, 5, 1};
    vector<int> coins(x, x+4);

    int numWay=0;
    int remain=0;
    for (int i=0; i<=n/coins[index]; i++)
    {
        remain = n - i*coins[index];
        comb[index]=i;

        if (remain==0)
        {
//            for (int i=index+1; i<coins.size(); i++)
//                comb[i] = 0;
            for (int i=0; i<comb.size(); i++)
                cout << comb[i] << " ";
            cout << endl;
            numWay++;
            continue;
        }

        if (index+1<coins.size())
        numWay += combinationOfCoins(remain, index+1, comb);

    }
    comb[index]=0;

    return numWay;
}

static void move(int n, vector<stack<int> > &towers, int src, int buff, int des)
{
    if (n==0) return;

    move(n-1, towers, src, des, buff);

    int x=towers[src].top();
    towers[src].pop();;
    towers[des].push(x);

    cout << "move " << x << " from " << src  << " to " << des << endl;

    move(n-1, towers, buff, src, des);

}

void Recursion::HanoiTower(const int numPlate)
{
    vector<stack<int> > towers(3);
    for (int i=numPlate-1; i>=0; i--)
        towers[0].push(i);

    move(numPlate, towers, 0, 1, 2);
}

static void printTeam(vector<circusPerson> &team)
{
    for (int i=team.size()-1; i>=0; i--)
    {
        cout << team[i].size << "," << team[i].height << "," << team[i].weight << endl;
    }

}

static vector<circusPerson> convertStreamToPersonTeam(int argc, char **argv)
{
    vector<circusPerson> team;
    for (int i=0; i<(argc-1)/3; i++)
    {
        circusPerson x(atoi(argv[i*3+1]), atoi(argv[i*3+2]), atoi(argv[i*3+3]));
        team.push_back(x);
    }
    return team;
}

void Recursion::testBuildTower(int argc, char **argv)
{
    vector<circusPerson> team=convertStreamToPersonTeam(argc, argv);
    printTeam(team);
    vector<circusPerson> tallestTower=getTallestCircusTower_exhaustive(team);
    cout << " solution " << endl;
    printTeam(tallestTower);
}

static int computeHeight(vector<circusPerson> & team)
{
    int height=0;
    for (int i=0; i<team.size(); i++)
        height += team[i].height;
    return height;
}

vector<circusPerson> getTallestTower_exhaustive_sub(vector<circusPerson> & team, circusPerson & bottom, map<circusPerson, vector<circusPerson> > &table)
{
    if (team.size()==0) return vector<circusPerson>();
    if (table.find(bottom)!=table.end()) return table.find(bottom)->second;

    int tallest=0;
    vector<circusPerson> tallestTeam;
    for (int i=0; i<team.size(); i++)
    {
        circusPerson p=team[i];

        if ( p.canBeAbove(bottom))
        {
//            p.print();
            vector<circusPerson> subTeam=getTallestTower_exhaustive_sub(team, p, table);
            int height=computeHeight(subTeam);
            if (tallest<height)
            {
                tallest=height;
                tallestTeam=subTeam;
            }
        }

    }

    if (bottom.size != 0)
    {
        tallestTeam.push_back(bottom);
        table.insert(pair<circusPerson, vector<circusPerson> > (bottom, tallestTeam));
//        cout << computeHeight(tallestTeam)<< endl;
//        printTeam(tallestTeam);
    }

    return tallestTeam;
}

vector<circusPerson> Recursion::getTallestCircusTower_exhaustive(vector<circusPerson> &team)
{
    if (team.empty()) return vector<circusPerson>();

    map<circusPerson, vector<circusPerson> > table;

    circusPerson bottom;
    return getTallestTower_exhaustive_sub(team, bottom, table);
}

static vector<circusPerson> getTallestTower_sub(vector<circusPerson> & team, int index, map<int, vector<circusPerson> > & table)
{
    if (index==team.size()) return vector<circusPerson>();

    if (table.find(index) != table.end()) return table.find(index)->second;

    int tallest=0;
    vector<circusPerson> tallestTeam;
    for (int i=index; i<team.size(); i++)
    {
        vector<circusPerson> subTeam=getTallestTower_sub(team, i+1, table);

        circusPerson p=team[i];

//        if (!subTeam.empty())
//        {
//        subTeam.back().print();
//        p.print();
//        cout << "can be above=" << p.canBeAbove(subTeam.back());
//        cin.get();
//        }
        if ( subTeam.empty() || p.canBeAbove(subTeam.back()))
        {
            subTeam.push_back(p);
        }
        int height=computeHeight(subTeam);
        if (tallest<height)
        {
            tallest=height;
            tallestTeam=subTeam;
        }

    }
    table.insert(pair<int, vector<circusPerson> > (index, tallestTeam));

    return tallestTeam;
}

vector<circusPerson> Recursion::getTallestCircusTower_greedy(vector<circusPerson> &team)
{
    if (team.empty()) return vector<circusPerson>();

    sort(team.begin(), team.end(), circusPerson::PersonComparator);

    map<int, vector<circusPerson> > table;

    return getTallestTower_sub(team, 0, table);
}

static void getNextQueen(vector<Position> & solution, vector<vector<Position> > & result, int index)
{
    if (index==8)
    {
        result.push_back(solution);
//        for (int j=0; j<solution.size(); j++)
//        {
//            Position p=solution[j];
//            cout << p.x << "," << p.y << "-> ";
//        }
//        cout << endl;
//        cin.get();
        return;
    }
    int boardSize=8;
//    for (int i=0; i<boardSize; i++)
//    {
        for (int j=0; j<boardSize; j++)
        {
            Position x(index, j);
            if (!x.isConflict(solution))
            {
                solution.push_back(x);
                getNextQueen(solution, result, index+1);
                solution.pop_back();
            }
        }
//    }

}

vector<vector<Position> > Recursion::getQueenPosition()
{
    vector<vector<Position> > result;
    vector<Position> solution;
    getNextQueen(solution, result, 0);
    cout << "done: numSolution=" << result.size() << endl;

    return result;

}

set<string> Recursion::getAllParentheses(int n)
{
    if (n<=0) return set<string>();
    if (n==1)
    {
        string x("()");
        set<string> t;
        t.insert(x);
        return t;
    }

    set<string> subResult=getAllParentheses(n-1);
    set<string> result;
    for (set<string>::iterator itr=subResult.begin(); itr!=subResult.end(); itr++)
    {
        string x=*itr;
        result.insert(x+"()");
        result.insert("()"+x);
        for (int j=0; j<x.size(); j++)
        {
            if (x[j]=='(')
            {
                string t=x.substr(0, j+1) + "()" + x.substr(j+1);
                result.insert(t);
            }
        }
    }
    return result;
}

void Recursion::getPermutation(string &str, int index, vector<string> &results)
{
    if (str.empty())return;
    if (index==str.size())
    {
        results.push_back(str);
        return;
    }

    for (int i=index; i<str.size(); i++)
    {
        char temp=str[index];
        str[index]=str[i];
        str[i]=temp;
        getPermutation(str, index+1, results);
        str[i]=str[index];
        str[index]=temp;
    }
}

vector<vector<int> > Recursion::getSubSet(vector<int> &arr, int index)
{
//    cout << "index=" << index << endl;
    if (arr.empty() || index==arr.size()) return vector<vector<int> >();

    vector<vector<int> > combination;
    vector<vector<int> > subSet = getSubSet(arr, index+1);
    combination.insert(combination.end(), subSet.begin(), subSet.end());
    combination.push_back(vector<int>(1, arr[index]));
    for (int j=0; j<subSet.size(); j++)
    {
        subSet[j].push_back(arr[index]);
        combination.push_back(subSet[j]);
    }
    return combination;
}

int Recursion::countWaysofStair(int numStair, map<int, int> &table) // but if the first time numstair =0, it is better return 0 in the main function
{
    if (numStair<0) return 0;
    if (numStair==0 || numStair==1)
        return 1;

    if (table.find(numStair) != table.end()) return table.find(numStair)->second;

    int k=countWaysofStair(numStair-1, table)+countWaysofStair(numStair-2, table)+countWaysofStair(numStair-3, table);

    table.insert(pair<int, int>(numStair, k));
    return k;
}

int Recursion::count2DBoardPathes(vector<vector<int> > &board, int y, int x, map<pair<int,int>, int> &table)
{
    if (board.size()==0 || board[0].size()==0)return 0;

    if (y<0 || x<0) return 0;
    if (y==0 && x==0) return 1;

    if (table.find(pair<int, int>(y, x)) != table.end()) return table.find(pair<int, int>(y, x))->second;

    int k=0;
    if (board[y][x]==0) // check whether it is blocked
        k=count2DBoardPathes(board, y-1, x, table)+count2DBoardPathes(board, y, x-1, table);

    table.insert(pair<pair<int,int>, int>(pair<int, int>(y, x), k));

    return k;
}

bool Recursion::find2DBoardPathesStartEndWith4Direction(vector<vector<int> > &board, int y, int x, int y_start, int x_start)
{
    if (board.size()==0 || board[0].size()==0) return false;

    if (y<0 || x<0 || y>=board.size() || x>=board[0].size()) return false;

    if (y==y_start && x==x_start)
    {
        return true;
    }

    if (board[y][x]==0)
    {
        board[y][x]=UP;
        if (find2DBoardPathesStartEndWith4Direction(board, y-1, x, y_start, x_start)) return true;
        board[y][x]=DOWN;
        if (find2DBoardPathesStartEndWith4Direction(board, y+1, x, y_start, x_start)) return true;
        board[y][x]=LEFT;
        if (find2DBoardPathesStartEndWith4Direction(board, y, x-1, y_start, x_start)) return true;
        board[y][x]=RIGHT;
        if (find2DBoardPathesStartEndWith4Direction(board, y, x+1, y_start, x_start)) return true;
    }
    return false;

}

/**
 * @brief Recursion::print2DPath: start may be end instead, because it change the board at (x,y) instead (xnext, ynext)
 * @param board
 * @param y
 * @param x
 * @param y_start
 * @param x_start
 */
void Recursion::print2DPath(vector<vector<int> > &board, int y, int x, int y_start, int x_start)
{
    bool find=find2DBoardPathesStartEndWith4Direction(board, y, x, y_start, x_start);
    if (find)
    {
        while(y!=y_start || x!=x_start)
        {
            cout << y << "," << x << endl;
            if (board[y][x]==UP)
                y=y-1;
            else if (board[y][x]==DOWN)
                y=y+1;
            else if (board[y][x]==LEFT)
                x=x-1;
            else if (board[y][x]==RIGHT)
                x=x+1;
        }
        cout << y << "," << x << endl;
    }
    else
    {
        cout << "there is no path" << endl;
    }
}

//int Recursion::count2DBoardPathesStartEndWith4Direction(vector<vector<int> > &board, int y, int x, int y_start, int x_start, map<pair<int,int>, int> &table)
//{
//    if (board.size()==0 || board[0].size()==0)return 0;

//    if (y<0 || x<0 || y>=board.size() || x>=board[0].size()) return 0;
//    if (y==y_start && x==x_start)
//    {
////        cout << __LINE__ << endl;
//        return 1;
//    }
////    cout << y << "," << x << endl;
////    cin.get();

//    if (table.find(pair<int, int>(y, x)) != table.end()) return table.find(pair<int, int>(y, x))->second;

////    cout << __LINE__ << endl;
//    int k=0;
//    if (board[y][x]==0) // check whether it is blocked
//    {
//        board[y][x]=1;
//        k=count2DBoardPathesStartEndWith4Direction(board, y-1, x, y_start, x_start, table)+count2DBoardPathesStartEndWith4Direction(board, y, x-1, y_start, x_start, table)
//                +count2DBoardPathesStartEndWith4Direction(board, y+1, x, y_start, x_start, table)+ count2DBoardPathesStartEndWith4Direction(board, y, x+1, y_start, x_start, table);
//        table.insert(pair<pair<int,int>, int>(pair<int, int>(y, x), k));
//    }

////    cout << __LINE__ << endl;
////    cin.get();

//    return k;
//}


