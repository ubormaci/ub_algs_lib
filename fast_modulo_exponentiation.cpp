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
using namespace std;


typedef int64_t ll;

ll fastexpmod(ll base, ll pw, ll md) {

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

void solve() {
    
}

int main()
{
	std::ios_base::sync_with_stdio(false);

	ll tests = 0;
	cin >> tests;

	while(tests--)
	{
		solve();
	}

	return 0;
}
