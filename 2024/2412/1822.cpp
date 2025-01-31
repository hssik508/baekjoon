#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

map<int,bool> b;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int na, nb, num;
    cin>>na>>nb;
    int arr[500000]={0};
    for (int i=0; i<na; i++)
    {
        cin>>arr[i];
    }
    for (int i=0; i<nb; i++)
    {
        cin>>num;
        b[num]=true;
    }
    sort(arr, arr+na);
    int cnt=0;
    for (int i=0; i<na; i++)
    {
        if (b[arr[i]]==false)
            cnt++;
    }
    cout<<cnt<<'\n';
    for (int i=0; i<na; i++)
    {
        if (b[arr[i]]==false)
            cout<<arr[i]<<' ';
    }
    return 0;
}

/*
// 투 포인터 풀이법
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int na, nb;
    cin >> na >> nb;
    vector<int> a(na), b(nb);

    for (int i = 0; i < na; i++) 
        cin >> a[i];
    for (int i = 0; i < nb; i++) 
        cin >> b[i];

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    vector<int> result;
    int i = 0, j = 0;

    while (i < na) 
    {
        if (a[i] < b[j] || j >= nb) 
        {
            result.push_back(a[i]);
            i++;
        } 
        else if (a[i] == b[j]) 
        {
            i++;
            j++;
        } 
        else
            j++;
    }

    cout << result.size() << '\n';
    for (int x : result) 
        cout << x << ' ';
    return 0;
}
*/