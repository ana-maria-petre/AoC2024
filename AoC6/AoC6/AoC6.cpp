#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <cstring>

using namespace std;

const vector<pair<int, int>> directions = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

vector<string> map;

bool simulate_loop( int obs_x, int obs_y)
{
    int rows = map.size(), cols = map[0].size();
    vector<string> map_cpy = map;
    map_cpy[obs_x][obs_y] = '#'; 

    set<tuple<int, int, int>> visited_states; 
    int start_x = 0, start_y = 0, dir = 0;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (map_cpy[i][j] == '^')
            {
                start_x = i;
                start_y = j;
                dir = 0; 
                break;
            }
        }
    }

    int x = start_x, y = start_y;

    while (true) 
    {
        if (visited_states.count({ x, y, dir })) 
        {
            return true; 
        }
        visited_states.insert({ x, y, dir });

        int nx = x + directions[dir].first;
        int ny = y + directions[dir].second;

        if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) 
        {
            break;
        }

        if (map_cpy[nx][ny] == '#') 
        {
            dir = (dir + 1) % 4; 
        }
        else
        {
            x = nx;
            y = ny; 
        }
    }

    return false; 
}

int main()
{
    ifstream f("input.in");
    string line;

    while (getline(f, line)) 
        map.push_back(line);


    int rows = map.size(), cols = map[0].size();
    int start_x = 0, start_y = 0, dir = 0; 
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (map[i][j] == '^') 
            {
                start_x = i;
                start_y = j;
                dir = 0;
                break;
            }
        }
    }

    set<pair<int, int>> visited;
    visited.insert({ start_x, start_y });

    int x = start_x, y = start_y;

    while (true) 
    {
        int nx = x + directions[dir].first;
        int ny = y + directions[dir].second;

        if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) 
        {
            break;
        }

        if (map[nx][ny] == '#') 
        {
            dir = (dir + 1) % 4; 
        }
        else 
        {
            x = nx;
            y = ny;
            visited.insert({ x, y });
        }
    }

    cout << "1: " << visited.size() << endl;

    rows = map.size(), cols = map[0].size();
    start_x = 0, start_y = 0;

    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            if (map[i][j] == '^') 
            {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    int loops = 0;

    for (int i = 0; i < rows; ++i) 
        for (int j = 0; j < cols; ++j) 
            if (map[i][j] == '.' && !(i == start_x && j == start_y)) 
                if (simulate_loop( i, j)) 
                    loops++;


    cout << "2: " << loops << endl;
    return 0;
}
