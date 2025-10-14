struct SegmentTree {
  vector<int> t;

  SegmentTree(int n) {
    t.resize(4 * n);
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
      t[v] = t[v * 2] + t[v * 2 + 1];
    }
  }

  int sum(int v, int tl, int tr, int l, int r) {
    if (l > r)
      return 0;
    if (l == tl && r == tr) {
      return t[v];
    }
    int tm = (tl + tr) / 2;
    return sum(v * 2, tl, tm, l, min(r, tm)) +
           sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r);
  }

  void update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
      t[v] = new_val;
    } else {
      int tm = (tl + tr) / 2;
      if (pos <= tm)
        update(v * 2, tl, tm, pos, new_val);
      else
        update(v * 2 + 1, tm + 1, tr, pos, new_val);
      t[v] = t[v * 2] + t[v * 2 + 1];
    }
  }
};

/*
*
*
* Segment Tree(SUM) Recursion Build, v = root(1), tl = pointer of first index(0), tl = pointer of last index(n - 1)
*
*
*/
