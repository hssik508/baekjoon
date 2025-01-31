#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin>>t;
    while (t--)
    {
        string order, array;
        int len;
        deque<int> d; // 덱 써야 시간초과 안됨, STL reverse()는 O(n)이라 이 문제어선 시간초과됨
        cin>>order>>len>>array;
        string tmp=""; // 파싱용 임시 문자열
        int temp; // 파싱용 임시 정수
        for (size_t i=0; i<array.size(); i++)
        {
            if (array[i]>='0' && array[i]<='9')
                tmp+=array[i];
            else if (array[i]==',' || array[i]==']')
            {
                if (tmp=="") // 배열에 숫자가 아무것도 없는 경우
                    break;
                temp=stoi(tmp);
                d.push_back(temp);
                tmp=""; // 빈 문자열로 초기화
            }
        }
        int signal=0, error=0; // signal이 0이면 덱 앞에서 삭제연산, 1이면 덱 뒤에서 삭제연산
        for (size_t i=0; i<order.size(); i++)
        {
            if (order[i]=='R')
            {
                if (signal==0)
                    signal=1;
                else
                    signal=0;
            }
            else
            {
                if (d.empty())
                {
                    error=1;
                    break;
                }

                if (signal==0)
                    d.pop_front();
                else
                    d.pop_back();
            }
        }

        if (error==1)
        {
            cout<<"error\n";
            continue;
        }

        cout<<'[';
        while (!d.empty())
        {
            if (signal==0)
            {
                cout<<d.front();
                d.pop_front();
                if (!d.empty())
                    cout<<',';
            }
            else
            {
                cout<<d.back();
                d.pop_back();
                if (!d.empty())
                    cout<<',';
            }
        }
        cout<<"]\n";
    }
    return 0;
}