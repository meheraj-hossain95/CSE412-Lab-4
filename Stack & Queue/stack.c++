//Next Smaller Element

vector<int> NSE(vector<int>a) {
  vector<int>result(a.size());
  stack<int>st;
  for(ll i = a.size() - 1; i >= 0; i--) {
    while(!st.empty() and a[st.top()] > a[i]) {
      st.pop();
    }
    if(st.empty())result[i] = -1;
    else result[i] = st.top();
    st.push(i);
  }
  return result;
}
