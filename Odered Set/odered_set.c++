#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T>
using pbds = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

--------------------------------------

declare = pbds<ll> p;
declare = pbds<pair<ll,ll>> p;

1. order_of_key → tells the position 
2. find_by_order → x index a who?


- 0 based indexing
- less = choto theke boro
- greater = boro theke choto
- less_equal = multiset
- greater_equal = ulta-multiset
--------------------------------------

||>> For less_equal and greater_equal regular erase doesnt works
we have to do it like this =>

auto it = p.find_by_order(p.order_of_key(a[x]));
if(it != p.end())p.erase(it);
---------------------------------------

==> In pair it sorts by({0, 1}, {1, 1}, {1, 2}, {2, 0});
if i find {1,3} => will give {2, 0}