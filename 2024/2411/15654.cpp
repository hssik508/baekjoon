#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int> arr;
vector<int> print(9);
vector<bool> visit(9);

void dfs(int level)
{
    if (level == m)
    {
        for (int i = 0; i < m; i++)
            cout << print[i] << ' ';
        cout << '\n';
    }
    for (int i = 1; i <= n; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            print[level] = arr[i];
            dfs(level + 1);
            visit[i] = false;
        }
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    arr.resize(n + 1); // 벡터 arr 크기 설정
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin() + 1, arr.begin() + n + 1); // 부분 정렬
    dfs(0);
    return 0;
}