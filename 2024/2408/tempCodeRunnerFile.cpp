#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int x, y, n1, n2;
    cin >> x >> y;
    int arr[101] = {0};
    bool visit[101] = {false};
    int mv[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < x + y; i++)
    {
        cin >> n1 >> n2;
        arr[n1] = n2;
    }
    queue<pair<int, int>> q;
    q.push({1, 0});
    visit[1] = true;
    int pos, num;
    while (1)
    {
        pos = q.front().first;
        num = q.front().second;
        q.pop();
        if (pos == 100)
            break;
        if (arr[pos] != 0)
        {
            q.push({arr[pos], num});
            visit[arr[pos]] = true;
            continue;
        }
        for (int k = 0; k < 6; k++)
        {
            int nx = pos + mv[k];
            if (nx > 100 || visit[nx] == true)
                continue;
            visit[nx] = true;
            q.push({nx, num + 1});
        }
    }
    cout << num;
    return 0;
}