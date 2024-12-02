#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool is_safe(const vector<int>& v) 
{
    if (v.size() < 2) 
        return true;

    bool increasing = true, decreasing = true;

    for (size_t i = 1; i < v.size(); i++) 
    {
        int diff = v[i] - v[i - 1];
        if (abs(diff) < 1 || abs(diff) > 3)
            return false;
        if (diff > 0) 
            decreasing = false;
        if (diff < 0)
            increasing = false;
    }

    return increasing || decreasing;
}

bool is_safe_after_remove(const vector<int>& v) 
{
    for (size_t i = 0; i < v.size(); ++i) 
    {
        vector<int> modif_lvl = v;
        modif_lvl.erase(modif_lvl.begin() + i);
        if (is_safe(modif_lvl)) 
            return true;
    }
    return false;
}

int main()
{
    string line;
    int ans = 0;

    while (getline(cin, line) && !line.empty()) 
    {
        istringstream iss(line);
        vector<int> v;
        int num;

        while (iss >> num) 
            v.push_back(num);
        if (is_safe(v) || is_safe_after_remove(v))
            ans++;
        
    }
    cout << ans << endl;

    return 0;
}
