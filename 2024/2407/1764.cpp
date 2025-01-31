#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

//효율적 풀이
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

/* 비효율적 풀이
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    unordered_map<string,bool> hear, see;
    vector<string> name;
    string s;
    for (int i=0; i<n; i++)
    {
        cin>>s;
        hear[s]=true;
        name.push_back(s);
    }
    for (int i=0; i<m; i++)
    {
        cin>>s;
        see[s]=true;
        if (hear[s]==true) continue;
        name.push_back(s);
    }
    sort(name.begin(), name.end());
    int cnt=0;
    for (size_t i=0; i<name.size(); i++)
    {
        if (hear[name[i]]==true && see[name[i]]==true)
            cnt++;
    }
    cout<<cnt<<'\n';
    for (size_t i=0; i<name.size(); i++)
    {
        if (hear[name[i]]==true && see[name[i]]==true)
            cout<<name[i]<<'\n';
    }
    return 0;
}
*/