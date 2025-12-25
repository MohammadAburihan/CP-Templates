class BinaryLifting {
public:
  int n, l;
  vector<vector<array<int, 2>>> adj;

  int timer;
  vector<int> tin, tout;
  vector<vector<int>> up;
  vector<vector<int>> mx;

  BinaryLifting(int n, vector<vector<array<int, 2>>>& adj) {
    this->n = n;
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    mx.assign(n, vector<int>(l + 1, INT_MIN));
    this->adj = adj;
  }

  void dfs(int v, int p, int we) {
    tin[v] = ++timer;
    up[v][0] = p;
    mx[v][0] = we;
    for (int i = 1; i <= l; ++i) {
      up[v][i] = up[up[v][i - 1]][i - 1];
      mx[v][i] = max(mx[v][i - 1], mx[up[v][i - 1]][i - 1]);
    }

    for (auto [u, w] : adj[v]) {
      if (u != p)
        dfs(u, v, w);
    }

    tout[v] = ++timer;
  }

  bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }

  int maxLca(int u, int v) {
    if (is_ancestor(u, v))
      return INT_MIN;
    int mxEdge = INT_MIN;
    for (int i = l; i >= 0; --i) {
      if (!is_ancestor(up[u][i], v) && up[u][i] != v) {
        mxEdge = max(mxEdge, mx[u][i]);
        u = up[u][i];
      }
    }
    return max(mxEdge, mx[u][0]);
  }

  int maxEdge(int u, int v) {
    return max(maxLca(u, v), maxLca(v, u));
  }

  void preprocess(int root) {
    dfs(root, root, INT_MIN);
  }
};

/*
 *
 *
 * Max Edge between two node using Binary Lifting Implementaion
 *
 *
 */
