struct SuffixArray {
  int n;
  string suffixString;
  vector<int> suffix;

  SuffixArray(string str) {
    n = str.size();
    suffix = suffix_array_construction(str);
    suffixString = str;
  }

  vector<int> sort_cyclic_shifts(string const &s) {
    int n = s.size();
    const int alphabet = 256;

    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
      cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
      cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; i++)
      p[--cnt[s[i]]] = i;
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
      if (s[p[i]] != s[p[i - 1]])
        classes++;
      c[p[i]] = classes - 1;
    }

    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
      for (int i = 0; i < n; i++) {
        pn[i] = p[i] - (1 << h);
        if (pn[i] < 0)
          pn[i] += n;
      }
      fill(cnt.begin(), cnt.begin() + classes, 0);
      for (int i = 0; i < n; i++)
        cnt[c[pn[i]]]++;
      for (int i = 1; i < classes; i++)
        cnt[i] += cnt[i - 1];
      for (int i = n - 1; i >= 0; i--)
        p[--cnt[c[pn[i]]]] = pn[i];
      cn[p[0]] = 0;
      classes = 1;
      for (int i = 1; i < n; i++) {
        pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
        pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n]};
        if (cur != prev)
          ++classes;
        cn[p[i]] = classes - 1;
      }
      c.swap(cn);
    }
    return p;
  }

  vector<int> suffix_array_construction(string s) {
    s += "$";
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
  }

  // Find all occurrences of t in s using the suffix array
  vector<int> find_occurrences(const string &t) {
    int n = (int)suffixString.size();
    int m = (int)t.size();

    // comparator helpers over indices in sa
    auto less_than_t = [&](int idx) {
      // true if suffix s[idx..] < t (lexicographically by first m chars)
      return suffixString.compare(idx, m, t) < 0;
    };
    auto less_equal_t = [&](int idx) {
      // true if suffix s[idx..] <= t (by first m chars)
      return suffixString.compare(idx, m, t) <= 0;
    };

    // lower_bound: first suffix whose prefix >= t
    int lo = 0, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (less_than_t(suffix[mid]))
        lo = mid + 1;
      else
        hi = mid;
    }
    int L = lo;

    // upper_bound: first suffix whose prefix > t
    lo = 0, hi = n;
    while (lo < hi) {
      int mid = (lo + hi) / 2;
      if (less_equal_t(suffix[mid]))
        lo = mid + 1;
      else
        hi = mid;
    }
    int R = lo;

    vector<int> res;
    for (int i = L; i < R; ++i) {
      // ensure the match actually fits (optional; range logic already enforces
      // it)
      if (suffix[i] + m <= n && suffixString.compare(suffix[i], m, t) == 0)
        res.push_back(suffix[i]);
    }
    sort(res.begin(), res.end()); // positions in ascending order (optional)
    return res;
  }
};
