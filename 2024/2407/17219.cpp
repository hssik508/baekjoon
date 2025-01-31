#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    unordered_map<string,string> u;
    string site, pw;
    for (int i=0; i<n; i++)
    {
        cin>>site>>pw;
        u[site]=pw;
    }
    for (int i=0; i<m; i++)
    {
        cin>>site;
        cout<<u[site]<<'\n';
    }
    return 0;
}
