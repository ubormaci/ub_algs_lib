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

typedef int32_t ll;

// az SCC reszt kimasoltam a mult heti kodbol

vector<vector<ll>> out;
vector<vector<ll>> into;
vector<ll> ord;
vector<ll> comp;

void dfs_out(ll curr, vector<bool> &vis) {

	for(const auto & ou : out[curr]) {
		if(vis[ou] == false) {
			vis[ou] = true;
			dfs_out(ou, vis);
		}
	}

	ord.push_back(curr);
}

void dfs_into(ll curr, vector<bool> &vis, ll currcomp) {

	for(const auto & i : into[curr]) {
		if(vis[i] == false) {
			vis[i] = true;
			dfs_into(i, vis, currcomp);
		}
	}

	comp[curr] = currcomp;

}

void compdebug(ll cn, ll n) {

	cerr << "\nin comp " << cn << ": ";
	for(ll i = 1; i <= n; i++) {
		if(comp[i] == cn) {
			cerr << i << " ";
		}
	}

}

void solve() {
	
	ll n, m, s;
	cin >> n >> m >> s;
	// find SCC's, then for each one that is not reachable from the SCC of the capital, 
	// draw an edge efrom the capital to there

	into.resize(n+1);
	out.resize(n+1);

	comp.resize(n+1, 0);

	for(ll i = 0; i < m; i++) {
		ll a, b;
		cin >> a >> b;
		out[a].push_back(b);
		into[b].push_back(a);
	}

	vector<bool> b(n+1, false);

	for(ll i = 1; i <= n; i++) {
		if(b[i] == false) {
			b[i] = true;
			dfs_out(i, b);
		}
	}

	b.clear();
	b.resize(n+1, false);

	ll cctr = 1;
	for(ll i = n - 1; i >= 0; i--) {
		if(b[ord[i]] == 0) {
			b[ord[i]] = true;
			dfs_into(ord[i], b, cctr);
			cctr++;
		}
	}
	
	cctr--;

	// build SCC graph

	vector<vector<ll>> otw(cctr+1); // out-two
	vector<ll> ic(cctr+1, 0); // counter of indegree
	//vector<vector<ll>> intw(cctr+1); // into-two

	for(ll i = 1; i <= n; i++) {

		for(const auto & o : out[i]) {
			if(comp[o] != comp[i]) {
				otw[comp[i]].push_back(comp[o]);
				ic[comp[o]]++;
				//intw[comp[o]].push_back(comp[i]);
			}
		}
	}

	/*
	cerr << "\ncomp";
	for(ll i = 1; i <= n; i++) {
		cerr << "\n" << i << " : " << comp[i] << "; ";
	}
	*/

	// es akkor ezen csinalunk egy topsort-ot? vagy amugy nem is szukseges?
	// de de, kell az
	
	vector<ll> ts; // topsort
	queue<ll> q;
	for(ll i = 1; i <= cctr; i++) {
		if(ic[i] == 0) {
			q.push(i);
		}
	}

	while(!q.empty()) {

		ll curr = q.front();
		q.pop();

		ts.push_back(curr);

		for(const auto & o : otw[curr]) {
			ic[o]--;
			if(ic[o] == 0) {
				q.push(o);
			}
		}
	}

	//cerr << "\ntopsort=" << ts;
	//cerr << "\nout-degree=" << otw;

	// na jo, most megvan a topsort
	vector<bool> act(cctr + 1, false); 
	act[comp[s]] = true;

	// inditunk egy bfs-t, aztan topsort szerint megyunk tovabb a maradekon
	q.push(comp[s]);
	while(!q.empty()) {
		ll curr = q.front();
		q.pop();

		for(const auto & o : otw[curr]) {
			if(act[o] == false) {
				act[o] = true;
				q.push(o);
			}
		}
	}

	ll mx = 0;

	for(const auto & x : ts) {
		// ha ebbe el lehet jutni, a kovetkezokbe is
		//cerr << "\nx=" << x;
		//cerr << "\nact[x]=" << act[x];
		//compdebug(x, n);

		if(act[x] == false) {
			//cerr << "\nwhy isn't mx increased?";
			mx++;
			act[x] = true;
		}

		if(act[x]) {
			for(const auto & y : otw[x]) {
				act[y] = true;
			}
		}
	}

	//cerr << "\nact=" << act; 

	cout << mx << "\n";

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

for CF999E Reachability from the Capital

https://codeforces.com/contest/999/problem/E

There are n cities and m roads in Berland. Each road connects a pair of cities. The roads in Berland are one-way.
What is the minimum number of new roads that need to be built to make all the cities reachable from the capital?
New roads will also be one-way.

Counts SCC components and builds the condensation graph

*/