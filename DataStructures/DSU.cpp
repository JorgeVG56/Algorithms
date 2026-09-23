#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ui = unsigned int;
const ll INF = 4e18;
const ll MOD = 1e9;
const int MAXN = 1e6 + 5;

struct DSU {
  int n;
  vector<int> parent, rank;

  DSU(int n) : n(n), parent(n, -1), rank(n, 1) { }

  int head(int u) {
    if(parent[u] == -1) return u;
    return parent[u] = head(parent[u]);
  }

  void join(int u, int v) {
    u = head(u), v = head(v);
    if(u == v) return;
    if(rank[u] < rank[v]) swap(u, v);
    parent[v] = u;
    rank[u] += rank[v];
  }
};