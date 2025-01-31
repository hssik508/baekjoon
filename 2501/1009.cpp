#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        int a, b;
        cin>>a>>b;
        a=a%10;
        if (a==0)
            a=10;
        b=b%4;
        if (b==0)
            b=4;
        int num=pow(a, b);
        string s=to_string(num);
        num=s[s.size()-1]-'0';
        if (num==0)
            num=10;
        cout<<num<<'\n';
    }
    return 0;
}



// 비효율적 풀이
// #include <iostream>
// #include <string>
// #include <cmath>

// using namespace std;

// int main()
// {
//     cin.tie(0)->sync_with_stdio(0);
//     int t;
//     cin>>t;
//     int arr[10][4], num;
//     for (int i=0; i<10; i++)
//     {
//         for (int j=0; j<4; j++)
//         {
//             if (i==0) // 나머지 0이면 10으로 만들기
//             {
//                 arr[i][j]=10;
//                 continue;
//             }
//             num=pow(i, j+1);
//             string s=to_string(num);
//             arr[i][j]=s[s.size()-1]-'0';
//         }
//     }
//     while (t--)
//     {
//         int a, b;
//         cin>>a>>b;
//         int namergeA=a%10;
//         int namergeB=b%4; 
//         if (namergeB==0) // 나머지 0나오면 4로 만들기
//             namergeB=4; 
//         cout<<arr[namergeA][namergeB-1]<<'\n';
//     }
//     return 0;
// }