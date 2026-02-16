#include <iostream>
#include <algorithm> // for sort, mainly
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <array>
#include <string>
#include <cstdio>
#include <iterator>
#include <unordered_set>
#include <cstdint> // for int64_t, int32_t, etc
#include <queue>
#include <stack>
#include <deque>
#include <numeric> // gcd, lcm
#include <fstream>
#include <bitset> // for bitset
#include <iomanip>
#include <cassert> // for set with custom ordering
#include <type_traits> // for set with custom ordering
#include <utility> // for swap, forward, etc
using namespace std;
 
#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
//#pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
typedef int64_t ll;
 
class sqrtdecomp{
 
    private:
        ll n;
        ll sq;
        vector<ll> s;
        vector<ll> v;
 
    public:
 
        void build(ll size, vector<ll> input) {
 
            n = size;
            sq = sqrtl(n);
            if(sq * sq < n) {
                sq++;
            }
            v.resize(n, 0);
            s.resize(sq, 1e9+1);
 
            for(ll i = 0; i < sq; i++) {
                for(ll j = sq * i; j < min(sq * (i+1), n); j++) 
                {
 
                    v[j] = input[j];
                    s[i] = min(s[i], v[j]);
                }
            }
 
            //cerr << "\nv=" << v;
            //cerr << "\ns=" << s;
        }
 
        void upd(ll pos, ll val) {
 
            ll seg = pos / sq;
            v[pos] = val;
            
            s[seg] = 1e9 + 1;
 
            for(ll i = seg * sq; i < min((seg +1) * sq, n); i++) {
 
                s[seg] = min(s[seg], v[i]);
            }
 
        }
 
        ll query(ll l, ll r) {
 
            //cerr << "\nquery, l=" << l << "; r=" << r;
 
            ll ans = 1e9 + 1;
 
            ll lseg = l / sq;
            ll rseg = r / sq;
            if(lseg == rseg) {
                for(ll i = l; i <= r; i++) {
                    ans = min(ans, v[i]);
                }
            }else{
 
                for(ll i = l; i < (lseg + 1) * sq; i++) {
                    ans = min(ans, v[i]);
                }
                //cerr << "\nans after left=" << ans;
 
                for(ll i = rseg * sq; i <= r; i++) {
                    ans = min(ans, v[i]);
                }
                //cerr << "\nans after right=" << ans;
 
                for(ll i = lseg + 1; i <= rseg - 1; i++) {
                    ans = min(ans, s[i]);
                }
                //cerr << "\nans after mid=" << ans;
            }
 
            return ans;
        }
};
 
void solve() {
 
    ll n, q;
    cin >> n >> q;
    vector<ll> v(n, 0);
    for(ll i = 0; i < n; i++) {
        cin >> v[i];
    }
 
    sqrtdecomp sq;
    sq.build(n, v);
 
    for(ll qi = 0; qi < q; qi++) {
        ll t;
        cin >> t;
        if(t == 1) {
            ll pos, val;
            cin >> pos >> val;
            sq.upd(pos - 1, val);
        }else{
            ll a, b;
            cin >> a >> b;
            cout << sq.query(a - 1, b - 1) << "\n";
        }
    }
 
}
 
int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);
 
	solve();
 
	return 0;
}

/*

tested for CSES Dynamic Range Minimum Queries
https://cses.fi/problemset/task/1649

Given an array of n integers, your task is to process q queries of the following types:

update the value at position k to u
what is the minimum value in range [a,b]?

*/