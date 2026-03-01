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

void dfs(ll curr, ll par, ll &time, vector<vector<ll>> &v, vector<ll> &entime,
		vector<ll> &low, stack<ll>& st, vector<vector<ll>>&comp, vector<ll>&root) {

	//cerr << "\ncurr=" << curr;

	entime[curr] = time;
	low[curr] = time;
	st.push(curr);
	time++;

	for(const auto & ch : v[curr]) {
		
		//cerr << "\nch=" << ch;
		
		if(entime[ch] == 0) {
			//cerr << "-> unvisited, let's see";
			dfs(ch, curr, time, v, entime, low, st, comp, root);
			low[curr] = min(low[curr], low[ch]);
		}else if(root[ch] == -1){
			//cerr << "-> back edge";
			low[curr] = min(low[curr], entime[ch]);
		}
	}

	if(entime[curr] == low[curr]) {

		comp[curr].push_back(curr);
		while(true) {
			ll h = st.top();
			root[h] = curr;
			st.pop();

			if(h == curr) {
				break;
			}

			comp[curr].push_back(h);
		}

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
	}

	vector<ll> entime(n+1, 0);
	vector<ll> low(n+1, 0);
	stack<ll> st;
	vector<vector<ll>> comp(n+1);
	vector<ll> root(n+1, -1);
	ll time = 1;
	for(ll i = 1; i <= n; i++) {
		if(entime[i] == 0) {
			dfs(i, 0, time, v, entime, low, st, comp, root);
		}
	}

	//cerr << "\nentime=" << entime;
	//cerr << "\nlow=" << low;

	//cerr << "\ncomps=" << comp;
	//cerr << "\nroot=" << root;

	for(ll i = 1; i <= n; i++) {
		if(comp[i].size() > 1) {
			// we start a bfs, until we reach an edge that has a back-edge towards 
			// the node that gives the component's id
			// then we track back through the parents
			
			vector<ll> p(n+1, -1);
			queue<ll> q;
			q.push(i);

			ll nd = 0;
			p[i] = 0;

			while(!q.empty()) {
				ll curr = q.front();
				q.pop();

				for(const auto & x : v[curr]) {
					if(p[x] == -1) {
						q.push(x);
						p[x] = curr;
					}
					if(x == i && nd == 0) {
						nd = curr;
					}
				}
			}

			vector<ll> path;
			path.push_back(i);
			ll g = nd;
			while(g != i) {
				path.push_back(g);
				g = p[g];
			}
			path.push_back(i);

			reverse(path.begin(), path.end());

			cout << path.size() << "\n";
			for(const auto & x : path) {
				cout << x << " ";
			}
			return;
		}
	}

	cout << "IMPOSSIBLE";

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

Finding SCC connected components using Tarjan's algorithm
tested on CSES Round Trip II

Byteland has n cities and m flight connections. Your task is to design a round trip that begins in a city, goes through one or more other cities, and finally returns to the starting city. Every intermediate city on the route has to be distinct.

*/