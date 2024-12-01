#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

ifstream f("input.in");
vector<int> l; 
vector<int> r; 

int solve()
{
    unordered_map<int, int> fr;
    for (int n : r) 
        fr[n]++;
    

    int sim = 0;
    for (int n : l) 
        sim += n * fr[n];
    

    return sim;
}

int main()
{
    int x, y;
    while (f >> x >> y)
    {
        l.push_back(x); 
        r.push_back(y); 
    }

    cout << solve() << endl;

    return 0;
}
