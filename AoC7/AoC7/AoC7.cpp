#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

ifstream f("input.in");
vector<string> in_data;

long long evaluate1(const vector<long long>& numbers, const vector<char>& operators) 
{
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) 
    {
        if (operators[i] == '+') 
            result += numbers[i + 1];
        else if (operators[i] == '*') 
            result *= numbers[i + 1];
        
    }
    return result;
}

bool solvable1(const vector<long long>& numbers, long long target)
{
    int n = numbers.size() - 1; //operatori necesari
    int combinations = pow(2, n); 

    for (int i = 0; i < combinations; i++) 
    {
        vector<char> operators;
        int mask = i;

        for (int j = 0; j < n; j++) 
        {
            if (mask % 2 == 0) 
                operators.push_back('+');
            else 
                operators.push_back('*');
            mask /= 2;
        }
        if (evaluate1(numbers, operators) == target) 
            return true;
    }
    return false;
}

long long solve1() 
{
    long long sum = 0;

    for (const string& line : in_data)
    {
        stringstream ss(line);
        long long target;
        char colon;
        ss >> target >> colon;

        vector<long long> numbers;
        long long num;
        while (ss >> num)
        {
            numbers.push_back(num);
        }

        if (solvable1(numbers, target)) 
            sum += target;
        
    }

    return sum;
}

long long evaluate2(const vector<long long>& numbers, const vector<char>& operators) 
{
    long long result = numbers[0];
    for (size_t i = 0; i < operators.size(); i++) 
    {
        if (operators[i] == '+') 
            result += numbers[i + 1];
        else if (operators[i] == '*') 
            result *= numbers[i + 1];
        else if (operators[i] == '|') 
        {
            string left = to_string(result);
            string right = to_string(numbers[i + 1]);
            result = stoll(left + right); 
        }
    }
    return result;
}

bool solvable2(const vector<long long>& numbers, long long target) 
{
    int n = numbers.size() - 1; 
    int combinations = pow(3, n); 

    for (int i = 0; i < combinations; i++) 
    {
        vector<char> operators;
        int mask = i;

        for (int j = 0; j < n; j++) 
        {
            int op = mask % 3;
            if (op == 0) 
                operators.push_back('+');
            else if (op == 1) 
                operators.push_back('*');
            else if (op == 2) 
                operators.push_back('|'); 
            mask /= 3;
        }
        if (evaluate2(numbers, operators) == target)
            return true;
        
    }

    return false;
}

long long solve2() 
{
    long long sum = 0;

    for (const string& line : in_data) 
    {
        stringstream ss(line);
        long long target;
        char colon;
        ss >> target >> colon;

        vector<long long> numbers;
        long long num;
        while (ss >> num)
        {
            numbers.push_back(num);
        }

        if (solvable2(numbers, target)) 
            sum += target;
    }

    return sum;
}

int main() 
{
    string line;
    while (getline(f, line))
    {
        in_data.push_back(line);
    }

    long long result1 = solve1();
    cout << result1 << '\n';

    long long result2 = solve2();
    cout << result2;

    return 0;
}
