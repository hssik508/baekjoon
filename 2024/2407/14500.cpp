#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> v(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> v[i][j];
        }
    }
    int sum, maxSum = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            sum = v[i][j] + v[i - 1][j] + v[i][j - 1] + v[i - 1][j - 1];
            if (sum > maxSum)
                maxSum = sum;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 3; j < m; j++)
        {
            sum = v[i][j] + v[i][j - 1] + v[i][j - 2] + v[i][j - 3];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    for (int i = 3; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum = v[i][j] + v[i - 1][j] + v[i - 2][j] + v[i - 3][j];
            if (sum > maxSum)
                maxSum = sum;
        }
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 2; j < m; j++)
        {
            for (int k = j - 2; k <= j; k++)
            {
                sum = v[i][j] + v[i][j - 1] + v[i][j - 2] + v[i - 1][k];
                if (sum > maxSum)
                    maxSum = sum;
            }
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 2; j < m; j++)
        {
            for (int k = j - 2; k <= j; k++)
            {
                sum = v[i][j] + v[i][j - 1] + v[i][j - 2] + v[i + 1][k];
                if (sum > maxSum)
                    maxSum = sum;
            }
        }
    }
    for (int i = 2; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            for (int k = i - 2; k <= i; k++)
            {
                sum = v[i][j] + v[i - 1][j] + v[i - 2][j] + v[k][j - 1];
                if (sum > maxSum)
                    maxSum = sum;
            }
        }
    }
    for (int i = 2; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            for (int k = i - 2; k <= i; k++)
            {
                sum = v[i][j] + v[i - 1][j] + v[i - 2][j] + v[k][j + 1];
                if (sum > maxSum)
                    maxSum = sum;
            }
        }
    }

    for (int i = 2; i < n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            sum = v[i][j] + v[i - 1][j] + v[i - 1][j - 1] + v[i - 2][j - 1];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    for (int i = 2; i < n; i++)
    {
        for (int j = 0; j < m - 1; j++)
        {
            sum = v[i][j] + v[i - 1][j] + v[i - 1][j + 1] + v[i - 2][j + 1];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 2; j < m; j++)
        {
            sum = v[i][j] + v[i][j - 1] + v[i - 1][j - 1] + v[i - 1][j - 2];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 2; j < m; j++)
        {
            sum = v[i][j] + v[i][j - 1] + v[i + 1][j - 1] + v[i + 1][j - 2];
            if (sum > maxSum)
                maxSum = sum;
        }
    }
    cout << maxSum;
    return 0;
}