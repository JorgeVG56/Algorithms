#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = 1e9;

struct Edge {
  int to, cap, cost, rev;
};

vector<vector<Edge>> adj;
vector<int> disS, disD;;
vector<pair<int, int>> par;

void addEdge(int from, int to, int cap, int cost) {
  adj[from].push_back({to, cap, cost, (int)adj[to].size()});
  adj[to].push_back({from, 0, -cost, (int)adj[from].size() - 1});
}

void initialSPFA(int n, int s) {
  fill(begin(disS), end(disS), INF); disS[s] = 0;
  vector<bool> vis(n); vis[s] = true;
  queue<int> q; q.push(s);
  
  while(!q.empty()) {
    int u = q.front(); q.pop(); vis[u] = false;
    
    for(auto& e : adj[u]) {
      if (e.cap <= 0 || disS[e.to] <= disS[u] + e.cost) continue;
      disS[e.to] = disS[u] + e.cost;
      if(vis[e.to]) continue;
      vis[e.to] = true;
      q.push(e.to);
    }
  }
}

bool dijkstra(int n, int s, int t) {
  fill(begin(disD), end(disD), INF); disD[s] = 0;
  fill(begin(par), end(par), make_pair(-1, -1)); 
  
  priority_queue<pair<int, int>> pq; pq.push({0, s});
  
  while(!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    d *= -1;
    
    if(d > disD[u]) continue;
    
    for(int i = 0; i < adj[u].size(); i++) {
      auto & e = adj[u][i];
      if(e.cap <= 0) continue;
      int reduced_cost = e.cost + disS[u] - disS[e.to]; 
      if(disD[e.to] <= disD[u] + reduced_cost) continue;
      disD[e.to] = disD[u] + reduced_cost;
      par[e.to] = {u, i};
      pq.push({-disD[e.to], e.to});
    }
  }
  return disD[t] != INF;
}

int minCostFlow(int n, int k, int s, int t) {
  disS.assign(n, 0);
  disD.assign(n, 0);
  par.assign(n, {-1, -1});

  initialSPFA(n, s);
  
  int flow = 0, totalCost = 0;
  
  while (flow < k) {
    if (!dijkstra(n, s, t)) break;
    
    for (int i = 0; i < n; i++) 
      if (disD[i] != INF) disS[i] += disD[i];
    
    int f = k - flow, cur = t;
    
    while (cur != s) {
      int p = par[cur].first, idx = par[cur].second;
      f = min(f, adj[p][idx].cap), cur = p;
    }
    
    flow += f, totalCost += f * disS[t];
    cur = t;
    
    while (cur != s) {
      int p = par[cur].first, idx = par[cur].second, revIdx = adj[p][idx].rev;
      adj[p][idx].cap -= f, adj[cur][revIdx].cap += f, cur = p;
    }
  }
  
  if (flow < k) return INF;
  return totalCost;
}