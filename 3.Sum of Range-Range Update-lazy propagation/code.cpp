// You are given an array(of integers) of length n.
// You are required to answer q queries.

// Queries can be of two types
// 0. 0 l r : In this you have to return sum of all elements arr[i] for i in l<=i<=r.
// 1. 1 l r val: In this query u have to increase all elements in this interval [l, r] by val.

// To do the above task u have to create a datastructure as follows :-

// Implement the SegmentTree class:
// 1. SegmentTree(int arr[]): Initializes the SegmentTree object with an array,
// 2. void update(int l, int r, int val): increase all elements in this interval [l, r] by val,
// 3. int query(int l, int r): return sum of all elements arr[i] for which i is in range [l, r].






#include <bits/stdc++.h>
using namespace std;
class SegmentTree
{
private:
    int build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return tree[node];
        }
        else
        {
            int mid = (start + end) / 2;
          int left= build(node * 2, start, mid, arr);
          int right= build(node * 2 + 1, mid + 1, end, arr);
            tree[node] = left+right;
            return tree[node];
        }
    }
    void propogate(int node,int start,int end){
        if(start==end){
            tree[node]=tree[node]+Lazy[node];
            Lazy[node]=0;
        }
        else{
            int numberOfElement=end-start+1;
            tree[node]=tree[node]+Lazy[node]*numberOfElement;
            Lazy[node*2]+=Lazy[node];
            Lazy[node*2+1]+=Lazy[node];
            Lazy[node]=0;
        }

    }
    void updateRangeProcess(int node, int start, int end, int left, int right, int value)
    {
        propogate(node,start,end);
        if (start > right || end < left)
        {
            return;
        }
        else if (start == end)
        {
            tree[node] = tree[node] + value;
        }
        else if (left <= start && end <= right)
        {
            Lazy[node] = Lazy[node] + value;
            propogate(node,start,end);
        }
        else
        {
            int mid = (start + end) / 2;
            updateRangeProcess(node * 2, start, mid, left, right, value);
            updateRangeProcess(node * 2 + 1, mid + 1, end, left, right, value);
            tree[node]=tree[node*2]+tree[node*2+1];
            
        }
    }


    int sumRangeprocess(int node, int start, int end, int left, int right)
    {

        propogate(node,start,end);   // for update the query
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
    vector<int> Lazy;
    int n;
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n, 0);
        Lazy.resize(4 * n, 0);
       int totalsum= build(1, 0, n - 1, arr);
        // printTree();
    }
    void printTree(){
        for(auto it: tree){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    void updateRange(int left, int right, int value)
    {
        updateRangeProcess(1, 0, n - 1, left, right, value);
        // printTree();
    }

    int Query(int left,int right)
    {
        return sumRangeprocess(1, 0, n - 1, left,right);

    }
};

int main()
{
    vector<int> arr;
    arr = {0, 10, 10, -1, 5, 8, 10, 2};

    vector<string> querys = {"Query", "update", "Query", "update", "Query"};
    vector<vector<int>> queryvalue = {{7,7}, {4, 6, 1}, {2,4}, {5,5, 7}, {3,7}};
    SegmentTree st(arr);

    for (int i = 0; i < querys.size(); i++)
    {
        if (querys[i] == "Query")
        {
            cout << " Value of index (" << queryvalue[i][0] <<", "<<queryvalue[i][1]<< ") -> " << st.Query(queryvalue[i][0],queryvalue[i][1]) << endl;
        }
        else if (querys[i] == "update")
        {
            st.updateRange(queryvalue[i][0], queryvalue[i][1], queryvalue[i][2]);
            cout << " Updated" << endl;
        }
    }
    return 0;
}