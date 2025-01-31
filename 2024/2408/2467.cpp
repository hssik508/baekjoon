#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num;
    cin >> n;
    vector<int> san, alc;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        if (num < 0)
            alc.push_back(num);
        else
            san.push_back(num);
    }
    sort(alc.begin(), alc.end());
    sort(san.begin(), san.end());
    if (alc.size() == 0)
    {
        cout << san[0] << ' ' << san[1];
        return 0;
    }
    if (san.size() == 0)
    {
        cout << alc[alc.size() - 2] << ' ' << alc[alc.size() - 1];
        return 0;
    }
    int min_alc = alc[0], min_san = san[0], min_dif = abs(min_alc + min_san);
    int i = 0, j = (int)san.size() - 1;
    while (i < (int)alc.size() && j >= 0)
    {
        int sum = alc[i] + san[j];
        if (abs(sum) < min_dif)
        {
            min_alc = alc[i];
            min_san = san[j];
            min_dif = abs(sum);
        }
        if (sum < 0)
            i++;
        else if (sum == 0)
            break;
        else
            j--;
    }
    if (alc.size() >= 2 && abs(alc[alc.size() - 1] + alc[alc.size() - 2]) < min_dif)
    {
        min_alc = alc[alc.size() - 2];
        min_san = alc[alc.size() - 1];
    }
    if (san.size() >= 2 && abs(san[0] + san[1]) < min_dif)
    {
        min_alc = san[0];
        min_san = san[1];
    }
    cout << min_alc << ' ' << min_san;
    return 0;
}

/* 다른 풀이(이진탐색)
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, num;
    cin >> n;
    vector<int> san, alc;
    for (int i = 0; i < n; i++)
    {
        cin >> num;
        if (num < 0)
            alc.push_back(num);
        else
            san.push_back(num);
    }
    sort(alc.begin(), alc.end());
    sort(san.begin(), san.end());
    if (alc.size() == 0)
    {
        cout << san[0] << ' ' << san[1];
        return 0;
    }
    if (san.size() == 0)
    {
        cout << alc[alc.size() - 2] << ' ' << alc[alc.size() - 1];
        return 0;
    }
    if (alc.size() == 1 && san.size() == 1)
    {
        cout << alc[0] << ' ' << san[0];
        return 0;
    }
    int min_alc = alc[0], min_san = san[0], min_dif = abs(min_alc + min_san);
    for (size_t i = 0; i < alc.size(); i++)
    {
        int left = 0, right = (int)san.size() - 1;
        while (left <= right)
        {
            if (min_dif == 0)
                break;
            int mid = (left + right) / 2;
            if (abs(alc[i] + san[mid]) < min_dif)
            {
                min_alc = alc[i];
                min_san = san[mid];
                min_dif = abs(min_alc + min_san);
            }
            if (alc[i] + san[mid] < 0)
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    if (alc.size() >= 2 && abs(alc[alc.size() - 1] + alc[alc.size() - 2]) < min_dif)
    {
        min_alc = alc[alc.size() - 2];
        min_san = alc[alc.size() - 1];
    }
    if (san.size() >= 2 && abs(san[0] + san[1]) < min_dif)
    {
        min_alc = san[0];
        min_san = san[1];
    }
    cout << min_alc << ' ' << min_san;
    return 0;
}
*/