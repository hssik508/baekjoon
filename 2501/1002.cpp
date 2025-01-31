#include <iostream>
#include <cmath>

using namespace std;

// 두 원의 교점 개수로 판별
// 두 원의 위치관계(외접, 내접 등)를 생각하며 조건을 분기해야함
// 참고: https://mathbang.net/101#gsc.tab=0

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int x1, y1, r1, x2, y2, r2;
        cin>>x1>>y1>>r1>>x2>>y2>>r2;
        int dist=pow(x2-x1, 2)+pow(y2-y1, 2); // dist: 두 원 중심사이 거리, 루트 씌우면 데이터 손실될수도 있으므로 제곱해준 상태로 계산(피타고라스)
        if (dist==0) // 두 원의 중심이 동일한 경우
        {
            if (r1==r2)
                cout<<-1<<'\n'; 
            else
                cout<<0<<'\n';
        }
        else 
        {
            int rSum=pow(r1+r2, 2); // 두 원 반지름 길이 합
            int rDiff=pow(abs(r1-r2), 2); // 두 원 반지름 길이 차이
            if (dist>rSum) // 두 원이 떨어져있음
                cout<<0<<'\n';
            else if (dist==rSum) // 두 원이 외접함
                cout<<1<<'\n';
            else if (dist<rDiff) // 한 원이 다른 원 안에 포함됨
                cout<<0<<'\n';
            else if (dist==rDiff) // 두 원이 내접함
                cout<<1<<'\n';
            else // 두 원이 두 점에서 만남
                cout<<2<<'\n';
        }
    }
    return 0;
}