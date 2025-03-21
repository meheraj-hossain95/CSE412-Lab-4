Flipping range and asking for sum of range.(For 1,0)

const int N = 1e3 + 9;
int a[N];

struct lazy_segmenttree {
  #define lc (n << 1)
  #define rc ((n << 1) | 1)
  pair<ll, ll> t[4 * N];
  ll lazy[4 * N];
  lazy_segmenttree() {
    memset(t, 0, sizeof t);
    memset(lazy, 0, sizeof lazy);
  }
  inline void push(int n, int b, int e) {
    if (lazy[n] == 0) return;
    swap(t[n].F,t[n].S);
    if (b != e) {
      lazy[lc] = lazy[lc] ^ lazy[n];
      lazy[rc] = lazy[rc] ^ lazy[n];
    }
    lazy[n] = 0;
  }
  inline long long combine(long long a,long long b) {
    return a + b;
  }
  inline void pull(int n) {
    t[n].F = t[lc].F + t[rc].F;
    t[n].S = t[lc].S + t[rc].S;
  }
  void build(int n, int b, int e) {
    lazy[n] = 0;
    if (b == e) {
    	// cout << a[b] << el;
      t[n] = {a[b], a[b]^1};
      return;
    }
    int mid = (b + e) >> 1;
    build(lc, b, mid);
    build(rc, mid + 1, e);
    pull(n);
  }
  void update(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (j < b || e < i) return;
    if (i <= b && e <= j) {
      lazy[n] ^= 1; //set lazy
      push(n, b, e);
      return;
    }
    int mid = (b + e) >> 1;
    update(lc, b, mid, i, j);
    update(rc, mid + 1, e, i, j);
    pull(n);
  }
  ll query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (i > e || b > j) return 0; //return null
    if (i <= b && e <= j) return t[n].F;
    int mid = (b + e) >> 1;
    return combine(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
  }
};

=====================================================================================================================
=====================================================================================================================
=====================================================================================================================

Number of bigger elements in the left and numbers of smaller elements in the right with array compression  

const ll N = 1e6 + 10; // !! HERE !! 

struct segmenttree {
  ll t[4 * N];
  static const int inf = 1e9; // !! HERE !!
  segmenttree() {
    memset(t, 0, sizeof t);
  }
  void build(ll n, ll b, ll e) {
    if (b == e) {
      t[n] = 0;
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    build(l, b, mid);
    build(r, mid + 1, e);
    t[n] = (t[l] + t[r]); // !! HERE !!
  }
  void update(ll n, ll b, ll e, ll i) {
    if (b > i || e < i) return;
    if (b == e && b == i) {
      t[n]++; // !! UPDATE !!
      return;
    }
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    update(l, b, mid, i);
    update(r, mid + 1, e, i);
    t[n] = (t[l] + t[r]); // !! HERE !!
  }
  ll query(ll n, ll b, ll e, ll i, ll j) {
    if (b > j || e < i) return 0; // !! HERE !!
    if (b >= i && e <= j) return t[n];
    int mid = (b + e) >> 1, l = n << 1, r = l | 1;
    return (query(l, b, mid, i, j) + query(r, mid + 1, e, i, j)); // !! HERE !!
  }
};

void solve() {

  ll n; cin >> n;
  ll a[n], b[n];
  std::vector<ll> big(n, 0), small(n, 0);

  // Aarray Compression 
  for(ll i = 0; i < n; i++) {
    cin >> a[i];
    b[i] = a[i];
  }
  sort(b, b + n);
  map<ll,ll>cmp;
  for(ll i = 0; i < n; i++)cmp[b[i]] = i + 1;
  for(ll i = 0; i < n; i++) {
    a[i] = cmp[a[i]];
    b[i] = cmp[b[i]];
  }
  // --------------------------
  segmenttree tree;

  tree.build(1, 1, n);
  tree.update(1, 1, n, a[0]);
  for(ll i = 1; i < n - 1; i++) {
    big[i] = i - tree.query(1, 1, n, 1, a[i]);
    tree.update(1, 1, n, a[i]);
  }

  segmenttree tree1;
  tree1.build(1, 1, n);
  tree1.update(1, 1, n, a[n - 1]);
  for(ll i = n - 2; i > 0; i--) {
    small[i] = tree1.query(1, 1, n, 1, a[i]);
    tree1.update(1, 1, n, a[i]);
  }
}   
// big got the bigger elements from left and small got smaller element from right.

