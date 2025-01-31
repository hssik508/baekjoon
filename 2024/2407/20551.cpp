#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    int num;
    while (m--)
    {
        cin >> num;
        int left = 0, right = n - 1, exist = 0;
        while (left <= right)
        {
            int mid = (left + right) / 2;
            if (v[mid] < num)
                left = mid + 1;
            else
            {
                if (v[mid] == num)
                    exist = 1;
                right = mid - 1;
            }
        }
        if (exist == 0)
            cout << -1 << '\n';
        else
            cout << left << '\n';
    }
    return 0;
}

/* 다른 풀이
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    vector<int> v(n);
    for (int i=0; i<n; i++)
    {
        cin>>v[i];
    }
    sort(v.begin(), v.end());
    unordered_map<int,int> u;
    for (int i=0; i<n; i++)
    {
        if (u[v[i]]!=0)
            continue;
        u[v[i]]=i+1;
    }
    int num;
    while (m--)
    {
        cin>>num;
        if (u[num]==0)
            cout<<-1<<'\n';
        else
            cout<<u[num]-1<<'\n';
    }
    return 0;
}
*/