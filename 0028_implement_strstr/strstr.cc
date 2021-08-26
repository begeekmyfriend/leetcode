#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
	
	// Rabin-Karp Algorithm for string matching
	int strStr(string haystack, string needle) {
		long long mod = 1e9 + 7, p = 53;
		int h = haystack.size(), n = needle.size();
		if (h < n) return -1;
		if (n == 0) return 0;

		// precalculating powers of p
		vector<long long> p_pow(max(h, n));
		p_pow[0] = 1;
		for (int i = 1; i < p_pow.size(); i++) {
			p_pow[i] = (p_pow[i - 1] * p) % mod;
		}
		// calculating haystack_hash
		vector<long long> haystack_hash(haystack.size() + 1, 0);
		for (int i = 0; i < h; i++) {
			haystack_hash[i + 1] = (haystack_hash[i] + (haystack[i] - 'a' + 1) * p_pow[i]) % mod;
		}

		// calculating needle_hash
		long long needle_hash = 0;
		for (int i = 0; i < n; i++) {
			needle_hash = (needle_hash + (needle[i] - 'a' + 1) * p_pow[i]) % mod;
		}

		// checking for matching hashes
		for (int i = 0; i <= h - n; i++) {
			long long curr_hash = (haystack_hash[i + n] + mod - haystack_hash[i]) % mod;
			if (curr_hash == (needle_hash * p_pow[i]) % mod) {
				return i;
			}
		}

		// if no hash is find
		return -1;
	}
};
