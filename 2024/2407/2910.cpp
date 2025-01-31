#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

unordered_map<int, int> u;
unordered_map<int, int> order;

bool compare(int a, int b)
{
    if (u[a] == u[b])
        return order[a] < order[b];
    return u[a] > u[b];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, c;
    cin >> n >> c;
    vector<int> v;
    int num, rank = 1;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        u[num]++;
        v.push_back(num);
        if (order[num] == 0)
        {
            order[num] = rank;
            rank++;
        }
    }
    sort(v.begin(), v.end(), compare);
    for (int list : v)
        cout << list << ' ';
    return 0;
}