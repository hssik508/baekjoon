#include <iostream>
#include <unordered_map>
#include <vector>

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
        string s1, s2;
        unordered_map<string, int> u;
        vector<string> v;
        for (int i=0; i<n; i++)
        {
            cin>>s1>>s2;
            if (u[s2]==0)
                v.push_back(s2);
            u[s2]++;
        }
        int sum=1;
        for (size_t i=0; i<v.size(); i++)
        {
            sum*=(u[v[i]]+1);
        }
        sum--; // 모든 종류를 아무것도 안입는 경우 제외
        cout<<sum<<'\n';
    }
    return 0;
}