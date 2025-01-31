#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, n1, n2;
    cin >> n;
    vector<vector<int>> v(n + 1);
    vector<bool> visit(n + 1);
    for (int i = 0; i < n; i++)
    {
        cin >> n1 >> n2;
        v[n1].push_back(n2);
        v[n2].push_back(n1);
    }
    unordered_map<int, int> u;
    queue<int> q;
    q.push(1);
    visit[1] = true;
    int node;
    while (!q.empty())
    {
        node = q.front();
        for (size_t i = 0; i < v[node].size(); i++)
        {
            if (visit[v[node][i]] == true)
                continue;
            q.push(v[node][i]);
            u[v[node][i]] = node;
            visit[v[node][i]] = true;
        }
        q.pop();
    }
    for (int i = 2; i <= n; i++)
    {
        cout << u[i] << '\n';
    }
    return 0;
}