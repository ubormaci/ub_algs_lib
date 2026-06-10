#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
// #pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")
 
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
 
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cout << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cout << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cout << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif
 
/*
 
notes:
 
int64_t
stoi(string s) -> string to int
to_string() -> int (or else) to string
 
vector declaration:
vector<ll> v(n, 0)
vector<vector<ll>> v(n, vector<ll>(n, 0));
 
{if statement} ? {truth value} : {false value}
 
#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
 
std::lcm(ll a, ll b), std::gcd(int a, int b)
 
cout << fixed << setprecision(n);
 
set with custom ordering
set<ll, decltype(&cmp)> qu(cmp);
 
*/
 
typedef int64_t ll;

class fenwick{
 
	// forced one-indexing
	// or, well, could manually corrigate it, but it's easier this way
 
	private:
		ll n;
		vector<ll> base;
		vector<ll> v;
 
		ll q(ll x) {
 
			ll ret = 0;
            while(x > 0) {
                ret += v[x];
                ll len = x & (-x);
                x -= len;
            }
            return ret;
		}
 
	public:
 
		void init(ll siz, vector<ll> inp) {
			
			n = siz;
			base.assign(n, 0);
			v.assign(n, 0);
 
			vector<ll> pref(n, 0);
 
			for(ll i = 0; i < n; i++) {
				base[i] = inp[i];
				pref[i] = base[i];
				if(i > 0) {
					pref[i] += pref[i-1];
				}
			}
 
			// minden poziciora eltaroljuk onmagat minusz az elozo pozicio
			for(ll i = 1; i < n; i++) {
 
				ll len = i & (-i);
				//cerr << "\ni=" << i << "; len=" << len;
				v[i] = pref[i] - pref[i- len];
			}
		}
 
		void debug() {
			cerr << "\nn=" << n << "\nbase=" << base << "\nv=" << v;
		}
 
		ll query(ll l, ll r) {
			return q(r) - q(l-1);
		}	
 
		void update(ll ind, ll val) {
 
			ll diff = val - base[ind];
			base[ind] = val;
 
			while(ind < n) {
 
				v[ind] += diff;
				ll len = ind & (-ind);
				ind += len;
			}
		}
};
 
void solve() {
 
	ll n, q;
	cin >> n >> q;
 
	vector<ll> v(n+1, 0);
	for(ll i = 1; i <= n; i++) {
		cin >> v[i];
	}
 
	//cerr << "\nv=" << v;
 
	fenwick st;
	st.init(n+1, v);
 
	//st.debug();
 
	for(ll i = 0; i < q; i++) {
		
		ll type;
		cin >> type;
 
		if(type == 1) {
 
			ll ind, val;
			cin >> ind >> val;
 
			st.update(ind, val);
 
		}else if(type == 2) {
 
			ll a, b;
			cin >> a >> b;
            
            ll ans = st.query(a, b);
			cout << ans << "\n";
		}
 
		//st.debug();
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

Point update range query sum Fenwick tree
tested on CSES Dynamic Range Sum Queries

*/