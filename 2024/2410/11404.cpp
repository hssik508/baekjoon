#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(n + 1, 100000000));
    vector<vector<int>> allDist(n + 1, vector<int>(n + 1));
    for (int i = 0; i < m; i++)
    {
        int c1, c2, cost;
        cin >> c1 >> c2 >> cost;
        if (cost > v[c1][c2])
            continue;
        v[c1][c2] = cost;
    }

    for (int i = 1; i <= n; i++)
    {
        vector<int> dist(n + 1, 100000000);
        dist[i] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // 가중치 가장 작은 간선부터 선택하기 위함
        for (int j = 1; j <= n; j++)
        {
            if (v[i][j] < 100000000 && dist[j] != 0) // 자기 자신으로 가는 경우 무시
            {
                dist[j] = v[i][j];
                pq.push({v[i][j], j}); // 비용과 노드번호 삽입
            }
        }

        while (!pq.empty())
        {
            int node = pq.top().second;
            int cost = pq.top().first;
            pq.pop();
            if (cost > dist[node])
                continue;
            dist[node] = cost;
            for (int k = 1; k <= n; k++)
            {
                if (v[node][k] == 100000000 || node == k)
                    continue;
                if (cost + v[node][k] < dist[k])
                    pq.push({cost + v[node][k], k}); // a->c 보다 a->b->c가 더 금방이면 새로운 값 pq에 삽입
            }
        }

        for (int j = 1; j <= n; j++)
        {
            allDist[i][j] = dist[j];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (allDist[i][j] == 100000000)
                allDist[i][j] = 0;
            cout << allDist[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}