#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    unordered_map<string,bool> hear;
    vector<string> name;
    string s;
    for (int i=0; i<n; i++)
    {
        cin>>s;
        hear[s]=true;
    }
    for (int i=0; i<m; i++)
    {
        cin>>s;
        if (hear[s]==true)
            name.push_back(s);
    }
    sort(name.begin(), name.end());
    cout<<name.size()<<'\n';
    for (string list:name)
        cout<<list<<'\n';
    return 0;
}
