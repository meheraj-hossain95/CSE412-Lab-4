ll a[N];

struct segmenttree {
  ll t[4 * N];
  static const int inf = 1e9; // !! HERE !!
  segmenttree() {
    memset(t, 0, sizeof t);
  }
  void build(ll n, ll b, ll e) {
    if (b == e) {
      t[n] = a[b];
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[n] = (t[l] + t[r]); // !! HERE !!
  }
  void update(ll n, ll b, ll e, ll i, ll x) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n] = x; // !! UPDATE !!
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    update(l, b, mid, i, x);
    update(r, mid + 1, e, i, x);
    t[n] = (t[l] + t[r]); // !! HERE !!
  }
  ll query(ll n, ll b, ll e, ll i, ll j) {
    if (b > j || e < i) return 0; // !! HERE !!
    if (b >= i && e <= j) return t[n];
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    return (query(l, b, mid, i, j) + query(r, mid + 1, e, i, j)); // !! HERE !!
  }
};

/*
  segmenttree tree;
  do one base indexing;
  tree.build(1, 1, n);
  tree.update(1, 1, n, pos, value);
  tree.query(1, 1, n, range_left, range_right);
*/
