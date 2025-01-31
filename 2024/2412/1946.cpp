#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int n;
        cin>>n;
        vector<pair<int,int>> v(n);
        for (int i=0; i<n; i++)
            cin>>v[i].first>>v[i].second;
        sort(v.begin(), v.end());
        int min=100001, cnt=0;
        for (int i=0; i<n; i++)
        {
            if (v[i].second<min)
            { 
                min=v[i].second;
                cnt++;
            }
        }
        cout<<cnt<<'\n';
    }
    return 0;
}