#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    string st, s;
    cin >> st;
    vector<int> v(26);
    for (size_t i = 0; i < st.size(); i++)
    {
        v[st[i] - 'A']++;
    }
    int cnt = 0;
    for (int i = 1; i < n; i++)
    {
        cin >> s;
        if (abs((int)s.size() - (int)st.size()) >= 2)
            continue;
        vector<int> arr(26);
        int numDif = 0;
        for (size_t j = 0; j < s.size(); j++)
        {
            arr[s[j] - 'A']++;
        }
        // 두 문자열의 길이 차이별로 numDif 허용 범위를 다르게 적용해야함.
        if (abs((int)s.size() - (int)st.size()) == 1)
        {
            for (size_t k = 0; k < v.size(); k++)
            {
                if (abs(v[k] - arr[k]) >= 2)
                    numDif = 10;
                if (abs(v[k] - arr[k]) == 1)
                    numDif++;
            }
            if (numDif == 1)
                cnt++;
        }
        else if (s.size() == st.size())
        {
            for (size_t k = 0; k < v.size(); k++)
            {
                if (abs(v[k] - arr[k]) >= 2)
                    numDif = 10;
                if (abs(v[k] - arr[k]) == 1)
                    numDif++;
            }
            if (numDif <= 2)
                cnt++;
        }
    }
    cout << cnt;
    return 0;
}