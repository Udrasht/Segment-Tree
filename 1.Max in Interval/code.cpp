#include <bits/stdc++.h>
using namespace std;
class SegmentTree
{

private:
    // create the segment tree
    void build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node] = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            int left = node * 2;
            int right = node * 2 + 1;
            build(left, start, mid, arr);
            build(right, mid + 1, end, arr);
            tree[node] = max(tree[left], tree[right]);
        }
    }

    // fild the maximum in the given range [left, right]
    // time complaxity O(logn)
    int queryprocess(int node, int start, int end, int left, int right)
    {
        if (end < left || right < start)
        {
            return INT_MIN;
        }

        else if (start == end)
        {
            return tree[node];
        }
        else if (left <= start && end <= right)
        {
            return tree[node];
        }
        else
        {
            int mid = (start + end) / 2;
            int leftValue = queryprocess(2 * node, start, mid, left, right);
            int rightValue = queryprocess(2 * node + 1, mid + 1, end, left, right);
            return max(leftValue, rightValue);
        }
    }
    void updateprocess(int node, int start, int end, int pos, int value)
    {
        if (start == end)
        {
            tree[node] = value;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= pos && pos <= mid)
            {
                updateprocess(node * 2, start, mid, pos, value);
            }
            else
            {
                updateprocess(node * 2 + 1, mid + 1, end, pos, value);
            }
            tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
        }
    }

public:
    vector<int> tree;
    int n;

    // constructoe
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n, INT_MIN);
        build(1, 0, n - 1, arr);
    }

    int query(int left, int right)
    {
        return queryprocess(1, 0, n - 1, left, right);
    }

    void update(int pos, int value)
    {
        updateprocess(1, 0, n - 1, pos, value);
    }
};
int main()
{
    vector<int> arr;
    arr = {8, 7, 4, 2, 5, 3, 1, 10};
    // arr={8,7,4,2,5};
    SegmentTree st(arr);
    vector<vector<int>> querys;
    querys = {{0, 7}, {0, 3}, {2, 7}, {1, 6}, {2, 6}};
    // querys={{0,4},{0,3},{2,4},{3,4},{2,3}};
    for (int i = 0; i < querys.size(); i++)
    {
        cout << "(" << querys[i][0] << ", " << querys[i][1] << ") -> " << st.query(querys[i][0], querys[i][1]) << endl;
    }
    return 0;
}