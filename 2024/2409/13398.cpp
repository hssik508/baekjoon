#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // 풀기 보류
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    int big=v[0], sum=0, negNumPos=0, remove=0, i=0;
    while (i<n)
    {
        cout<<"아이 위치: "<<i<<'\n';
        if (remove==0 && sum<0)
        {
            negNumPos=i;
            cout<<"네가포스!!!"<<'\n';
            remove=1;
            i++;
            continue;
        }
        sum+=v[i];
        cout<<"현재 썸: "<<sum<<" "<<'\n';
        if (sum>big)
            big=sum;
        cout<<"===== 현재최대값: "<<big<<" ====="<<'\n';
        if (remove==1 && sum<0)
        {
            sum=0;
            remove=0;
            i=negNumPos+1;
            continue;
        }
        i++;
    }
    cout<<big;
    return 0;
}