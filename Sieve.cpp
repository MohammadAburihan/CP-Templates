#define MAXN 1000001
vector<int> spf(MAXN + 1, 1);

void sieve() {
  spf[0] = 0;
  for (int i = 2; i <= MAXN; i++) {
    if (spf[i] == 1) {
      for (int j = i; j <= MAXN; j += i) {
        if (spf[j] == 1)
          spf[j] = i;
      }
    }
  }
}

vector<int> getFactorization(int x) {
  vector<int> ret;
  while (x != 1) {
    ret.push_back(spf[x]);
    x = x / spf[x];
  }
  return ret;
}

/*
*
*
* Sieve and getFactorization of number n in log(n) time.
*
*
*/
