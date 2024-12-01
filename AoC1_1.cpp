#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

ifstream f("input.in");
vector<int> l;
vector<int> r;

int solve() 
{
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());
    int t = 0;
    for (size_t i = 0; i < l.size(); ++i) 
        t += abs(l[i] - r[i]);
    return t;
}

int main()
{
    int x, y;
    while (f >> x >> y)
    {
        l.push_back(x);
        r.push_back(y);
    }

    cout << solve();

    return 0;
}
