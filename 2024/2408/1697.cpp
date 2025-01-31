#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    int pos = n, sec = 0;
    int visit[100001] = {0};
    queue<pair<int, int>> q;
    q.push({pos, sec});
    visit[pos] = 1;
    while (1)
    {
        pos = q.front().first;
        sec = q.front().second;
        int mx[] = {-1, 1, pos};
        if (pos == k)
            break;
        for (int i = 0; i < 3; i++)
        {
            int x = pos + mx[i];
            if (x < 0 || x > 100000)
                continue;
            if (visit[x] == 1)
                continue;
            visit[x] = 1;
            q.push({x, sec + 1});
        }
        q.pop();
    }
    cout << sec;
    return 0;
}