#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n + 1);
    arr[1] = 0;
    int num;
    for (int i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + 1;
        if (i % 2 == 0)
            arr[i] = min(arr[i], arr[i / 2] + 1);
        if (i % 3 == 0)
            arr[i] = min(arr[i], arr[i / 3] + 1);
    }
    cout << arr[n];
    return 0;
}