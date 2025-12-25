#include <bits/stdc++.h>
using namespace std;

// Depth First Search
void dfs(int node, vector<vector<int> >& graph,
        vector<vector<int> >& ancestor, int parent)
{
    ancestor[node][0] = parent;
    for (int neighbor : graph[node]) {
        dfs(neighbor, graph, ancestor, node);
    }
}

// Method to initialize ancestor table
void preprocess(vector<vector<int> >& graph,
                vector<vector<int> >& ancestor, int V,
                int maxN)
{
    dfs(1, graph, ancestor, -1);
    for (int j = 1; j < maxN; j++) {
        for (int i = 1; i <= V; i++) {
            if (ancestor[i][j - 1] != -1)
                ancestor[i][j]
                    = ancestor[ancestor[i][j - 1]][j - 1];
        }
    }
}

// Method to find Kth ancestor of node
int findKthAncestor(vector<vector<int> >& ancestor,
                    int node, int K, int maxN)
{
    for (int i = maxN - 1; i >= 0; i--) {
        if (K & (1 << i)) {
            if (ancestor[node][i] == -1)
                return -1;
            node = ancestor[node][i];
        }
    }
    return node;
}

int main()
{
    int V = 7;
    int maxN = log2(V) + 1;

    // edge list
    vector<vector<int> > edges
        = { { 1, 2 }, { 1, 3 }, { 3, 4 },
            { 4, 5 }, { 4, 6 }, { 5, 7 } };
    vector<vector<int> > graph(V + 1),
        ancestor(V + 1, vector<int>(maxN, -1));

    // construct the adjacency list
    for (auto edge : edges) {
        graph[edge[0]].push_back(edge[1]);
    }

    // preprocessing
    preprocess(graph, ancestor, V, maxN);

    // queries
    cout << findKthAncestor(ancestor, 7, 3, maxN) << "\n";
    cout << findKthAncestor(ancestor, 5, 1, maxN) << "\n";
    cout << findKthAncestor(ancestor, 7, 4, maxN) << "\n";
    cout << findKthAncestor(ancestor, 6, 4, maxN) << "\n";
    return 0;
}
