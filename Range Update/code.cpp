#include <bits/stdc++.h>
using namespace std;
class SegmentTree
{
private:
    void build(int node, int start, int end, vector<int> &arr)
    {
        if (start == end)
        {
            tree[node] = arr[start];
        }
        else
        {
            int mid = (start + end) / 2;
            build(node * 2, start, mid, arr);
            build(node * 2 + 1, mid + 1, end, arr);
            tree[node] = 0;
        }
    }

    void updateRangeProcess(int node, int start, int end, int left, int right, int value)
    {
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
            tree[node] = tree[node] + value;
        }
        else
        {
            int mid = (start + end) / 2;
            updateRangeProcess(node * 2, start, mid, left, right, value);
            updateRangeProcess(node * 2 + 1, mid + 1, end, left, right, value);
        }
    }
    int processQuery(int node, int start, int end, int index)
    {
        if (start == end)
        {
            return tree[node];
        }
        else
        {
            int mid = (start + end) / 2;
            if (tree[node] != 0)
            {
                tree[node * 2] =tree[node * 2] + tree[node];
                tree[node * 2 + 1] =tree[node * 2 + 1]+ tree[node];
                tree[node] = 0;
            }

            if (start <= index && index <= mid)
            {
              return  processQuery(node * 2, start, mid, index);
            }
            else
            {
              return  processQuery(node * 2+1, mid + 1, end, index);
            }
        }
    }

public:
    vector<int> tree;
    int n;
    SegmentTree(vector<int> &arr)
    {
        n = arr.size();
        tree.resize(4 * n, 0);
        build(1, 0, n - 1, arr);
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

    int Query(int index)
    {
        return processQuery(1, 0, n - 1, index);

    }
};

int main()
{
    vector<int> arr;
    arr = {8, 7, 4, 2, 5, 3, 1, 10};
    // arr={8,7,4,2,5};
vector<string> querys={"Query", "update", "Query","Query","Query","update","Query","Query","Query","Query","Query","Query"};
    vector<vector<int>> queryvalue={{0}, {0,2,1}, {0},{1},{2},{2,5,-2},{1},{2},{3},{4},{5},{6}};
    SegmentTree st(arr);
   
    for(int i=0;i<querys.size();i++){
        if(querys[i]=="Query"){
             cout << " Value of index "<< queryvalue[i][0]<<"-> " << st.Query(queryvalue[i][0]) << endl;
             

        }
        else if(querys[i]=="update"){
            st.updateRange(queryvalue[i][0],queryvalue[i][1],queryvalue[i][2]);
            cout<<" Updated"<<endl;

        }


    }
    return 0;
}