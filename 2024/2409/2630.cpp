#include <iostream>
#include <vector>

using namespace std;

int white = 0;
int blue = 0;

void divide(int xstart, int ystart, int size, vector<vector<int>>& v) // 벡터를 참조에 의한 전달(&)로 해줘야 효율적임
{
    int existW = 0, existB = 0;
    for (int i = xstart; i < xstart + size; i++)
    {
        for (int j = ystart; j < ystart + size; j++)
        {
            if (v[i][j] == 0)
                existW = 1;
            else
                existB = 1;
        }
    }
    if (size == 1) // 크기가 1이면 색종이(파랑 or 하양)개수 즉시 증가 후 함수 종료
    {
        if (existW == 1)
            white++;
        else
            blue++;
        return;
    }

    if (existW == existB)
    {
        divide(xstart, ystart, size / 2, v);
        divide(xstart + size / 2, ystart, size / 2, v);
        divide(xstart, ystart + size / 2, size / 2, v);
        divide(xstart + size / 2, ystart + size / 2, size / 2, v);
    }
    else
    {
        if (existW == 1)
            white++;
        if (existB == 1)
            blue++;
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<vector<int>> v(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> v[i][j];
        }
    }
    divide(0, 0, n, v);
    cout << white << '\n'
         << blue;
    return 0;
}