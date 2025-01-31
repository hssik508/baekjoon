#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int k, dir, len;
    cin>>k;
    vector<int> seq, east, west, south, north;
    for (int i=0; i<6; i++)
    {
        cin>>dir>>len;
        seq.push_back(dir);
        if (dir==1)
            east.push_back(len);
        if (dir==2)
            west.push_back(len);
        if (dir==3)
            south.push_back(len);
        if (dir==4)
            north.push_back(len);
    }
    // 빼야 하는 넓이 구하는 방법: 방향이 한번만 나타나는 변과 인접해 있는 두 변의 길이의 차를 각각 구해서 곱하면 됨
    

    



}