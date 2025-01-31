#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void level(vector<vector<int>> &v, vector<int> &inorder, int left, int right, int lv)
{
    if (left <= right)
    {
        int mid = (left + right) / 2;
        v[lv].push_back(inorder[mid]);
        level(v, inorder, left, mid - 1, lv + 1);
        level(v, inorder, mid + 1, right, lv + 1);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int k;
    cin >> k;
    int n = pow(2, k) - 1;
    vector<int> inorder(n);
    for (int i = 0; i < n; i++)
    {
        cin >> inorder[i];
    }
    vector<vector<int>> v(k);
    level(v, inorder, 0, n - 1, 0);
    for (int i = 0; i < k; i++)
    {
        for (size_t j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << ' ';
        }
        cout << '\n';
    }
    return 0;
}
