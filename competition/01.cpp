#include <iostream>
#include <cstdlib>

using namespace std;

int B[1000001] = {0};
int maxarr[1001] = {0};
int arr1[1001][1001]={0}, arr2[1001][1001]={0};


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;

    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            cin>>arr1[i][j];
        }
    }
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=n; j++)
        {
            cin>>arr2[i][j];
        }
    }
    for(int i = 1; i<=m; i++){
        cin >> B[i];
    }

    for(int j=1; j<=n; j++){
        int absmax=0, k=0;
        for(int i = 1; i<=n; i++){
            k = arr1[i][j]-arr2[i][j];
            if(k<0) k = -k;
            if (absmax<k) absmax=k;
        }
        maxarr[j] = absmax;
    }

    int sum=0;

    for(int i = 1; i<=m; i++){
        sum += maxarr[B[i]];
    }

    cout << sum;


    return 0;
}