const int MOD = 1e9 + 7;
const int MAXFAC = 1e5 + 1;

int fac[MAXFAC] = {0};
int invf[MAXFAC] = {0};

int inv(int a) {
  return a <= 1 ? a : MOD - (long long)(MOD / a) * inv(MOD % a) % MOD;
}

void factorial() {
  fac[0] = 1, fac[1] = 1;
  for (int i = 2; i < MAXFAC; i++) {
    fac[i] = fac[i - 1] * i % MOD;
  }
}

void invFac() {
  invf[MAXFAC - 1] = inv(fac[MAXFAC - 1]);
  for (int i = MAXFAC - 2; i >= 0; i--) {
    invf[i] = invf[i + 1] * (i + 1) % MOD;
  }
}

int nCr(int n, int r) {
  return fac[n] * invf[r] % MOD * invf[n - r] % MOD;
}

// factorial();
// invFac();
// Don't forget to insert it to the main.

/*
*
*
* Compute nCr in O(1) time complexity.
*
* MAXFAC the size of factorial and inverse factorial arrays.
*
* MOD use to mod.
* 
* nCr is the function to compute the result.
*
*
*/
