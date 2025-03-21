#include<bits/stdc++.h>
using namespace std;

#include <vector>
const int N = 2e5+5, K = 20;
// K -> How many jumps ; 

vector<int> adj[N];
int t, tin[N], tout[N], dep[N], par[N][K]; 

// O(nlogn)
void dfs(int u, int p) {
  tin[u] = t++;
  par[u][0] = p;
  for (int k = 1; k < K; ++k) {
    par[u][k] = par[par[u][k - 1]][k - 1];
  }
  for (auto v: adj[u]) {
    if (v == p)  continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
  tout[u] = t++;
}

// O(1) --> is u an ancestor of v? 
bool is_anc(int u, int v){
  return tin[u] <= tin[v] and tout[u] >= tout[v];
}

// O(log(n))
int lca(int u, int v){
  if(is_anc(u, v))  return u;
  for(int k = K - 1; k >= 0; k--){
    if(!is_anc(par[u][k], v)) {
      u = par[u][k];
    }
  }
  return par[u][0];
}

// O(1)
int dis(int u, int v) {
  return dep[u] + dep[v] - 2 * dep[lca(u, v)];
}

// O(log(n))
int get_kth_ancestor(int u, int k) {
    for (int i = 0; i < K and u != -1; i++) {
        if (k & (1 << i)) {
            u = par[u][i];
        }
    }
    return u;
}
// - ALternate : 
int kth_anc(int u, int k) {
  for (int j = K - 1; j >= 0; --j) {
    if(k >= (1 << j)) {
      u = par[u][j];
      k -= (1 << j);
    }
  }
  return u;
}
 // - // 


int main(){
  int n, q;  
  cin >> n >> q;

  // If parent of nodes from 2 to n is given
  for (int u = 1; u < n; ++u) {
    int p;  
    cin >> p;  
    p--;
    adj[p].push_back(u);
  }

  // If edges are given
  for (int e = 0; e < n - 1; ++e) {
    int u, v;  
    cin >> u >> v;  
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(0, 0);
  while (q--) {
    int u, v;  
    cin >> u >> v; 
    u--, v--;
    int l = lca(u, v);
    int d = dis(u, v);
  }
}
