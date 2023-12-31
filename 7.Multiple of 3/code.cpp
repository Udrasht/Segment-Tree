//Link:-  https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-interview-prep/segment-tree/multiples-of-3-official/ojquestion

// There are N numbers(indexed from 1 to N) initially all are 0.
// You have to perform Q operations of two types:
// 1. 1 A B: increase all numbers in range from index A to B by 1.
// 2. 2 A B: count how many numbers in range from index A to B are divisible by 3.



#include <bits/stdc++.h>
using namespace std;
struct pal
{
    int zero = 0;
    int one = 0;
    int two = 0;
};
class SegmentTree
{
private:
    void update(int node, int left, int right)
    {
        tree[node].zero = tree[left].zero + tree[right].zero;
        tree[node].one = tree[left].one + tree[right].one;
        tree[node].two = tree[left].two + tree[right].two;
    }
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            tree[node].zero = 1;
        }
        else
        {
            int mid = (start + end) / 2;
            build(node * 2, start, mid);
            build(node * 2 + 1, mid + 1, end);
            update(node, node * 2, node * 2 + 1);
        }
    }

    void shift(int node)
    {
        pal temp;

        temp.zero = tree[node].two;
        temp.one = tree[node].zero;
        temp.two = tree[node].one;
        tree[node] = temp;
    }

    void propogate(int node, int start, int end)
    {
        if(Lazy[node]==0||Lazy[node]%3==0){
            Lazy[node]=0;
            return;
        }
        if (start == end)
        {
            int rotation = Lazy[node] % 3;
            pal temp;
            if (rotation == 1)
            {
                shift(node);
            }
            else if (rotation == 2)
            {
                shift(node);
                shift(node);
            }
            Lazy[node] = 0;
        }
        else
        {
            int rotation = Lazy[node] % 3;
            pal temp;
            if (rotation == 1)
            {
                temp.zero = tree[node].two;
                temp.one = tree[node].zero;
                temp.two = tree[node].one;
            }
            else if (rotation == 2)
            {
                temp.zero = tree[node].one;
                temp.one = tree[node].two;
                temp.two = tree[node].zero;
            }
            tree[node] = temp;
            Lazy[node * 2] += Lazy[node];
            Lazy[node * 2 + 1] += Lazy[node];
            Lazy[node] = 0;
        }
    }

    int queryProcess(int node, int start, int end, int left, int right)
    {
        propogate(node, start, end);
        if (left > end || right < start)
            return 0;
        if (start == end)
        {
            return tree[node].zero;
        }
       else if (left <= start && end <= right)
        {
            return tree[node].zero;
        }
        else
        {
            int mid = (start + end) / 2;
            int leftvalue = queryProcess(node*2, start, mid, left, right);
            int rightvalue = queryProcess(node*2+1, mid + 1, end, left, right);
            
            return leftvalue+rightvalue;
        }
    }

    void updateProcess(int node, int start, int end, int left, int right)
    {
        propogate(node, start, end);
        if (start > right || end < left)
        {
            return;
        }
        else if (start == end)
        {
            shift(node);
        }
        else if (left <= start && end <= right)
        {
            Lazy[node]+=1;
            propogate(node, start, end);
        }
        else
        {
            int mid = (start + end) / 2;
            updateProcess(node * 2, start, mid, left, right);
            updateProcess(node * 2 + 1, mid + 1, end, left, right);
           update(node, node * 2, node * 2 + 1);
            
        }
    }

public:
    int n;
    vector<pal> tree;
    vector<int> Lazy;

    SegmentTree(int n)
    {
        this->n = n;
        tree.resize(4 * n);
        Lazy.resize(4 * n);
        // initally all the elements are zero;
        build(1, 0, n - 1);
        printTree();
    }
    void printTree(){
        for(auto it: tree){
            cout<<"("<<it.zero<<" "<<it.one<<" "<<it.two<<")  ";
        }
        cout<<endl;

    }
    int query(int left, int right)
    {
        return queryProcess(1, 0, n - 1, left, right);
    }
    void updateRange(int left, int right)
    {
        updateProcess(1, 0, n - 1, left, right);
    }
};



int main()
{
    int numberOfBulb=8;
    
    SegmentTree st(numberOfBulb);
    vector<string> querys = {"Query","Query", "update", "Query", "update", "Query","Query","Query","Query","update","update","Query"};
    vector<vector<int>> queryvalue = {{0,7},{3,5}, {4, 6}, {2,4}, {5,5}, {3,7},{0,7},{5,5},{6,6},{0,7},{3,7},{0,7}};
    

    for (int i = 0; i < querys.size(); i++)
    {
        if (querys[i] == "Query")
        {
            cout << " Number of element in  (" << queryvalue[i][0] <<", "<<queryvalue[i][1]<< ")  Multiple of 3 -> " << st.query(queryvalue[i][0],queryvalue[i][1]) << endl;
        // st.printTree();
        }
        else if (querys[i] == "update")
        {
            st.updateRange(queryvalue[i][0], queryvalue[i][1]);
            // st.printTree();
            cout << " Updated" << endl;
        }
    }
    return 0;
}