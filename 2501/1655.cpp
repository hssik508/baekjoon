#include <iostream>
#include <queue>

using namespace std;
// 중앙값과 새로 들어오는 값을 비교하여 힙에 저장해주고 크기가 불균형해지면 중앙값을 새롭게 갱신해주고 기존 중앙값을 힙에 넣어줌
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n;
    cin>>n;
    priority_queue<int> maxHeap; // 중앙값보다 작은 수 저장
    priority_queue<int, vector<int>, greater<>> minHeap; // 중앙값보다 큰 수 저장
    int num, middle;
    cin>>middle; // 일단 처음 받는 수를 중앙값으로 설정
    cout<<middle<<'\n';
    for (int i=0; i<n-1; i++)
    {
        cin>>num;
        if (num>=middle)
            minHeap.push(num);
        else
            maxHeap.push(num);
        
        if (minHeap.size()-maxHeap.size()==2)
        {
            maxHeap.push(middle);
            middle=minHeap.top();
            minHeap.pop();
        }
        if (maxHeap.size()-minHeap.size()==1)
        {
            minHeap.push(middle);
            middle=maxHeap.top();
            maxHeap.pop();
        }
        cout<<middle<<'\n';
    }
    return 0;
}