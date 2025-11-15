#include <bits/stdc++.h>
using namespace std;
const int N = 200 + 1, M = 400 + 1;

int head[N], nxt[M], to[M], cap[M], ne, n, src, snk;
int vis[N], vid;

void init() {
    memset(head, -1, n * sizeof(head[0]));
    ne = 0;
}

void addEdge(int u, int v, int c) {
    nxt[ne] = head[u];
    to[ne] = v;
    cap[ne] = c;
    head[u] = ne++;
}

void addAugEdge(int u, int v, int c, int r = 0) {
    addEdge(u, v, c);
    addEdge(v, u, r);
}

int dfs(int u, int f) {
    if (u == snk)return f;
    if (vis[u] == vid or !f)return 0;
    vis[u] = vid;
    for (int e = head[u]; ~e; e = nxt[e]) {
        int v = to[e];
        int c = cap[e];
        int res = dfs(v, min(f, c));
        if (res) {
            cap[e] -= res;
            cap[e ^ 1] += res;
            return res;
        }
    }
    return 0;
}

int maxFlow() {
    int res = 0, f;
    for (++vid; f = dfs(src, INT_MAX); ++vid)
        res += f;
    return res;
}

int main() {
    //freopen("ditch.in", "r", stdin);
    //freopen("ditch.out", "w", stdout);
    int m;
    while (~scanf("%d%d", &m, &n)) {
        init();
        src = 0, snk = n - 1;
        while (m--) {
            int u, v, c;
            scanf("%d%d%d", &u, &v, &c);
            addAugEdge(--u, --v, c);
        }
        printf("%d\n", maxFlow());
    }
    return 0;
}
