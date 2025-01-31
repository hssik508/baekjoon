#include <iostream>

using namespace std;

int main()
{
    int n;
    cin>>n;
    int arr[51][51];
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            cin>>arr[i][j];
        }
    }
    if (arr[1][1] < arr[1][2] && arr[1][1] < arr[2][1])
    {
        cout << 0;
    }
    else if (arr[1][1] > arr[1][2] && arr[1][1] < arr[2][1])
    {
        cout << 1;
    }
    else if (arr[1][1] > arr[1][2] && arr[1][1] > arr[2][1])
    {
        cout << 2;
    }
    else if (arr[1][1] < arr[1][2] && arr[1][1] > arr[2][1])
    {
        cout << 3;
    }
    return 0;
}