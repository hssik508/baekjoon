#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string s;
    cin >> s;
    string temp = "";
    vector<int> v;
    vector<char> c;
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]))
            temp += s[i];
        else
        {
            v.push_back(stoi(temp));
            temp = "";
            c.push_back(s[i]);
        }
    }
    v.push_back(stoi(temp));
    c.push_back('\0');
    int sum = 0, tmp = 0, sig = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (sig == 0)
            sum += v[i];
        else
            tmp += v[i];
        if (c[i] == '-')
            sig = 1;
    }
    cout << sum - tmp;
    return 0;
}