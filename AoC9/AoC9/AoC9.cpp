#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

ifstream f("input.in");

int final_id(int block_count)
{
    block_count = (!(block_count & 1)) ? block_count - 1 : block_count; 
    return block_count / 2;
}

size_t solve1(vector<int>& disk_map, size_t disk_size)
{
    size_t crt_idx = 0;
    size_t start_index = 0;
    size_t end_index = (disk_size % 2 == 1) ? disk_size - 1 : disk_size - 2;
    size_t start_ID = 0;
    size_t end_ID = final_id(disk_size);
    size_t sum = 0;

    while (start_index <= end_index)
    {
        if (start_index % 2 == 1)
        {
            if (disk_map[end_index] == 0)
            {
                end_index -= 2;
                end_ID--;
                if (start_index >= end_index)
                {
                    break;
                }
            }

            while (disk_map[start_index] > 0)
            {
                if (disk_map[end_index] == 0)
                {
                    end_index -= 2;
                    --end_ID;
                    if (start_index >= end_index)
                    {
                        break;
                    }
                }

                disk_map[end_index] -= 1;
                disk_map[start_index] -= 1;
                sum += end_ID * crt_idx;
                crt_idx++;
            }

        }
        else
        {
            for (int i = 0; i < disk_map[start_index]; ++i)
            {
                sum += start_ID * crt_idx;
                crt_idx++;
            }

            start_ID++;
        }

        start_index++;
    }

    return sum;
}

size_t solve2(const string& input_line)
{
    vector<pair<size_t, size_t>> disk_map; 
    size_t disk_size = 0;

    for (size_t i = 0; i < input_line.size(); i++) 
    {
        size_t in_size = input_line[i] - '0';  
        size_t out_size = in_size;               
        disk_map.push_back(make_pair(in_size, out_size));  
        disk_size++;
    }

    size_t crt_idx = 0;
    size_t start_index = 0;
    size_t end_index = (disk_size % 2) ? disk_size - 1 : disk_size - 2; 
    size_t end_ID = final_id(disk_size);
    size_t sum = 0;

    while (end_ID > 0)
    {
        start_index = 0;
        crt_idx = 0;

        while (start_index < end_index)
        {
            if (start_index % 2 == 1)
            { 
                if (disk_map[start_index].second >= disk_map[end_index].first) 
                {
                    while (disk_map[end_index].first > 0) 
                    {
                        disk_map[start_index - 1].second += 1;
                        disk_map[start_index].second -= 1;
                        disk_map[end_index].first -= 1;
                        sum += end_ID * crt_idx;
                        crt_idx++;
                    }
                    break;
                }
                else 
                {
                    crt_idx += disk_map[start_index].second;
                }
            }
            else 
            { 
                crt_idx += disk_map[start_index].second;
            }
            start_index++;
        }

        if (start_index == end_index) 
        {
            while (disk_map[end_index].first > 0)
            {
                disk_map[end_index].first -= 1;
                sum += end_ID * crt_idx;
                ++crt_idx;
            }
        }
        end_index -= 2;
        end_ID--;
    }

    return sum ;
}

int main()
{
    vector<int> disk_map;
    string line;
    getline(f, line);
    for (char ch : line)
    {
        if (ch != '\n') 
        {
            disk_map.push_back(ch - '0');
        }
    }
    size_t disk_size = disk_map.size();
    size_t result1 = solve1(disk_map, disk_size);
    size_t result2 = solve2(line);
    cout << "1: " << result1 << '\n';
    cout << "2: " << result2;
    getline(f, line);
    solve2(line);

    return 0;
}
