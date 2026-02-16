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

vector<ll> entime;
vector<ll> p;
vector<ll> low;
vector<pair<ll,ll>> necc;
vector<vector<ll>> v;
ll t = 1;

void dfs(ll curr) {

	// nezzuk a visszaeleket
	entime[curr] = t;
	low[curr] = t;
	t++;

	for(const auto & x : v[curr]) {
		if(entime[x] == 0) {
			p[x] = curr;
			dfs(x);
			low[curr] = min(low[curr], low[x]);
		}else if(x != p[curr]) {
			low[curr] = min(low[curr], entime[x]);
		}
	}

	if(low[curr] == entime[curr] && p[curr] != 0) {
		necc.push_back({curr, p[curr]});
	}
}

void solve() {
	
	ll n, m;
	cin >> n >> m;

	entime.assign(n+1, 0);
	p.assign(n+1, 0);
	low.assign(n+1, 0);
	v.resize(n+1);

	for(ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	dfs(1);

	cout << necc.size() << "\n";
	for(const auto & [x, y] : necc) {
		cout << x << " " << y << "\n";
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

Finds all bridges in linear time
for CSES Necessary Roads

There are n cities and m roads between them. There is a route between any two cities.
A road is called necessary if there is no route between some two cities after removing that road. Your task is to find all necessary roads.

*/