#include <iostream>

using namespace std;

int main()
{
    // 역방향으로 풀기 => b를 a로 만드는 횟수 구하기
    int a, b, cnt = 1;
    cin >> a >> b;
    while (b > a)
    {
        if (b % 10 == 1)
        {
            b--;
            b /= 10;
        }
        else if (b % 2 == 0)
            b /= 2;
        else
            break;
        cnt++;
    }
    if (b == a)
        cout << cnt;
    else
        cout << -1;
    return 0;
}

/* 비효율적 코드
#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
    long long a, b;
    cin>>a>>b;
    string s;
    long long tmp;
    queue<pair<long long,int>> q; // 값, 연산횟수 저장
    q.push({a,0});
    long long ans=-2;
    while (!q.empty())
    {
        long long num=q.front().first;
        int cnt=q.front().second;
        q.pop();
        if (num==b)
        {
            ans=cnt;
            break;
        }
        if (num>1000000000)
            continue;
        q.push({num*2, cnt+1});
        s=to_string(num);
        s+="1";
        if (s.length() > 10)
            continue;
        tmp=stoll(s);
        q.push({tmp, cnt+1});
    }
    cout<<ans+1;
    return 0;
}
 */