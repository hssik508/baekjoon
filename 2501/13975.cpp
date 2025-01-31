#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        long long k, num;
        cin>>k;
        priority_queue<long long, vector<long long>, greater<>> pq;
        for (int i=0; i<k; i++)
        {
            cin>>num;
            pq.push(num);
        }
        long long a, b;
        long long minSum=0;
        while (1)
        {
            a=pq.top();
            pq.pop();
            b=pq.top();
            pq.pop();
            minSum+=a+b;
            pq.push(a+b);
            if (pq.size()==1)
                break;
        }
        cout<<minSum<<'\n';
    }
    return 0;
}