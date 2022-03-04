/* Splay tree implementation in C/C++
Author - Abhishek Kumar */
#include <iostream>
#include<queue>
#include "map.h"
using namespace std;

int digitCount(int n){
    int cnt = 0;
    while (n){
        cnt++;
        n /= 10;
    }
    return cnt;
}

class Splay
{
public:
    static class Splay *root;
    class Splay *par, *left, *right;
    int data;

    Splay *create(int data)
    {
        Splay *newnode = (Splay *)malloc(sizeof(Splay));
        newnode->data = data;
        newnode->left = 0;
        newnode->right = 0;
        newnode->par = 0;
        return newnode;
    }

    void dfs(Splay *head = root)
    {
        if (root == 0)
            return;
        if (head->left != 0)
        {
            dfs(head->left);
        }
        cout << head->data << ' ';
        if (head->right != 0)
        {
            dfs(head->right);
        }
    }

    void rightRotation(Splay *x)
    {
        Splay *y = x->left;
        x->left = y->right;
        if (y->right != 0)
        {
            y->right->par = x;
        }
        if (x->par != 0 && x->par->right == x)
        {
            x->par->right = y;
        }
        else if (x->par != 0 && x->par->left == x)
        {
            x->par->left = y;
        }
        y->par = x->par;
        y->right = x;
        x->par = y;
    }

    void leftRotation(Splay *x)
    {
        Splay *y = x->right;
        x->right = y->left;
        if (y->left != 0)
        {
            y->left->par = x;
        }
        if (x->par != 0 && x->par->left == x)
        {
            x->par->left = y;
        }
        else if (x->par != 0 && x->par->right == x)
        {
            x->par->right = y;
        }
        y->par = x->par;
        y->left = x;
        x->par = y;
    }

    void splay(Splay *newnode)
    {
        if (newnode->par == 0)
        {
            root = newnode;
            return;
        }
        Splay *p = newnode->par, *g = p->par;
        if (newnode->par == root)
        {
            if (newnode->par->left == newnode)
            {
                // cout<<"hi\n";
                rightRotation((p));
            }
            else
            {
                // cout<<"hello\n";
                leftRotation((p));
            }
        }
        else if (g->left == p && p->left == newnode)
        {
            rightRotation((g));
            rightRotation((p));
        }
        else if (g->right == p && p->right == newnode)
        {
            leftRotation((g));
            leftRotation((p));
        }
        else if (g->left == p)
        {
            leftRotation((p));
            rightRotation((g));
        }
        else
        {
            rightRotation((p));
            leftRotation((g));
        }
        splay(newnode);
    }

    void insert(int data)
    {
        Splay *newnode = create(data);
        if (root == 0)
        {
            root = newnode;
            return;
        }
        Splay *temp = root, *prev = 0;
        while (temp != 0)
        {
            prev = temp;
            if (data < temp->data)
            {
                temp = temp->left;
            }
            else if (data > temp->data)
            {
                temp = temp->right;
            }
            else
            {
                return;
            }
        }
        if (data < prev->data)
        {
            prev->left = newnode;
        }
        else
        {
            prev->right = newnode;
        }
        newnode->par = prev;
        splay(newnode);
    }

    Splay *inorderPredecessor(Splay *head)
    {
        if (head == 0)
            return head;
        while (head->right != 0)
        {
            head = head->right;
        }
        return head;
    }

    Splay *inorderSuccessor(Splay *head)
    {
        if (head == 0)
            return head;
        while (head->left != 0)
        {
            head = head->left;
        }
        return head;
    }

    void remove(int data, Splay *temp = root)
    {
        Splay *prev = 0;
        while (temp != 0 && temp->data != data)
        {
            prev = temp;
            if (data < temp->data)
            {
                temp = temp->left;
            }
            else if (data > temp->data)
            {
                temp = temp->right;
            }
        }
        if (temp->data != data)
        {
            if (prev != 0)
                splay(prev);
            return;
        }
        Splay *l = inorderPredecessor(temp->left);
        Splay *r = inorderSuccessor(temp->right);
        if (l == 0 && r == 0)
        {
            if (prev == 0)
            {
                root = 0;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = 0;
                }
                else
                {
                    prev->right = 0;
                }
                free(temp);
                splay(prev);
            }
            return;
        }
        if (l != 0)
        {
            if (l == temp->left)
            {
                l->right = temp->right;
                if (l->right != 0)
                {
                    l->right->par = l;
                }
            }
            else
            {
                if (l->left != 0)
                {
                    l->left->par = l->par;
                }
                l->par->right = l->left;
                l->right = temp->right;
                l->par = 0;
                if (l->right != 0)
                {
                    l->right->par = l;
                }
                l->left = temp->left;
                temp->left->par = l;
            }
            if (prev == 0)
            {
                root = l;
            }
            else
            {
                if (prev->left == temp)
                {
                    prev->left = l;
                    l->par = prev;
                }
                else
                {
                    prev->right = l;
                    l->par = prev;
                }
                free(temp);
                splay(prev);
            }
            return;
        }
        else
        {
            if (r == temp->right)
            {
                r->left = temp->left;
                if (r->left != 0)
                {
                    r->left->par = r;
                }
            }
            else
            {
                if (r->right != 0)
                {
                    r->right->par = r->par;
                }
                r->par->left = r->right;
                r->left = temp->left;
                r->par = 0;
                if (r->left != 0)
                {
                    r->left->par = r;
                }
                r->right = temp->right;
                temp->right->par = r;
            }
            if (prev == 0)
            {
                root = r;
            }
            else
            {
                if (prev->right == temp)
                {
                    prev->right = r;
                    r->par = prev;
                }
                else
                {
                    prev->left = r;
                    r->par = prev;
                }
                free(temp);
                splay(prev);
            }
            return;
        }
    }
    bool search(int data)
    {
        Splay *temp = root;
        while (temp != 0 && temp->data != data)
        {
            if (data < temp->data)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }
        if (temp != 0)
        {
            splay(temp);
            return 1;
        }
        return 0;
    }
    void printTree()
    {
        cout << "\n\n";
        Map dist, offset;
        vector<Splay *> mp[200];
        queue<Splay *> q;
        int maxdepth = 0;
        q.push(root);
        dist[root->data] = 0;
        mp[0].push_back(root);
        while (!q.empty())
        {
            Splay *curr = q.front();
            q.pop();
            if (curr->left != 0)
            {
                q.push(curr->left);
                dist[curr->left->data] = dist.search(curr->data) + 1;
                mp[dist.search(curr->left->data)].push_back(curr->left);
                maxdepth = max(maxdepth, dist.search(curr->left->data));
            }
            if (curr->right != 0)
            {
                q.push(curr->right);
                dist[curr->right->data] = dist.search(curr->data) + 1;
                mp[dist.search(curr->right->data)].push_back(curr->right);
                maxdepth = max(maxdepth, dist.search(curr->right->data));
            }
        }
        printf("%72d\n\n", root->data);
        offset[root->data] = 70;
        Map hashing;
        hashing[root->data] = 1;
        int k = maxdepth + 1;
        for (int i = 1; i <= maxdepth; i++)
        {
            int cnt = 0;
            for (auto z : mp[i])
            {
                if (hashing.search(z->data))
                    continue;
                while (cnt < offset.search(z->par->data) - k * (maxdepth - i + 1))
                {
                    cout << ' ';
                    cnt++;
                }
                if (z->par->left != 0)
                {
                    offset[z->data] = cnt;
                    cout << (z->data);
                    cnt += digitCount(z->data);
                    hashing[z->data] = 1;
                    while (cnt < offset.search(z->par->data))
                    {
                        cnt++;
                        cout << '_';
                    }
                    cout << '|';
                    cnt++;
                }
                if (z->par->right != 0)
                {
                    if (z->par->left == 0)
                    {
                        while (cnt < offset.search(z->par->data))
                        {
                            cnt++;
                            cout << ' ';
                        }
                        cout << '|';
                        cnt++;
                    }
                    offset[z->par->right->data] = offset.search(z->par->data) - 2 + k * (maxdepth - i + 1);
                    while (cnt < offset.search(z->par->right->data))
                    {
                        cnt++;
                        cout << '_';
                    }
                    cout << z->par->right->data;
                    cnt += digitCount(z->par->right->data);
                    hashing[z->par->right->data] = 1;
                }
            }
            cout << "\n\n";
            k--;
        }
        cout << "\n\n\n";
    }
};

Splay *Splay::root = 0;

int main()
{

    Splay s;
    s.insert(15);
    s.insert(10);
    s.insert(17);
    s.insert(7);
    s.insert(13);
    s.insert(16);
    s.insert(-2);
    s.insert(3322);
    s.insert(50);
    s.insert(-9);
    // cout << s.search(12) << endl;
    s.printTree();
    s.remove(17);
    s.printTree();
    // cout << s.search(16) << endl;
    // cout << s.search(15) << endl;
    // s.dfs();
    return 0;
}