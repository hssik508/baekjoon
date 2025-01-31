#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num;
    cin >> n;
    if (n == 1)
    {
        cout << 0;
        return 0;
    }
    priority_queue<int, vector<int>, greater<>> q;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        q.push(num);
    }
    int sum = 0, twoSum, temp1, temp2;
    while (1)
    {
        temp1 = q.top();
        q.pop();
        temp2 = q.top();
        q.pop();
        twoSum = temp1 + temp2;
        sum += twoSum;
        if (q.empty())
            break;
        q.push(twoSum);
    }
    cout << sum;
    return 0;
}