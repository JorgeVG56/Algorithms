#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

pair<vector<vector<int>>, int> cdfs(vector<vector<int>> & adj) {
  int n = size(adj); 

  vector<int> size(n), taken(n);
  auto dfsZ = [&](auto & self, int u, int p = -1) -> int {
    size[u] = 1;
    for(int v : adj[u]) {
      if(v == p || taken[v]) continue;
      size[u] += self(self, v, u);
    }
    return size[u];
  };

  auto dfsC = [&](auto & self, int u, int sz, int p = -1) -> int {
    for(int v : adj[u]) {
      if(v == p || taken[v] || size[v] * 2 <= sz) continue;
      return self(self, v, sz, u);
    }
    return u;
  };

  vector<vector<int>> centroidTree(n);

  auto buildCentroidTree = [&](auto & self, int u = 0) -> int {
    int centroid = dfsC(dfsC, u, dfsZ(dfsZ, u));
    taken[centroid] = true;
    for(int v : adj[centroid]) {
      if(taken[v]) continue;
      int newCentroid = self(self, v);
      adj[centroid].push_back(newCentroid);
      adj[newCentroid].push_back(centroid);
    }
    return centroid;
  };

  int root = buildCentroidTree(buildCentroidTree);

  return {centroidTree, root};
}