#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    cin>>n;
    vector<vector<int>> v(n);
    int num, root;
    for (int i=0; i<n; i++)
    {
        cin>>num;
        if (num==-1)
        {
            root=i; // root 노드 저장
            continue;
        }
        v[num].push_back(i); // 자식 노드 저장
    }
    int rm, cnt=0;
    cin>>rm;
    if (rm==root)
    {
        cout<<0;
        return 0;
    }
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int node=q.front();
        q.pop();
        int exist=0;
        for (size_t i=0; i<v[node].size(); i++)
        {
            if (v[node][i]!=rm) // 제거된 노드가 아닌 경우만 포함
            { 
                q.push(v[node][i]);
                exist=1;
            }
        }
        if (exist==0)
            cnt++;
    }
    cout<<cnt;
    return 0;
}