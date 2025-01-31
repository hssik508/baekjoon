#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int mx[] = {-1, 0, 0, 1};
int my[] = {0, -1, 1, 0};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<char>> v(n, vector<char>(n));
    vector<vector<char>> vec(n, vector<char>(n));
    vector<vector<bool>> visit(n, vector<bool>(n, false));
    vector<vector<bool>> vi(n, vector<bool>(n, false));
    for (int i = 0; i < n; i++)
    {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++)
        {
            v[i][j] = s[j];
            if (s[j] == 'G')
                vec[i][j] = 'R';
            else
                vec[i][j] = s[j];
        }
    }

    char c;
    int cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (visit[i][j] == true)
                continue;
            c = v[i][j];
            queue<pair<int, int>> q;
            q.push({i, j});
            visit[i][j] = true;
            int x, y;
            cnt1++;
            while (!q.empty())
            {
                x = q.front().first;
                y = q.front().second;
                for (int k = 0; k < 4; k++)
                {
                    if (x + mx[k] < 0 || y + my[k] < 0 || x + mx[k] >= n || y + my[k] >= n || visit[x + mx[k]][y + my[k]] == true || v[x + mx[k]][y + my[k]] != c)
                        continue;
                    q.push({x + mx[k], y + my[k]});
                    visit[x + mx[k]][y + my[k]] = true;
                }
                q.pop();
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (vi[i][j] == true)
                continue;
            c = vec[i][j];
            queue<pair<int, int>> q;
            q.push({i, j});
            vi[i][j] = true;
            int x, y;
            cnt2++;
            while (!q.empty())
            {
                x = q.front().first;
                y = q.front().second;
                for (int k = 0; k < 4; k++)
                {
                    if (x + mx[k] < 0 || y + my[k] < 0 || x + mx[k] >= n || y + my[k] >= n || vi[x + mx[k]][y + my[k]] == true || vec[x + mx[k]][y + my[k]] != c)
                        continue;
                    q.push({x + mx[k], y + my[k]});
                    vi[x + mx[k]][y + my[k]] = true;
                }
                q.pop();
            }
        }
    }

    cout << cnt1 << ' ' << cnt2;
    return 0;
}