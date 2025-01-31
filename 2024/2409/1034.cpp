#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    vector<pair<int, int>> off(n); // 각 행별로 꺼져있는 램프의 개수를 저장
    for (int i = 0; i < n; i++)
    {
        int cnt = 0;
        string s;
        cin >> s;
        for (int j = 0; j < m; j++)
        {
            v[i][j] = s[j] - '0'; // 문자를 숫자로 변환
            if (v[i][j] == 0)
                cnt++;
        }
        off[i] = {cnt, i}; // 꺼진 램프 개수, 행 번호
    }
    cin >> k;
    sort(off.begin(), off.end());
    if (off[0].first > k)
    {
        cout << 0;
        return 0;
    }
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (off[i].first > k)
            break;
        int temp = k;
        temp -= off[i].first;
        if (temp % 2 == 1)
            continue;
        vector<vector<int>> tmp = v; // 조건에 맞게 스위치 눌렀을 때 램프 상태 저장용 임시 벡터
        for (int j = 0; j < m; j++)
        {
            if (v[off[i].second][j] == 0)
            {
                for (int k = 0; k < n; k++)
                {
                    if (tmp[k][j] == 1)
                        tmp[k][j] = 0;
                    else
                        tmp[k][j] = 1;
                }
            }
        }
        int onCnt = 0;
        for (int j = 0; j < n; j++)
        {
            bool on = true;
            for (int k = 0; k < m; k++)
            {
                if (tmp[j][k] == 0)
                {
                    on = false;
                    break;
                }
            }
            if (on == true)
                onCnt++;
        }
        if (onCnt > max)
            max = onCnt;
    }
    cout << max;
    return 0;
}