#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin>>s;
    stack<char> st;
    char c;
    int cnt=0;
    for (size_t i=0; i<s.size(); i++)
    {
        c=s[i];
        if (i==0) 
        {
            st.push(c);
            continue;
        }
        if (c==')')
        {
            st.pop();
            if (s[i]!=s[i-1])
                cnt+=st.size();
            else
                cnt++;
        }
        else
            st.push(c);
    }
    cout<<cnt;
    return 0;
}


/* 비효율적 풀이
#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    string s;
    cin >> s;
    stack<char> st;
    char c;
    int tempcnt = 0, cnt = 0;

    for (size_t i = 0; i < s.size(); i++)
    {
        c = s[i];

        if (c == ')')
        {
            st.pop();
            if (i > 0 && s[i] != s[i - 1]) // i가 0일 때 s[i-1]을 참조하지 않게 처리
                cnt += tempcnt;
            else
            {
                cnt++;
                tempcnt--;
            }
        }
        else
        {
            if (i > 0 && s[i] == '(' && s[i - 1] == '(') // i가 0일 때 참조하지 않도록 수정
                tempcnt++;
            st.push(c);
        }

        if (st.empty())
            tempcnt = 0;
    }
    cout << cnt;
    return 0;
}
*/