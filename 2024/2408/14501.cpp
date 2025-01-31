#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<pair<int,int>> v(n+1);
    vector<int> maxMoney(n+1); // 상담을 n일차에 시작했을 때 얻을 수 있는 최대이득
    for (int i=1; i<=n; i++)
    {
        cin>>v[i].first>>v[i].second;
    }
    for (int i=n; i>=1; i--)
    {
        if (i+v[i].first>n+1)
            continue;
        int pay=v[i].second, max=0;
        for (int j=i+v[i].first; j<=n; j++)
        {
            if (maxMoney[j]>max)
                max=maxMoney[j];
        }
        maxMoney[i]=pay+max;
    }
    int max=0;
    for (int i=1; i<=n; i++)
    {
        if (maxMoney[i]>max)
            max=maxMoney[i];
    }
    cout<<max;
    return 0;
}