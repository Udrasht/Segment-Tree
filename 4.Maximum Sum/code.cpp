// You are given an array(of integers) of length n.
// You are required to answer q queries.

// Queries can be of two types :-
// Update
// 0 idx val : set arr[idx] to val.
// Query
// 1 l r: find i,j such that l <= i < j <= r, such that arr[i]+arr[j] is maximized. return arr[i]+arr[j].


// update T.C=O(logn)
// query T.C=O(logn)


#include <bits/stdc++.h>
using namespace std;

struct pal
{
    int sum = 0;
    int maxi = INT_MIN;
};

class SegmentTree
{
private:
     pal calc(pal leftnode, pal rightnode)
    {
        pal res;
        res.sum = max(leftnode.sum, max(rightnode.sum, leftnode.maxi + rightnode.maxi));
        res.maxi = max(leftnode.maxi, rightnode.maxi);
        return res;
        
    }
    void build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node].sum = arr[start];
            tree[node].maxi = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            build(node * 2, start, mid, arr);
            build(node * 2 + 1, mid + 1, end, arr);
            tree[node]= calc( tree[node*2], tree[node*2+1]);
        }
    }

    void updateValue(int node, int start, int end, int indx, int value)
    {
        if (start == end)
        {
            tree[node].maxi = tree[node].sum = value;
        }
        else
        {
            int mid = (start + end) / 2;
            if (start <= indx && indx <= mid)
            {
                updateValue(node * 2, start, mid, indx, value);
            }
            else
            {
                updateValue(node * 2 + 1, mid + 1, end, indx, value);
            }
           tree[node]= calc( tree[node*2], tree[node*2+1]);
           
        }
    }

   pal  maxSumQuery(int node, int start, int end, int left, int right)
    {

        if (end < left || right < start)
        {
            pal temp;
            temp.sum=0;
            temp.maxi=0;
            return temp;
        }

        else if (start == end)
        {
            return  tree[node];
        }
        else if (left <= start && end <= right)
        {
            return tree[node];
        }
        else
        {
            int mid = (start + end) / 2;
            pal leftValue = maxSumQuery(2 * node, start, mid, left, right);
            pal rightValue = maxSumQuery(2 * node + 1, mid + 1, end, left, right);
            return calc(leftValue, rightValue);
        }
    }

public:
    vector<pal> tree;
    
    int n;
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, arr);
        // printTree();
    }
    // void printTree(){
    //     for(auto it: tree){
    //         cout<<it.sum<<" "<<it.maxi<<",  ";
    //     }
    //     cout<<endl;
    // }
    void Update(int indx, int value)
    {
        updateValue(1, 0, n - 1, indx, value);
        // printTree();
    }

    pal Query(int left, int right)
    {
        return maxSumQuery(1, 0, n - 1, left, right);
    }
};

int main()
{
    vector<int> arr;
    arr = {0, 10, 10, 2, 5, 8, 10, 2};

    vector<string> querys = {"Query", "update", "Query", "update", "Query","Query"};
    vector<vector<int>> queryvalue = {{7, 7}, {4, 6}, {2, 4}, {5, 30}, {0, 1},{2, 7}};
    SegmentTree st(arr);

    for (int i = 0; i < querys.size(); i++)
    {
        if (querys[i] == "Query")
        {  pal ans=st.Query(queryvalue[i][0], queryvalue[i][1]);
            cout << " maximum Sum at indix (" << queryvalue[i][0] << ", " << queryvalue[i][1] << ") -> " << ans.sum << endl;
        }
        else if (querys[i] == "update")
        {
            st.Update(queryvalue[i][0], queryvalue[i][1]);
            cout << " Updated" << endl;
        }
    }
    return 0;
}