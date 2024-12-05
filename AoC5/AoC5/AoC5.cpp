#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

vector<string> split(const string& s, char delimiter)
{
    vector<string> result;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter)) 
    {
        result.push_back(token);
    }
    return result;
}

pair<set<pair<string, string>>, vector<vector<string>>> parse(istream& input) 
{
    string data((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    size_t delimiter_idx = data.find("\n\n");

    set<pair<string, string>> rules;
    stringstream rules_ss(data.substr(0, delimiter_idx));
    string line;
    while (getline(rules_ss, line)) 
    {
        vector<string> rule_parts = split(line, '|');
        rules.insert(make_pair(rule_parts[0], rule_parts[1]));
    }

    vector<vector<string>> pages;
    stringstream pages_ss(data.substr(delimiter_idx + 2));
    while (getline(pages_ss, line)) 
    {
        pages.push_back(split(line, ','));
    }

    return make_pair(rules, pages);
}


void solve(istream& input) 
{
    pair<set<pair<string, string>>, vector<vector<string>>> split_input = parse(input);
    set<pair<string, string>> rules = split_input.first;
    vector<vector<string>> pages = split_input.second;

    long s[2] = { 0, 0 }; 

    for (size_t row = 0; row < pages.size(); ++row) 
    {
        vector<string> old = pages[row];
        vector<string> new_sq;

        for (int i = 0; i < 100; ++i) 
        { 
            for (size_t i = 0; i < old.size(); i++) 
            {
                string o = old[i];
                if (find(new_sq.begin(), new_sq.end(), o) != new_sq.end()) continue;

                bool ok = true;
                for (set<pair<string, string>>::iterator it = rules.begin(); it != rules.end(); it++) 
                {
                    string b = it->first;
                    string a = it->second;

                    if (o == a && find(old.begin(), old.end(), b) != old.end() && find(new_sq.begin(), new_sq.end(), b) == new_sq.end()) 
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok) 
                {
                    new_sq.push_back(o);
                }
            }
        }

        int m = new_sq.size() / 2;
        if (new_sq == old) 
        {
            s[0] += stoi(new_sq[m]);
        }
        else 
        {
            s[1] += stoi(new_sq[m]);
        }
    }

    cout << s[0] << "\n" << s[1] << endl;
}

int main()
{
    ifstream f("input.in"); 
    solve(f);
    return 0;
}
