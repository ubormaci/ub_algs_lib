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

void dfs(ll curr, ll parent, ll &time, vector<ll> &entime, vector<ll>& low, vector<vector<ll>> &v, ll &first, vector<bool> & necc) {

	entime[curr] = time;
	low[curr] = time;
	time++;

	// ha van legalabb egy olyan gyereke
	// amelyiknek a reszfajabol csak maximum obele lehet visszajutni
	// akkor szukseges

	//cerr << "\ncurrent=" << curr;

	ll mxch = 0;

	for(const auto & ch : v[curr]) {

		if(entime[ch] == 0) {
			dfs(ch, curr, time, entime, low, v, first, necc);

			//cerr << "\ncurr=" << curr;
			//cerr << "\nchild=" << ch << "; low[ch]=" << low[ch];

			low[curr] = min(low[curr], low[ch]);
			mxch = max(low[ch], mxch);
		}else if(ch != parent){
			low[curr] = min(low[curr], entime[ch]);
		}
	}

	/*
	cerr << "\ncurr=" << curr;
	cerr << "\nlow[curr]=" << low[curr];
	for(const auto & ch : v[curr]) {
		if(entime[ch] > entime[curr]) {
			cerr << "\nlow[" << ch << "]=" << low[ch]; 
		}
	}
	cerr << "\nmxch=" << mxch;
	*/

	if(v[curr].size() == 1) {
		// ha nincsenek gyerekei
		// akkor ha ot kivesszuk, a komponensek szama nem valtozik
		//cerr << "\nend of an edge;";
		return;
	}

	// a node ahonnan kezdjuk az egyedi eset
	if(curr == first) {
		//cerr << "\nit's the first edge";
		return;
		// futtatunk kettot, ket kulonbozo kiindulo pontbol
	}
	
	// van szuloje es van gyereke
	if(mxch >= entime[curr]) {
		
		// hid-el a szulojebe vezeto el
		// vagyis o maga hid-csucs
		//cerr << "\nit's necessary";
		necc[curr] = true;

	}

}

void solve() {
	
	ll n, m;
	cin >> n >> m;

	vector<vector<ll>> v(n+1);
	for(ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}

	// effektive ugyanaz mint a masik
	// csak az a kiveteles eset, amikor o van a szelen

	vector<bool> necc(n+1, false);

	for(ll i = 1; i <= 2; i++) {

		//cerr << "\nstart=" << i;

		vector<ll> entime(n+1, 0);
		vector<ll> low(n+1, 0);
		ll time = 1;	

		ll fs = i;

		dfs(i, -1, time, entime, low, v, fs, necc);

		//cerr << "\nnecc=" << necc;
	}

	ll cnt = 0;
	for(ll i = 1; i <= n; i++)
	{
		cnt += necc[i];
	}

	cout << cnt << "\n";
	for(ll i = 1; i <= n; i++) {
		if(necc[i]) {
			cout << i << " ";
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

Finds articulation points in linear time
tested on CSES Necessary Cities

https://cses.fi/problemset/task/2077

There are n cities and m roads between them. There is a route between any two cities.
A city is called necessary if there is no route between some other two cities after removing that city (and adjacent roads). Your task is to find all necessary cities.

*/