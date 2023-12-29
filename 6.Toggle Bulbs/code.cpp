// You are given n bulbs, numbered from 1 to n. Initially all the bulbs are turned off.
// You have to perform 2 types of operations:-

// 1. Toggle all bulds numbered between A to B.Here toggle mean turn on bulbs to off and off bulbs to on.This is represented by 1 A B.
// 2. Count how many bulbs numbered between A to B are on.This is represented by 2 A B.



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
    void propogate(int node,int start,int end){
        if(Lazy[node]==0){
            return;
        }
        if(start==end){
            tree[node]=1-tree[node];
            Lazy[node]=0;
        }
        else{
            int numberOfElement=end-start+1;
            int currentvalue=tree[node];
            int newvalue=numberOfElement-currentvalue;

            tree[node]=newvalue;
            Lazy[node*2]=1-Lazy[node*2];
            Lazy[node*2+1]=1-Lazy[node*2+1];
            Lazy[node]=0;
        }

    }
    void toggelRange(int node, int start, int end, int left, int right)
    {
        propogate(node,start,end);
        if (start > right || end < left)
        {
            return;
        }
        else if (start == end)
        {
            tree[node] = 1-tree[node];
        }
        else if (left <= start && end <= right)
        {
            Lazy[node] = 1-Lazy[node];
            propogate(node,start,end);
        }
        else
        {
            int mid = (start + end) / 2;
            toggelRange(node * 2, start, mid, left, right);
            toggelRange(node * 2 + 1, mid + 1, end, left, right);
            tree[node]=tree[node*2]+tree[node*2+1];
            
        }
    }


    int OpenBulbInRange(int node, int start, int end, int left, int right)
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
            int leftValue = OpenBulbInRange(2 * node, start, mid, left, right);
            int rightValue = OpenBulbInRange(2 * node + 1, mid + 1, end, left, right);
            return leftValue+rightValue;
        }
    }

public:
    vector<int> tree;
    vector<int> Lazy;
    int n;
    SegmentTree(int numberOfBulb)
    {
        n = numberOfBulb;
        tree.resize(4 * n, 0);
        Lazy.resize(4 * n, 0);
       
        // printTree();
    }
    void printTree(){
        for(auto it: tree){
            cout<<it<<" ";
        }
        cout<<endl;
    }
    void toggel(int left, int right)
    {
        toggelRange(1, 0, n - 1, left, right);
        // printTree();
    }

    int Query(int left,int right)
    {
        return OpenBulbInRange(1, 0, n - 1, left,right);

    }
};

int main()
{
    int numberOfBulb=8;
    
    SegmentTree st(numberOfBulb);
    vector<string> querys = {"Query","Query", "update", "Query", "update", "Query","Query","Query","Query","update","Query"};
    vector<vector<int>> queryvalue = {{0,7},{3,5}, {4, 6}, {2,4}, {5,5}, {3,7},{0,7},{5,5},{6,6},{0,7},{0,7}};
    

    for (int i = 0; i < querys.size(); i++)
    {
        if (querys[i] == "Query")
        {
            cout << " Number of Bulb open in range (" << queryvalue[i][0] <<", "<<queryvalue[i][1]<< ") -> " << st.Query(queryvalue[i][0],queryvalue[i][1]) << endl;
        }
        else if (querys[i] == "update")
        {
            st.toggel(queryvalue[i][0], queryvalue[i][1]);
            cout << " Updated" << endl;
        }
    }
    return 0;
}