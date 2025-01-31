#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> sumHang(n+1, vector<int>(n+1)); // 각 행끼리의 구간합을 저장
    int num;
    for (int i=1; i<=n; i++)
    {
        int sum=0;
        for (int j=1; j<=n; j++)
        {
            cin>>num;
            sum+=num;
            sumHang[i][j]=sum;
        }
    }
    int x1, x2, y1, y2;
    while (m--)
    {
        cin>>x1>>y1>>x2>>y2;
        int value=0;
        for (int i=x1; i<=x2; i++)
        {
            value+=sumHang[i][y2]-sumHang[i][y1-1];
        }
        cout<<value<<'\n';
    }
    return 0;
}