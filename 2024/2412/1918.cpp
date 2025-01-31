#include <iostream>
#include <stack>

using namespace std;

string s;
stack<char> st;

void manageStack(char ch)
{
    if (ch=='+' || ch=='-')
    {
        while (!st.empty())
        {
            if (st.top()=='(')
                break;
            cout<<st.top();
            st.pop();
        }
        st.push(ch);
    }
    else if (ch=='*' || ch=='/')
    {
        while (!st.empty() && (st.top()=='*' || st.top()=='/')) // 스택이 비어있지 않고 곱셈 혹은 나눗셈이 st.top()값인 경우에만 실행
        {
            cout<<st.top();
            st.pop();
        }
        st.push(ch);
    }
    else if (ch=='(')
        st.push(ch);
    else if (ch==')')
    {
        while (1)
        {
            if (st.top()=='(')
            {
                st.pop();
                break;
            }
            cout<<st.top();
            st.pop();
        }
    }
    // 기본 매커니즘: st.pop()에 위치한 문자보다 연산 우선순위가 높은 경우만 제거연산 안함
    // 덧셈이거나 뺄셈이면 여는 괄호 있는거 아닌이상 몽땅 다 제거 후 본인 삽입
    // 곱셈이거나 나눗셈이면 우선순위가 똑같은 곱셈이나 나눗셈 만나면 모두 제거 후 덧셈, 곱셈, 여는 괄호 중 하나 만나면 그 위치에 본인 삽입
    // 여는 괄호면 무조건 본인 삽입
    // 닫는 괄호면 여는 괄호 나올때까지 몽땅 다 pop, 삽입 x
    // oufofbounds 예외 주의
}

int main()
{
    cin>>s;
    for (size_t i=0; i<s.size(); i++)
    {
        if (s[i]>='A' && s[i]<='Z')
            cout<<s[i];
        else
            manageStack(s[i]);    
    }
    while (!st.empty())
    {
        cout<<st.top();
        st.pop();
    }
    return 0;
}