#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num, max=0;
    cin>>n;
    priority_queue<int, vector<int>, greater<>> pq;
    for (int i=0; i<n; i++)
    {
        cin>>num;
        if (num>max)
            max=num;
        pq.push(num);
    }

    int mindiff=1000000000;
    while (pq.top()<=1000000000)
    {
        num=pq.top();
        if (max-num<mindiff)
            mindiff=max-num;
        pq.pop();
        pq.push(num*2);
        if (num*2>max)
            max=num*2;
    }
    cout<<mindiff;
    return 0;
}