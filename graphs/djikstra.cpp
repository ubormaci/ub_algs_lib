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
using namespace std;

/*

quickly workable Djikstra template, originally written for  
https://codeforces.com/problemset/problem/20/C
Codeforces Alpha Round 20: Problem C: Djikstra?

includes path reconstruction

*/

typedef long long ll;

ll n = 0;
ll const tenfive = 100000;
array<vector<pair<ll, ll>>, tenfive> mp;

vector<ll> restorePath(ll start, ll end, vector<ll> const& p)
{
	vector<ll> path;

	//DEBUG
	//cout << "\nentering path reconstruction:";

	for (ll node = end; node != start; node = p[node])
	{
		//cout << "\nnode = " << node;
		path.push_back(node);
	}
	path.push_back(start);
	reverse(path.begin(), path.end());
	return path;
}

void djikstra(ll start, ll end)
{
	const ll invalid = -1;

	vector<ll> d(n, invalid);
	vector<bool> u(n, false);
	vector<ll> p(n, -1);

	d[start] = 0;

	// 'd' contains the shortest paths from 'start' to 'end', and has a length equal to the number of vertices
	// initially, d[start] = 0, while all others are qual to 'infinity' (-1, in this case)

	// 'u' contains whether a vertice is 'marked'
	// initially, none are

	// at each iteration, the smallest d[v] value is chosen where u[v] == false, v is unmarked

	// this v is then marked
	// we check all of its neighbors, where a neighbor in the iteration is 'to'
	// d[to] = min(d[to], d[v] + {dist between v, to} )

	// after n iterations in the upper loop, the algorithm concludes

	set<pair<ll, ll>> q;
	q.insert({ 0, start });

	while (!q.empty())
	{
		ll curr = q.begin()->second;
		q.erase(q.begin());

		for (auto const & next : mp[curr])
		{
			ll to = next.first;
			ll len = next.second;

			if (d[curr] + len < d[to] || d[to] == invalid)
			{
				q.erase({d[to], to});
				d[to] = d[curr] + len;
				p[to] = curr;
				q.insert({ d[to], to });
			}
		}
	}

	if (d[end] != invalid)
	{
		vector<ll> path = restorePath(start, end, p);

		for (auto const& x : path)
		{
			cout << x + 1 << " ";
		}
		cout << "\n";
	}
	else
	{
		cout << "-1\n";
	}

	/*
	// DEBUG
	for (ll i = 0; i < n; i++)
	{
		cout << "d[" << i << "] = " << d[i];
	}
	*/

}

void solve()
{
	ll m = 0;
	cin >> n >> m;
	for (ll i = 0; i < m; i++)
	{
		ll a, b, c;
		cin >> a >> b >> c;
		a -= 1;
		b -= 1;
		mp[a].push_back({b, c});
		mp[b].push_back({a, c});
	}
	
	djikstra(0, n - 1);

}

int main()
{
	std::ios_base::sync_with_stdio(false);

	solve();

	return 0;
}
