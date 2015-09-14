#include "matrix.h"
#include "limits.h"
#include <queue>
#include "recursion.h"

Matrix::Matrix()
{
}

static void print2DPath(vector<vector<Direction> > & directMat, Point2D start, Point2D end)
{
    if (directMat.size()==0 || directMat[0].size()==0 ) return;

    Point2D curNode=start;
    while (curNode.x != end.x || curNode.y != end.y)
    {
        cout << curNode.y << "," << curNode.x << endl;
        if (directMat[curNode.y][curNode.x]==LEFT)
            curNode=Point2D(curNode.x-1, curNode.y);
        else if (directMat[curNode.y][curNode.x]==RIGHT)
            curNode=Point2D(curNode.x+1, curNode.y);
        else if (directMat[curNode.y][curNode.x]==UP)
            curNode=Point2D(curNode.x, curNode.y-1);
        else if (directMat[curNode.y][curNode.x]==DOWN)
            curNode=Point2D(curNode.x, curNode.y+1);
        else
            cout << " Direction is not decided" << endl;
    }
    cout << curNode.y << "," << curNode.x << endl;
}

static void pushNeighbor(Point2D neighbor, Direction direction, vector<vector<int> > & arr,
                         vector<vector<Direction> > & directionMat, queue<Point2D> &q )
{
    if (neighbor.isAvailable(arr))
    {
        q.push(neighbor);
        arr[neighbor.y][neighbor.x]=1;
        directionMat[neighbor.y][neighbor.x]=direction;
    }

}

/**
 * @brief Matrix::findPathBetweenPoints
 * @param arr matrix with 0 (free), 1 (block)
 * @param start start point
 * @param end end point
 */
void Matrix::findPathBetweenPoints(vector<vector<int> > &arr, Point2D start, Point2D end)
{
    if (arr.size()==0 || arr[0].size()==0) return;
    vector<vector<Direction> > directionMat(arr.size(), vector<Direction>(arr[0].size(), UNDECIDED));

    queue<Point2D> q;
    q.push(end);
    arr[end.y][end.x]=1;

    bool find=false;
    while(!q.empty())
    {
        Point2D node=q.front();
        q.pop();

//        cout << node.y << "," << node.x << "-";
//        cin.get();
        if (node.x==start.x && node.y== start.y)
        {
            find=true;
            break;
        }

        pushNeighbor(Point2D(node.x-1, node.y), RIGHT, arr, directionMat, q);
        pushNeighbor(Point2D(node.x+1, node.y), LEFT, arr, directionMat, q);
        pushNeighbor(Point2D(node.x, node.y-1), DOWN, arr, directionMat, q);
        pushNeighbor(Point2D(node.x, node.y+1), UP, arr, directionMat, q);

//        cout << "q.size=" << q.size() << endl;
//        cin.get();
    }

    if (!find)
    {
        cout << "there is no path" << endl;
        return;
    }
//    cout << "before print" << endl;

    print2DPath(directionMat, start, end);

}

/**
 * @brief Matrix::findMaxRectSum
 * complexity: n^4, brute force n^6
 * @param arr2D
 * @return
 */
int Matrix::findMaxRectSum(vector<vector<int> > &arr2D)
{
    // compute integral sum
    vector<vector<int> > arrSum(arr2D.size(), vector<int>(arr2D[0].size(), 0));

    for (int i=0; i<arr2D.size(); i++)
    {
        for (int j=0; j<arr2D[i].size(); j++)
        {
            if (i==0 && j==0)
                arrSum[i][j]=arr2D[i][j];
            else if (i==0)
                arrSum[i][j]=arrSum[i][j-1]+arr2D[i][j];
            else if (j==0)
                arrSum[i][j]=arrSum[i-1][j]+arr2D[i][j];
            else
                arrSum[i][j]=arr2D[i][j]+arrSum[i-1][j]+arrSum[i][j-1]-arrSum[i-1][j-1];
        }
    }

    int maxSum=INT_MIN;
    for (int y1=0; y1<arr2D.size(); y1++)
    {
        for (int x1=0; x1<arr2D[0].size(); x1++)
        {
            for (int y2=y1; y2<arr2D.size(); y2++)
            {
                for (int x2=x1; x2<arr2D[0].size(); x2++)
                {
                    int sum;
                    if (x1==x2 && y1==y2)
                        sum=arr2D[x1][y1];
                    else if (x1==x2)
                        sum=arrSum[y2][x2]-arrSum[y1][x1];
                    else if (y1==y2)
                        sum=arrSum[y2][x2]-arrSum[y1][x1];
                    else
                        sum=arrSum[y2][x2]-arrSum[y2][x1]-arrSum[y1][x2]+arrSum[y1][x1];

                    if (maxSum < sum)
                        maxSum=sum;
                }
            }

        }
    }
    return maxSum;
}

struct Cell
{
    int x, y;
    Cell(): x(0), y(0)
    {}
    void set(int i, int j)
    {
        x=i;
        y=j;
    }
};

bool isSquare(int len, int y1, int x1, vector<vector<Cell> > & arrSum)
{
    if (arrSum[y1][x1].x<len || arrSum[y1][x1].y<len)
        return false;

    if (arrSum[y1-len][x1].x< len || arrSum[y1][x1-len].y<len) return false;

    return true;
}

int Matrix::findMaxSquareWithBlackBolder(vector<vector<int> > &arr2D)
{
    vector<vector<Cell> > arrSum(arr2D.size(), vector<Cell>(arr2D[0].size(), Cell()));

    for (int i=0; i<arr2D.size(); i++)
    {
        for (int j=0; j<arr2D[0].size(); j++)
        {
            if (arr2D[i][j]==1) // white cell, use default
                continue;

            if (i==0 && j==0)
                arrSum[i][j].set(1, 1);
            else if (i==0)
                arrSum[i][j].set(arrSum[i][j-1].x+1, 1);
            else if (j==0)
                arrSum[i][j].set(1, arrSum[i-1][j].y+1);
            else
                arrSum[i][j].set(arrSum[i][j-1].x+1, arrSum[i-1][j].y+1);
        }
    }

    for (int len=arr2D.size(); len>=1; len--)
    {
        for (int y1=arr2D[0].size()-1; y1>=len; y1--)
        {
            for (int x1=arr2D.size()-1; x1>=len; x1--)
            {
                if (isSquare(len, y1, x1, arrSum))
                    return len;
            }
        }
    }
    return 0;

}

void Matrix::rotateMatrix(vector<vector<int> > &arr)
{
    if (arr.empty()) return;
    int size=arr.size();

    for (int i=0; i<size; i++)
        for (int j=i; j<size/2; j++)
        {
            int temp=arr[i][j];
            arr[i][j]=arr[size-1-j][i];
            arr[size-1-j][i]=arr[size-1-i][size-1-j];
            arr[size-1-i][size-1-j]=arr[j][size-1-i];
            arr[j][size-1-i]=temp;

        }

}




