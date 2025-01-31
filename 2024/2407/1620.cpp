#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    unordered_map<string, int> u1;
    unordered_map<int, string> u2;
    string s;
    for (int i = 1; i <= n; i++)
    {
        cin >> s;
        u1[s] = i;
        u2[i] = s;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        if (s[0] >= '1' && s[0] <= '9')
        {
            int num = stoi(s);
            cout << u2[num] << '\n';
        }
        else
            cout << u1[s] << '\n';
    }
    return 0;
}
