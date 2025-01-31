#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int x, y, n1, n2;
    cin >> x >> y;
    int arr[101] = {0};
    bool visit[101] = {false};
    int mv[] = {1, 2, 3, 4, 5, 6};
    for (int i = 0; i < x + y; i++)
    {
        cin >> n1 >> n2;
        arr[n1] = n2;
    }
    queue<pair<int, int>> q;
    q.push({1, 0});
    visit[1] = true;
    int pos, num;
    while (1)
    {
        pos = q.front().first;
        num = q.front().second;
        // cout<<"현위치: "<<pos<<' '<<"주사위 굴린 횟수: "<<num<<'\n';
        q.pop();
        if (pos == 100)
            break;
        for (int k = 0; k < 6; k++)
        {
            int nx = pos + mv[k];
            if (nx > 100 || visit[nx] == true)
                continue;
            visit[nx] = true;               // arr[nx]: 새로 이동한 위치에 표시되어 있는 수
            int index = arr[nx], temp = nx; // index: 새로 이동한 위치에 표시되어 있는 수, temp: 새로 이동한 위치
            while (1)                       // 사다리 or 뱀을 타고 간 위치에 또 사다리 or 뱀이 있는 경우를 처리하기 위함
            {
                if (index == 0)
                    break;
                temp = index;
                index = arr[index];
                visit[index] = true;
            }
            q.push({temp, num + 1});
        }
    }
    cout << num;
    return 0;
}