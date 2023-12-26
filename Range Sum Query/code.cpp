#include <bits/stdc++.h>
using namespace std;
class SegmentTree {
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
            tree[node] = tree[left]+tree[right];
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
            tree[node] = tree[node * 2]+tree[node * 2 + 1];
        }
    }
 int sumRangeprocess(int node, int start, int end, int left, int right)
    {
        if (end < left || right < start)
        {
            return 0;
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
            int leftValue = sumRangeprocess(2 * node, start, mid, left, right);
            int rightValue = sumRangeprocess(2 * node + 1, mid + 1, end, left, right);
            return leftValue+rightValue;
        }
    }

public:
   vector<int> tree;
    int n;
    SegmentTree(vector<int> &arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        build(1, 0, n - 1, arr);
        
    }
    
    void update(int pos, int value) {
        updateprocess(1, 0, n - 1, pos, value);
        
    }
    
    int sumRange(int left, int right) {
        return sumRangeprocess(1, 0, n - 1, left, right);
        
    }
};

int main()
{
    vector<int> arr;
    arr = {1, 3, 5};
    vector<string> querys={"sumRange", "update", "sumRange"};
    vector<vector<int>> queryvalue={{0, 2}, {1, 2}, {0, 2}};
    SegmentTree st(arr);
    for(int i=0;i<querys.size();i++){
        if(querys[i]=="sumRange"){
             cout << "Sum of Range (" << queryvalue[i][0] << ", " << queryvalue[i][1] << ") -> " << st.sumRange(queryvalue[i][0], queryvalue[i][1]) << endl;

        }
        else if(querys[i]=="update"){
            st.update(queryvalue[i][0],queryvalue[i][1]);
            cout<<"updated"<<endl;

        }


    }
   
    return 0;
}
