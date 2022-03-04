/* AVL tree implementation in C/C++
Author - Abhishek Kumar */
#include <iostream>
#include <queue>
#include "map.h"
using namespace std;

int digitCount(int n)
{
    int cnt = 0;
    while (n)
    {
        cnt++;
        n /= 10;
    }
    return cnt;
}

class AVL
{
public:
    static class AVL *root;
    AVL *left, *right, *par;
    int data, depth;

    AVL *create(int data)
    {
        AVL *newnode = (AVL *)malloc(sizeof(AVL));
        newnode->data = data;
        newnode->left = 0;
        newnode->right = 0;
        newnode->par = 0;
        newnode->depth = 1; //depth of a newnode shall be 1 and not zero to \
        differentiate between no child (which return 0) and having child
        return newnode;
    }

    void dfs(AVL *head = root)
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

    void right_rotation(AVL *x)
    {
        AVL *y = x->left;
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

    void left_rotation(AVL *x)
    {
        AVL *y = x->right;
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

    int depthf(AVL *node)
    {
        if (node == 0)
            return 0;
        return node->depth;
    }

    // draw the initial and final graph of each cases(take case where every node has two child)\
    and update the nodes depth before rotation
    void helper(AVL *node)
    {
        if (depthf(node->left) - depthf(node->right) > 1)
        {
            if (depthf(node->left->left) > depthf(node->left->right))
            {
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right) + 1);
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node) + 1);
                right_rotation(node);
            }
            else
            {
                node->left->depth = max(depthf(node->left->left) + 1, depthf(node->left->right->left) + 1);
                node->depth = max(depthf(node->right) + 1, depthf(node->left->right->right) + 1);
                node->left->right->depth = max(depthf(node) + 1, depthf(node->left) + 1);
                left_rotation(node->left);
                right_rotation(node);
            }
        }
        else if (depthf(node->left) - depthf(node->right) < -1)
        {
            if (depthf(node->right->right) > depthf(node->right->left))
            {
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left) + 1);
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node) + 1);
                left_rotation(node);
            }
            else
            {
                node->right->depth = max(depthf(node->right->right) + 1, depthf(node->right->left->right) + 1);
                node->depth = max(depthf(node->left) + 1, depthf(node->right->left->left) + 1);
                node->right->left->depth = max(depthf(node) + 1, depthf(node->right) + 1);
                right_rotation(node->right);
                left_rotation(node);
            }
        }
    }

    void balance(AVL *node)
    {
        while (node != root)
        {
            int d = node->depth;
            node = node->par;
            if (node->depth < d + 1)
            {
                node->depth = d + 1;
            }
            if (node == root && depthf(node->left) - depthf(node->right) > 1)
            {
                if (depthf(node->left->left) > depthf(node->left->right))
                {
                    root = node->left;
                }
                else
                {
                    root = node->left->right;
                }
                helper(node);
                break;
            }
            else if (node== root && depthf(node->left) - depthf(node->right) < -1)
            {
                if (depthf(node->right->right) > depthf(node->right->left))
                {
                    root = node->right;
                }
                else
                {
                    root = node->right->left;
                }
                helper(node);
                break;
            }
            helper(node);
        }
    }

    void insert(int data)
    {
        AVL *newnode = create(data);
        if (root == 0)
        {
            root = newnode;
            return;
        }
        AVL *temp = root, *prev = 0;
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
        balance(newnode);
    }
    AVL *inorderPredecessor(AVL *head)
    {
        if (head == 0)
            return head;
        while (head->right != 0)
        {
            head = head->right;
        }
        return head;
    }

    AVL *inorderSuccessor(AVL *head)
    {
        if (head == 0)
            return head;
        while (head->left != 0)
        {
            head = head->left;
        }
        return head;
    }

    void remove(int data, AVL *temp = root)
    {
        AVL *prev = 0;
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
            return;
        }
        AVL *l = inorderPredecessor(temp->left);
        AVL *r = inorderSuccessor(temp->right);
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
                balance(prev);
            }
            return;
        }
        // while going upward from this node till root - we will keep balancing
        AVL *start;
        if (l != 0)
        {
            if (l == temp->left)
            {
                l->right = temp->right;
                if (l->right != 0)
                {
                    l->right->par = l;
                }
                start = l;
            }
            else
            {
                if (l->left != 0)
                {
                    l->left->par = l->par;
                }
                start = l->par;
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
            }
            balance(start);
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
                start = r;
            }
            else
            {
                if (r->right != 0)
                {
                    r->right->par = r->par;
                }
                start = r->par;
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
            }
            balance(start);
            return;
        }
    }
    bool search(int data)
    {
        AVL *temp = root;
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
            return 1;
        }
        return 0;
    }
    void printTree()
    {
        cout << "\n\n";
        Map dist, offset;
        vector<AVL *> mp[200];
        queue<AVL *> q;
        int maxdepth = 0;
        q.push(root);
        dist[root->data] = 0;
        mp[0].push_back(root);
        while (!q.empty())
        {
            AVL *curr = q.front();
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

AVL *AVL::root = 0;

int main()
{

    AVL s;
    s.insert(14);
    s.insert(17);
    s.insert(11);
    s.insert(7);
    s.insert(53);
    s.insert(4);
    s.insert(13);
    s.insert(12);
    s.printTree();
    s.insert(8);
    s.insert(60);
    s.insert(19);
    s.insert(16);
    s.printTree();
    s.remove(19);
    s.remove(11);

    // cout << s.search(20) << endl;
    // cout << s.search(89) << endl;
    // s.dfs();
    s.printTree();
    return 0;
}