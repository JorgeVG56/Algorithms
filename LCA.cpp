#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

vector<vector<int>> jmp;
vector<int> depth;

void preCalc(vector<vector<int>> & adj, int root = 0) {
  int n = size(adj);
  jmp.assign(24, vector<int>(n, -1));
  depth.assign(n, 0);
  auto dfs = [&](auto & self, int u, int p = -1) -> void {
    jmp[u][0] = p;
    for(int i = 1; i < 24; i++) 
      if(jmp[i - 1][u] != -1) 
        jmp[i][u] = jmp[i - 1][jmp[i - 1][u]];

    for(int v : adj[u]) {
      if(v == p) continue;
      depth[v] = depth[u] + 1;
      self(self, v, u);
    }
  }; dfs(dfs, root);
}

int lca(int u, int v) {
  if(depth[u] < depth[v]) swap(u, v);
  int dist = depth[u] - depth[v];
  for(int i = 31; i >= 0; i--) 
    if((dist >> i) & 1) u = jmp[i][u];

  if(u == v) return u;
  
  for(int i = 31; i >= 0; i--) {
    if(jmp[i][u] == jmp[i][v]) continue;
    u = jmp[i][u], v = jmp[i][v];
  }

  return jmp[0][u];
}