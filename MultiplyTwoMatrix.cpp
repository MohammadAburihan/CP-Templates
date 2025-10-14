vector<vector<int>> multiplyMatrix(const vector<vector<int>> &a,
                                   const vector<vector<int>> &b) {
    const size_t m = a.size();
    const size_t p = a[0].size();
    const size_t n = b[0].size();

    // Transpose B to improve locality: bt[j][k] = b[k][j]
    vector<vector<int>> bt(n, vector<int>(p));
    for (size_t k = 0; k < p; ++k)
        for (size_t j = 0; j < n; ++j)
            bt[j][k] = b[k][j];

    vector<vector<int>> res(m, vector<int>(n, 0));

    for (size_t i = 0; i < m; ++i) {
        const auto& ai = a[i];
        for (size_t j = 0; j < n; ++j) {
            const auto& bj = bt[j];
            long long sum = 0;
            size_t k = 0;
            size_t lim = p & ~size_t(3); // unroll by 4
            for (; k < lim; k += 4) {
                sum += 1LL*ai[k]*bj[k]
                     + 1LL*ai[k+1]*bj[k+1]
                     + 1LL*ai[k+2]*bj[k+2]
                     + 1LL*ai[k+3]*bj[k+3];
            }
            for (; k < p; ++k) sum += 1LL*ai[k]*bj[k];
            res[i][j] = static_cast<int>(sum);
        }
    }
    return res;
}

/*
*
*
* Multiply Two Matrix and return the result
*
*
*/
