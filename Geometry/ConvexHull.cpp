#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct Point {
	ll x, y;
	Point(ll a = 0, ll b = 0) : x(a), y(b) {}

  Point operator+(Point p){ return {x + p.x, y + p.y}; }
  Point operator-(Point p){ return {x - p.x, y - p.y}; }
  Point operator*(Point p){ return {x * p.x - y * p.y, x * p.y + y * p.x}; }

  Point operator*(ll d){ return {x * d, y * d}; };
  Point operator/(ll d){ return {x / d, y / d}; };

  bool operator<(Point p) const { return x < p.x || (x == p.x && y < p.y); }
  bool operator==(Point p) const{ return x == p.x && y == p.y; }

  ll dot(Point p){ return x * p.x + y * p.y; }
  ll cross(Point p){ return x * p.y - y * p.x; }
  ll cross(Point p1, Point p2){ return (p1 - *this).cross(p2 - *this); }

  ll dist(Point p) { return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y); }

	friend istream &operator>>(istream &in, Point &p) {
		in >> p.x >> p.y;
		return in;
	}
};

vector<Point> convexHull(vector<Point> & a) {
  auto orientation = [&](Point a, Point b, Point c) -> int {
    double v = a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y);
    if(v < 0) return -1;
    if(v > 0) return 1;
    return 0;
  };

  auto cw = [&](Point a, Point b, Point c) -> bool {
    int o = orientation(a, b, c);
    return o < 0;
  };

  Point p0 = *min_element(begin(a), end(a), [&](Point a, Point b) -> bool {
    return a.y < b.y || (a.y == b.y && a.x < b.x);
  });

  sort(begin(a), end(a), [&](Point a, Point b) -> bool {
    int o = orientation(p0, a, b);
    if(o == 0) return p0.dist(a) < p0.dist(b);
    return o < 0;
  });

  vector<Point> st;

  for(int i = 0; i < size(a); i++) {
    while(st.size() > 1 && !cw(st[st.size() - 2], st.back(), a[i]))
      st.pop_back();
    st.push_back(a[i]);
  }

  if(st.size() == 2 && st[0] == st[1]) 
    st.pop_back();

  return st;
}