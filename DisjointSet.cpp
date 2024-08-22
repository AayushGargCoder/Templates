#include <iostream>
#include <vector>
using namespace std;
class Disjoint
{
public:
    vector<int> rank, parent, size;

    Disjoint(int n)
    {
        // n+1->works for both 0 and 1 based indexing
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        for (int i = 0; i < n + 1; i++)
            parent[i] = i;
    }
    int findP(int n)
    {
        if (n == parent[n])
            return n;
        /// Path Compression
        return parent[n] = findP(parent[n]);
    }
    void unionByRank(int u, int v)
    {
        int pu = findP(u), pv = findP(v), r1 = rank[pu], r2 = rank[pv];
        if (pu == pv)
            return;
        if (r1 < r2)
        {
            parent[pu] = pv;
        }
        else if (r1 > r2)
        {
            parent[pv] = pu;
        }
        else
        {
            parent[pv] = pu;
            rank[pu]++;
        }
    }
    void unionBySize(int u, int v)
    {
        int pu = findP(u), pv = findP(v), s1 = size[pu], s2 = size[pv];
        if (pu == pv)
            return;
        if (s1 < s2)
        {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else
        {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};
