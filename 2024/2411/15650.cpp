#include <iostream>
#include <vector>

using namespace std;

int n, m;
vector<int> v(9);
vector<bool> visit(9);

void back(int st, int len)
{
    if (m == len)
    {
        for (int i = 0; i < m; i++)
            cout << v[i] << ' ';
        cout << '\n';
        return;
    }
    for (int i = st; i <= n; i++)
    {
        if (!visit[i])
        {
            visit[i] = true;
            v[len] = i;
            back(i + 1, len + 1);
            visit[i] = false;
        }
    }
}

int main()
{
    cout.tie(0)->sync_with_stdio(0);
    cin >> n >> m;
    back(1, 0);
    return 0;
}