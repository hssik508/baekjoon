#include <iostream>
#include <vector>

using namespace std;
vector<vector<char>> v(800, vector<char>(800, ' '));

void star(int num, int edge, int range)
{
    if (edge==num-range)
    {
        v[edge][edge]='*';
    }
    else
    {
        for (int i=edge; i<=num-range; i++)
        {
            for (int j=edge; j<=num-range; j++)
            {
                if (i==edge || i==num-range)
                    v[i][j]='*';
                else if (j==edge || j==num-range)
                    v[i][j]='*';
            }
        }
        star(num, edge+2, range+2);
    }
}


int main()
{
    cout.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    int num=1+4*(n-1);
    star(num, 1, 0);
    for (int i=1; i<=num*2-1; i++)
    {
        for (int j=1; j<=num; j++)
        {
            cout<<v[i][j];
        }
        cout<<'\n';
    }
    return 0;
}