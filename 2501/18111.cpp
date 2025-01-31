#include <iostream>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m, b;
    cin>>n>>m>>b;
    int v[500][500];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin>>v[i][j];
        }
    }

    int time[257]; // 땅 높이에 따른 소요 시간
    for (int i=0; i<=256; i++)
        time[i]=987654321;

    for (int i=0; i<=256; i++) {
        int currBlock=b; // 가용 가능한 블록 개수 저장
        int currTime=0;
        for (int j=0; j<n; j++) {
            for (int k=0; k<m; k++) {
                int height=v[j][k];
                if (i-height>0) // 블록을 설치해야 하는 경우
                {
                    currTime+=i-height;
                    currBlock-=i-height;
                }
                else if (i-height<0) // 블록을 부숴야 하는 경우
                {
                    currTime-=2*(i-height);
                    currBlock-=i-height;
                }
            }
        }
        if (currBlock<0) // 최종적으로 사용한 블록이 가용가능한 블록보다 많은 경우 탈락
        {
            time[i]=987654321;
            continue;
        }
        time[i]=currTime;
    }
    int minTime=987654321, minHeight=0;
    for (int i=0; i<=256; i++)
    {
        if (time[i]<987654321 && time[i]<=minTime)
        {
            minTime=time[i];
            minHeight=i;
        }
    }
    cout<<minTime<<' '<<minHeight;
    return 0;
}