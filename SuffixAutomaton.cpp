#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct SuffixAutomaton {
  struct State {
    int len = 0, link = -1, nxt[26];
    ll dp = -1;
    State() { 
      fill(nxt, nxt + 26, -1); 
    }
  };
  
  State st[200005];
  int sz = 1, last = 0;
  
  SuffixAutomaton(string s) {
    for (char c : s) extend(c);
  }
  
  void extend(char c) {
    int x = c - 'a', cur = sz++, p = last;
    st[cur].len = st[last].len + 1;
    
    while (p != -1 && st[p].nxt[x] == -1) st[p].nxt[x] = cur, p = st[p].link;
    
    if (p == -1) st[cur].link = 0;
    else {
      int q = st[p].nxt[x];
      if (st[p].len + 1 == st[q].len) st[cur].link = q;
      else {
        int clone = sz++;
        st[clone] = st[q];
        st[clone].len = st[p].len + 1;
        while (p != -1 && st[p].nxt[x] == q)
        st[p].nxt[x] = clone, p = st[p].link;
        st[q].link = st[cur].link = clone;
      }
    }
    last = cur;
  }
};