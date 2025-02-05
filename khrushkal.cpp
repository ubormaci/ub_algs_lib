#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <array>
#include <string>
#include <cstdio>
#include <iterator>
#include <unordered_set>
#include <cstdint>
#include <queue>
#include <stack>
#include <deque>
#include <numeric>
#include <fstream>
#include <bitset>
#include <iomanip>
using namespace std;

#pragma GCC optimize("O2")
// #pragma GCC optimize("O1","O2","O3","Ofast","unroll-loops")
// #pragma GCC target("sse","sse2","sse3","sse4.1","sse4.2","avx","avx2")

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

set lower bound/upper bound:
 	// . . . m1 . . . d . . . . m2
    auto m1_it = b.lower_bound(d);
    advance(m1_it, -1);
    m1 = *m1_it;
	m2 = *b.upper_bound(d);

#ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif

constexpr auto lcm(auto x, auto... xs)
{
	return ((x = std::lcm(x, xs)), ...);
}

std::gcd(int a, int b)

cout << setprecision(n);

*/

// Khruskal with "We have DSU at home" implementation of DSU
// stress tested against CSES: Road Reparation

typedef long long ll;

int main()
{
    vector < pair<ll, pair<ll, ll>>> gr;
    // length - from - to
     
    //ifstream cin("example.txt");
    ll n, m;
    cin >> n >> m;
    for (ll i = 0; i < m; i++) {
        ll weight, from, to;
        cin >> from >> to >> weight;
        gr.push_back({ weight, {from, to} });
    }

	/* 
	if(m < n - 1) {
		cout << "IMPOSSIBLE";
		return 0;
	}
	*/

    sort(gr.begin(), gr.end());
    // two vectors: one that stores the colors of each vertex
    // vertex -> color
    // and one that stores colors and the vertexes that are colored
    // color -> vertex
    // this second one is more for speed's sake
     
    // and a third one that keeps track of which edges are kept
    vector<bool> kept(m, false);
    vector<ll> vertexcolor(n+1, -1);
    map<ll, vector<ll>> colors;
    ll keptctr = 0;
     
    ll i = 0;
    ll currcol = 0;
    while (i < m) {
        ll start = gr[i].second.first;
        ll end = gr[i].second.second;
        //ll vertexcolor[start] = vertexcolor[start];
        //ll vertexcolor[end] = vertexcolor[end];
    
        string debug = "\n      ";
    
        //cout << "\n";
        //cout << debug << "i=" << i;
        //cout << debug << "start = " << start;
        //cout << debug << "end=" << end;
        //cout << debug << "vertexcolor[start]=" << vertexcolor[start];
        //cout << debug << "vertexcolor[end]=" << vertexcolor[end];
    
        if (vertexcolor[start] == vertexcolor[end] && vertexcolor[start] != -1 && vertexcolor[end] != -1) {
            i++;
            continue;
        }

        kept[i] = true;
        keptctr++;
        i++;
    
        if (vertexcolor[start] == -1 && vertexcolor[end] == -1) {
            vertexcolor[start] = currcol;
            vertexcolor[end] = currcol;
            colors[currcol].push_back(start);
            colors[currcol].push_back(end);
            currcol++;
        }
        else if (vertexcolor[start] != -1 && vertexcolor[end] == -1) {
            vertexcolor[end] = vertexcolor[start];
            colors[vertexcolor[start]].push_back(end);
        }
        else if (vertexcolor[start] == -1 && vertexcolor[end] != -1) {
            vertexcolor[start] = vertexcolor[end];
            colors[vertexcolor[end]].push_back(start);
        }
        else {
            // thus we have concluded that both have been colored, in different colors
            ll col1ctr = colors[vertexcolor[start]].size();
            ll col2ctr = colors[vertexcolor[end]].size();
            //cout << debug << "col1ctr=" << col1ctr;
            //cout << debug << "col2ctr=" << col2ctr;
            if (col1ctr > col2ctr) {
                // ha tobb van az egyesbol mint a kettesbol
                // akkor a kettest az egyesre szinezzuk
                ll prevendcol = vertexcolor[end];
                for (const auto& x : colors[vertexcolor[end]]) {
                    vertexcolor[x] = vertexcolor[start];
                    colors[vertexcolor[start]].push_back(x);
                }
                colors[prevendcol].clear();
            }
            else {
                ll prevstartcol = vertexcolor[start];
                for (const auto& x : colors[vertexcolor[start]]) {
                    vertexcolor[x] = vertexcolor[end];
                    colors[vertexcolor[end]].push_back(x);
                }
                colors[prevstartcol].clear();
            }
        }
        //cout << debug << "vertexcolors: ";
            //for (ll i = 1; i <= n; i++) {
            //cout << i << ":" << vertexcolor[i] << " ; ";
        	//}
        /*
		//cout << debug << "colored vertexes: ";
        for (const auto& x : colors) {
            if (x.second.size() != 0) {
                cout << debug << x.first << " ";
                for (const auto& y : x.second) {
                    cout << y << " ";
                }
            }
        }
		*/
    }
 
    //cout << "\nMin-fa:";
    //cout << "\n" << n << " " << n - 1;

	//cerr << "vcol=" << vertexcolor;

	for(ll i = 1; i <= n; i++) {
		if(vertexcolor[i] == -1 || vertexcolor[i] != vertexcolor[1]) {
			cout << "IMPOSSIBLE";
			return 0;
		}
	}

	ll cost = 0;
	
    for(ll i = 0; i < m; i++) {
        if (kept[i] == true) {
			cost += gr[i].first;
            //ll start = gr[i].second.first;
            //ll end = gr[i].second.second;
            //cout << "\n" << gr[i].first << " " << start << " " << end;
        }
    }
	cout << cost;
  
}
