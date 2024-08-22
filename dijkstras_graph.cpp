#include <iostream>
#include <climits>
#include <queue>
#include <set>
using namespace std;
int find_min(int *distance, bool *visited, int n)
{
    int min = -1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i] && (distance[i] < distance[min] || min == -1))
        {
            min = i;
        }
    }
    return min;
}
void dijkstras(int **edges, int n, int e)
{
    int *parent = new int[n];
    bool *visited = new bool[n];
    int *distance = new int[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        distance[i] = INT_MAX;
    }
    distance[0] = 0;
    parent[0] = -1;
    for (int i = 0; i < n; i++)
    {
        int min = find_min(distance, visited, n);
        visited[min] = true;
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (edges[min][j] != 0 && !visited[j])
            {
                if (distance[min] + edges[min][j] < distance[j])
                {
                    distance[j] = distance[min] + edges[min][j];
                    parent[j] = min;
                }
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << i << " " << parent[i] << " " << distance[i] << endl;
    }
    cout << endl;
    delete[] parent;
    delete[] visited;
    delete[] distance;
}
void dijkstrasPriorityQ(int **edges, int n, int e)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 0});
    int *parent = new int[n];
    bool *visited = new bool[n];
    int *distance = new int[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        distance[i] = INT_MAX;
    }
    distance[0] = 0;
    parent[0] = -1;
    while (!pq.empty())
    {
        auto min = pq.top();
        visited[min.second] = true;
        pq.pop();
        for (int j = 0; j < n; j++)
        {
            if (edges[min.second][j] != 0 && !visited[j])
            {
                if (min.first + edges[min.second][j] < distance[j])
                {
                    distance[j] = min.first + edges[min.second][j];
                    parent[j] = min.second;
                    pq.push({distance[j], j});
                }
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << i << " " << parent[i] << " " << distance[i] << endl;
    }
    cout << endl;
    delete[] parent;
    delete[] visited;
    delete[] distance;
}

void dijkstrasSet(int **edges, int n, int e)
{
    set<pair<int, int>> pq;
    pq.insert({0, 0});
    int *parent = new int[n];
    bool *visited = new bool[n];
    int *distance = new int[n];
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
        distance[i] = INT_MAX;
    }
    distance[0] = 0;
    parent[0] = -1;
    while (!pq.empty())
    {
        auto min = *(pq.begin());
        visited[min.second] = true;
        pq.erase(min);
        for (int j = 0; j < n; j++)
        {
            if (edges[min.second][j] != 0 && !visited[j])
            {
                if (min.first + edges[min.second][j] < distance[j])
                {
                    if (distance[j] != INT_MAX)
                        pq.erase({distance[j], j});
                    distance[j] = min.first + edges[min.second][j];
                    parent[j] = min.second;
                    pq.insert({distance[j], j});
                }
            }
        }
    }
    for (int i = 1; i < n; i++)
    {
        cout << i << " " << parent[i] << " " << distance[i] << endl;
    }
    cout << endl;
    delete[] parent;
    delete[] visited;
    delete[] distance;
}
int main()
{
    cout << "enter nodes and edges:";
    int n, e;
    cin >> n >> e;
    int **edges = new int *[n];
    for (int i = 0; i < n; i++)
    {
        edges[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            edges[i][j] = 0;
        }
    }
    for (int i = 0; i < e; i++)
    {
        int s, d, w;
        cin >> s >> d >> w;
        edges[s][d] = w;
        edges[d][s] = w;
    }

    dijkstras(edges, n, e);
    dijkstrasPriorityQ(edges, n, e);
    dijkstrasSet(edges, n, e);
    for (int i = 0; i < n; i++)
        delete[] edges[i];
    delete[] edges;
}