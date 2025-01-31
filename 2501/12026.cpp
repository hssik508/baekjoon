#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    int n;
    cin>>n;
    string s;
    cin>>s;
    int len=(int)s.size();
    vector<int> dp(len, 123456789); // dp배열: 특정 지점까지 이동하는 최소 비용 저장
    dp[0]=0;
    for (int i=0; i<len; i++)
    {
        if (dp[i]==123456789)
            continue;
        char c=s[i];
        //cout<<"차: "<<c<<'\n';
        if (c=='B')
        {
            for (int j=i; j<len; j++)
            {
                if (s[j]=='O')
                    dp[j]=min(dp[j], (int)(dp[i]+pow(j-i,2)));
            }
        }
        else if (c=='O')
        {
            for (int j=i; j<len; j++)
            {
                if (s[j]=='J')
                    dp[j]=min(dp[j], (int)(dp[i]+pow(j-i,2)));
            }
        }
        else
        {
            for (int j=i; j<len; j++)
            {
                if (s[j]=='B')
                    dp[j]=min(dp[j], (int)(dp[i]+pow(j-i,2)));
            }
        }
        // for (int list: dp)
        //     cout<<list<<' ';
        // cout<<'\n';
    }
    cout<<((dp[len-1]==123456789)?-1:dp[len-1]);
    return 0;
}