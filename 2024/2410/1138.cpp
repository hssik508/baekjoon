#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int tall[11]={0}, arr[11]={0};
    for (int i=1; i<=n; i++)
    {
        cin>>tall[i];
    }
    for (int i=1; i<=n; i++)
    {
        int target=1+tall[i];
        for (int j=1; j<=target; j++)
        {
            if (arr[j]!=0)
                target++;
        }
        arr[target]=i;
    }
    for (int i=1; i<=n; i++)
    {
        cout<<arr[i]<<' ';
    }
    return 0;
}