#include <bits/stdc++.h>
using namespace std;

int maxN = 31;

// Depth First Search
void dfs(int node, vector<vector<pair<int, int> > >& graph,
        vector<vector<pair<int, int> > >& ancestor,
        vector<int>& level)
{
    for (pair<int, int> edge : graph[node]) {
        int neighbor = edge.first;
        int weight = edge.second;
        ancestor[neighbor][0].first = node;
        ancestor[neighbor][0].second = weight;
        level[neighbor] = level[node] + 1;
        dfs(neighbor, graph, ancestor, level);
    }
}

// Method to initialize ancestor table
void preprocess(vector<vector<pair<int, int> > >& graph,
                vector<vector<pair<int, int> > >& ancestor,
                vector<int>& level, int V)
{
    dfs(1, graph, ancestor, level);
    for (int j = 1; j < maxN; j++) {
        for (int i = 1; i <= V; i++) {
            int ancestorNode = ancestor[i][j - 1].first;
            if (ancestorNode != -1) {
                ancestor[i][j].first
                    = ancestor[ancestorNode][j - 1].first;
                ancestor[i][j].second = max(
                    ancestor[i][j - 1].second,
                    ancestor[ancestorNode][j - 1].second);
            }
        }
    }
}

// Method to find LCA of two nodes
int findLCA(vector<vector<pair<int, int> > >& ancestor,
            vector<int>& level, int X, int Y)
{
    if (level[X] < level[Y])
        swap(X, Y);
    int diff = level[X] - level[Y];
    for (int i = maxN; i >= 0; i--) {
        if (diff & (1 << i)) {
            diff -= (1 << i);
            X = ancestor[X][i].first;
        }
    }
    if (X == Y)
        return X;
    for (int i = maxN; i >= 0; i--) {
        if (ancestor[X][i].first != -1
            && ancestor[X][i].first
                != ancestor[Y][i].first) {
            X = ancestor[X][i].first;
            Y = ancestor[Y][i].first;
        }
    }
    return ancestor[X][0].first;
}

// Method to get max edge weight between a node
// and its ancestor
int getMaxEdge(vector<vector<pair<int, int> > >& ancestor,
            vector<int>& level, int X, int Y)
{
    int maxEdge = 0;
    if (level[X] < level[Y])
        swap(X, Y);
    int diff = level[X] - level[Y];
    for (int i = maxN; i >= 0; i--) {
        if (diff & (1 << i)) {
            diff -= (1 << i);
            maxEdge = max(maxEdge, ancestor[X][i].second);
            X = ancestor[X][i].first;
        }
    }
    return maxEdge;
}

// Method to get max edge weight between 2 nodes
int findMaxWeight(
    vector<vector<pair<int, int> > >& ancestor,
    vector<int>& level, int X, int Y)
{
    int LCA = findLCA(ancestor, level, X, Y);
    // Max edge weight from node X to LCA
    int path1 = getMaxEdge(ancestor, level, X, LCA);
    // Max edge weight from LCA to node Y
    int path2 = getMaxEdge(ancestor, level, Y, LCA);
    // Return maximum of both paths
    return max(path1, path2);
}

int main()
{
    int V = 7;
    // edge list
    vector<vector<int> > edges
        = { { 1, 2, 6 }, { 1, 3, 3 }, { 3, 4, 4 },
            { 4, 5, 2 }, { 4, 6, 1 }, { 5, 7, 5 } };

    vector<vector<pair<int, int> > > graph(V + 1);

    // ancestor[i][j].first = (2^j)th ancestor of node i
    // ancestor[i][j].second = max edge weight which lies
    // in the path from node i to (2^j)th ancestor of node i
    vector<vector<pair<int, int> > > ancestor(
        V + 1, vector<pair<int, int> >(maxN, { -1, 0 }));

    // vector to store level of nodes
    vector<int> level(V + 1, 0);

    // construct the adjacency list
    for (auto edge : edges) {
        graph[edge[0]].push_back({ edge[1], edge[2] });
    }

    // preprocessing
    preprocess(graph, ancestor, level, V);

    // queries
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++)
            cout << findMaxWeight(ancestor, level, i, j)
                << " ";
        cout << "\n";
    }
    return 0;
}
