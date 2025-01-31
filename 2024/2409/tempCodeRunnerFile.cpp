#include <iostream>
#include <vector>

using namespace std;

struct Price
{
    int red;
    int green;
    int blue;
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<Price> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i].red >> v[i].green >> v[i].blue;
    }
    vector<char> color(n - 1); // 각 집별로 색칠해야 하는 색깔 저장
    int r, g, b;
    r = v[1].red - v[0].red;
    g = v[1].green - v[0].green;
    b = v[1].blue - v[0].blue;
    pair<char, int> big = {'r', r}; // 차이가 젤 큰 애를 red라 가정
    if (g > big.second)
        big = {'g', g};
    if (b > big.second)
        big = {'b', b};
    color[0] = big.first;
    for (int i = 1; i < n - 1; i++)
    {
        if (color[i - 1] == 'r')
        {
            g = v[i + 1].green - v[i].green;
            b = v[i + 1].blue - v[i].blue;
            color[i] = (g > b) ? 'g' : 'b';
        }
        if (color[i - 1] == 'g')
        {
            r = v[i + 1].red - v[i].red;
            b = v[i + 1].blue - v[i].blue;
            color[i] = (r > b) ? 'r' : 'b';
        }
        if (color[i - 1] == 'b')
        {
            r = v[i + 1].blue - v[i].blue;
            g = v[i + 1].green - v[i].green;
            color[i] = (r > g) ? 'r' : 'g';
        }
    }
    int sum = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (color[i] == 'r')
            sum += v[i].red;
        if (color[i] == 'g')
            sum += v[i].green;
        if (color[i] == 'b')
            sum += v[i].blue;
    }
    // 맨 마지막 집은 전에 색칠한 집의 색깔이 아닌 둘 중에 그냥 작은 값 더해주면 됨
    if (color[n - 2] == 'r')
        sum += min(v[n - 1].green, v[n - 1].blue);
    if (color[n - 2] == 'g')
        sum += min(v[n - 1].red, v[n - 1].blue);
    if (color[n - 2] == 'b')
        sum += min(v[n - 1].red, v[n - 1].green);
    cout << sum;
    return 0;
}