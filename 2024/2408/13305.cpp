#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<pair<long long, long long>> v(n + 1); // <1리터당 가격, 다음도시까지 거리>
    for (int i = 1; i < n; i++)
    {
        cin >> v[i].second;
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> v[i].first;
    }

    long long minPrice = v[1].first, priceSum = minPrice * v[1].second;
    for (int i = 2; i <= n - 1; i++)
    {
        if (v[i].first < minPrice)
        {
            minPrice = v[i].first;
        }
        priceSum += minPrice * v[i].second;
    }
    cout << priceSum;
    return 0;
}

/* <매커니즘>
minPrice -> 1번 도시 가격으로 우선 지정 , 1번 도시와 2번 도시 가격 비교
만약 1번 도시가 싸다면 2번 도시 통과할때도 1번 도시 가격으로 기름 넣기
만약 2번 도시가 싸다면 minPrice값을 2번 도시 가격으로 변경 한 후 2번 도시 통과할때부턴 2번 도시 가격으로 기름 넣기
목적지 도착할때까지 위에 행위 반복 */