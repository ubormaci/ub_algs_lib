#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
using namespace std;
     
typedef long long ll;
     
    /*
     
    https://www.pbinfo.ro/articole/19048/algoritmul-lui-kruskal
     
    input1:
     
    9 14
    4 1 2
    8 1 8
    8 2 3
    11 2 8
    4 3 6
    7 3 4
    2 3 9
    9 4 5
    14 4 6
    10 5 6
    2 6 7
    6 7 9
    1 7 8
    7 8 9
     
    output
     
    9 8
    1 7 8
    2 3 9
    2 6 7
    4 1 2
    4 3 6
    7 3 4
    8 1 8
    9 4 5
     
    */
     
int main()
{
    vector < pair<ll, pair<ll, ll>>> gr;
    // length - from - to
     
    ifstream cin("example.txt");
    ll n, m;
    cin >> n >> m;
    for (ll i = 0; i < m; i++) {
        ll weight, from, to;
        cin >> weight >> from >> to;
        gr.push_back({ weight, {from, to} });
    }
     
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
    while (keptctr < (n - 1)) {
        ll start = gr[i].second.first;
        ll end = gr[i].second.second;
        //ll vertexcolor[start] = vertexcolor[start];
        //ll vertexcolor[end] = vertexcolor[end];
    
        string debug = "\n      ";
    
        cout << "\n";
        cout << debug << "i=" << i;
        cout << debug << "start = " << start;
        cout << debug << "end=" << end;
        cout << debug << "vertexcolor[start]=" << vertexcolor[start];
        cout << debug << "vertexcolor[end]=" << vertexcolor[end];
    
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
            cout << debug << "col1ctr=" << col1ctr;
            cout << debug << "col2ctr=" << col2ctr;
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
        cout << debug << "vertexcolors: ";
            for (ll i = 1; i <= n; i++) {
            cout << i << ":" << vertexcolor[i] << " ; ";
        }
        cout << debug << "colored vertexes: ";
        for (const auto& x : colors) {
            if (x.second.size() != 0) {
                cout << debug << x.first << " ";
                for (const auto& y : x.second) {
                    cout << y << " ";
                }
            }
        }
    }
 
    cout << "\nMin-fa:";
    cout << "\n" << n << " " << n - 1;

     for (ll i = 0; i < m; i++) {
        if (kept[i] == true) {
            ll start = gr[i].second.first;
            ll end = gr[i].second.second;
            cout << "\n" << gr[i].first << " " << start << " " << end;
        }
    }
  
}