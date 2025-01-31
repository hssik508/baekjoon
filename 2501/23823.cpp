#include <iostream>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, q;
    cin>>n>>q;
    int t, a;
    int garoHeight[30001]={0}, seroHeight[30001]={0}; // a번째 가로 & 세로의 높이가 각각 몇인지 저장
    int cnt=0, maxGaroHeight=0, maxSeroHeight=0, maxGaroCnt=0, maxSeroCnt=0; 
    // 출력해야 하는 숫자, 가로줄 최대 초코칩 높이, 세로줄 최대 초코칩 높이, 최대 높이인 가로줄 개수, 최대 높이인 세로줄 개수
    for (int i=0; i<q; i++)
    {
        cin>>t>>a;
        if (t==1) // 가로
        {
            garoHeight[a]++;
            if (garoHeight[a]>maxGaroHeight)
            {
                maxGaroCnt=0;
                maxGaroHeight=garoHeight[a];
            }
            if (garoHeight[a]==maxGaroHeight)
                maxGaroCnt++;
            
            if (maxSeroCnt==0)
                cnt=maxGaroCnt*n;
            else
                cnt=maxGaroCnt*maxSeroCnt;
        }
        else // 세로
        {
            seroHeight[a]++;
            if (seroHeight[a]>maxSeroHeight)
            {
                maxSeroCnt=0;
                maxSeroHeight=seroHeight[a];
            }
            if (seroHeight[a]==maxSeroHeight)
                maxSeroCnt++;
            
            if (maxGaroCnt==0)
                cnt=maxSeroCnt*n;
            else
                cnt=maxGaroCnt*maxSeroCnt;
        }
        cout<<cnt<<'\n';
    }
    return 0;
}