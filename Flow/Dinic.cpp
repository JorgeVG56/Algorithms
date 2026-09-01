#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int INF = 1e9;

struct Edge {
  int from, to, cap, orig, rev;
};

struct Dinic {
  int n;
  vector<vector<Edge>> adj;
  vector<int> level, cur;
  
  Dinic(int n) : n(n), adj(n), level(n), cur(n) {}
  
  void addEdge(int u, int v, int cap){
    int uIdx = adj[u].size(), vIdx = adj[v].size();
    adj[u].push_back({u, v, cap, cap, vIdx});
    adj[v].push_back({v, u, 0, 0, uIdx});
  }
  
  bool bfs(int s, int t){
    fill(level.begin(), level.end(), -1); level[s] = 0;
    queue<int> q; q.push(s);
    
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto& e : adj[v]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[v] + 1; q.push(e.to);
        }
      }
    }
    
    return level[t] != -1; 
  }
  
  int dfs(int v, int t, int pushed) {
    if (v == t) return pushed;
    if (pushed == 0) return 0;
    
    for (int& i = cur[v]; i < (int)adj[v].size(); i++) {
      Edge & e = adj[v][i];
      if (e.cap <= 0 || level[e.to] != level[v] + 1) continue;
      
      int d = dfs(e.to, t, min(pushed, e.cap));
      
      if (d > 0) {
        e.cap -= d;
        adj[e.to][e.rev].cap += d;
        return d;
      }
      
      level[e.to] = -1;
    }
    
    return 0;
  }
  
  long long maxflow(int s, int t) {
    long long flow = 0;
    while (bfs(s, t)) {
      fill(cur.begin(), cur.end(), 0);
      while (int pushed = dfs(s, t, INT_MAX)) flow += pushed;
    }
    return flow;
  }
  
  vector<Edge> minCut(int s) {
    vector<bool> inS(n, false); inS[s] = true;
    queue<int> q; q.push(s);
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (auto& e : adj[v])
      if (e.cap > 0 && !inS[e.to]) {
        inS[e.to] = true;
        q.push(e.to);
      }
    }
    
    vector<Edge> cut;
    for (int u = 0; u < n; u++) {
      if (!inS[u]) continue;
      for (auto& e : adj[u])
      if (!inS[e.to] && e.orig > 0)
      cut.push_back(e);
    }
    
    return cut;
  }
};