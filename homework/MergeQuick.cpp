#include <iostream>
#include <vector>
#include <chrono> // 시간 측정을 위한 라이브러리

using namespace std;
using namespace chrono;

// 합병 정렬 함수들
void merge(vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// 퀵 정렬 함수들
int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int num;
    vector<int> arr;
    while (1)
    {
        cin >> num;
        if (cin.eof())
            break;
        arr.push_back(num);
    }
    vector<int> arrCopy = arr; // 배열을 복사해서 동일한 배열을 사용

    // 입력받은 숫자 개수
    cout << "입력받은 숫자 개수: " << arr.size() << endl;

    // 합병 정렬 시간 측정
    auto startMerge = high_resolution_clock::now();
    mergeSort(arr, 0, arr.size() - 1);
    auto endMerge = high_resolution_clock::now();
    auto mergeDuration = duration_cast<microseconds>(endMerge - startMerge);
    cout << "합병 정렬 시간: " << mergeDuration.count() << " 마이크로초" << endl;

    // 퀵 정렬 시간 측정
    auto startQuick = high_resolution_clock::now();
    quickSort(arrCopy, 0, arrCopy.size() - 1);
    auto endQuick = high_resolution_clock::now();
    auto quickDuration = duration_cast<microseconds>(endQuick - startQuick);
    cout << "퀵 정렬 시간: " << quickDuration.count() << " 마이크로초" << endl;

    // 정렬된 배열 출력(단, 정렬하고자 하는 숫자가 100개보다 많으면 생략)
    if (arr.size() <= 100)
    {
        cout << "합병 정렬된 배열: ";
        for (int num : arr)
            cout << num << " ";
        cout << endl;
    }
    if (arr.size() <= 100)
    {
        cout << "퀵 정렬된 배열: ";
        for (int num : arrCopy)
            cout << num << " ";
        cout << endl;
    }
    return 0;
}
