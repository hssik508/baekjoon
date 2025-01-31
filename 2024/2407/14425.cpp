#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    unordered_map<string, bool> u;
    string s;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        u[s] = true;
    }
    int cnt = 0;
    for (int i = 0; i < m; i++)
    {
        cin >> s;
        if (u[s] == true)
            cnt++;
    }
    cout << cnt;
    return 0;
    
}
