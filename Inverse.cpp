const int MOD = 1e9 + 7;

int inv(int a) {
  return a <= 1 ? a : MOD - (long long)(MOD / a) * inv(MOD % a) % MOD;
}

/*
*
*
* Inverse in CPP
*
*
*/
