#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> score(n+1);
    vector<int> best(301);
    for (int i=1; i<=n; i++)
    {
        cin>>score[i];
    }
    best[1]=score[1];
    best[2]=score[1]+score[2];
    for (int i=3; i<=n; i++)
    {
        best[i]=max(best[i-2]+score[i], best[i-3]+score[i-1]+score[i]);
    }
    cout<<best[n];
    return 0;
}