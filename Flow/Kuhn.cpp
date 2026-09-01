#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
#define int ll
const ll INF = 4e18;
const ll MOD = 1e9;
const int MAXN = 1e6 + 5;

int kuhn(vector<vector<int>> & adj, int n, int k) {
  vector<int> mt(k, -1), used(n);

  auto tryKuhn = [&](auto & self, int u) -> bool {
    if(used[u]) return false;
    used[u] = true;
    for(int v : adj[u]) {
      if(mt[v] == -1 || self(self, mt[v])) {
        mt[v] = u;
        return true;
      }
    }
    return false;
  };

  int matching = 0;
  for(int u = 0; u < n; u++) {
    fill(begin(used), end(used), 0);
    matching += tryKuhn(tryKuhn, u);
  }
  return matching;
}