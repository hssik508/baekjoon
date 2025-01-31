#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num;
    cin>>n;
    priority_queue<int, vector<int>, greater<>> q;
    for (int i=0; i<n*n; i++)
    {
        cin>>num;
        q.push(num);
        if (i>=n)
        {
            q.pop();
        }
    }
    cout<<q.top();
    return 0;
}

/* 메모리 많이 쓰는 풀이 
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num;
    cin>>n;
    vector<int> v(n*n);
    for (int i=0; i<n*n; i++)
    {
        cin>>v[i];
    }
    sort(v.begin(), v.end(), greater<>());
    cout<<v[n-1];
    return 0;
} */