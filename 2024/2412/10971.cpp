#include <iostream>

using namespace std;

int n;
int cost[10][10]={0};
bool visit[10]={false};
int minCost=12345678;

void tsp(int hang, int cnt, int curCost) // (시작 도시, 현재 위치한 도시, 현재까지 방문한 도시 개수, 현재까지의 비용)
{
    if (curCost>minCost) // 현재 비용이 이미 갱신한 최적 비용보다 커진 경우 즉시 탐색 종료
        return;

    if (cnt==n && cost[hang][0]!=0) // 도시 모두 방문했고 현 위치에서 시작 도시로 가는 경로가 있는 경우
    {
        minCost=min(curCost+cost[hang][0], minCost);
        return;
    }
    
    for (int next=0; next<n; next++) // next: 이동할 다음 도시
    {
        if (!visit[next] && cost[hang][next]!=0)
        {
            visit[next]=true;
            tsp(next, cnt+1, curCost+cost[hang][next]);
            visit[next]=false;
        }
    }
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>n;
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cin>>cost[i][j];
        }
    }
    visit[0]=true; // 시작점은 0번 도시
    tsp(0, 1, 0);
    cout<<minCost;
    return 0;
}