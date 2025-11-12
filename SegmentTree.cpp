#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Item{

  Item (int n) { }

  Item operator+(Item item){

  }
};

struct SegmentTree{
  #define lp (u << 1) + 1
  #define rp (u << 1) + 2

  int n;
  vector<Item> st;

  SegmentTree(int n) : n(n), st(n << 2) { }

  void build(int u, int tl, int tr, vector<int> & a){
    if(tl == tr){
      st[u] = a[tl];
      return ;
    }

    int tm = (tl + tr) >> 1;
    build(lp, tl, tm, a); build(rp, tm + 1, tr, a);
    st[u] = st[lp] + st[rp];
  }

  void update(int u, int tl, int tr, int idx, int x){
    if(tl == tr){
      st[u] = x;
      return;
    }

    int tm = (tl + tr) >> 1;
    if(idx <= tm) update(lp, tl, tm, idx, x);
    else update(rp, tm + 1, tr, idx, x);
    st[u] = st[lp] + st[rp];
  }

  Item query(int u, int tl, int tr, int l, int r){
    if(r < l) return 0;
    if(tl == l && tr == r) return st[u];

    int tm = (tl + tr) >> 1;
    return query(lp, tl, tm, l, min(tm, r)) + query(rp, tm + 1, tr, max(l, tm + 1), r);
  }


  void build(vector<int> & a){
    build(0, 0, n - 1, a);
  }

  void update(int idx, int x){
    update(0, 0, n - 1, idx, x);
  }

  Item query(int l, int r){
    return query(0, 0, n - 1, l, r);
  }
};