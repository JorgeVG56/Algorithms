#pragma GCC optimize("O3,unroll-loops")
#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Node{
  int nxt[26];
  int suffix;

  Node(){
    memset(nxt, -1, sizeof(nxt));
    suffix = -1;
  }
};

vector<Node> nodes;

struct Trie{
  int root = -1;

  Trie(){
    root = size(nodes); nodes.emplace_back();
  }

  void insert(string s){
    int node = root;
    for(char c : s){
      if(nodes[node].nxt[c - 'a'] == -1){
        nodes[node].nxt[c - 'a'] = size(nodes); nodes.emplace_back();
      }
      node = nodes[node].nxt[c - 'a'];
    }
  }

  void bfs(){
    queue<int> q;
    for(int i = 0; i < 26; i++){
      if(nodes[root].nxt[i] != -1) continue;
      nodes[nodes[root].nxt[i]].suffix = root;
      q.push(nodes[root].nxt[i]);
    }

    while(!q.empty()){
      int u = q.front(); q.pop();
      for(int i = 0; i < 26; i++){
        if(nodes[u].nxt[i] == -1) continue;
        int node = nodes[u].suffix;
        while(nodes[node].nxt[i] == -1) node = nodes[node].suffix;
        nodes[nodes[u].nxt[i]].suffix = nodes[node].nxt[i];
      }
    }
  }
};
