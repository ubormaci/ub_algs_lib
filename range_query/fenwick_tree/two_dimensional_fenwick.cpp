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
// #pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2","fma")
 
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
 
cout << fixed << setprecision(n);
 
set with custom ordering
set<ll, decltype(&cmp)> qu(cmp);
 
*/
 
typedef int64_t ll;
 
class fenwick_twodim{
 
	// forced one-indexing
	// or, well, could manually corrigate it, but it's easier this way
 
	private:
		ll n;
		ll m;
		vector<vector<ll>> base;
		vector<vector<ll>> v;
 
		ll q(ll y, ll x) {
			
			//cerr << "\nat query " << y << " " << x;
 
			ll ret = 0;
 
			while(y > 0) {
 
				ll xh = x;
				while(xh > 0) {
					ret += v[y][xh];
					ll xlen = xh & (-xh);
					xh -= xlen;
				}
 
				ll ylen = y & (-y);
				y -= ylen;
			}
 
			//cerr << "\nreturn is " << ret;
 
			return ret;
		}
 
	public:
 
		void init(ll ni, ll mi, vector<vector<ll>> &inp) {
			
			n = ni;
			m = mi;
			base.assign(n, vector<ll>(m, 0));
			v.assign(n, vector<ll>(m, 0));
 
			for(ll i = 1; i < n; i++) {
				for(ll j = 1; j < n; j++) {
					base[i][j] = inp[i][j];
				}
			}
 
			// na jo itt jon a komplikalt resze
 
			vector<vector<ll>> pref(n, vector<ll>(m, 0));
			
			for(ll i = 1; i < n; i++) {
				for(ll j = 1; j < m; j++) {
					pref[i][j] = base[i][j] + pref[i][j-1];
				}
			}
 
			for(ll i = 1; i < n; i++) {
				for(ll j = 1; j < m; j++) {
					pref[i][j] += pref[i-1][j];
				}
			}
 
			// pelda, hogy egy 1D-ben hogy mukodik
			// fenwick[i] = prefix[i] - prefix[i - (i & (-i))]
 
			for(ll i = 1; i < n; i++) {
				for(ll j = 1; j < m; j++) {
 
					ll ilen = i & (-i);
					ll jlen = j & (-j);
 
					ll ip = i - ilen;
					ll jp = j - jlen;
 
					v[i][j] += pref[i][j];
					v[i][j] -= pref[ip][j];
					v[i][j] -= pref[i][jp];
					v[i][j] += pref[ip][jp];
				}
			}
 
			//cerr << "\ntwo d prefixes computed as\npref=" << pref;
			//debug();
		}
 
		void debug() {
			cerr << "\nn=" << n << "\nm=" << m << "\nbase=" << base << "\nv=" << v;
		}
 
		ll query(ll y1, ll x1, ll y2, ll x2) {
 
			//cerr << "\nquerying " << y1 << " " << x1 << " " << y2 << " " << x2 << " rectangle";
 
			ll s1 = q(y2, x2);
			ll s2 = q(y2, x1-1);
			ll s3 = q(y1-1, x2);
			ll s4 = q(y1-1, x1-1);
 
			ll res = s1 - s2 - s3 + s4;
 
			return res;
		}	
 
		void update(ll y, ll x) {
 
			//cerr << "\nupdating " << y << " " << x;
 
			ll val = 1 - base[y][x];
			ll diff = val - base[y][x];
			base[y][x] = val;
			
			while(y < n) {
 
				ll xh = x;
				while(xh < m) {
					v[y][xh] += diff;
					ll len = xh & (-xh);
					xh += len;
				}
				ll ylen = y & (-y);
				y += ylen;
			}
		}
};
 
void solve() {
	
	// 2d-s segment tree?
	// eleg durva
 
	// ha van n darab 1d-s segment tree
	// akkor minden query O(n log n) idoben megvaloszalhato
	// ami kicsit geci, mert q = 2 * 10^5 n = 10^3 ~ 2 * 10^9
 
	ll n, q;
	cin >> n >> q;
	vector<vector<ll>> v(n+1, vector<ll>(n+1, 0));
	for(ll i = 1; i <= n; i++) {
		for(ll j = 1; j <= n; j++) {
			char c;
			cin >> c;
			if(c == '*') {
				v[i][j] = 1;
			}
		}
		//cerr << "\ni=" << i << "; h=" << h;
	}
 
	fenwick_twodim fen;
	fen.init(n+1, n+1, v);
 
	for(ll qi = 0; qi < q; qi++) {
 
		ll type;
		cin >> type;
 
		if(type == 1) {
 
			ll x, y;
			cin >> y >> x;
 
			fen.update(y, x);
 
		}else if(type == 2) {
 
			ll x1, y1, x2, y2;
			cin >> y1 >> x1 >> y2 >> x2;
 
			ll here = fen.query(y1, x1, y2, x2);
 
			cout << here << "\n";
		}
 
	}
 
}
 
int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
 
	solve();
 
	return 0;
}

/*

Two-dimensional fenwick tree template written for CSES Forest Queries II
supports two-dimensional range queries and point updates in log^2 n time

*/