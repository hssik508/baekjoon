#include <iostream>
#include <vector>

using namespace std;

vector<vector<pair<int, int>>> v; // <노드번호, 비용> 저장
int n;
int Max = 0;

void dfs(int node, int len, vector<bool> &visit) // len: 시작 노드부터 특정 노드까지 내려왔을때의 길이 저장하기 위한 변수
{
    visit[node] = true;
    for (size_t i = 0; i < v[node].size(); i++)
    {
        if (visit[v[node][i].first] || v[node][i].second == 0) // 노드가 방문했거나 비용이 없는경우 패스
            continue;
        dfs(v[node][i].first, len + v[node][i].second, visit);
    }
    if (len > Max)
        Max = len;
    return;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n;
    v.resize(n + 1);
    int n1, n2, cost;
    for (int i = 0; i < n - 1; i++)
    {
        cin >> n1 >> n2 >> cost;
        v[n1].push_back({n2, cost});
        v[n2].push_back({n1, cost});
    }
    for (int i = 1; i <= n; i++)
    {
        vector<bool> visit(n + 1);
        dfs(i, 0, visit);
    }
    cout << Max;
    return 0;
}