#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(n + 1, 123456789));
    for (int i = 0; i < m; i++)
    {
        int st, end, mon;
        cin >> st >> end >> mon;
        v[st][end] = min(v[st][end], mon); 
    }
    int st, end;
    cin >> st >> end;
    vector<int> dist(n + 1, 123456789);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    dist[st] = 0;
    q.push({0, st});
    while (!q.empty())
    {
        int curDist = q.top().first;
        int i = q.top().second;
        q.pop();
        if (curDist > dist[i])
            continue;
        for (int j = 1; j <= n; j++)
        {
            if (v[i][j] != 123456789)
            {
                int newDist = dist[i] + v[i][j];
                if (newDist < dist[j])
                {
                    dist[j] = newDist;
                    q.push({dist[j], j});
                }
            }
        }
    }
    cout << (dist[end] == 123456789 ? 0 : dist[end]);
    return 0;
}

/* 최적화 하기 전 코드(위의 최적화 코드는 지피티의 도움을 좀 받았다)
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n + 1, vector<int>(n + 1, 123456789));
    for (int i = 0; i < m; i++)
    {
        int st, end, mon;
        cin >> st >> end >> mon;
        if (mon > v[st][end])
            continue;
        if (st == end)
            v[st][end] = 0;
        v[st][end] = mon;
    }
    int st, end;
    cin >> st >> end;
    vector<int> dist(n + 1);
    vector<bool> visit(n + 1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q; // 비용, 노드번호
    // 다익스트라에 따라 st 지점으로부터 실시간으로 비용이 제일 적은 노드를 계속 골라줘야 하므로 우선순위 큐 활용
    for (int i = 1; i < n + 1; i++)
    {
        dist[i] = v[st][i];
        if (st != i && dist[i] != 123456789)
            q.push({dist[i], i});
    }
    dist[st] = 0;
    visit[st] = true;
    while (!q.empty())
    {
        int i = q.top().second; // st 지점으로부터 비용 젤 적은 노드 픽
        if (visit[i] == true)
        {
            q.pop();
            continue;
        }
        for (int j = 1; j < n + 1; j++)
        {
            if (v[i][j] == 123456789 || visit[j] == true)
                continue;
            int newDist = dist[i] + v[i][j]; // *** 주의사항: v[st][i]+v[i][j]로 하면 안됨
            if (newDist < dist[j])
            {
                dist[j] = newDist;
                q.push({dist[j], j});
            }
        }
        visit[i] = true;
        q.pop();
    }
    if (dist[end] == 123456789)
        dist[end] = 0;
    cout << dist[end];
    return 0;
}
*/