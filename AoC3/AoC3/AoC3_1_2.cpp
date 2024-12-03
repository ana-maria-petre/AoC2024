#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;
 
int part1(const string& data) 
{
    regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    smatch matches;
    int result = 0;
    string::const_iterator src_start(data.cbegin());
    while (regex_search(src_start, data.cend(), matches, pattern))
    {
        int x = stoi(matches[1].str());
        int y = stoi(matches[2].str());
        result += x * y;
        src_start = matches.suffix().first;
    }

    return result;
}

int part2(const string& data) 
{
    regex pattern(R"((mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\)))");
    smatch matches;
    bool enabled = true;
    int result = 0;

    string::const_iterator src_start(data.cbegin());
    while (regex_search(src_start, data.cend(), matches, pattern))
    {
        if (matches[1].str() == "do()") 
        {
            enabled = true;
        }
        else if (matches[1].str() == "don't()") 
        {
            enabled = false;
        }
        else if (enabled) 
        {
            int x = stoi(matches[2].str());
            int y = stoi(matches[3].str());
            result += x * y;
        }
        src_start = matches.suffix().first;
    }

    return result;
}

int main() {
    ifstream f("input.in");
    string data((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
    f.close();

    int ans1 = part1(data);
    cout << ans1 << '\n';

    int ans2 = part2(data);
    cout << ans2;

    return 0;
}
