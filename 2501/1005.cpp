#include <iostream>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int n, k;
        cin>>n>>k;
        vector<vector<int>> v(n+1);
        vector<int> time(n+1); // 각 번호별로 건물 건설 시간
        vector<int> before(n+1); // 이 건물 직전에 건설해야하는 이전 건물 수
        vector<int> ans(n+1); // 답을 누적해서 저장
        for (int i=1; i<=n; i++)
        {
            cin>>time[i];
        }
        int x, y;
        for (int i=0; i<k; i++)
        {
            cin>>x>>y;
            v[x].push_back(y);
            before[y]++;
        }
        int target;
        cin>>target;
        queue<int> q;
        for (int i=1; i<=n; i++)
        {
            if (before[i]==0)
            {
                q.push(i);
                ans[i]=time[i];
            }
        }
        while (!q.empty())
        {
            int node=q.front();
            q.pop();
            for (size_t i=0; i<v[node].size(); i++)
            {
                int next=v[node][i];
                before[next]--;
                if (ans[node]+time[next]>ans[next])
                    ans[next]=ans[node]+time[next];
                if (before[next]==0)
                {
                    q.push(next);
                }
            }
        }
        cout<<ans[target]<<'\n';
    }
    return 0;
}