#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    int sum=0, max=-1000;
    for (int i=0; i<n; i++)
    {
        sum+=v[i];
        if (sum>max)
            max=sum;
        if (sum<0)
            sum=0;
    }
    cout<<max;
    return 0;
}