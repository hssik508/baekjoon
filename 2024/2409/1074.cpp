#include <iostream>
#include <cmath>

using namespace std;

int r, c; // 타깃 좌표

int divide(int hang, int yeol, int length, int seq)
{
    if (length==1)
        return seq;
    int mid=length/2;
    int halfhang=hang+mid;
    int halfyeol=yeol+mid;
    if (r<halfhang && c<halfyeol)
        return divide(hang, yeol, mid, seq);
    else if (r<halfhang && c>=halfyeol)
        return divide(hang, yeol+mid, mid, seq+mid*mid);
    else if (r>=halfhang && c<halfyeol)
        return divide(hang+mid, yeol, mid, seq+2*mid*mid);
    else
        return divide(hang+mid, yeol+mid, mid, seq+3*mid*mid);
    // *주의사항: seq+pow(2, mid) 를 대입할 경우 마지막 부분을 처리할 때 1*1 대신 2*1(2의 1승)이 더해져서 잘못된 값 출력됨
}

int main()
{
    int n;
    cin>>n>>r>>c;
    // 타깃의 좌표가 몇 사분면이냐에 따라 재귀적으로 분할
    int len=pow(2, n);
    int res=divide(0, 0, len, 0); // 왼쪽 위 행 좌표, 왼쪽 위 열 좌표, 가로길이, 방문 순서
    cout<<res;
    return 0;
}