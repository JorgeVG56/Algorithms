#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

void BCTree(vector<vector<int>> & adj, vector<vector<int>> & bcTree, vector<vector<int>> & blocks, vector<bool> & isCut) {
  int n = adj.size(); isCut.assign(n, 0);

  vector<int> tin(n, -1), low(n, -1), st;
  int t = 0;

  auto dfsT = [&](auto & self, int u, int p = -1) -> void {
    tin[u] = low[u] = t++;
    st.push_back(u);
    int children = 0;

    for(auto v : adj[u]) {
      if(v == p) continue;

      if(tin[v] != -1) {
        low[u] = min(low[u], tin[v]);
      } else {
        children++;
        self(self, v, u);
        low[u] = min(low[u], low[v]);
        if(low[v] >= tin[u]) {
          if(p != -1) isCut[u] = true;

          vector<int> block = {u};
          while(1) {
            int node = st.back(); st.pop_back();
            block.push_back(node);
            if(node == v) break;
          }
          blocks.push_back(block);
        }
      }
    }

    if(p == -1 && children > 1) 
      isCut[u] = true;
  };

  for(int u = 0; u < n; u++) 
    if(tin[u] == -1)
      dfsT(dfsT, u);

  int numBlocks = blocks.size();
  int newN = n + numBlocks;

  bcTree.assign(newN, vector<int>());

  for(int block = 0; block < numBlocks; block++) {
    int blockNode = n + block;
    for(int u : blocks[block]) {
      bcTree[blockNode].push_back(u);
      bcTree[u].push_back(blockNode);
    }
  }
}