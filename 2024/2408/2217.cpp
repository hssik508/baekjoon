#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    sort(v.begin(), v.end(), greater<>());
    int max=v[0];
    for (int i=0; i<n; i++)
    {
        if (v[i]*(i+1)>max)
            max=v[i]*(i+1);
    }
    cout<<max;
    return 0;
}