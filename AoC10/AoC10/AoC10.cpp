#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

const vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

vector<vector<int>> read(const string& input) 
{
    ifstream f(input);
    vector<vector<int>> map;
    string line;

    while (f >> line)
    {
        vector<int> row;
        for (char ch : line) 
        {
            row.push_back(ch - '0');
        }
        map.push_back(row);
    }

    return map;
}

bool valid_move(size_t x, size_t y, int prev_height, const vector<vector<int>>& map)
{
    size_t n = map.size();
    size_t m = map[0].size();
    return x < n && y < m && map[x][y] == prev_height + 1;
}

int calc_score(size_t startX, size_t startY, const vector<vector<int>>& map) 
{
    size_t n = map.size();
    size_t m = map[0].size();
    set<pair<size_t, size_t>> visited;
    set<pair<size_t, size_t>> reachable_9s;
    queue<pair<size_t, size_t>> q;

    q.push({ startX, startY });
    visited.insert({ startX, startY });

    while (!q.empty()) 
    {
        pair<size_t, size_t> crt = q.front();
        q.pop();

        size_t x = crt.first;
        size_t y = crt.second;

        for (const pair<int, int>& dir : directions) 
        {
            int dx = dir.first;
            int dy = dir.second;

            size_t nx = x + dx;
            size_t ny = y + dy;

            if (valid_move(nx, ny, map[x][y], map) && visited.find({ nx, ny }) == visited.end())
            {
                visited.insert({ nx, ny });
                q.push({ nx, ny });

                if (map[nx][ny] == 9)
                {
                    reachable_9s.insert({ nx, ny });
                }
            }
        }
    }

    return static_cast<int>(reachable_9s.size());
}

int calc_rating(size_t start_x, size_t start_y, const vector<vector<int>>& map) 
{
    size_t n = map.size();
    size_t m = map[0].size();
    vector<vector<int>> trail_cnt(n, vector<int>(m, 0));
    queue<pair<size_t, size_t>> q;

    q.push({ start_x, start_y });
    trail_cnt[start_x][start_y] = 1;

    int trails = 0;

    while (!q.empty())
    {
        pair<size_t, size_t> crt = q.front();
        q.pop();

        size_t x = crt.first;
        size_t y = crt.second;

        for (const pair<int, int>& dir : directions) 
        {
            int dx = dir.first;
            int dy = dir.second;

            size_t nx = x + dx;
            size_t ny = y + dy;

            if (valid_move(nx, ny, map[x][y], map))
            {
                if (trail_cnt[nx][ny] == 0) 
                {
                    q.push({ nx, ny });
                }
                trail_cnt[nx][ny] += trail_cnt[x][y];
            }
        }
    }

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j) 
        {
            if (map[i][j] == 9) 
            {
                trails += trail_cnt[i][j];
            }
        }
    }

    return trails;
}

int solve1(const vector<vector<int>>& map) 
{
    size_t n = map.size();
    size_t m = map[0].size();
    int score = 0;

    for (size_t i = 0; i < n; ++i) 
    {
        for (size_t j = 0; j < m; ++j) 
        {
            if (map[i][j] == 0) 
            {
                score += calc_score(i, j, map);
            }
        }
    }

    return score;
}

int solve2(const vector<vector<int>>& map) 
{
    size_t n = map.size();
    size_t m = map[0].size();
    int rating = 0;

    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < m; ++j)
        {
            if (map[i][j] == 0) 
            {
                rating += calc_rating(i, j, map);
            }
        }
    }

    return rating;
}

int main() 
{
    vector<vector<int>> map = read("input.in");

    int score = solve1(map);
    int rating = solve2(map);

    cout << "1: " << score << '\n';
    cout << "2: " << rating;

    return 0;
}
