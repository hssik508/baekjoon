#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    stack<int> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    int index = 1, popNum = 1, possible = 1;
    s.push(v[0]);
    while (1)
    {
        if (index == n && s.empty())
            break;
        if (!s.empty() && s.top() == popNum) // 스택 비어있는지 확인해준 다음에 s.top() 체크해줄것 
        {
            s.pop();
            popNum++;
            continue;
        }
        if (index == n && s.top() != popNum)
        {
            possible = 0;
            break;
        }
        s.push(v[index++]);
    }
    if (possible == 1)
        cout << "Nice";
    else
        cout << "Sad";
    return 0;
}