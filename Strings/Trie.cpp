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
};
