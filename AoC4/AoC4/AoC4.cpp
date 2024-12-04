#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ifstream f("input.in");
vector<string> grid;
const string word = "XMAS";

const vector<pair<int, int>> dir = {
    {0, 1},  {1, 0},  {0, -1}, {-1, 0},    
    {1, 1},  {1, -1}, {-1, 1}, {-1, -1}    
};

bool find_xmas( int row, int col, const pair<int, int>& dir) 
{
    int rows = grid.size();
    int cols = grid[0].size();

    for (int i = 0; i < word.size(); i++)
    {
        int nx = row + i * dir.first;
        int ny = col + i * dir.second;

        if (nx < 0 || nx >= rows || ny < 0 || ny >= cols || grid[nx][ny] != word[i]) 
            return false;
        
    }
    return true;
}


int count_xmas( ) 
{
    int rows = grid.size();
    int cols = grid[0].size();
    int cnt = 0;

    for (int r = 0; r < rows; r++) 
        for (int c = 0; c < cols; c++) 
            for (const auto& d : dir) 
                if (find_xmas( r, c, d)) 
                    cnt++;
    return cnt;
}

bool find_x_mas(int x, int y)
{
    int rows = grid.size();
    int cols = grid[0].size();

    if (x - 1 < 0 || x + 1 >= rows || y - 1 < 0 || y + 1 >= cols)
        return false;

    if (grid[x - 1][y - 1] == 'M' && grid[x + 1][y + 1] == 'S')
        if (grid[x - 1][y + 1] == 'M' && grid[x + 1][y - 1] == 'S')
            return true;


    if (grid[x - 1][y + 1] == 'S' && grid[x + 1][y - 1] == 'M')
        if (grid[x - 1][y - 1] == 'S' && grid[x + 1][y + 1] == 'M')
            return true;

    if (grid[x - 1][y + 1] == 'M' && grid[x + 1][y - 1] == 'S')
        if (grid[x - 1][y - 1] == 'S' && grid[x + 1][y + 1] == 'M')
            return true;

    if (grid[x - 1][y + 1] == 'S' && grid[x + 1][y - 1] == 'M')
        if (grid[x - 1][y - 1] == 'M' && grid[x + 1][y + 1] == 'S')
            return true;

    return false;
}

int count_x_mas()
{
    int rows = grid.size();
    int cols = grid[0].size();
    int cnt = 0;
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            if (grid[i][j] == 'A' && find_x_mas(i, j)) 
                cnt++;
    return cnt;
}

int main()
{
    string line;
    while (getline(f, line)) 
        grid.push_back(line);

    int ans1 = count_xmas();
    int ans2 = count_x_mas();

    cout <<  ans1 << '\n' << ans2;

    return 0;
}
