#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n, num;
    cin >> n;
    priority_queue<int> a;
    priority_queue<int, vector<int>, greater<>> b;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        a.push(num);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        b.push(num);
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += a.top() * b.top();
        a.pop();
        b.pop();
    }
    cout << sum;
    return 0;
}