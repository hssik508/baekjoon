#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int tempSum, minSum = 0;
    for (int i = 0; i < n; i++)
    {
        tempSum = 0;
        for (int j = 0; j <= i; j++)
        {
            tempSum += v[j];
        }
        minSum += tempSum;
    }
    cout << minSum;
    return 0;
}