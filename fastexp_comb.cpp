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

const ll md = 1e9 + 7;

vector<ll> fact;

ll fastexpmod(ll base, ll pw) {
 
    if(base == 0 && pw == 0) {
        return 1;
    }
 
    ll cp = 0; // currpow
    ll cv = base; // currval
 
    ll ret = 1; // return value
 
    //cerr << "\npw=" << pw;
 
    while(pw > 0) {
        ll rm = pw % 2;
        pw /= 2;
 
        //cerr << "\nrm=" << rm;
        //cerr << "\ncv=" << cv;
 
        if(rm == 1) {
            ret = (ret * cv) % md;
        }
 
        cv = (cv * cv) % md;
        cp++;
 
    }
 
    return ret;
 
}
 
ll comb(ll k, ll n) {


	// c(k, n) = n! / (n-k!) * k!
	//cerr << "\nk=" << k << "; n=" << n;

	ll up = fact[n];
	ll d1 = fastexpmod(fact[n-k], md - 2);
	ll d2 = fastexpmod(fact[k], md - 2);

	return ((((up * d1) % md) * d2) % md);

}

void pre(ll lim) {

    fact.resize(lim + 1);
    ll i = 1;
    fact[0] = 1;
    for(ll j = 1; j <= lim; j++) {
 
        i *= j;
        i %= md;
 
        fact[j] = i;
    }
 
}

void solve() {

}

int main()
{
	std::ios_base::sync_with_stdio(false);
	//cin.tie(nullptr);
	//cout.tie(nullptr);

    pre(1e6);

	solve();

	return 0;
}
