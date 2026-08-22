#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

void findBridges(vector<vector<pair<int, int>>> & adj, vector<bool> & isBridge) {
  int n = adj.size();
  vector<int> vis(n), tin(n, -1), low(n, -1);
  int t = 0;

  auto dfs = [&](auto & self, int u, int p = -1) -> void {
    vis[u] = 1; tin[u] = low[u] = t++;

    bool parentSkipped = false;
    for(auto [v, idx] : adj[u]) {
      if(v == p && !parentSkipped) {
        parentSkipped = true;
        continue;
      }
      if(vis[v]) {
        low[u] = min(low[u], tin[v]);
      } else{
        self(self, v, u);
        low[u] = min(low[u], low[v]);
        if(low[v] > tin[u]) isBridge[idx] = true;
      }
    }
  };

  for(int u = 0; u < n; u++) {
    if(vis[u]) continue;
    dfs(dfs, u);
  }
}