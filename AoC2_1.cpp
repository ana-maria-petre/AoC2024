#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

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
        

        if (v.size() < 2)
        {
            ans++;
            continue;
        }

        bool safe = true;
        bool increasing = true, decreasing = true;

        for (size_t i = 1; i < v.size(); ++i)
        {
            int diff = v[i] - v[i - 1];

            if (abs(diff) < 1 || abs(diff) > 3) 
            {
                safe = false;
                break;
            }

            if (diff > 0)
                decreasing = false; 
            if (diff < 0) 
                increasing = false; 

        }

        if (!(increasing || decreasing)) 
            safe = false;
        if (safe) 
            ++ans;
    }
    cout << ans << endl;

    return 0;
}
