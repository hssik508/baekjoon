#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

unordered_map<string, int> u;

bool compare(string a, string b)
{
    if (u[a] == u[b])
        return a < b;
    return u[a] > u[b];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<string> v;
    string str, s;
    cin.ignore();
    getline(cin, str);
    stringstream ss(str);
    while (getline(ss, s, ' '))
    {
        v.push_back(s);
    }

    for (size_t i = 0; i < v.size(); i++)
    {
        getline(cin, str);
        ss.clear();
        ss.str(str);
        while (getline(ss, s, ' '))
        {
            u[s]++;
        }
    }

    sort(v.begin(), v.end(), compare);
    for (size_t i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ' << u[v[i]] << '\n';
    }
    return 0;
}