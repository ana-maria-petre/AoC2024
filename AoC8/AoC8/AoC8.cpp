#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <fstream>
#include <string>
using namespace std;

ifstream f("input.in");

unordered_map<char, vector<pair<int, int>>> antenna_positions;

set<pair<int, int>> count_antinodes( int rows, int cols, int part)
{
    set<pair<int, int>> antinodes;

    for (const auto& pairs : antenna_positions)
    {
        const auto& pos = pairs.second;

        for (size_t i = 0; i < pos.size(); ++i)
        {
            for (size_t j = i + 1; j < pos.size(); ++j)
            {
                int row1 = pos[i].first;
                int col1 = pos[i].second;
                int row2 = pos[j].first;
                int col2 = pos[j].second;
                int d_row = row2 - row1;
                int d_col = col2 - col1;

                if (part == 2)
                {
                    antinodes.insert({ row1, col1 });
                    antinodes.insert({ row2, col2 });
                }

                while (true)
                {
                    row2 += d_row;
                    col2 += d_col;
                    if (row2 >= 0 && row2 < rows && col2 >= 0 && col2 < cols)
                    {
                        antinodes.insert({ row2, col2 });
                    }
                    else
                    {
                        break;
                    }
                    if (part == 1)
                    {
                        break;
                    }
                }

                while (true)
                {
                    row1 -= d_row;
                    col1 -= d_col;
                    if (row1 >= 0 && row1 < rows && col1 >= 0 && col1 < cols)
                    {
                        antinodes.insert({ row1, col1 });
                    }
                    else
                    {
                        break;
                    }
                    if (part == 1)
                    {
                        break;
                    }
                }
            }
        }
    }

    return antinodes;
}

int main()
{
    string line;
    vector<string> grid;

    while (getline(f, line))
    {
        grid.push_back(line);
    }

    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < rows; i++) 
    {
        for (int j = 0; j < cols; j++) 
        {
            char c = grid[i][j];
            if (c != '.') 
            { 
                antenna_positions[c].emplace_back(i, j);
            }
        }
    }

    set<pair<int, int>> ans1 = count_antinodes( rows, cols, 1);
    set<pair<int, int>> ans2 = count_antinodes( rows, cols, 2);

    cout << "1: " << ans1.size() << '\n';
    cout << "2: " << ans2.size();

    return 0;
}
