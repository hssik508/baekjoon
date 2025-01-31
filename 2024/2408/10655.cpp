#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<pair<int,int>> point(n);
    vector<int> dist(n);
    for (int i=0; i<n; i++)
    {
        cin>>point[i].first>>point[i].second;
        if (i==0) continue;
        dist[i]=abs(point[i].first-point[i-1].first)+abs(point[i].second-point[i-1].second);
    }
    int passpoint, maxDiff=0, newDist, bestDist;
    for (int i=2; i<n; i++)
    {
        newDist=abs(point[i].first-point[i-2].first)+abs(point[i].second-point[i-2].second);
        if (newDist<dist[i]+dist[i-1])
        {
            if ((dist[i]+dist[i-1])-newDist>maxDiff)
            {
                maxDiff=(dist[i]+dist[i-1])-newDist;
                passpoint=i-1;
                bestDist=newDist;
            }
        }    
    }   
    dist[passpoint+1]=bestDist;
    int sum=0;
    for (int i=1; i<n; i++)
    {
        if (i==passpoint) continue;
        sum+=dist[i];
    }
    cout<<sum;
    return 0;
}