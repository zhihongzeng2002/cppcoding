#include "gtest/gtest.h"
#include "tree/tree.h"

class TreeTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int k=7;
        std::list<int> values;
        for (int i=0; i<k; i++)
        {
            values.push_back(i);
        }
        s.build(values);
    }

    Tree<int> s;
};

TEST_F(TreeTest, BFS)
{
    std::list<int> nodeSeq = s.BFS();
    int i=0;
    for (std::list<int>::iterator itr = nodeSeq.begin(); itr != nodeSeq.end(); itr++, i++)
    {
        std::cout << i << ": " <<  *itr << " ";
        EXPECT_EQ(i, *itr);
    }
    std::cout << std::endl;
}

TEST_F(TreeTest, DFSMain)
{
    std::list<int> nodeSeq = s.DFS_main();
    int i=0;
    for (std::list<int>::iterator itr = nodeSeq.begin(); itr != nodeSeq.end(); itr++, i++)
    {
        std::cout << i << ": " <<  *itr << " ";
        EXPECT_EQ(i, *itr);
    }
    std::cout << std::endl;
}
