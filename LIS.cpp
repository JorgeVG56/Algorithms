#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

int LIS(vector<int> & a) {
	vector<int> dp;

	for(int & x : a){
		int pos = lower_bound(dp.begin(), dp.end(), x) - dp.begin();
		if (pos == dp.size()) dp.push_back(x);
		else dp[pos] = i;
	}
    
	return dp.size();
}