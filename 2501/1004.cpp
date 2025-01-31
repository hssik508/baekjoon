#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int x1, y1, x2, y2;
        cin>>x1>>y1>>x2>>y2;
        int cnt1=0, cnt2=0; // 출발지 둘러싸는 원의 개수, 도착지 둘러싸는 원의 개수
        int n, x, y, r;
        cin>>n;
        while (n--)
        {
            cin>>x>>y>>r;
            int distS=pow(x1-x, 2)+pow(y1-y, 2);
            int distE=pow(x2-x, 2)+pow(y2-y, 2);
            r=r*r;
            if (r>distS && r>distE) // 출발지와 도착지를 동시에 둘러싸는 경우 체크
                continue;
            else if (r>distS)
                cnt1++;
            else if (r>distE)
                cnt2++;
        }
        cout<<cnt1+cnt2<<'\n';
    }
    return 0;
}

// 출발지 둘러싸는 원의 개수 + 도착지 둘러싸는 원의 개수 (단, 출발지와 도착지를 동시에 둘러싸는 원은 포함하면 안됨)
// 출발지와 원의 중심의 거리가 그 원의 반지름보다 짧으면 둘러싸고 있는 상태