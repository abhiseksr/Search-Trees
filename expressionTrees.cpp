/* Expression tree evaluating expression implementation in C/C++ 
Author - Abhishek Kumar */

#include<iostream>
#include<map>
#include<stack>
using namespace std;

struct node{
    int data;
    struct node *left, *right;
};

typedef struct node node;

node * create(int value){
    node * newnode = (node *)malloc(sizeof(node));
    newnode->data = value;
    newnode->left = 0;
    newnode->right = 0;
    return newnode;
}

// postorder traversal
int dfs(node * ptr, map<int, int (*)(int,int)> &mp){
    if (ptr->left != 0) {
        int l = dfs(ptr->left,mp);
        int r = dfs(ptr->right,mp);
        return mp[ptr->data](l,r);
    }
    return ptr->data;
}

int mul(int a,int b){
    return a*b;
}

int add(int a,int b){
    return a+b;
}

int sub(int a,int b){
    return a-b;
}

int divide(int a,int b){
    return a/b;
}

int main(){

    // without parenthesis
    //mapping ->  (-1:+) (-2:-) (-3:*) (-4:/)
    int postfix[] = {8,4,2,-4,3,-3,-2,9,-1}; // infix: a-b/c*d+e    postfix: abc/d*-e+
    int n = sizeof(postfix)/sizeof(int);
    map<int,int (*)(int,int)> mp = {{-1,add},{-2,sub},{-3,mul},{-4,divide}};
    stack<node *> st;
    for (int i=0;i<n;i++){
        node * ptr = create(postfix[i]);
        if (postfix[i]>=0){
            st.push(ptr);
        }
        else{
            node *ptr2 = st.top();
            st.pop();
            node *ptr1 = st.top();
            st.pop();
            ptr->left = ptr1;
            ptr->right = ptr2;
            st.push(ptr);
        }
    }
    cout<<dfs(st.top(),mp)<<endl;
    return 0;
}