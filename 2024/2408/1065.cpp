#include <iostream>
#include <string>

using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n < 100)
    {
        cout << n;
        return 0;
    }
    int cnt = 99;
    for (int i = 100; i <= n; i++)
    {
        string s = to_string(i);
        int dif = s[0] - s[1], hansu = 1;
        for (size_t i = 1; i < s.length() - 1; i++)
        {
            if (s[i] - s[i + 1] != dif)
            {
                hansu = 0;
                break;
            }
        }
        if (hansu == 1)
            cnt++;
    }
    cout << cnt;
    return 0;
}