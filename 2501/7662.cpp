#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--)
    {
        int k;
        cin >> k;
        priority_queue<int, vector<int>, greater<>> q1; // 최소 힙
        priority_queue<int> q2;                         // 최대 힙
        unordered_map<int, int> u;                      // 숫자 존재 여부 확인용 맵
        char c;
        int num;
        for (int i = 0; i < k; i++)
        {
            cin >> c;
            cin >> num;
            if (c == 'I')
            {
                q1.push(num);
                q2.push(num);
                u[num]++;
            }
            else
            {
                if (q1.empty() || q2.empty())
                    continue;
                int tmp;
                if (num == -1)
                {
                    while (!q1.empty())
                    {
                        tmp = q1.top();
                        if (u[tmp] != 0)
                        {
                            u[tmp]--;
                            if (u[tmp] == 0)
                                u.erase(tmp);
                            q1.pop();
                            break;
                        }
                        q1.pop();
                    }
                }
                else
                {
                    while (!q2.empty())
                    {
                        tmp = q2.top();
                        if (u[tmp] != 0)
                        {
                            u[tmp]--;
                            if (u[tmp] == 0)
                                u.erase(tmp);
                            q2.pop();
                            break;
                        }
                        q2.pop();
                    }
                }
            }
        }
        while (1)
        {
            if (q1.empty() || u[q1.top()] != 0)
                break;
            q1.pop();
        }
        while (1)
        {
            if (q2.empty() || u[q2.top()] != 0)
                break;
            q2.pop();
        }

        if (q1.empty() && q2.empty())
        {
            cout << "EMPTY\n";
            continue;
        }
        else if (q1.empty())
            cout << q2.top() << ' ' << q2.top() << '\n';
        else if (q2.empty())
            cout << q1.top() << ' ' << q1.top() << '\n';
        else
            cout << q2.top() << ' ' << q1.top() << '\n';
    }
    return 0;
}