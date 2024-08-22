#include <iostream>
#include <vector>
using namespace std;
class segmentTree
{
    vector<int> segment;
    int n;
    void buildTree(vector<int> &nums, int s, int e, int treeNode)
    {
        if (s == e)
        {
            segment[treeNode] = nums[s];
            return;
        }
        int mid = (s + e) / 2;
        buildTree(nums, s, mid, 2 * treeNode + 1);
        buildTree(nums, mid + 1, e, 2 * treeNode + 2);
        // Perform Task for TreeNode
    }
    void updateTree(int s, int e, int treeNode, int ind, int value)
    {
        if (s == e)
        {
            segment[treeNode] = value;
            return;
        }
        int mid = (s + e) / 2;
        if (ind <= mid)
            updateTree(s, mid, 2 * treeNode + 1, ind, value);
        else
            updateTree(mid + 1, e, 2 * treeNode + 2, ind, value);
        // Perform Task for Treenode
    }

public:
    segmentTree(vector<int> &nums)
    {
        this->n = nums.size();
        this->segment.resize(4 * n);
        buildTree(nums, 0, n - 1, 0);
    }

    void update(int index, int val)
    {
        updateTree(0, n - 1, 0, index, val);
    }
};
