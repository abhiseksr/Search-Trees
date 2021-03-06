/* Binary Search tree implementation in C/C++
Author - Abhishek Kumar */
#include <iostream>
#include <queue>
#include "printer.h"
using namespace std;

class BST
{
public:
    static class BST *root;
    BST *left, *right, *par;
    int data;

    BST *create(int data)
    {
        BST *newnode = (BST *)malloc(sizeof(BST));
        newnode->data = data;
        newnode->left = 0;
        newnode->right = 0;
        newnode->par = 0;
        return newnode;
    }

    void dfs(BST *head = root)
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

    void insert(int data)
    {
        BST *newnode = create(data);
        if (root == 0)
        {
            root = newnode;
            return;
        }
        BST *temp = root, *prev = 0;
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
    }
    BST *inorderPredecessor(BST *head)
    {
        if (head == 0)
            return head;
        while (head->right != 0)
        {
            head = head->right;
        }
        return head;
    }

    BST *inorderSuccessor(BST *head)
    {
        if (head == 0)
            return head;
        while (head->left != 0)
        {
            head = head->left;
        }
        return head;
    }

    void remove(int data, BST *temp = root)
    {
        BST *prev = 0;
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
        BST *l = inorderPredecessor(temp->left);
        BST *r = inorderSuccessor(temp->right);
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
            }
            return;
        }
    }
    bool search(int data)
    {
        BST *temp = root;
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
        printer<BST>(root);
    }
};

BST *BST::root = 0;

int main()
{

    BST s;
    s.insert(15);
    s.insert(17);
    s.insert(11);
    s.insert(7);
    s.insert(53);
    s.insert(4);
    s.insert(14);
    s.insert(13);
    s.insert(12);
    s.insert(8);
    s.insert(60);
    s.insert(19);
    s.insert(16);
    s.insert(65);
    s.insert(55);
    s.insert(9);
    s.insert(10);
    s.remove(55);
    s.remove(14);

    cout << s.search(20) << endl;
    cout << s.search(89) << endl;
    s.dfs();
    cout << endl;
    s.printTree();
    return 0;
}