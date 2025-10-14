int compute_hash(string &s, const int m) {
  int prime = 103;
  int hs = 1;
  for (char c : s) {
    hs = hs * prime + c;
    hs %= m;
  }
  return hs;
}

/*
*
*
* Hashing of String
*
*
*/
