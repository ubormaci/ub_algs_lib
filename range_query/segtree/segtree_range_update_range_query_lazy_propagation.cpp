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

class segtree{
	
	// zero-indexed

	private:
		ll n;
		ll lim;
		vector<vector<ll>> v;
		vector<ll> tp; // two-powers
		const ll dummy = 0; // for sum = 0

		ll join(const ll a, const ll b) {
			return a + b;
		}

		ll build(ll curr, ll level) {

			//cerr << "\nbuild, curr=" << curr << "; level=" << level;

			if(curr < 0 || curr >= n) {
				return dummy;
			}

			if(level == 0) {
				return v[level][curr];
			}else{
				v[level][curr] = join(build(2 * curr, level-1), build(2 * curr+1, level-1));
				return v[level][curr];
			}

		}

		ll q(ll curr, ll level, ll l, ll r) {

			// egy adott node-ra 3 valasz van:
			// a keresett intervallum egyaltalan nem metszi, return dummy
			// a keresett intervallum reszlegesen metszi -> tovabbhivjuk a gyerekeire
			// a keresett intervallum teljesen metszi -> visszakuldjuk a sajat erteket

			//cerr << "\ncurr=" << curr << "; level=" << level << "; l=" << l << "; r=" << r;

			ll lh = curr * tp[level];
			ll rh = curr * tp[level] + tp[level] - 1;
			if(rh >= n) {
				rh = n-1;
			}

			//cerr << "\nlh=" << lh << "; rh=" << rh;

			// nincs metszes
			if(r < lh || rh < l) {
				return dummy;
			}
			
			// teljesen benne van
			if(l <= lh && rh <= r) {
				return v[level][curr];
			}

			// reszlegesen van benne

			return join(q(curr * 2, level-1, l, r), q(curr * 2 + 1, level-1, l, r));
		}

	public:

		void init(ll size, vector<ll> inp) {

			n = size;
			lim = ceil(log2(n)) + 1;

			tp.assign(lim, 1);
			for(ll i = 1; i < lim; i++) {
				tp[i] = 2 * tp[i-1];
			}

			v.assign(lim, vector<ll>(n, 0));
			for(ll i = 0; i < n; i++) {
				v[0][i] = inp[i];
			}

			//cerr << "\nmid-init:";
			//debug();

			build(0, lim-1);
		}

		void debug() {
			cerr << "\nn=" << n << "; lim=" << lim;
			cerr << "\nv, top-to-bottom:\n";
			for(ll i = lim-1; i >= 0; i--) {
				cerr << v[i] << "\n";
			}
		}

		/*
		void upd(ll ind, ll val) {

			ll diff = val;

			ll level = 0;
			while(level < lim) {
				
				v[level][ind] += diff;
				
				ind /= 2;
				level++;
			}
		}
		*/

		// range update, add to sum
		void upd(ll l, ll r, ll val) {
			
		}	

		ll query(ll l, ll r) {
			return q(0, lim-1, l, r);
		}

};

void solve() {

	ll n, q;
	cin >> n >> q;

	vector<ll> v(n, 0);

	//cerr << "\nv=" << v;

	segtree st;
	st.init(n, v);
	
	//st.debug();

	for(ll i = 0; i < q; i++) {
		
		ll type;
		cin >> type;

		if(type == 0) {

			ll a, b, x;
			cin >> a >> b >> x;
			a--;
			b--;

			st.upd(a, b, x);

		}else if(type == 1) {

			ll a, b;
			cin >> a >> b;
			a--;
			b--;
			ll ans = st.query(a, b);
			cout << ans << "\n";
		}

		st.debug();
	}

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);

	ll t;
	cin >> t;
	for(ll ti = 0; ti < t; ti++) {
		solve();
	}

	return 0;
}

/*

Range-update Range-query segment tree written for SPOJ HORRIBLE QUERIES
https://www.spoj.com/problems/HORRIBLE/

World is getting more evil and it's getting tougher to get into the Evil League of Evil. Since the legendary Bad Horse has retired, now you have to correctly answer the evil questions of Dr. Horrible, who has a PhD in horribleness (but not in Computer Science). You are given an array of N elements, which are initially all 0. After that you will be given C commands. They are:

0 p q v - you have to add v to all numbers in the range of p to q (inclusive), where p and q are two indexes of the array.
1 p q - output a line containing a single integer which is the sum of all the array elements between p and q inclusive.


home-grown nlogn-spaced segment tree, now with lazy propagation

*/
