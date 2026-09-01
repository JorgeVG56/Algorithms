#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e9;

struct Edge{
  int u, v, cap, cost; 
};

vector<vector<int>> adj, cost, cap;

void shortestPaths(int n, int u, vector<int> & dp, vector<int> & par){
  dp.assign(n, INF); dp[u] = 0;
  par.assign(n, -1);
  vector<bool> vis(n); vis[u] = true;
  queue<int> q; q.push(u);

  while(!q.empty()){
    int u = q.front(); q.pop();
    vis[u] = false;
    for(int & v : adj[u]){
      if(cap[u][v] <= 0 || dp[v] <= dp[u] + cost[u][v]) continue;
      dp[v] = dp[u] + cost[u][v];
      par[v] = u;
      if(vis[v]) continue;
      vis[v] = true;
      q.push(v);
    }
  }
}

int minCostFlow(int n, vector<Edge> & edges, int k, int s, int t){
  adj.assign(n, vector<int>());
  cost.assign(n, vector<int>(n));
  cap.assign(n, vector<int>(n));
  for(auto & e : edges){
    adj[e.u].push_back(e.v);
    adj[e.v].push_back(e.u);
    cost[e.u][e.v] = e.cost;
    cost[e.v][e.u] = -e.cost;
    cap[e.u][e.v] = e.cap;
  }

  int flow = 0, cost = 0;
  vector<int> dp, par;
  while(flow < k){
    shortestPaths(n, s, dp, par);
    if(dp[t] == INF) break;

    int f = k - flow, cur = t;
    while(cur != s) f = min(f, cap[par[cur]][cur]), cur = par[cur];

    flow += f, cost += f * dp[t], cur = t;
    while(cur != s) cap[par[cur]][cur] -= f, cap[cur][par[cur]] += f, cur = par[cur];
  }

  if(flow < k) return -1;
  else return cost;
}