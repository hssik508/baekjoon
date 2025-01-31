#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin >> n;
    vector<int> v(31);
    int num;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        int index = 0;
        while (num >= 1)
        {
            if (num % 2 == 1)
                v[index]++;
            index++;
            num /= 2;
        }
    }
    int seq = 0;
    while (n--)
    {
        seq++;
        int temp = 0;
        for (int i = 30; i >= 0; i--)
        {
            temp *= 2;
            if (seq <= v[i])
                temp++;
        }
        cout << temp << " ";
    }
    return 0;
}