#include <iostream>

using namespace std;

int n;
bool visitY[15] = {false}; // 방문한 열인 경우 제외시키기 위함
int chess[15][15] = {0};   // 체스판 상태(퀸 놓인곳은 1로 표시)
int cnt = 0;               // 경우의 수

int is_place(int x, int y) // (x, y) 좌표에 퀸을 놓을 수 있는지 탐색
{
    if (visitY[y] == true) // 같은 열에 퀸 있으면 배제
        return 0;

    int tmpX = x, tmpY = y;
    while (1) // 대각선 왼쪽 위 탐색
    {
        tmpX--;
        tmpY--;
        if (tmpX < 0 || tmpY < 0)
            break;
        if (chess[tmpX][tmpY] == 1)
            return 0;
    }

    tmpX = x, tmpY = y;
    while (1) // 대각선 오른쪽 위 탐색
    {
        tmpX--;
        tmpY++;
        if (tmpX < 0 || tmpY >= n)
            break;
        if (chess[tmpX][tmpY] == 1)
            return 0;
    }

    return 1;
}

void nq(int hang) // (퀸 놓을 좌표 탐색 & 백트래킹)
{
    if (hang == n) // n개의 퀸을 조건에 맞게 모두 배치한 경우
    {
        cnt++;
        return;
    }

    for (int yeol = 0; yeol < n; yeol++) // 현재 행에서 가능한 열 확인
    {
        if (is_place(hang, yeol) == 1)
        {
            visitY[yeol] = true;   // 열 방문 표시
            chess[hang][yeol] = 1; // 퀸 배치
            nq(hang + 1);          // 다음 행 이동
            visitY[yeol] = false;  // 열 방문 해제(백트래킹)
            chess[hang][yeol] = 0; // 퀸 제거(백트래킹)
        }
    }
}

int main()
{
    cin >> n;
    nq(0);
    cout << cnt;
    return 0;
}