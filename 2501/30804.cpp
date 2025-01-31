#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, arr[200000];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    if (n == 1)
    {
        cout << 1;
        return 0;
    }

    int maxlen = 2;
    int p1 = 0, p2 = 1;
    unordered_map<int, int> u; // 과일 종류, 개수 저장
    u[arr[p1]]++;
    u[arr[p2]]++;
    while (p2 < n)
    {
        if (u.size() > 2)
        {
            while (u.size() > 2)
            {
                u[arr[p1]]--;
                if (u[arr[p1]] == 0)
                    u.erase(arr[p1]); // 맵 상에서 해당 <키, 값> 쌍을 완전히 제거
                p1++;
            }
        }
        else
        {
            maxlen = max((p2 - p1) + 1, maxlen);
            p2++;
            u[arr[p2]]++;
        }
    }

    cout << maxlen;
    return 0;
}

// 추가 테스트케이스

// 9
// 5 5 5 1 1 1 1 2 1

// 9
// 2 2 2 2 2 3 3 3 4

// 10
// 1 2 1 1 1 1 1 3 3 3
