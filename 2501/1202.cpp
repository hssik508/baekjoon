#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin>>n>>k;
    vector<pair<long long, long long>> v(n);
    priority_queue<long long> jewelValue; // 보석 가치 내림차순 정렬
    priority_queue<long long, vector<long long>, greater<>> bagWeight; // 가방 무게 오름차순 정렬
    for (int i=0; i<n; i++)
    {
        cin>>v[i].first>>v[i].second;
    }
    sort(v.begin(), v.end());
    long long num;
    for (int i=0; i<k; i++)
    {
        cin>>num;
        bagWeight.push(num);
    }
    long long valueSum=0;
    for (int i=0; i<n; i++)
    {
        long long weight=v[i].first;
        long long value=v[i].second;
        if (bagWeight.empty()) // 가방 몽땅 다 사용한 경우
            break;
        if (weight<=bagWeight.top()) // 현재 보석을 가장 용량이 작은 가방에 넣을 수 있는 경우 
            jewelValue.push(value); // 일단 현재 보석의 가격을 보석 pq에 삽입
        else // 현재 보석을 가장 용량이 작은 가방에 넣을 수 없는 경우
        {
            while (weight>bagWeight.top() && !bagWeight.empty()) // 현재의 보석을 넣을 수 있는 가방 나타날때까지 반복
            {
                if (!jewelValue.empty()) // 가방에 보석 pq에 저장된 보석을 넣을 수 있는 경우 
                {
                    valueSum+=jewelValue.top();
                    jewelValue.pop();
                    bagWeight.pop();
                }
                else // 가방에 더이상 넣을 수 있는 보석이 없는 경우
                    bagWeight.pop();
            }
            jewelValue.push(value);
        }
    }
    while (!jewelValue.empty() && !bagWeight.empty()) // 넣을 수 있는 가방과 보석이 남아있는 경우 마저 처리
    {
        valueSum+=jewelValue.top();
        jewelValue.pop();
        bagWeight.pop();
    }
    cout<<valueSum;
    return 0;
}