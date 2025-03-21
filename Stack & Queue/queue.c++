Next Smaller Element (in a range)

deque<pair<int, int> >dq;

void add(int val, int idx){
    while(!dq.empty() && dq.back().first >= val){
        dq.pop_back();
    }
    dq.push_back({val, idx});
}

void del(int idx){
    if(!dq.empty() && dq.front().second==idx)dq.pop_front();
}

vector<int> min_range(vector<int> a, int k) {
  vector<int> ans;


  for(ll i = 0; i < k; i++) {
    add(a[i], i);
  }
  ans.pb(dq.front().first);
  for(ll i = k; i < a.size(); i++) {
    del(i - k);
    add(a[i], i);
    ans.pb(dq.front().first);
  }
  return ans;
}
