#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<vector<int>> graphDegeneracy(vector<vector<int>> & adj) {
  int n = adj.size();

  set<int> added;
  vector<int> degree(n);
  for(int i = 0; i < n; i++) {
    degree[i] = size(adj[i]);
  }

  vector<set<int>> vertices(n);
  for(int i = 0; i < n; i++) {
    vertices[degree[i]].insert(i);
  }

  vector<vector<int>> adjDegen(n);
  for(int i = 0; i < n; i++) {
    int j = 0;
    while(vertices[j].empty()) j++;
    int u = *vertices[j].begin(); vertices[j].erase(u);
    added.insert(u);
    for(int v : adj[u]) {
      if(added.count(v)) continue;
      adjDegen[u].push_back(v);
      vertices[degree[v]--].erase(v);
      vertices[degree[v]].insert(v);
    }
  }

  return adjDegen;
}