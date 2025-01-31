#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(n + 1));
    int n1, n2;
    for (int i = 0; i < m; i++)
    {
        cin >> n1 >> n2;
        v[n1][n2]++;
        v[n2][n1]++;
    }
    int min = 12345678;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        int seq = 0, sum = 0;
        vector<int> visit(n + 1);
        queue<pair<int, int>> q;
        q.push({i, seq});
        visit[i] = true;
        while (!q.empty())
        {
            int node = q.front().first;
            int nowSeq = q.front().second;
            sum += nowSeq;
            q.pop();
            for (int j = 1; j <= n; j++)
            {
                if (visit[j] == true)
                    continue;
                if (v[node][j] != 0)
                {
                    q.push({j, nowSeq + 1});
                    visit[j] = true;
                }
            }
        }
        if (sum < min)
            min = sum;
        arr[i] = sum;
    }
    for (int i = 1; i <= n; i++)
    {
        if (arr[i] == min)
        {
            cout << i;
            break;
        }
    }
    return 0;
}