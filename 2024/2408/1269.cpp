#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin>>n>>m;
    int num;
    unordered_map<int, bool> A, B;
    int asize=0, bsize=0;
    for (int i=0; i<n; i++)
    {
        cin>>num;
        A[num]=true;
    }
    for (int i=0; i<m; i++)
    {
        cin>>num;
        B[num]=true;
    }
    for (auto i:A)
    {
        if (!B[i.first])
            asize++;
    }
    for (auto i:B)
    {
        if (!A[i.first])
            bsize++;
    }
    cout<<asize+bsize;
    return 0;
}