#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    vector<string> v;
    string name, inOut;
    unordered_map<string, bool> u;
    for (int i=0; i<n; i++)
    {
        cin>>name>>inOut;
        if (inOut=="enter")
        {
            u[name]=true;
            v.push_back(name);
        }
        if (inOut=="leave")
            u[name]=false;
    }
    sort(v.begin(), v.end(), greater<>());
    for (size_t i=0; i<v.size(); i++)
    {
        if (u[v[i]]==true)
        {
            cout<<v[i]<<'\n';
            u[v[i]]=false;
        }
    }
    return 0;
}