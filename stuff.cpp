/*
* returns how many leading zeros are in the binary representation of an unsigned int.
*/
__builtin_clz(int number);
l = 32 - __builtin_clz(n); // equivalent to log2(n).

/*
* return number of set bits in the given number.
* Input: n = 5
* binary value of 5: 101
* Output: 2
*/
__builtin_popcount(int number);
