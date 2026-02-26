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

class matrix{

	public:

	ll n, m;
	vector<vector<ll>> v;

	bool mod = false;
	ll mdval = 0;

	void init(ll rows, ll cols, vector<vector<ll>> inp) {
		n = rows;
		m = cols;

		v.assign(n, vector<ll>(m, 0));

		for(ll i =0; i < n; i++) {
			for(ll j = 0; j < m; j++) {
				v[i][j] = inp[i][j];
				if(mod) {
					v[i][j] %= mdval;
				}
			}
		}
	}

	friend ostream& operator<<(ostream &os, const matrix & a) {
		for(ll i = 0; i < a.n; i++) {
			os << "{";
			for(ll j = 0; j < a.m; j++) {
				os << a.v[i][j];
				if(j < a.m - 1) {
					os << ", ";
				}
			}
			os << "}\n";
		}
		return os;
	}

	matrix friend operator*(const matrix &a, const matrix &b) {

		matrix ret;
		ret.n = a.n;
		ret.m = b.m;

		if(a.mod) {
			ret.mod = true;
			ret.mdval = a.mdval;
		}

		if(a.m != b.n) {
			cerr << "\nsomething's wrong here";
			ret.n = 0;
			ret.m = 0;
			return ret;
		}

		ret.v.assign(ret.n, vector<ll>(ret.m, 0));
		for(ll i = 0; i < ret.n; i++) {
			for(ll j = 0; j < ret.m; j++) {
				for(ll k = 0; k < a.m; k++) {
					ret.v[i][j] += a.v[i][k] * b.v[k][j];

					if(ret.mod) {
						ret.v[i][j] %= ret.mdval;
					}
				}
			}
		}

		return ret;
	}
};

matrix fastmatrixexp(matrix base, ll pw) {

	matrix ret;

	if(base.n != base.m) {
		cerr << "\nmatrix can't be exponentiated, period";
		ret.n = 0;
		ret.m = 0;
		return ret;		
	}

	// here, we presume that base has an equal number of rows and columns
	ret.init(base.n, base.n, vector<vector<ll>>(base.n, vector<ll>(base.n, 0)));
	for(ll i = 0; i < base.n; i++) {
		ret.v[i][i] = 1;
	}
	ret.mod = base.mod;
	ret.mdval = base.mdval;

	matrix p = base;
	while(pw > 0) {
		if(pw % 2 == 1) {
			ret = ret * p;
		}

		p = p * p;
		pw /= 2;
	}

	return ret;
}

ll fibn(ll n, const ll md) {

	matrix fibstart;
	fibstart.init(2, 1, vector<vector<ll>>{{1}, {0}});
	// fibstart = 
	// { F1 }
	// { F0 }

	if(n == 0) {
		return fibstart.v[1][0];
	}
	if(n == 1) {
		return fibstart.v[0][0];
	}

	matrix a;
	a.init(2, 2, vector<vector<ll>>{{1, 1}, {1, 0}});
	a.mod = true;
	a.mdval = md;

	matrix res = fastmatrixexp(a, n-1);
	res = res * fibstart;

	return res.v[0][0];
}

void solve() {

	/*
	matrix a, b;
	a.init(2, 2, vector<vector<ll>>{{1, 2}, {3,4}});
	b.init(2, 2, vector<vector<ll>>{{1, 2}, {1, 2}});

	matrix c = a * b;
	cerr << c;
	*/

	ll f = 10;

	//cerr << "\nfib " << f << ": " << fibn(f, INT64_MAX);

	cin >> f;

	cout << fibn(f, 1e9 + 7);
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

tested on CSES Fibonacci Numbers

*/