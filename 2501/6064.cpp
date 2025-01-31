#include <iostream>
#include <numeric>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int m, n, x, y;
        cin>>m>>n>>x>>y;
        int hae=-1, a=0;
        int limit=(m*n)/gcd(m,n); // 멸망해, gcd: 두 수의 최대공약수 구하는 함수
        while (m*a+x<=limit)
        {
            int namerge=(m*a+x)%n;
            if (namerge==0)
                namerge=n;
            if (namerge==y)
            {
                hae=m*a+x;
                break;
            }
            a++;
        }
        cout<<hae<<'\n';
    }
    return 0;
}