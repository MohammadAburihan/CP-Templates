struct SegmentTree {
  vector<int> t;
  vector<int> lazy;

  SegmentTree(int n) {
    t.resize(4 * n);
    lazy.resize(4 * n);
  }

  SegmentTree(vector<int> &a) : SegmentTree(a.size()) {
    build(a, 1, 0, a.size() - 1);
  }

  void build(vector<int> &a, int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = a[tl];
    } else {
      int tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = max(t[v * 2], t[v * 2 + 1]);
    }
  }

  void push(int v) {
    t[v * 2] += lazy[v];
    lazy[v * 2] += lazy[v];
    t[v * 2 + 1] += lazy[v];
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
  }

  void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r)
      return;
    if (l == tl && tr == r) {
      t[v] += addend;
      lazy[v] += addend;
    } else {
      push(v);
      int tm = (tl + tr) / 2;
      update(v * 2, tl, tm, l, min(r, tm), addend);
      update(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, addend);
      t[v] = max(t[v * 2], t[v * 2 + 1]);
    }
  }

  int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
      return INT_MIN;
    if (l == tl && tr == r)
      return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return max(query(v * 2, tl, tm, l, min(r, tm)),
               query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }
};

/*
*
*
*
*
*/
