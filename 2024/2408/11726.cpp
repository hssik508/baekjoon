#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int arr[1001]={0};
    arr[1]=1;
    arr[2]=2;
    for (int i=3; i<=n; i++)
    {
        arr[i]=arr[i-1]+arr[i-2];
        if (arr[i]>=10007)
            arr[i]=arr[i]%10007;
    }
    cout<<arr[n];
    return 0;
}