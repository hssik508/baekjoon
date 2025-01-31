#include <iostream>
#include <vector>

using namespace std;

int mx[] = {0, 1, 1, 1, 0, -1, -1, -1};
int my[] = {1, 1, 0, -1, -1, -1, 0, 1};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<char>> v(n, vector<char>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                int nx = i;
                int ny = j;
                int mbti = 1;
                for (int l = 0; l < 4; l++)
                {
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    {
                        mbti = 0;
                        break;
                    }
                    if (l == 0 && !(v[nx][ny] == 'E' || v[nx][ny] == 'I'))
                    {
                        mbti = 0;
                        break;
                    }
                    if (l == 1 && !(v[nx][ny] == 'N' || v[nx][ny] == 'S'))
                    {
                        mbti = 0;
                        break;
                    }
                    if (l == 2 && !(v[nx][ny] == 'T' || v[nx][ny] == 'F'))
                    {
                        mbti = 0;
                        break;
                    }
                    if (l == 3 && !(v[nx][ny] == 'P' || v[nx][ny] == 'J'))
                    {
                        mbti = 0;
                        break;
                    }
                    nx += mx[k];
                    ny += my[k];
                }
                if (mbti == 1)
                    cnt++;
            }
        }
    }
    cout << cnt;
    return 0;
}